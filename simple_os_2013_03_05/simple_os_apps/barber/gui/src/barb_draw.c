#include "barb_draw.h"

#include "si_ui.h"

// #include <stdio.h>

/* draw_barber_shop: makes a graphical printout of the barbershop,
   its customers in the chairs, and all waiting customers */

static char message[SI_UI_MAX_MESSAGE_SIZE]; 

void draw_barber_shop(barber_shop_type barber_shop)
{

    int chair_x = 50; 
    int chair_y = 110; 
    int chair_y_text = 90; 
    int chair_delta = 125; 
        
    int wait_x = 50; 
    int wait_y = 20; 

    int barber_x = 50; 
    int barber_y = 40; 

    int info_x = 250; 
    int info_y = 30; 
        
    int j; 

    si_ui_draw_begin(); 

    si_ui_draw_string(
        "Sleeping Barber Simulation (send \"new\" to create new customers)",
        info_x, info_y); 

    for (j = 0; j < N_CHAIRS; j++)
    {
        if (barber_shop->free_chair[j])
        {
            si_ui_draw_image("chair", chair_x + j*chair_delta, chair_y); 
        }
        else
        {
            if (barber_shop->time_left[j] > 2)
            {
                if (barber_shop->time_left[j] % 2 == 0)
                {
                    si_ui_draw_string("\"cut cut\"", chair_x + j*chair_delta, chair_y_text); 
                }
                else
                {
                    si_ui_draw_string("\"talk talk\"", chair_x + j*chair_delta, chair_y_text); 
                }
            }
            else if (barber_shop->time_left[j] > 1)
            {
                si_ui_draw_string("Ok?", chair_x + j*chair_delta, chair_y_text); 
            }
            else
            {
                si_ui_draw_string("Bye!", chair_x + j*chair_delta, chair_y_text); 
            }

            if (barber_shop->time_left[j] > 2)
            {
                si_ui_draw_image("hair", chair_x + j*chair_delta, chair_y); 
            }
            else
            {
                si_ui_draw_image("nohair", chair_x + j*chair_delta, chair_y); 
            }
        }
    }

    if (barber_shop->n_waiting > 0)
    {
        if (barber_shop->n_waiting == 1)
        {
            si_string_copy(message, "%x customer waiting"); 
            si_insert_int_as_hex(message, barber_shop->n_waiting); 
            // sprintf(message, "%d customer waiting", barber_shop->n_waiting); 
            si_ui_draw_string(message,wait_x, wait_y); 
        }
        else
        {
            si_string_copy(message, "%x customer waiting"); 
            si_insert_int_as_hex(message, barber_shop->n_waiting); 
            // sprintf(message, "%d customers waiting", barber_shop->n_waiting); 
            si_ui_draw_string(message,wait_x, wait_y); 
        }
    }
    else
    {
        si_ui_draw_string("No customers waiting", wait_x, wait_y); 
    }


    /* if (barber_shop->barber_sleeping) */
    /* { */
    /*     printf("   ");  */
    /* } */
    /* printf("A barber shop with ");  */
    /* printf("%d waiting customers and a ", barber_shop->n_waiting);  */
    if (barber_shop->barber_sleeping)
    {
        // printf("sleeping barber\n"); 
        si_ui_draw_string("The barber is asleep!", barber_x, barber_y); 
    }
    else
    {
        // printf("barber which is awake\n"); 
        si_ui_draw_string("The barber is awake!", barber_x, barber_y); 
    }

    si_ui_draw_end(); 
}

