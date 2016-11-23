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

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "tcb_storage.h"

#define WAIT_LIST_SIZE TCB_LIST_SIZE

/* fig_begin sem_def */ 
typedef struct 
{
    /* the list of waiting processes */ 
    int wait_list[WAIT_LIST_SIZE]; 
    /* semaphore value */
    int counter; 
} si_semaphore; 
/* fig_end sem_def */ 

void si_sem_init(si_semaphore *sem, int init_val); 

void si_sem_wait(si_semaphore *sem); 

void si_sem_signal(si_semaphore *sem); 

#endif
