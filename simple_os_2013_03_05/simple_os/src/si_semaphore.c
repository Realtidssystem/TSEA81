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

#include "si_semaphore.h"

#include "wait_list.h"
#include "interrupt.h"
#include "task.h"
#include "ready_list.h"
#include "schedule.h"

/* fig_begin si_sem_init */ 
/* si_sem_init: intialisation of semaphore sem */ 
void si_sem_init(si_semaphore *sem, int init_val)
{
    wait_list_reset(sem->wait_list, WAIT_LIST_SIZE); 
    sem->counter = init_val; 
}
/* fig_end si_sem_init */ 

/* fig_begin si_sem_wait */ 
/* si_sem_wait: wait operation on semaphore sem */ 
void si_sem_wait(si_semaphore *sem)
{
    /* task id */ 
    int task_id; 
    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* check counter */ 
    if (sem->counter > 0)
    {
        /* decrement */ 
        sem->counter--; 
    }
    else
    {
        /* get task_id of running task */ 
        task_id = task_get_task_id_running();
        /* remove it from ready list */ 
        ready_list_remove(task_id); 
        /* insert it into the semaphore waiting list */ 
        wait_list_insert(
            sem->wait_list, WAIT_LIST_SIZE, task_id); 
        /* call schedule */ 
        schedule(); 
    }
    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}
/* fig_end si_sem_wait */ 

/* fig_begin si_sem_signal */ 
/* si_sem_signal: signal operation on semaphore sem */ 
void si_sem_signal(si_semaphore *sem)
{
    /* task id */ 
    int task_id; 

    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* check if tasks are waiting */ 
    if (!wait_list_is_empty(
            sem->wait_list, WAIT_LIST_SIZE))
    {
        /* get task_id with highest priority */ 
        task_id = wait_list_remove_highest_prio(
            sem->wait_list, WAIT_LIST_SIZE); 
        /* make this task ready to run */ 
        ready_list_insert(task_id); 
        /* call schedule */ 
        schedule(); 
    }
    else
    {
        /* increment counter */ 
        sem->counter++; 
    }
    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}
/* fig_end si_sem_signal */ 

