/* includes */

#include <simple_os.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* size of stacks */
#define STACK_SIZE 5000

/* stack for print task */ 
stack_item Print_Task_Stack[STACK_SIZE]; 

/* stack for read task */ 
stack_item Read_Task_Stack[STACK_SIZE]; 

/* coordinates */ 
int Print_X = 110; 
int Print_Y = 100; 

/* semaphore to protect coordinates */ 
si_semaphore Mutex; 

/* tasks */

void test_draw_string(char Message_String[], char string[], int x_coord, int y_coord)
{
    si_string_copy(Message_String, "draw_string:%x:%x:%s"); 
    si_insert_int_as_hex(Message_String, x_coord); 
    si_insert_int_as_hex(Message_String, y_coord); 
    si_insert_string(Message_String, string); 

    console_put_string(Message_String); 
    console_put_string("\n"); 
}

/* print_task: print task */
void print_task(void)
{
    /* a counter */ 
    int i = 0; 

    /* coordinates */ 
    int x; 
    int y; 

    /* message to GUI */ 
    char message[SI_UI_MAX_MESSAGE_SIZE]; 

    char svenne[SI_UI_MAX_MESSAGE_SIZE]; 

    while (1) 
    {
        /* get coordinates */ 
        si_sem_wait(&Mutex); 
        x = Print_X; 
        y = Print_Y; 
        si_sem_signal(&Mutex); 

        /* store data in message */ 
        // si_string_copy(message, "before %s and %x after\n"); 
        // si_insert_string(message, "sven"); 
        // si_insert_int_as_hex(message, 1234); 

        si_string_copy(message, "This is the NICE String number %x"); 
        si_insert_int_as_hex(message, i++); 
        // console_put_string(message); 
        // console_put_string("\n"); 

        // test_draw_string(svenne, message, x, y); 

        /* print something */ 
        si_ui_draw_begin(); 
        si_ui_draw_string(message, x, y); 
        si_ui_draw_end(); 

        /* wait for a while */
        si_wait_n_ms(2000); 
    }
}

/* change_coordinates : modifies Print_X and Print_Y, using Mutex 
   for mutual exclusion */ 
void change_coordinates(int delta_x, int delta_y)
{
    si_sem_wait(&Mutex); 
    Print_X += delta_x; 
    Print_Y += delta_y; 
    si_sem_signal(&Mutex); 
}

void read_task(void)
{
    /* message from GUI */ 
    char message[SI_UI_MAX_MESSAGE_SIZE]; 

    /* change in coordinates */ 
    int delta = 40; 

    /* set size of GUI window */ 
    si_ui_set_size(400, 400); 

    while (1)
    {
        /* receive message from GUI */
        si_ui_receive(message); 

        // console_put_string(message); 

        /* decide on what to do */ 
        if (si_string_compare(message, "up") == 0)
        {
            change_coordinates(0, -delta); 
        }
        else if (si_string_compare(message, "down") == 0)
        {
            change_coordinates(0, delta); 
        }
        else if (si_string_compare(message, "left") == 0)
        {
            change_coordinates(-delta, 0); 
        }
        else if (si_string_compare(message, "right") == 0)
        {
            change_coordinates(delta, 0); 
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
            si_ui_show_error("Illegal command, use \"left\",\"right\",\"up\" or \"down\""); 
        }
    }
}

/* main function */ 
int main(void)
{
    /* initialise kernel */ 
    si_kernel_init(); 

    /* initialise semaphore */ 
    si_sem_init(&Mutex, 1);

    /* initialise GUI communication */ 
    si_ui_init(); 

    /* create tasks */

    si_task_create(print_task, &Print_Task_Stack[STACK_SIZE-1], 15); 
   
    si_task_create(read_task, &Read_Task_Stack[STACK_SIZE-1], 10); 
   
    /* start the kernel */ 
    si_kernel_start(); 

    /* will never be here! */ 
    return 0; 
}
