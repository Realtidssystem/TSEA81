#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include "lift.h"
#include "si_ui.h"
#include "messages.h"

#include "draw.h"
#include <sys/time.h>
struct timeval starttime;
struct timeval endtime;
long long int timediff;
#define QUEUE_UI 0
#define QUEUE_LIFT 1
#define QUEUE_FIRSTPERSON 10

// These variables keeps track of the process IDs of all processes
// involved in the application so that they can be killed when the
// exit command is received.
static pid_t lift_pid;
static pid_t uidraw_pid;
static pid_t liftmove_pid;
static pid_t person_pid[MAX_N_PERSONS];

typedef enum {LIFT_TRAVEL, // A travel message is sent to the list process when a person would
	                   // like to make a lift travel
	      LIFT_TRAVEL_DONE, // A travel done message is sent to a person process when a
	                        // lift travel is finished
	      LIFT_MOVE         // A move message is sent to the lift task when the lift shall move
	                        // to the next floor
} lift_msg_type;

struct lift_msg{
	lift_msg_type type;  // Type of message
	int person_id;       // Specifies the person
	int from_floor;      // Specify source and destion for the LIFT_TRAVEL message.
	int to_floor;
};



// Since we use processes now and not
static int get_random_value(int person_id, int maximum_value)
{
	return rand() % (maximum_value + 1);
}


// Initialize the random seeds used by the get_random_value() function
// above.
static void init_random(void)
{
	srand(getpid()); // The pid should be a good enough initialization for
                         // this case at least.
}


static void liftmove_process(void)
{
	struct lift_msg m;
	m.type = LIFT_MOVE;

		while(1){
			//    Sleep 2 seconds

	        //sleep(2);
	        //    Send a message to the lift process to move the lift.
	        message_send((char *) &m, sizeof(m), QUEUE_LIFT, 0);
		}
}


static void lift_process(void)
{
	lift_type Lift;
	Lift = lift_create();
	int change_direction, next_floor;

	char msgbuf[4096];
	while(1){
		int i;
		struct lift_msg reply;
		struct lift_msg *m;
		//message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0); // Draw the lift
		int len = message_receive(msgbuf, 4096, QUEUE_LIFT); // Wait for a message
		if(len < sizeof(struct lift_msg)){
			fprintf(stderr, "Message too short\n");
			continue;
		}

		m = (struct lift_msg *) msgbuf;
		switch(m->type){
		case LIFT_MOVE:
			//    Check if passengers want to leave elevator
			//        Remove the passenger from the elevator
			//        Send a LIFT_TRAVEL_DONE for each passenger that leaves
			//        the elevator

				reply.type = LIFT_TRAVEL_DONE;
				for(i = 0; i < MAX_N_PASSENGERS; i++){

	        			if (Lift->passengers_in_lift[i].to_floor == Lift->floor)
	        			{
									int id = Lift->passengers_in_lift[i].id;
									Lift->passengers_in_lift[i].id = NO_ID;
	    						Lift->passengers_in_lift[i].to_floor = NO_FLOOR;
									message_send((char *) &reply, sizeof(reply), QUEUE_FIRSTPERSON + id ,0);

	    						}
	    			}

				//    Check if passengers want to enter elevator
				//    Remove the passenger from the floor and into the elevator
						for(i = 0; i < MAX_N_PERSONS; i++){

							person_data_type person = Lift->persons_to_enter[Lift->floor][i];
	        			if (person.id != NO_ID && (n_passengers_in_lift(Lift) < MAX_N_PASSENGERS))
	        			{
									leave_floor(Lift, person.id, Lift->floor);
									put_passenger_in_lift(Lift, person.id, person.to_floor);
	        			}
	    			}
				//    Move the lift
				lift_next_floor(Lift, &next_floor, &change_direction);
				lift_move(Lift, next_floor, change_direction);
				//message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0);
				change_direction = 0;

				break;
		case LIFT_TRAVEL:

			//    Update the Lift structure so that the person with the given ID is now present on the floor
				for(i=0; i<MAX_N_PERSONS;i++){
					if(Lift->persons_to_enter[m->from_floor][i].id == NO_ID){
						Lift->persons_to_enter[m->from_floor][i].id= m->person_id;
						Lift->persons_to_enter[m->from_floor][i].to_floor= m->to_floor;
						break;
					}
				}
				//message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0);

				break;
		default:
			fprintf(stderr, "Error: unkown message type sent \n");
		}
	}
	return;
}
static void person_process(int id)
{
	init_random();
	char buf[4096];
	struct lift_msg m;
	long long int max_timediff = 0;
	while(1){
		gettimeofday(&starttime, NULL);
		//    Generate a to and from floor
		int to_floor = get_random_value(id,N_FLOORS-1);
		int from_floor = get_random_value(id, N_FLOORS-1);
		m.person_id = id;
		m.to_floor = to_floor;
		m.from_floor = from_floor;
		m.type = LIFT_TRAVEL;
		while(m.to_floor == m.from_floor){
			m.to_floor = get_random_value(id , N_FLOORS -1);
		}
		//    Send a LIFT_TRAVEL message to the lift process
		message_send((char *) &m, sizeof(m), QUEUE_LIFT,0);
		//    Wait for a LIFT_TRAVEL_DONE message
		int len = message_receive(buf, 4096, QUEUE_FIRSTPERSON + id);

		while(len < sizeof(struct lift_msg)){
			fprintf(stderr, "Message too short\n");
			continue;
		}

		gettimeofday(&endtime, NULL);
		timediff = (endtime.tv_sec*1000000ULL + endtime.tv_usec) -
		           (starttime.tv_sec*1000000ULL + starttime.tv_usec);

		if(timediff > max_timediff){
			max_timediff = timediff;
			printf("  Passenger id: %d\n", id);
			printf("  time difference: %lld\n", max_timediff);
		}
		//    Wait a little while
		//sleep(5);
	}
}

