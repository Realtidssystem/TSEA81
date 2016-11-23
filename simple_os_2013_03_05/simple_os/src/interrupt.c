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

#include "interrupt.h"

#include "console.h"

#include "exceptions.h"

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST || defined BUILD_X86_MAC_HOST

#ifdef BUILD_X86_WIN_HOST

void enable_int_win(void); 
void disable_int_win(void); 

void disable_interrupts(void)
{
    disable_int_win(); 
}

void enable_interrupts(void)
{
    enable_int_win(); 
}

void enable_timer_interrupts()
{
}

#else

#include <signal.h>
#include <stdlib.h>

void disable_interrupts(void)
{
   sigset_t set; 
   sigemptyset(&set); 
   sigaddset(&set, SIGVTALRM);  
   sigprocmask(SIG_BLOCK, &set, NULL); 
   // sigblock(sigmask(SIGVTALRM));
}

void enable_interrupts(void)
{
   sigset_t set; 
   sigemptyset(&set); 
   sigaddset(&set, SIGVTALRM);  
   sigprocmask(SIG_UNBLOCK, &set, NULL); 
   // sigsetmask(0); 
}

void enable_timer_interrupts()
{
}

#endif

#endif

#ifdef BUILD_ARM_BB

volatile unsigned int * const INTCPS_MIR0 = (unsigned int *)0x48200084; 
volatile unsigned int * const INTCPS_MIR1 = (unsigned int *)0x482000A4; 
volatile unsigned int * const INTCPS_MIR2 = (unsigned int *)0x482000C4; 

void enable_timer_interrupts(void)
{
    *INTCPS_MIR1 = 0xFFFFFFDF; 
    console_put_string("timer interrupts enabled"); 
}

#endif


#ifdef BUILD_ARM_BB

// parts of code below is from the puppybits project, available at 
// https://code.google.com/p/puppybits
// Licensed under GPL v3
// Copyright by http://a-hackers-craic.blogspot.se/

        /* irq_set_handler(INTC_GPT1_IRQ, gptimer1_handler); */
        /* irq_set_mask(INTC_GPT1_IRQ, 1); */

#define GPTIMER1 0x48318000
#define GPTIMER1_TPIR 0x48318048
#define GPTIMER1_TNIR 0x48318048
#define GPTIMER1_TLDR 0x48318048
#define GPTIMER1_TCRR 0x48318048
#define GPTIMER1_TISR 0x48318048
#define GPTIMER1_TIER 0x48318048
#define GPTIMER1_TOCR 0x48318048
#define GPTIMER1_TOWR 0x48318048
#define GPTIMER1_TPIR 0x48318048
#define GPTIMER1_TPIR 0x48318048

void tick_handler_function(void); 

typedef unsigned int uint32_t; 

// Read/write I/O registers
#define reg32r(b, r) (*(volatile uint32_t *)((b)+(r)))
#define reg32w(b, r, v) (*((volatile uint32_t *)((b)+(r))) = (v))
#define reg32s(b, r, m, v) reg32w(b, r, (reg32r(b, r) & ~(m)) | ((v) & (m)))

#define GPTIMER1_BASE 0x48318000
#define GPT_TISR 0x018

#define OVF_IT_FLAG (1<<1)

void int_handler_function(void)
{
    int irq = reg32r(GPTIMER1_BASE, GPT_TISR);
    if (irq & OVF_IT_FLAG) 
    {
        // console_put_char('#'); 
        tick_handler_function(); 
        // console_put_char('@'); 
    }
    reg32w(GPTIMER1_BASE, GPT_TISR, ~0);
}

#endif
