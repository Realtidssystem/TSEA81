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

#ifndef INTERRUPT_H
#define INTERRUPT_H

#ifdef BUILD_ARM_BB

/* set_interrupt_handler: installs an interrupt handler */ 
void set_interrupt_handler(int start_address, int entry_number); 

/* disable and enable interrupts, using in-line 
   assembler */ 

#endif 

#ifdef BUILD_X86_TARGET 

#define DISABLE_INTERRUPTS asm("cli")

#define ENABLE_INTERRUPTS asm("sti")

#endif 

#ifdef BUILD_ARM_BB 

#define DISABLE_INTERRUPTS asm volatile("cpsid i")

#define ENABLE_INTERRUPTS asm volatile("cpsie i")

#endif 

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST || defined BUILD_X86_MAC_HOST

void disable_interrupts(void); 

#define DISABLE_INTERRUPTS disable_interrupts()

void enable_interrupts(void); 

#define ENABLE_INTERRUPTS enable_interrupts()

#endif

void enable_timer_interrupts(); 

#endif

