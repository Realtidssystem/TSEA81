/* includes */

#include <simple_os.h>

/* size of stacks */
#define STACK_SIZE 5000

/* stack for print task */ 
stack_item Print_Task_Stack[STACK_SIZE]; 

/* tasks */

/* print_task: print task */
void print_task(void)
{
    /* a counter */ 
    int i = 0; 
    while (1) 
    {
        /* print something */ 
        console_put_string("This is string number "); 
        console_put_hex(i++); 
        console_put_string("\n"); 
        /* wait for a while */
        si_wait_n_ms(2000); 
    }
}

/* main function */ 
int main(void)
{
    /* initialise kernel */ 
    si_kernel_init(); 

    /* create task */
    si_task_create(print_task, &Print_Task_Stack[STACK_SIZE-1], 10); 
   
    /* start the kernel */ 
    si_kernel_start(); 

    /* will never be here! */ 
    return 0; 
}
