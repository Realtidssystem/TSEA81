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

#include "si_time.h"

#include "time_handler.h"
#include "time_storage.h"

#include "interrupt.h"

#include "console.h"

static int calculate_n_ticks(int n_ms)
{
    /* number of milliseconds per tick */ 
    int n_ms_per_tick; 

    /* number of ticks */ 
    int n_ticks; 

    n_ms_per_tick = time_storage_get_ms_per_tick(); 

    n_ticks = 1; 
    while (n_ticks * n_ms_per_tick < n_ms)
    {	
        n_ticks++; 
    }

    // console_put_hex(n_ms); 
    // console_put_string(" ms is ");
    // console_put_hex(n_ticks); 
    // console_put_string(" ticks\n"); 

    return n_ticks; 
}

/* si_wait_n_ms: makes the calling process wait n_ms
   milliseconds */ 
void si_wait_n_ms(int n_ms)
{
    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* wait a calculated number of ticks */ 
    time_handler_wait_n_ticks(calculate_n_ticks(n_ms)); 

    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}

/* si_wait_until_time: makes the calling process 
   wait until the time *time */ 
void si_wait_until_time(si_time *time)
{
    /* the current time */ 
    si_time current_time; 

    /* number of milliseconds to wait */ 
    int n_ms; 
    /* number of ticks to wait */ 
    int n_ticks; 

    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    /* get the current time */ 
    time_storage_get_current_time(&current_time); 
    
    /* calculate number of ticks to wait */ 
    n_ms = si_time_diff_n_ms(time, &current_time); 
    n_ticks = calculate_n_ticks(n_ms); 

    /* wait the calculated number of ticks */  
    time_handler_wait_n_ticks(n_ticks); 

    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}

void si_get_current_time(si_time *time)
{
    /* disable interrupts */ 
    DISABLE_INTERRUPTS; 

    time_storage_get_current_time(time);

    /* enable interrupts */ 
    ENABLE_INTERRUPTS; 
}

