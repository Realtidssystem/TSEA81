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

#ifndef TCB_H
#define TCB_H

#include "arch_types.h"

/* fig_begin tcb_def */ 
/* type definition for a task control block */
typedef struct
{
    /* reference to the stack */
    mem_address stack_pointer;
    /* identity */
    int task_id; 
    /* validity flag */ 
    int valid;
    /* waiting time in ticks */ 
    int wait_ticks; 
    /* priority */ 
    int priority; 
} task_control_block;
/* fig_end tcb_def */ 

/* tcb_reset: reset all fields in *tcb */ 
void tcb_reset(task_control_block *tcb); 

/* tcb_init: initialises *tcb, setting the fields 
   stack_pointer and priority */ 
void tcb_init(
    task_control_block *tcb, 
    mem_address stack_pointer, int priority); 

/* tcb_is_valid: checks if the valid flag in *tcb 
   is set */ 
int tcb_is_valid(task_control_block *tcb); 

/* tcb_set_valid: makes *tcb valid */ 
void tcb_set_valid(task_control_block *tcb); 

/* tcb_set_task_id: sets task_id in *tcb to task_id */ 
void tcb_set_task_id(task_control_block *tcb, int task_id); 

/* tcb_set_wait_ticks: sets wait_ticks in *tcb to wait_ticks */
void tcb_set_wait_ticks(task_control_block *tcb, int wait_ticks); 

#endif

