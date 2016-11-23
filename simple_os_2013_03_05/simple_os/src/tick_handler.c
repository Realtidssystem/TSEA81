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

#include "tick_handler.h"

#include "console.h"
#include "timer.h"

#include "interrupt.h"

#include "tcb_storage.h"
#include "time_list.h"
#include "ready_list.h"
#include "schedule.h"

#include "time_storage.h"

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

#ifdef BUILD_X86_WIN_HOST

// Windows host

#include <windows.h>

// variables needed for the multimedia timer
MMRESULT res; 
TIMECAPS timecaps; 
UINT timerid; 

/* variable to simulate switching on and off interrupts */ 
static int Int_Enabled_Win = 0; 

void enable_int_win(void)
{
    Int_Enabled_Win = 1; 
}

void disable_int_win(void)
{       
    Int_Enabled_Win = 0; 
}

# else 

// Linux host (default)
#include <signal.h>

#endif

#endif

static int interrupt_counter; 
static int interrupt_counter_max; 
static char interrupt_char; 

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

#ifdef BUILD_X86_WIN_HOST

// windows host 

/* windows callback function */ 
void CALLBACK tick_handler_function(
    UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)

#else

// Linux host (default) 

void tick_handler_function(int dummy)

#endif

#endif

#if defined BUILD_ARM_BB || defined BUILD_X86_TARGET 
void tick_handler_function(void)
#endif 

{
    /* loop counter */ 
    int i; 
    /* number of ready tasks */ 
    int n_new_tasks_ready; 
    /* task ids for ready tasks */ 
    int new_task_ids_ready[TCB_LIST_SIZE]; 

#ifdef BUILD_X86_WIN_HOST 

    /* return if interrupts are not enabled */ 
    if (!Int_Enabled_Win) 
    {
        return; 
    }

#endif 

    // DISABLE_INTERRUPTS; 
    interrupt_counter++; 
    if (interrupt_counter == interrupt_counter_max)
    {
        interrupt_counter = 0; 
        // console_put_char(interrupt_char); 
        interrupt_char = (char) (((int) interrupt_char) + 1);  
        if (interrupt_char == 'z')
        {
    	    interrupt_char = 'a'; 
        }
    }
    /* register the interrupt */ 
    time_storage_register_tick(); 
    /* decrement timers for all waiting processes */ 
    time_list_decrement_timers(
        &n_new_tasks_ready, new_task_ids_ready); 
    /* check if any tasks have become ready */ 
    if (n_new_tasks_ready > 0)
    {
        for (i = 0; i < n_new_tasks_ready; i++) 
        {
            /* move from time list */ 
            time_list_remove(new_task_ids_ready[i]); 
            /* and insert in ready list */ 
            ready_list_insert(new_task_ids_ready[i]); 
        }
        /* perform scheduling */ 
        schedule(); 
    }

#ifdef BUILD_X86_WIN_HOST 
    
    enable_int_win(); 

#endif

}


void tick_handler_init(void)
{
    interrupt_counter = 0; 
#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST
    interrupt_counter_max = 50; 
#endif
#if defined BUILD_ARM_BB
    interrupt_counter_max = 50; 
#endif
    interrupt_char = 'a'; 

    timer_init(); 
    time_storage_set_ms_per_tick(20); 

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

// we build for host (i.e. soft-kernel)

#ifdef BUILD_X86_WIN_HOST

// Windows host

    /* register the multimedia timer interrupt handler */ 
    res = timeGetDevCaps(&timecaps, sizeof(timecaps)); 
    timeBeginPeriod(timecaps.wPeriodMin); 
    timerid = timeSetEvent(20, timecaps.wPeriodMin, &tick_handler_function, 0, TIME_PERIODIC); 

#else

// Linux host (default)

    /* register the signal handler */ 
    signal(SIGVTALRM, tick_handler_function); 

#endif

#endif

    // console_put_string("tick handler installed\n"); 
}


