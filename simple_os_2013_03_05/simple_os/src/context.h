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

#ifndef CONTEXT_H
#define CONTEXT_H

#include "arch_types.h"

/* fig_begin context_restore_h */ 
/* context_restore: starts task with current
   stack pointer new_stack_pointer */ 
void context_restore(mem_address new_stack_pointer); 
/* fig_end context_restore_h */ 

void context_switch(mem_address *old_stack_pointer, mem_address new_stack_pointer); 

/* fig_begin context_switch_swi_h */ 
/* context_switch_swi: performs a task switch, using software interrupt, 
   by saving registers, and 
   storing the saved value of the stack pointer in old_stack_pointer, and 
   then restoring registers from the stack addressed by new_stack_pointer */ 
void context_switch_swi(mem_address *old_stack_pointer, mem_address new_stack_pointer); 
/* fig_end context_switch_swi_h */ 

/* fig_begin context_switch_int_h */ 
/* context_switch_int: performs a task switch, from 
   interrupt, by storing a saved value of the stack 
   pointer in old_stack_pointer, and then restoring 
   registers from the stack addressed by 
   new_stack_pointer */ 
void context_switch_int(
    mem_address *old_stack_pointer, 
    mem_address new_stack_pointer); 
/* fig_end context_switch_int_h */ 

#endif 
