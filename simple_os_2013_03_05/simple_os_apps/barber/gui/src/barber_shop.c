/* includes */

#include <simple_os.h>

#include "si_ui.h"

#ifndef BUILD_ARM_BB

#include <stdlib.h>

#endif

/* size of stacks */
#define STACK_SIZE 5000

/* maximum number of customers */
#define MAX_N_CUSTOMERS 10

/* stack for customer creation task */ 
stack_item Create_Customers_Stack[STACK_SIZE]; 

/* stack for barber task */
stack_item Barber_Stack[STACK_SIZE];

/* stacks for customer tasks */
stack_item Customer_Stack[MAX_N_CUSTOMERS][STACK_SIZE];

/* include barber shop type */
#include "barb_mon.h"

#define CREATE_CUSTOMERS_PRIO 10
#define BARBER_PRIO 15
#define CUSTOMER_START_PRIO 20

/* variables */

/* the barbershop */
barber_shop_data_type Barber_Shop;

/* tasks */

/* customer_task: customer task */
void customer_task(void)
{
    while (1) 
    {
        /* go to the barber shop */
        go_to_barber_shop(&Barber_Shop);
        /* wait until hair has grown */
        si_wait_n_ms(60000); 
    }
}

/* barber_task: barber task */
void barber_task(void)
{
    while (1) 
    {
        /* cut some hair from all customers */
        process_all_customers(&Barber_Shop);
        /* take a short break */
        si_wait_n_ms(3000); 
    }
}


void create_customers_task(void)
{
    int customer_prio;

    int n_customers = 0; 

    char message[SI_UI_MAX_MESSAGE_SIZE]; 
    char message_to_send[SI_UI_MAX_MESSAGE_SIZE]; 
        
    customer_prio = CUSTOMER_START_PRIO;

    /* set size of GUI window */ 
    si_ui_set_size(750, 500); 

    while (1)
    {
        si_ui_receive(message); 
        if (si_string_compare(message, "new") == 0)
        {
            if (n_customers < MAX_N_CUSTOMERS)
            { 
                si_task_create(customer_task, &Customer_Stack[n_customers][STACK_SIZE-1], customer_prio++); 
                n_customers++; 
            }
            else
            {
                si_ui_show_error("Maximum number of customers created!"); 
            }

        }
        else if (si_string_compare(message, "exit") == 0)
        {
            si_ui_close(); 
#ifndef BUILD_ARM_BB
            exit(0); 
#endif
        }
        else
        {
            si_string_copy(message_to_send, "Illegal command \"%s\" sent, use \"new\""); 
            si_insert_string(message_to_send, message); 
            // sprintf(message_to_send, "Illegal command \"%s\" sent, use \"new\"", message); 
            si_ui_show_error(message_to_send);
        }
    }
}

/* main function */ 
int main(void)
{
    /* initialise kernel */ 
    si_kernel_init(); 

    /* initialise the barber shop */
    init_barber_shop(&Barber_Shop);

    /* initialise GUI communication */ 
    si_ui_init(); 

    /* create tasks */

    si_task_create(barber_task, &Barber_Stack[STACK_SIZE-1], BARBER_PRIO); 
   
    si_task_create(create_customers_task, &Create_Customers_Stack[STACK_SIZE-1], CREATE_CUSTOMERS_PRIO); 

    /* start the kernel */ 
    si_kernel_start(); 

    /* will never be here! */ 
    return 0; 
}

