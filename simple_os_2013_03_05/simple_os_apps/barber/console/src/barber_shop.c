/* includes */

#include <simple_os.h>

#include <stdio.h>
#include <string.h>

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

/* a semaphore to prevent customer creation task 
   from termination */ 
si_semaphore Create_Customers_Sem; 

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

    const int customer_create_delay_sec = 2;

    int i;

    customer_prio = CUSTOMER_START_PRIO;

    for (i = 0; i < MAX_N_CUSTOMERS; i++)
    {
        si_task_create(customer_task, &Customer_Stack[i][STACK_SIZE-1], customer_prio++); 

        si_wait_n_ms(customer_create_delay_sec * 1000 + 150); 
    }
    si_sem_wait(&Create_Customers_Sem); 
}

/* main function */ 
int main(void)
{
    /* initialise kernel */ 
    si_kernel_init(); 

    /* initialise the barber shop */
    init_barber_shop(&Barber_Shop);

    /* initialise customer creation semaphore */ 
    si_sem_init(&Create_Customers_Sem, 0); 

    /* create tasks */
    si_task_create(barber_task, &Barber_Stack[STACK_SIZE-1], BARBER_PRIO); 
   
    si_task_create(create_customers_task, &Create_Customers_Stack[STACK_SIZE-1], CREATE_CUSTOMERS_PRIO); 

    /* start the kernel */ 
    si_kernel_start(); 

    /* will never be here! */ 
    return 0; 
}

