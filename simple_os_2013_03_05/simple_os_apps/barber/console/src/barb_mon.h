#ifndef BARB_MON_H
#define BARB_MON_H

#include <simple_os.h>

/* definition of monitor data type for barbershop */

/* number of chairs */
#define N_CHAIRS 5

/* time for the barber to cut one customer's hair */
#define BARB_DURATION 8

typedef struct
{
    /* chairs that are available */
    int free_chair[N_CHAIRS];

    /* time left until finished */
    int time_left[N_CHAIRS];

    /* number of customers waiting at the door */
    int n_waiting;

    /* flag to indicate that the barber is sleeping */ 
    int barber_sleeping; 

    /* semaphore for protection of the buffer */
    si_semaphore mutex; 

    /* event to indicate that something has happened */
    si_condvar change; 

} barber_shop_data_type;

typedef barber_shop_data_type* barber_shop_type;

/* definition of operations on monitor data type for barber shop */

/* init_barber_shop: initialisation of barber_shop */ 
void init_barber_shop(barber_shop_type barber_shop); 

/* delete_barber_shop: deallocates memory for barber_shop */
void delete_barber_shop(barber_shop_type barber_shop); 

/* MONIOR FUNCTION process_all_customers: called by the barber task
   for the purpose of cutting some hair from all the available
   customers */
void process_all_customers(barber_shop_type barber_shop); 

/* MONITOR FUNCTION go_to_barber_shop: called by customer tasks when
   the customer hair is too long */
void go_to_barber_shop(barber_shop_type barber_shop); 

#endif


