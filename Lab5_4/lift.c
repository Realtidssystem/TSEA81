#include "lift.h"

/* Simple_OS include */
#include <pthread.h>

/* drawing module */
#include "draw.h"

/* standard includes */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>


sem_t set_floor;
/* panic function, to be called when fatal errors occur */
static void lift_panic(const char message[])
{
    printf("LIFT_PANIC!!! ");
    printf("%s", message);
    printf("\n");
    exit(0);
}

/* definition of monitor data type for lift */



/* --- monitor data type for lift and operations for create and delete START --- */





/* lift_create: creates and initialises a variable of type lift_type */
lift_type lift_create(void)
{
    /* the lift to be initialised */
    lift_type lift;

    /* floor counter */
    int floor;

    /* loop counter */
    int i;

    /* allocate memory */
    lift = (lift_type) malloc(sizeof(lift_data_type));

    /* initialise variables */

    /* initialise floor */
    lift->floor = 0;

    /* set direction of lift travel to up */
    lift->up = 1;

    /* the lift is not moving */
    lift->moving = 0;

    /* initialise person information */
    for (floor = 0; floor < N_FLOORS; floor++)
    {
        for (i = 0; i < MAX_N_PERSONS; i++)
        {
            lift->persons_to_enter[floor][i].id = NO_ID;
            lift->persons_to_enter[floor][i].to_floor = NO_FLOOR;
        }
    }

    /* initialise passenger information */
    for (i = 0; i < MAX_N_PASSENGERS; i++)
    {
        lift->passengers_in_lift[i].id = NO_ID;
        lift->passengers_in_lift[i].to_floor = NO_FLOOR;
    }

    /* initialise mutex and event variable */

    return lift;
}

/* lift_delete: deallocates memory for lift */
void lift_delete(lift_type lift)
{
    free(lift);
}


/* --- monitor data type for lift and operations for create and delete END --- */


/* --- functions related to lift task START --- */

/* MONITOR function lift_next_floor: computes the floor to which the lift
   shall travel. The parameter *change_direction indicates if the direction
   shall be changed */
void lift_next_floor(lift_type lift, int *next_floor, int *change_direction)
{
  if (lift->up == 0) {
   if (lift->floor == 1) {
     *change_direction = 1;
   }
   *next_floor = lift->floor - 1;
 }
 else if (lift->up == 1) {
   if (lift->floor == N_FLOORS-2) {
     *change_direction = 1;
   }
   *next_floor = lift->floor + 1;
 }
}

void lift_move(lift_type lift, int next_floor, int change_direction)
{
  /* the lift has arrived at next_floor */
  lift->floor = next_floor;

  /* check if direction shall be changed */
  if (change_direction)
  {
      lift->up = !lift->up;
  }
}

/* this function is used also by the person tasks */
int n_passengers_in_lift(lift_type lift)
{
    int n_passengers = 0;
    int i;

    for (i = 0; i < MAX_N_PASSENGERS; i++)
    {
        if (lift->passengers_in_lift[i].id != NO_ID)
        {
            n_passengers++;
        }
    }
    return n_passengers;
}

int n_passengers_on_floor(lift_type lift)
{
  int n_passengers = 0;
  int i;

  for (i = 0; i < MAX_N_PERSONS; i++)
  {
      if (lift->persons_to_enter[lift->floor][i].id != NO_ID)
      {
          n_passengers++;
      }
  }

  if (n_passengers_in_lift(lift) == MAX_N_PASSENGERS)
  {
    n_passengers = 0;
  }
  return n_passengers;
}

/* MONITOR function lift_has_arrived: shall be called by the lift task
   when the lift has arrived at the next floor. This function indicates
   to other tasks that the lift has arrived, and then waits until the lift
   shall move again. */


/* --- functions related to lift task END --- */


/* --- functions related to person task START --- */

/* passenger_wait_for_lift: returns non-zero if the passenger shall
   wait for the lift, otherwise returns zero */
int passenger_wait_for_lift(lift_type lift, int wait_floor)
{
    int waiting_ready =
        /* the lift is not moving */
        !lift->moving &&
        /* and the lift is at wait_floor */
        lift->floor == wait_floor &&
        /* and the lift is not full */
        n_passengers_in_lift(lift) < MAX_N_PASSENGERS;
    return !waiting_ready;
}
int passenger_wait_to_leave(lift_type lift, int dest_floor){
  int leave_lift =
      /*the lift is not moving */
      !lift->moving &&
      /*and the lift is at the same floor as the passengers to_floor*/
      lift->floor == dest_floor;
  return !leave_lift;

}

int n_passengers_to_leave(lift_type lift)
{
  int j = 0;
  int i = 0;
  for (i = 0; i < MAX_N_PASSENGERS; i++)
  {
      if (lift->passengers_in_lift[i].to_floor == lift->floor)
      {
          j++;
      }
  }
  return j;
}

void lift_has_arrived(lift_type lift)
{
  draw_lift(lift);
  while ((n_passengers_on_floor(lift) != 0) || (n_passengers_to_leave(lift) != 0))
  {
    usleep(1);

  }
}

