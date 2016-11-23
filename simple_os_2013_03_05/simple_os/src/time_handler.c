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

#include "time_handler.h"

#include "task.h"
#include "time_list.h"
#include "tcb.h"
#include "tcb_storage.h"
#include "ready_list.h"
#include "schedule.h"

/* set_wait_ticks_running: sets number of wait 
   ticks in TCB for the running task */ 
static void set_wait_ticks_running(int wait_ticks)
{
    /* task_id for the running task */ 
    int task_id = task_get_task_id_running(); 
    /* a pointer to the TCB of the running task */ 
    task_control_block *tcb = 
        tcb_storage_get_tcb_ref(task_id); 
    /* set number of wait ticks */ 
    tcb_set_wait_ticks(tcb, wait_ticks); 
}

/* move_running_to_time_list: moves the task_id of 
   the running task from the ready list 
   to the time list */ 
static void move_running_to_time_list(void)
{
    /* task_id for the running task */ 
    int task_id = task_get_task_id_running(); 
    /* remove the task_id from the ready list */ 
    ready_list_remove(task_id); 
    /* and insert it into the time list */ 
    time_list_insert(task_id); 
}

void time_handler_wait_n_ticks(int n_ticks)
{
    /* set the wait ticks */ 
    set_wait_ticks_running(n_ticks); 
    /* move running task to time list */ 
    move_running_to_time_list(); 
    /* make another task run */ 
    schedule(); 
}
