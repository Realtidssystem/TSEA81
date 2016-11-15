#ifndef CLOCK_H
#define CLOCK_H

#include <pthread.h>
#include <semaphore.h>

typedef struct
{
int hours;
int minutes;
int seconds;
} time_data_type;

typedef struct
{
  /* the current time */
  time_data_type time;

  /* alarm time */
  time_data_type alarm_time;

  /* alarm enabled flag */
  int alarm_enabled;

  /* semaphore for mutual exclusion */
  pthread_mutex_t mutex;

  /* semaphore for alarm activation */
  sem_t start_alarm;

} clock_data_type;

/* clock_init: initialise clock */
void init_clock(void);

/* clock_set_time: set current time to hours, minutes and seconds */
void set_time(int hours, int minutes, int seconds);
void set_alarm(int hours, int minutes, int seconds);
void increment_time();
int compare();
void get_time(int *hours, int *minutes, int *seconds);
void get_alarm_time(int *hours, int *minutes, int *seconds);
void alarm_wait();
int checkifenable();
void reset_alarm();

int main(void);

#endif