void delete_passenger(lift_type lift,int id, int floor){
  int i;
  int floor_index;
  int found;

  /* leave the floor */
  found = 0;
  for (i = 0; i < MAX_N_PERSONS && !found; i++)
  {
      if (lift->persons_to_enter[floor][i].id == id)
      {
          found = 1;
          floor_index = i;
      }
  }

  if (!found)
  {
      lift_panic("cannot delete passenger");
  }

  /* leave floor at index floor_index */
  lift->persons_to_enter[floor][floor_index].id = NO_ID;
  lift->persons_to_enter[floor][floor_index].to_floor = NO_FLOOR;

}
/* enter_floor: makes a person with id id stand at floor floor */
 void enter_floor(
    lift_type lift, int id, int floor,int to_floor)
{

    int i;
    int j = 0;
    int floor_index;
    int found;

    /* stand at floor */
    found = 0;
    for (i = 0; i < MAX_N_PERSONS && !found; i++)
    {
        if (lift->persons_to_enter[floor][i].id == NO_ID)
        {
            found = 1;
            floor_index = i;
        }
    }
    if (!found)
    {
      //printf("%d\n", floor);
      //printf("%d\n", id);
      //printf("%d\n", to_floor);
      for(j = 0; j < MAX_N_PERSONS;j++){
        printf("%d",lift->persons_to_enter[floor][j].id);
      }

      lift_panic("cannot enter floor");
    }

    /* enter floor at index floor_index */
    lift->persons_to_enter[floor][floor_index].id = id;
    lift->persons_to_enter[floor][floor_index].to_floor = to_floor;

}
void leave_for_vip(lift_type lift, person_data_type person, int floor){
  int i;
  int floor_index;
  int found;

  found = 0;
  int leave_id = lift->passengers_in_lift[0].id;
  int leave_to_floor = lift->passengers_in_lift[0].to_floor;
  lift->passengers_in_lift[0].id = NO_ID;
  lift->passengers_in_lift[0].to_floor = NO_FLOOR;

    for (i = 0; i < MAX_N_PERSONS && !found; i++)
    {
        if (lift->persons_to_enter[floor][i].id == NO_ID)
        {
          found = 1;
          floor_index = i;
        }
    }

      if (!found)
      {
          lift_panic("cannot enter floor");
      }

  lift->persons_to_enter[floor][floor_index].id = leave_id;
  lift->persons_to_enter[floor][floor_index].to_floor = leave_to_floor;

}

/* leave_floor: makes a person with id id at enter_floor leave
   enter_floor */
 void leave_floor(
    lift_type lift, int id, int enter_floor)

/* fig_end lift_c_prot */
{
    int i;
    int floor_index;
    int found;

    /* leave the floor */
    found = 0;
    for (i = 0; i < MAX_N_PERSONS && !found; i++)
    {
        if (lift->persons_to_enter[enter_floor][i].id == id)
        {
            found = 1;
            floor_index = i;
        }
    }

    if (!found)
    {
        lift_panic("cannot leave floor");
    }

    /* leave floor at index floor_index */

    lift->persons_to_enter[enter_floor][floor_index].id = NO_ID;
    lift->persons_to_enter[enter_floor][floor_index].to_floor = NO_FLOOR;

    //draw_lift(lift);
}
 void put_person_on_floor(lift_type lift,int id,int from_floor,int to_floor){
  int i;
  int floor_index;
  int found;

  /* leave the floor */
  found = 0;
  for (i = 0; i < MAX_N_PERSONS && !found; i++)
  {
      if (lift->persons_to_enter[from_floor][i].id == NO_ID)
      {
          found = 1;
          floor_index = i;
      }
  }

  if (!found)
  {
      lift_panic("cannot be put on floor");
  }
  /* leave floor at index floor_index */
  lift->persons_to_enter[from_floor][floor_index].id = id;
  lift->persons_to_enter[from_floor][floor_index].to_floor = to_floor;

}
 void put_passenger_in_lift(lift_type lift,int id,int to_floor){
  int i;
  int floor_index;
  int found;

  /* stand at floor */
  found = 0;
  for (i = 0; i < MAX_N_PASSENGERS && !found; i++)
  {
      if (lift->passengers_in_lift[i].id == NO_ID)
      {
          found = 1;
          floor_index = i;
      }
  }

  if (!found)
  {
      lift_panic("cannot enter lift");
  }

  /* enter floor at index floor_index */
  leave_floor(lift, id, lift->floor);
  lift->passengers_in_lift[floor_index].id = id;
  lift->passengers_in_lift[floor_index].to_floor = to_floor;


}
int leave_lift(lift_type lift,int floor, int id){
  int i;
  int found;

  /* stand at floor */
  found = 0;
  for (i = 0; i < MAX_N_PASSENGERS && !found; i++)
  {
      if ((lift->passengers_in_lift[i].id == id)&&(lift->passengers_in_lift[i].to_floor == floor))
      {
          found = 1;
          lift->passengers_in_lift[i].id = NO_ID;
          lift->passengers_in_lift[i].to_floor = NO_FLOOR;
          return lift->passengers_in_lift[i].id;
      }
  }

  /* enter floor at index floor_index */
  return 0;
}
/* MONITOR function lift_travel: performs a journey with the lift
   starting at from_floor, and ending at to_floor */
/*void lift_travel(lift_type lift, int id, int from_floor, int to_floor)
{
  put_person_on_floor(lift,id,from_floor,to_floor);

  draw_lift(lift);
  while(passenger_wait_for_lift(lift,from_floor))
  {
    usleep(1);
  };

  leave_floor(lift, id, from_floor);
  draw_lift(lift);
  put_passenger_in_lift(lift,id,to_floor);
  draw_lift(lift);

  while(passenger_wait_to_leave(lift, to_floor))
  {
    usleep(1);

    printf("passenger wait to leave to floor:");
    printf("%d\n", to_floor);
  };

  leave_lift(lift,id);
  draw_lift(lift);
  enter_floor(lift,id,to_floor);
  draw_lift(lift);

  delete_passenger(lift,id,to_floor);
  draw_lift(lift);

  usleep(5000000);

}
 --- functions related to person task END --- */
