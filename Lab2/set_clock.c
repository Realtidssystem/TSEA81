/* A clock program

Two tasks are used, clock_task for updating a clock, and
set_task for setting the clock

*/

/* standard library includes */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "si_ui.h"
#include "display.h"
#include "clock.h"

/* increment_time: increments the current time with
   one second */


/* make_display_message: create string for printout, given a time expressed
   in hours, minutes and seconds */
void make_display_message(char display_message[], int hours, int minutes, int seconds)
{
    display_message[0] = hours / 10 + '0';
    display_message[1] = hours % 10 + '0';
    display_message[2] = ':';
    display_message[3] = minutes / 10 + '0';
    display_message[4] = minutes % 10 + '0';
    display_message[5] = ':';
    display_message[6] = seconds / 10 + '0';
    display_message[7] = seconds % 10 + '0';
    display_message[8] = '\0';
}

/* time_from_set_message: extract time from set message from user interface */
void time_from_set_message(char message[], int *hours, int *minutes, int *seconds)
{
    sscanf(message,"set:%d:%d:%d",hours, minutes, seconds);
    sscanf(message,"alarm:%d:%d:%d",hours, minutes, seconds);
}


/* time_ok: returns nonzero if hours, minutes and seconds represents a valid time */
int time_ok(int hours, int minutes, int seconds)
{
    return hours >= 0 && hours <= 11 && minutes >= 0 && minutes <= 59 &&
        seconds >= 0 && seconds <= 59;
}

/* display_time: displays hours, minutes and seconds by
   sending them to the user interface */
void display_time1(int hours, int minutes, int seconds)
{
    char display_message[20];

    char draw_message[100];

    /* convert hours, minutes and seconds to display format */
    make_display_message(display_message, hours, minutes, seconds);

    sprintf(draw_message, "Time: %s", display_message);

    /* write to user interface */
    si_ui_draw_begin();
    si_ui_draw_string("send \"set:hh:mm:ss\" to set time", 90, 20);
    si_ui_draw_string(draw_message, 145, 55);
    si_ui_draw_end();
}

/* tasks */

/* clock_task: clock task */
void *clock_thread(void *unused)
{
    /* local copies of the current time */
    int hours, minutes, seconds;


    /* infinite loop */
    while (1)
    {

        /* read and display current time */
        get_time(&hours, &minutes, &seconds);
        display_time(hours, minutes, seconds);

        compare();
        /* increment time */
        increment_time();

        /* wait one second */
        usleep(500000);
    }
}
void *alarm_thread(void *unused)
{
  while (1)
  {
    alarm_wait();

    while (checkifenable())
    {  /* wait one second */
      //  printf("alaram enabled\n");
        display_alarm_text();
        usleep(1500000);
    }
  }
}
/* set_task: reads messages from the user interface, and
   sets the clock, or exits the program */
void * set_thread(void *unused)
{
    /* message array */
    char message[SI_UI_MAX_MESSAGE_SIZE];

    /* time read from user interface */
    int hours, minutes, seconds;

    /* set GUI size */
    si_ui_set_size(400, 200);

    while(1)
    {
        /* read a message */
        si_ui_receive(message);
        /* check if it is a set message */
        if (strncmp(message, "set", 3) == 0)
        {
            time_from_set_message(message, &hours, &minutes, &seconds);
            if (time_ok(hours, minutes, seconds))
            {
                set_time(hours, minutes, seconds);
            }
            else
            {
                si_ui_show_error("Illegal value for hours, minutes or seconds");
            }
        }
        else if (strncmp(message, "alarm", 3) == 0)
        {
            time_from_set_message(message, &hours, &minutes, &seconds);
            if (time_ok(hours, minutes, seconds))
            {
                set_alarm(hours, minutes, seconds);
            }
            else
            {
                si_ui_show_error("Illegal value for hours, minutes or seconds");
            }
        }
        else if (strcmp(message, "reset") == 0)
        {
            reset_alarm();
        }
        /* check if it is an exit message */
        else if (strcmp(message, "exit") == 0)
        {
            exit(0);
        }
        /* not a legal message */
        else
        {
            si_ui_show_error("unexpected message type");
        }
    }
}

/* main */
int main(void)
{

    init_clock();
    display_init();

    /* initialise UI channel */
    si_ui_init();

    /* initialise variables */

    /* create tasks */
    pthread_t clock_thread_handle;
    pthread_t set_thread_handle;
    pthread_t alarm_thread_handle;


    pthread_create(&clock_thread_handle, NULL, clock_thread, 0);
    pthread_create(&set_thread_handle, NULL, set_thread, 0);
    pthread_create(&alarm_thread_handle, NULL, alarm_thread, 0);

    pthread_join(alarm_thread_handle, NULL);
    pthread_join(clock_thread_handle, NULL);
    pthread_join(set_thread_handle, NULL);
    /* will never be here! */
    return 0;
}
