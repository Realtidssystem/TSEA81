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

#ifndef CONDVAR_H
#define CONDVAR_H

#include "si_semaphore.h"

typedef struct 
{
    /* the associated semaphore */ 
    si_semaphore *mutex; 
    /* the list of processes waiting for the condition variable */ 
    int wait_list[WAIT_LIST_SIZE]; 
} si_condvar; 

void si_cv_init(si_condvar *cv, si_semaphore *mutex); 

void si_cv_wait(si_condvar *cv); 

void si_cv_broadcast(si_condvar *cv); 

#endif
