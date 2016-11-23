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

#include "ready_list.h"
#include "tcb.h"
#include "tcb_storage.h"
#include "task_id_list.h"
#include "tcb_list.h"
#include "console.h"

/* fig_begin ready_list */ 
/* size of ready-list */ 
#define READY_LIST_SIZE TCB_LIST_SIZE

/* the list of ready-to-run tasks */ 
static int Ready_List[READY_LIST_SIZE]; 
/* fig_end ready_list */ 

void ready_list_init(void)
{
    task_id_list_reset(Ready_List, READY_LIST_SIZE); 
}

void ready_list_insert(int task_id)
{
    task_id_list_insert(Ready_List, READY_LIST_SIZE, task_id); 
    // console_put_string("ready_inserted "); 
    // console_put_hex(task_id); 
}

int ready_list_get_task_id_highest_prio(void)
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
        Ready_List, READY_LIST_SIZE);

    /* return the task_id */
    return task_id_highest_prio;
}

void ready_list_remove(int task_id)
{
    task_id_list_remove(Ready_List, READY_LIST_SIZE, task_id); 
}


