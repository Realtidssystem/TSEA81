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

#ifndef TASK_H
#define TASK_H

#include "arch_types.h"

/* task_init: intialise the task module */ 
void task_init(void); 

/* task_create: creates a task from the function 
   task_function, associates a stack with bottom stack_bottom 
   to the task, and sets the priority to priority. 
   The task_id of the created task is returned. */ 
int task_create(
    void (*task_function)(void), 
    stack_item *stack_bottom, int priority); 

/* task_get_task_id_running: returns the task id of the 
   running task */ 
int task_get_task_id_running(); 

/* task_start: starts task task_id */ 
void task_start(int task_id); 

/* task_switch: switches from task task_id_old to 
   task task_id_new */ 
void task_switch(int task_id_old, int task_id_new); 

#endif
