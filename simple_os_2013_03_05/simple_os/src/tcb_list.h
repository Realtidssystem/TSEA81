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

#ifndef TCB_LIST_H
#define TCB_LIST_H

#include "tcb.h"

void tcb_list_reset(task_control_block tcb_list[], int length); 

int tcb_list_insert(
    task_control_block tcb_list[], int length,
    task_control_block tcb); 

/* tcb_list_get_task_id_highest_prio: get the task id in 
   task_id_list, corresponding to the task with the 
   highest priority, as specified by the TCBs stored 
   in tcb_list */ 
int tcb_list_get_task_id_highest_prio(
    task_control_block tcb_list[], int tcb_list_length, 
    int task_id_list[], int task_id_list_length); 

void tcb_list_decrement_timers(
    task_control_block tcb_list[], int tcb_list_length, 
    int task_id_list[], int task_id_list_length, 
    int *n_timers_set_to_zero, int task_ids_set_to_zero[]); 

#endif

