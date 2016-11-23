/* This file is part of Simple_OS, a real-time operating system  */
/* designed for research and education */
/* Copyright (c) 2003-2013 Ola Dahl */

/* The software accompanies the book Into Realtime, available at  */
/* http://theintobooks.com */

/* Simple_OS is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "time_list.h"
#include "tcb_storage.h"
#include "task_id_list.h"
#include "tcb.h"
#include "tcb_list.h"

#include "console.h"

/* size of time-list */ 
#define TIME_LIST_SIZE TCB_LIST_SIZE

/* the list of processes waiting for time to expire */ 
static int Time_List[TIME_LIST_SIZE]; 

void time_list_init(void)
{
    task_id_list_reset(Time_List, TIME_LIST_SIZE); 
}

void time_list_insert(int pid)
{
    task_id_list_insert(Time_List, TIME_LIST_SIZE, pid); 
}

void time_list_remove(int pid)
{
    task_id_list_remove(Time_List, TIME_LIST_SIZE, pid); 
    // console_put_string("time_removed "); 
    // console_put_hex(pid); 
}

void time_list_decrement_timers(int *n_new_tasks_ready, int new_task_ids_ready[])
{
    /* a pointer to a TCB, to be used as a pointer
       to the common TCB list */ 
    task_control_block *tcb_list_ref; 

    /* get a pointer to the common TCB list */  
    tcb_list_ref = tcb_storage_get_tcb_list_ref(); 

    /* decrement timers */ 
    tcb_list_decrement_timers(
        tcb_list_ref, tcb_storage_get_tcb_list_size(), 
        Time_List, TIME_LIST_SIZE, 
        n_new_tasks_ready, new_task_ids_ready);
}

