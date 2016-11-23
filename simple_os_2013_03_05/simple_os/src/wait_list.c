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

#include "wait_list.h"

#include "tcb_storage.h"
#include "tcb_list.h"
#include "tcb.h"
#include "task_id_list.h"

void wait_list_reset(int wait_list[], int length)
{
    task_id_list_reset(wait_list, length); 
}

/* wait_list_insert: inserts task_id in wait_list */ 
void wait_list_insert(int wait_list[], int length, int task_id)
{
    task_id_list_insert(wait_list, length, task_id); 
}

int wait_list_is_empty(int wait_list[], int length)
{
    return task_id_list_is_empty(wait_list, length); 
}

int wait_list_remove_highest_prio(int wait_list[], int length)
{
    /* a pointer to a TCB, to be used as a pointer
       to the common TCB list */ 
    task_control_block *tcb_list_ref; 

    /* task_id for task with highest priority */ 
    int task_id_highest_prio; 

    /* get a pointer to the common TCB list */  
    tcb_list_ref = tcb_storage_get_tcb_list_ref(); 

    /* get task_id for task with highest priority */ 
    task_id_highest_prio = tcb_list_get_task_id_highest_prio(
        tcb_list_ref, tcb_storage_get_tcb_list_size(), 
        wait_list, length); 

    /* remove the task_id from wait_list */ 
    task_id_list_remove(wait_list, length, task_id_highest_prio); 

    /* return the task_id */ 
    return task_id_highest_prio; 
}

int wait_list_remove_one(int wait_list[], int length)
{
    return task_id_list_remove_first(wait_list, length); 
}

