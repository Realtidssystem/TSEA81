#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/prctl.h>
#include "lift.h"
#include "si_ui.h"
#include "debug.h"

// Unfortunately the rand() function is not thread-safe. However, the
// rand_r() function is thread-safe, but need a pointer to an int to
// store the current state of the pseudo-random generator.  This
// pointer needs to be unique for every thread that might call
// rand_r() simultaneously. The functions below are wrappers around
// rand_r() which should work in the environment encountered in
// assignment 3.
//

static unsigned int rand_r_state[MAX_N_PERSONS];
// Get a random value between 0 and maximum_value. The passenger_id
// parameter is used to ensure that the rand_r() function is called in
// a thread-safe manner.

static int get_random_value(int passenger_id, int maximum_value)
{
	return rand_r(&rand_r_state[passenger_id]) % (maximum_value + 1);
}

static lift_type Lift;

// Initialize the random seeds used by the get_random_value() function
// above.
static void init_random(void)
{
	int i;
	prctl(PR_SET_NAME,"Lift Thread",0,0,0); // Sets a name shown in debuggers
	for(i=0; i < MAX_N_PERSONS; i++){
		// Use this statement if the same random number sequence
		// shall be used for every execution of the program.
		rand_r_state[i] = i;

		// Use this statement if the random number sequence
		// shall differ between different runs of the
		// program. (As the current time (as measured in
		// seconds) is used as a seed.)
		rand_r_state[i] = i+time(NULL);
	}
}



static void *lift_thread(void *unused)
{
	while(1){
		// Move lift one floor
		int next_floor;
		int change_direction = 0;
		if(Lift->up){
			next_floor = Lift->floor -1;
		}
		else{
			next_floor = Lift->floor +1;
		}
		if((Lift->floor == 0) || (Lift->floor == N_FLOORS-1))
		{
				change_direction = 1;
		}
		lift_move(Lift, next_floor, change_direction);
		lift_has_arrived(Lift);

	}
	return NULL;
}

static void *passenger_thread(void *idptr)
{
	// Code that reads the passenger ID from the idptr pointer
	// (due to the way pthread_create works we first need to cast
	// the void pointer to an int pointer).

	int *tmp = (int *) idptr;
	int id = *tmp;
	static person_data_type person;
	person->id = id;
  get_random_value(id,N_FLOORS)= random_origin;
	person->to_floor = random_origin;
	random_to = get_random_value(id,N_FLOORS);
	person->to_floor = random_to;
	lift->persons_to_enter[random_origin][id].id = id;

        // Sets a unique name shown in debuggers
        char buf[100];
        sprintf(buf, "Passenger #%d", id);
	prctl(PR_SET_NAME,buf,0,0,0);

	while(1){
		// * Select random floors
		// * Travel between these floors
		// * Wait a little while
		int change_direction = 0;
		int random_floor = get_random_value(0,N_FLOORS);

		lift_travel(Lift, id, Lift->floor, random_to);
		usleep(50000);

	}
	return NULL;
}

static void *user_thread(void *unused)
{
	int current_passenger_id = 0;
	char message[SI_UI_MAX_MESSAGE_SIZE];

	si_ui_set_size(670, 700);
	prctl(PR_SET_NAME,"User Thread",0,0,0); // Sets the name shown in debuggers for this thread

	while(1){
		// Read a message from the GUI
		si_ui_receive(message);
		if(!strcmp(message, "new")){
			// create a new passenger if possible, else
			// use si_ui_show_error() to show an error
			// message if too many passengers have been
			// created. Make sure that each passenger gets
			// a unique ID between 0 and MAX_N_PERSONS-1.
			passenger_handle();


		}else if(!strcmp(message, "exit")){
			lift_delete(Lift);
			exit(0);
		}
	}
	return NULL;
}

static void passenger_handle()
{
	pthread_t passenger_thread_handle;
	int i = 1;
	if(i < MAX_N_PERSONS +1){
		pthread_create(&passenger_thread_handle, NULL, passenger_thread,(void*)i)
		i++;
	}
	else {
		si_ui_show_error();
	}
	pthread_detach(passenger_thread, NULL);
}
int main(int argc, char **argv)
{
	si_ui_init();
	init_random();
	Lift = lift_create();
	pthread_t user_thread_handle;
	pthread_t lift_thread_handle;

	pthread_create(&user_thread_handle, NULL, user_thread,0);
	pthread_create(&lift_thread_handle, NULL, lift_thread,0);

	pthread_join(user_thread_handle, NULL);
	pthread_join(lift_thread_handle, NULL);

        // Create tasks as appropriate here


	return 0;
}
