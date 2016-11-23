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

#include "timer.h"

#include "console.h"

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST || defined BUILD_X86_MAC_HOST

#ifdef BUILD_X86_WIN_HOST 

void timer_init(void)
{
}

#else 

#include <sys/time.h>
#include <signal.h>
#include <stdio.h>

static struct itimerval timer_value; 

void timer_init(void)
{
    /* set up timer interval, selecting a frequency of 50 Hz */ 
    timer_value.it_interval.tv_sec = 0; 
    timer_value.it_interval.tv_usec = 20000; 
    timer_value.it_value = timer_value.it_interval; 

    /* initialise the timer */ 
    setitimer(ITIMER_VIRTUAL, &timer_value, 0); 
}

#endif

#endif

// code below is from the puppybits project, available at 
// https://code.google.com/p/puppybits
// Licensed under GPL v3
// Copyright by http://a-hackers-craic.blogspot.se/

#ifdef BUILD_ARM_BB

typedef unsigned int uint32_t; 

// Read/write I/O registers
#define reg32r(b, r) (*(volatile uint32_t *)((b)+(r)))
#define reg32w(b, r, v) (*((volatile uint32_t *)((b)+(r))) = (v))
#define reg32s(b, r, m, v) reg32w(b, r, (reg32r(b, r) & ~(m)) | ((v) & (m)))

#define GPTIMER1_BASE 0x48318000

#define GPT_TIOCP_CFG 0x010
#define GPT_TISTAT 0x014
#define GPT_TISR 0x018
#define GPT_TIER 0x01C
#define GPT_TWER 0x020
#define GPT_TCLR 0x024
#define GPT_TCRR 0x028
#define GPT_TLDR 0x02C
#define GPT_TTGR 0x030
#define GPT_TWPS 0x034
#define GPT_TMAR 0x038
#define GPT_TCAR1 0x03C
#define GPT_TSICR 0x040
#define GPT_TCAR2 0x044
#define GPT_TPIR 0x048
#define GPT_TNIR 0x04C
#define GPT_TCVR 0x050
#define GPT_TOCR 0x054
#define GPT_TOWR 0x058

// TISR/TIER flags
#define TCAR_IT_FLAG (1<<2)
#define OVF_IT_FLAG (1<<1)
#define MAT_IT_FLAG (1<<0)

void timer_init(void)
{
        // timer off
        reg32s(GPTIMER1_BASE, GPT_TCLR, 1, 0);

        // Sets true 1Khz rate w/ 32768Hz clock:  S 16.2.4.3 TRM D
        reg32w(GPTIMER1_BASE, GPT_TPIR, 232000);
        reg32w(GPTIMER1_BASE, GPT_TNIR, -768000);
        reg32w(GPTIMER1_BASE, GPT_TLDR, 0xffffffe0);
        reg32w(GPTIMER1_BASE, GPT_TCRR, 0xffffffe0);

        // clear int status bits
        reg32w(GPTIMER1_BASE, GPT_TISR, ~0);
        // enable overflow int
        reg32w(GPTIMER1_BASE, GPT_TIER, OVF_IT_FLAG);

        // dividisor = 100 -> 10Hz so it's visible
        reg32w(GPTIMER1_BASE, GPT_TOCR, 0);
        reg32w(GPTIMER1_BASE, GPT_TOWR, 20);

        // force 32K clock
        reg32s(0x48004c00, 0x40, 1, 0);

        // turn timer back on
        reg32s(GPTIMER1_BASE, GPT_TCLR, 1|2|(2<<10), ~0);

        console_put_string("timer initialised"); 
}

#endif
