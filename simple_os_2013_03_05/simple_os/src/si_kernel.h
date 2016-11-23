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

#ifndef SI_KERNEL_H
#define SI_KERNEL_H

#include "arch_types.h"

#define IDLE_PRIORITY 1000

/* si_kernel_init: initialise real-time kernel */ 
void si_kernel_init(void); 

/* si_kernel_start: start real-time kernel */ 
void si_kernel_start(void); 

/* si_task_create: create a task from the 
   function task_function, with stack starting at stack_bottom, 
   and having priority priority. */ 
void si_task_create(
    void (*task_function)(void), 
    stack_item *stack_bottom, int priority); 

#endif
