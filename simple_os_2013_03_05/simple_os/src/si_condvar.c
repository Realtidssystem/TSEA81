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

#include "si_condvar.h"

#include "task.h"
#include "interrupt.h"
#include "wait_list.h"
#include "ready_list.h"
#include "schedule.h"

/* si_cv_init: intialisation of condvar cv */ 
void si_cv_init(si_condvar *cv, si_semaphore *mutex)
{
    cv->mutex = mutex; 
    wait_list_reset(cv->wait_list, WAIT_LIST_SIZE); 
}

/* si_cv_wait: wait operation on cv */
void si_cv_wait(si_condvar *cv)
{
    int task_id; 
        
    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* check if tasks are waiting */ 
    if (!wait_list_is_empty(
            cv->mutex->wait_list, WAIT_LIST_SIZE))
    {
        /* get task_id with highest priority */ 
        task_id = wait_list_remove_highest_prio(
            cv->mutex->wait_list, WAIT_LIST_SIZE); 
        /* make this task ready to run */ 
        ready_list_insert(task_id); 
    }
    else
    {
        /* increment counter */ 
        cv->mutex->counter++; 
    }
    /* get task_id of running task */ 
    task_id = task_get_task_id_running();
    /* remove it from ready list */ 
    ready_list_remove(task_id); 
    /* insert it into the condvar waiting list */ 
    wait_list_insert(cv->wait_list, WAIT_LIST_SIZE, task_id); 
    /* call schedule */ 
    schedule(); 

    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}

/* si_cv_broadcast: broadcast operation on cv */
void si_cv_broadcast(si_condvar *cv)
{
    int done; 
    int task_id;    

    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* we are done if the wait list is empty */ 
    done = wait_list_is_empty(
               cv->wait_list, WAIT_LIST_SIZE); 
    while (!done)
    {
        /* remove one task from the list of waiting 
           tasks */ 
        task_id = wait_list_remove_one(
            cv->wait_list, WAIT_LIST_SIZE); 
        /* insert it into the mutex waiting list */ 
        wait_list_insert(
            cv->mutex->wait_list, WAIT_LIST_SIZE, task_id); 
        /* check if we are done */ 
        done = wait_list_is_empty(
                   cv->wait_list, WAIT_LIST_SIZE); 
    }

    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}

