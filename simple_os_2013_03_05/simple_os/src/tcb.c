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

#include "tcb.h"

#include "console.h"

void tcb_reset(task_control_block *tcb)
{
    /* set all fields to zero */ 
    tcb->stack_pointer = 0; 
    tcb->task_id = 0; 
    tcb->valid = 0;
    tcb->wait_ticks = 0; 
    tcb->priority = 0; 
}

void tcb_init(
    task_control_block *tcb, mem_address stack_pointer, int priority)
{
    tcb_reset(tcb); 
    tcb->stack_pointer = stack_pointer; 
    tcb->priority = priority; 
}

int tcb_is_valid(task_control_block *tcb)
{
    return tcb->valid; 
}

void tcb_set_valid(task_control_block *tcb)
{
    tcb->valid = 1; 
}

void tcb_set_task_id(task_control_block *tcb, int task_id)
{
    tcb->task_id = task_id; 
}

void tcb_set_wait_ticks(task_control_block *tcb, int wait_ticks)
{
    tcb->wait_ticks = wait_ticks; 
}
