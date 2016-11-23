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

#include "schedule.h"

#include "ready_list.h"
#include "task.h"

#include "console.h"

/* fig_begin schedule */ 
/* schedule: perform priority based scheduling */ 
void schedule(void)
{
    /* task id for the running task */ 
    int task_id_running; 

    /* task id for the task in ready list with 
       highest priority */ 
    int task_id_highest_prio; 

    /* get task id for the running task */ 
    task_id_running = task_get_task_id_running(); 

    /* get task id for task in ready list with 
       highest priority */ 
    task_id_highest_prio = 
        ready_list_get_task_id_highest_prio(); 

    /* check if a task switch shall be performed */ 
    if (task_id_highest_prio != task_id_running)
    {
        /* perform task switch */ 
        task_switch(task_id_running, task_id_highest_prio); 
    }
    else
    {
        return; /* no task switch */
    }
}
/* fig_end schedule */ 
