#include "barb_mon.h"
#include "barb_draw.h"

#include <simple_os.h>

#ifndef TARGET

#include <stdio.h>
#include <stdlib.h>

#endif

void barber_panic(char message[])
{
#ifdef TARGET
    print_string(14, 10, message); 
#else
    printf("%s\n", message); 
    exit(1); 
#endif
}

/* definition of operations on monitor data type for barber shop */

/* init_barber_shop: initialisation of barber_shop */ 
void init_barber_shop(barber_shop_type barber_shop)
{
    /* loop counter */
    int i;

    /* initialise all chairs as free */
    for (i = 0; i < N_CHAIRS; i++)
    {
        barber_shop->free_chair[i] = 1;
        barber_shop->time_left[i] = 0;
    }

    /* no customers are waiting */
    barber_shop->n_waiting = 0;

    /* the barber is not sleeping */ 
    barber_shop->barber_sleeping = 0; 

    /* initialise semaphore for protection */
    si_sem_init(&barber_shop->mutex, 1); 

    /* initialise event */
    si_cv_init(&barber_shop->change, &barber_shop->mutex);
}

/* no_free_chairs: returns non-zero if all chairs are taken */
static int no_free_chairs(barber_shop_type barber_shop)
{
    int i;
    int no_free = 1;

    for (i = 0; i < N_CHAIRS; i++)
    {
        no_free = no_free && !barber_shop->free_chair[i];
    }
    return no_free;
}

/* all_chairs_free: returns non-zero if all chairs are free */
static int all_chairs_free(barber_shop_type barber_shop)
{
    int i;
    int all_free = 1;

    for (i = 0; i < N_CHAIRS; i++)
    {
        all_free = all_free && barber_shop->free_chair[i];
    }
    return all_free;
}



/* take_a_chair: lets the customer have a chair, and returns the chair
   number. This function must NOT be called when there are no free chairs */
static int take_a_chair(barber_shop_type barber_shop)
{
    /* loop counter */
    int i = 0;

    /* flag to indicate that a chair is found */
    int chair_found = 0;

    /* the chair number */
    int chair_number;

    /* look for a free chair, and when found, initialise barbing time to
       BARB_DURATION */
    while (i < N_CHAIRS && !chair_found)
    {
        if (barber_shop->free_chair[i])
        {
            barber_shop->free_chair[i] = 0;
            barber_shop->time_left[i] = BARB_DURATION;
            chair_found = 1;
            chair_number = i;
        }
        i++;
    }

    if (!chair_found)
    {
        barber_panic("take_a_chair: NO FREE CHAIRS!");
    }

    return chair_number;
}

/* leave_the_chair: lets the customer leave the chair chair_number.
   This function must NOT be called if chair_number represents a
   free chair. */
static void leave_the_chair(barber_shop_type barber_shop, int chair_number)
{
    if (barber_shop->free_chair[chair_number])
    {
        barber_panic("leave_the_chair: CHAIR IS FREE");
    }

    barber_shop->free_chair[chair_number] = 1;
}

/* barber_finished: returns non-zero if the barber is finished with
   the customer sitting in chair chair_number. This function must NOT
   be called if chair chair_number represents a free chair */
static int barber_finished(barber_shop_type barber_shop, int chair_number)
{
    if (barber_shop->free_chair[chair_number])
    {
        barber_panic("barber_finished: WRONG CHAIR NUMBER");
    }

    return barber_shop->time_left[chair_number] == 0;
}


/* MONITOR FUNCTION process_all_customers: called by the barber task
   for the purpose of cutting some hair from all the available
   customers */
void process_all_customers(barber_shop_type barber_shop)
{
    /* loop counter */
    int i;

    /* reserve barber_shop */
    si_sem_wait(&barber_shop->mutex);

    /* go to sleep if all chairs are free */ 
    while (all_chairs_free(barber_shop))
    {
        barber_shop->barber_sleeping = 1; 
        draw_barber_shop(barber_shop);
        si_cv_wait(&barber_shop->change); 
        barber_shop->barber_sleeping = 0; 
    }
    
    for (i = 0; i < N_CHAIRS; i++)
    {
        if (!barber_shop->free_chair[i] && barber_shop->time_left[i] > 0)
        {
            barber_shop->time_left[i]--;
        }
    }

    /* draw barber_shop, since a change has occurred */
    draw_barber_shop(barber_shop);

    /* indicate to other tasks that a change has occurred */
    si_cv_broadcast(&barber_shop->change);

    /* release barber_shop */
    si_sem_signal(&barber_shop->mutex);
}

/* MONITOR FUNCTION go_to_barber_shop: called by customer tasks when
   the customer hair is too long */
void go_to_barber_shop(barber_shop_type barber_shop)
{
    /* the chair number */
    int chair_nr;

    /* reserve barber_shop */
    si_sem_wait(&barber_shop->mutex);

    /* increase number of waiting customers */
    barber_shop->n_waiting++;

    /* wake up barber */ 
    si_cv_broadcast(&barber_shop->change); 

    if (no_free_chairs(barber_shop))
    {
        draw_barber_shop(barber_shop);
    }
        
    /* wait for a free chair */
    while (no_free_chairs(barber_shop))
    {
        si_cv_wait(&barber_shop->change);
    }

    /* decrease number of waiting customers */
    barber_shop->n_waiting--;

    /* take a chair */
    chair_nr = take_a_chair(barber_shop);

    /* perform some drawing */
    draw_barber_shop(barber_shop);

    /* wait for barber to finish */
    while (!barber_finished(barber_shop, chair_nr))
    {
        si_cv_wait(&barber_shop->change);
    }

    /* leave the chair */
    leave_the_chair(barber_shop, chair_nr);

    /* and some drawing */
    draw_barber_shop(barber_shop);

    /* release barber_shop */
    si_sem_signal(&barber_shop->mutex);
}

