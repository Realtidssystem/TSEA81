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

#ifndef INT_STATUS
#define INT_STATUS

void int_status_init(void); 

/* int_status_save_stack_pointer: saves esp */ 
void int_status_save_stack_pointer(int esp); 

/* int_status_get_saved_stack_pointer: returns saved 
   value of esp */ 
int int_status_get_saved_stack_pointer(void); 

/* int_status_set_interrupt_active: sets interrupt
   active flag */ 
void int_status_set_interrupt_active(void); 

/* int_status_clear_interrupt_active: clears interrupt
   active flag */ 
void int_status_clear_interrupt_active(void); 

/* int_status_is_interrupt_active: returns nonzero 
   if interrupt active flag is set, returns zero 
   otherwise */ 
int int_status_is_interrupt_active(void); 
 
#endif 
