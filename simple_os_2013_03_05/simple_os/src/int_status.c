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

#include "int_status.h"

#include "console.h"

/* saved value of esp */ 
static int Saved_Stack_Pointer; 

/* interrupt active flag */ 
static int Interrupt_Active; 

void int_status_init(void)
{
    Saved_Stack_Pointer = 0; 
    Interrupt_Active = 0; 
}

void int_status_save_stack_pointer(int esp)
{
    Saved_Stack_Pointer = esp; 
}

int int_status_get_saved_stack_pointer(void)
{
    // console_put_string("RETURning sp: "); 
    // console_put_hex(Saved_Stack_Pointer); 
    // console_put_string("SAVED sp: "); 
    // console_put_hex(Saved_Stack_Pointer); 
#ifdef BUILD_ARM_BB
    // console_put_mem(Saved_Stack_Pointer); 
#endif
    return Saved_Stack_Pointer; 
}

void int_status_set_interrupt_active(void)
{
    Interrupt_Active = 1; 
}

void int_status_clear_interrupt_active(void)
{
    Interrupt_Active = 0; 
}

int int_status_is_interrupt_active(void)
{
    return Interrupt_Active; 
}