// This is the final process called by main()
// It is responsible for:
//   * Receiving and executing commands from the java GUI
//   * Killing off all processes when exiting the application
void uicommand_process(void)
{
	int i;
    int person_counter = 0;
	char message[SI_UI_MAX_MESSAGE_SIZE];

	while(1){
		// Read a message from the GUI
		si_ui_receive(message);
        // * Check that we don't create too many persons
		if(!strcmp(message, "new")){
            if(person_counter > MAX_N_PERSONS - 1) {
                si_ui_show_error("No more passengers allowed");
            }
            // * fork and create a new person process (and
			//   record the new pid in person_pid[])
            else {
                person_pid[person_counter] = fork();
                if (!person_pid[person_counter]) {
                    person_process(person_counter);
                }
                person_counter++;
            }
		}else if(!strcmp(message, "test")){
			while(person_counter < MAX_N_PERSONS) {
				person_pid[person_counter] = fork();
				if (!person_pid[person_counter]) {
						person_process(person_counter);
				}
				person_counter++;
			}
		}

		else if(!strcmp(message, "exit")){
			// The code below sends the SIGINT signal to
			// all processes involved in this application
			// except for the uicommand process itself
			// (which is exited by calling exit())
			kill(uidraw_pid, SIGINT);
			kill(lift_pid, SIGINT);
			kill(liftmove_pid, SIGINT);
			for(i=0; i < MAX_N_PERSONS; i++){
				if(person_pid[i] > 0){
					kill(person_pid[i], SIGINT);
				}
			}
			exit(0);
		}
	}
}

// This process is responsible for drawing the lift. Receives lift_type structures
// as messages.
void uidraw_process(void)
{
	char msg[1024];
	si_ui_set_size(670, 700);
	while(1){
		message_receive(msg, 1024, QUEUE_UI);
		lift_type Lift = (lift_type) &msg[0];
		draw_lift(Lift);
	}
}

int main(int argc, char **argv)
{
	message_init();
        si_ui_init(); // Initialize user interface. (Must be done
		      // here!)

	lift_pid = fork();
	if(!lift_pid) {
		lift_process();
	}
	uidraw_pid = fork();
	if(!uidraw_pid){
		uidraw_process();
	}
	liftmove_pid = fork();
	if(!liftmove_pid){
		liftmove_process();
	}
	uicommand_process();

	return 0;
}
