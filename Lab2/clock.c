
#include "clock.h"
#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "si_ui.h"
/* set_time: set time to hours, minutes and seconds */

/* init_clock: initialises the clock variables */



/* the actual clock */
static clock_data_type Clock;


void init_clock(void)
{
    /* set starting time */
    Clock.time.hours = 0;
    Clock.time.minutes = 0;
    Clock.time.seconds = 0;

    Clock.alarm_time.hours = 0;
    Clock.alarm_time.minutes = 0;
    Clock.alarm_time.seconds = 0;

    /* alarm is not enabled */
    Clock.alarm_enabled = 0;

    /* initialise semaphores */
    sem_init(&Clock.start_alarm, 0, 0);

    pthread_mutex_init(&Clock.mutex, NULL);
}


void alarm_wait()
{

  sem_wait(&Clock.start_alarm);

}

int checkifenable()
{
  int checkinenable = 0;
  pthread_mutex_lock(&Clock.mutex);
  if(Clock.alarm_enabled == 1)
  {
    checkinenable = 1;
  }
  else
  {
    checkinenable = 0;
  }
  pthread_mutex_unlock(&Clock.mutex);
  return checkinenable;
}

void set_alarm(int hours, int minutes, int seconds)
{
    /* reserve clock variables */
    pthread_mutex_lock(&Clock.mutex);
    /* assign values */
    Clock.alarm_time.hours = hours;
    Clock.alarm_time.minutes = minutes;
    Clock.alarm_time.seconds = seconds;
    Clock.alarm_enabled = 1;
    display_alarm_time(hours, minutes, seconds);
    /* release clock variables */
    pthread_mutex_unlock(&Clock.mutex);
}

void set_time(int hours, int minutes, int seconds)
{
    /* reserve clock variables */
    pthread_mutex_lock(&Clock.mutex);

    /* assign values */
    Clock.time.hours = hours;
    Clock.time.minutes = minutes;
    Clock.time.seconds = seconds;

    /* release clock variables */
    pthread_mutex_unlock(&Clock.mutex);
}
void increment_time(void)
{
    /* reserve clock variables */
    pthread_mutex_lock(&Clock.mutex);

    /* increment time */
    Clock.time.seconds++;
    if (Clock.time.seconds > 59)
    {
        Clock.time.seconds = 0;
        Clock.time.minutes++;
        if (Clock.time.minutes > 59)
        {
            Clock.time.minutes = 0;
            Clock.time.hours++;
            if (Clock.time.hours > 11)
            {
                Clock.time.hours = 0;
            }
        }
    }

    /* release clock variables */
    pthread_mutex_unlock(&Clock.mutex);
}

void reset_alarm()
{
  pthread_mutex_lock(&Clock.mutex);
  Clock.alarm_enabled = 0;
//  printf("alarm diabled\n" );
  erase_alarm_time();
  erase_alarm_text();
  pthread_mutex_unlock(&Clock.mutex);
}

int compare()
{
    int compare = 0;
    if ((Clock.alarm_time.hours == Clock.time.hours) &&
      (Clock.alarm_time.minutes == Clock.time.minutes) &&
      (Clock.alarm_time.seconds == Clock.time.seconds) &&
      (Clock.alarm_enabled == 1))
      {
        //display_alarm_text();
        compare = 1;
        sem_post(&Clock.start_alarm);
      }
    else
    {
      compare = 0;
    }
    return compare;
}


/* get_time: read time from common clock variables */
void get_time(int *hours, int *minutes, int *seconds)
{
    /* reserve clock variables */
    pthread_mutex_lock(&Clock.mutex);

    /* read values */
    *hours = Clock.time.hours;
    *minutes = Clock.time.minutes;
    *seconds = Clock.time.seconds;
    display_time(*hours, *minutes, *seconds);
    /* release clock variables */
    pthread_mutex_unlock(&Clock.mutex);
}
/*void get_alarm_time(int *hours, int *minutes, int *seconds)
{

    pthread_mutex_lock(&Clock.mutex);


    *hours = Clock.alarm_time.hours;
    *minutes = Clock.alarm_time.minutes;
    *seconds = Clock.alarm_time.seconds;

    display_alarm_time(*hours, *minutes, *seconds);


    pthread_mutex_unlock(&Clock.mutex);
}*/
