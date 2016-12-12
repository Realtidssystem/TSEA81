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
#define NUMBER_OF_TRIPS 120
#define VIP_ID 5

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
	int from_floor[NUMBER_OF_TRIPS];      // Specify source and destion for the LIFT_TRAVEL message.
	int to_floor[NUMBER_OF_TRIPS];
	int trips;
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
	struct lift_msg every_person_trip_counter[MAX_N_PERSONS];
	char msgbuf[4096];
	while(1){
		int i;
		int j;
		struct lift_msg reply;
		struct lift_msg *m;
	//	message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0); // Draw the lift
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
					int id = Lift->passengers_in_lift[i].id;
						if (Lift->passengers_in_lift[i].to_floor == Lift->floor)
      			{
							(every_person_trip_counter[id].trips)++;
							Lift->passengers_in_lift[i].id = NO_ID;
  						Lift->passengers_in_lift[i].to_floor = NO_FLOOR;
							if(every_person_trip_counter[id].trips < NUMBER_OF_TRIPS){
								//printf("Enter floor travel done\n");
								enter_floor(Lift, id, every_person_trip_counter[id].from_floor[every_person_trip_counter[id].trips],every_person_trip_counter[id].to_floor[every_person_trip_counter[id].trips]);
							}
							else{
								//printf("Travel done\n");
								message_send((char *) &reply, sizeof(reply), QUEUE_FIRSTPERSON + id ,0);
							}
						/*	else{
								printf("%d\n",every_person_trip_counter[id].trips );
								printf("här är jag \n");
								exit(1);
							}*/
						}
  			  }

				//    Check if passengers want to enter elevator
				//    Remove the passenger from the floor and into the elevator
				for(j = 0; j < MAX_N_PERSONS; j++){

					person_data_type person = Lift->persons_to_enter[Lift->floor][j];
					person_data_type person_to_leave = Lift->passengers_in_lift[0];
      			if (person.id != NO_ID && (n_passengers_in_lift(Lift) < MAX_N_PASSENGERS))
      			{
							leave_floor(Lift, person.id, Lift->floor);
							put_passenger_in_lift(Lift, person.id, person.to_floor);
      			}
					/* Försök att få till en vip-person*/
						else if (person.id == VIP_ID && (n_passengers_in_lift(Lift) == MAX_N_PASSENGERS))
						{
							printf("Enter floor prio\n");
							printf("%d\n",person_to_leave.id);
							printf("%d\n", Lift->floor);
							leave_for_vip(Lift, person_to_leave, Lift->floor);
							leave_floor(Lift, person.id, Lift->floor);
							put_passenger_in_lift(Lift, person.id, person.to_floor);
						}
  			}
				//    Move the lift
			lift_next_floor(Lift, &next_floor, &change_direction);
			lift_move(Lift, next_floor, change_direction);
		//	message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0);
			change_direction = 0;

				break;
		case LIFT_TRAVEL:

			//    Update the Lift structure so that the person with the given ID is now present on the floor

			  every_person_trip_counter[m->person_id]=*m;
				//printf("Enter floor in Lift travel\n");
				//printf("%d\n",m->from_floor[0]);
				enter_floor(Lift, m->person_id, m->from_floor[0], m->to_floor[0]);
			//	message_send((char *) Lift, sizeof(*Lift), QUEUE_UI,0);

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
	unsigned long long int data[9999];
	int iterations = 0;
	while(iterations < 10000){
		gettimeofday(&starttime, NULL);
		//    Generate a to and from floor
		int i;
		for(i = 0; i < NUMBER_OF_TRIPS; i++){
			m.to_floor[i] = get_random_value(id,N_FLOORS-1);
			m.from_floor[i] = get_random_value(id,N_FLOORS-1);
			while(m.from_floor[i] == m.to_floor[i]){
				m.to_floor[i] = get_random_value(id, N_FLOORS-1);
			}
		}
		m.person_id = id;
		m.trips = 0;
		m.type = LIFT_TRAVEL;
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

	  data[iterations] = timediff;
	//	printf("%d\n", iterations);
		iterations++;
		//    Wait a little while
		//sleep(5);
	}
	unsigned long long int sum = 0;
	unsigned long long int printsum = 0;
	int i = 0;
	for(i = 0; i < 10000; i++){
		sum = sum + data[i];
	}
	printsum = sum/1200000;
	printf("  Passenger id: %d\n", id);
	printf( "medeltid: %lld\n", printsum);
	exit(1);
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

			while(person_counter < MAX_N_PERSONS)
			{
				person_pid[person_counter] = fork();
					if (!person_pid[person_counter])
					{
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
