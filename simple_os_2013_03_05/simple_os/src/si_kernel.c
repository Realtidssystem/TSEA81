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

#include "si_kernel.h"

#include "tcb_storage.h"
#include "task.h"
#include "ready_list.h"
#include "tick_handler.h"
#include "time_list.h"
#include "time_storage.h"
#include "schedule.h" 
#include "interrupt.h"
#include "exceptions.h"
#include "int_status.h"
#include "console.h"

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

#ifdef BUILD_X86_WIN_HOST

/* Windows API include file */ 
#include <windows.h>

#else

/* unistd is needed for usleep and sleep */ 
#include <unistd.h>

#endif

#endif

/* CHANGE this string when doing new release of Simple_OS */ 
#define SIMPLE_OS_VERSION_STRING "Simple_OS - 2013-03-05\n"

/* stack for idle task */ 
#define IDLE_STACK_SIZE 5000 

static stack_item Idle_Stack[IDLE_STACK_SIZE]; 

static int Kernel_Running; 

/* a function which does a lot of work */ 
static void do_work(void)
{
#ifdef BUILD_ARM_BB
    long max_count = 1000000; 
#endif
#ifdef BUILD_X86_HOST
    long max_count = 400000000; 
#endif
#ifdef BUILD_X86_64_HOST
    long max_count = 200000000; 
#endif
#ifdef BUILD_X86_MAC_HOST
    long max_count = 200000000; 
#endif
    long i; int x, y; 
    for (i = 0; i < max_count; i++)
    {
       x = 2; 
       y = 3*x - 12; 
    }
}

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

static void do_sleep(void)
{
#ifdef BUILD_X86_WIN_HOST
    Sleep(10); 
#else
    do_work(); // usleep(10000); 
#endif
}

#endif

/* idle task */ 
static void idle_task(void)
{
    while(1)
    {
#ifdef BUILD_ARM_BB
        do_work(); 
#else
        do_sleep(); 
#endif
    }
}

/* si_kernel_init: initialise real-time kernel */ 
void si_kernel_init(void)
{
    /* task_id for idle task */ 
    int task_id_idle; 

    /* kernel is not running yet */ 
    Kernel_Running = 0; 

    /* initialise task module */ 
    task_init(); 

    /* initialise ready list */ 
    ready_list_init(); 

    /* disable interrupts. The interrupts will be 
       enabled when the first task starts */ 
    DISABLE_INTERRUPTS; 

    /* initialise tick handler */ 
    tick_handler_init(); 

    /* initialise time list */ 
    time_list_init(); 

    /* initialise time storage */ 
    time_storage_init(); 

    /* create idle task */ 
    task_id_idle = task_create(idle_task, 
        &Idle_Stack[IDLE_STACK_SIZE-1], 
        IDLE_PRIORITY); 

    /* and insert it into the ready list */
    ready_list_insert(task_id_idle); 

    int_status_init(); 

    setup_int_handler(); 
    enable_timer_interrupts(); 
}

/* fig_begin si_kernel_start */
/* si_kernel_start: start real-time kernel */ 
void si_kernel_start(void)
{
    /* task_id for task with highest priority */ 
    int task_id_highest; 
  
    /* the kernel is running */ 
    Kernel_Running = 1; 

    /* print version information */ 
    console_put_string(SIMPLE_OS_VERSION_STRING); 

    /* get task_id for task with highest priority */ 
    task_id_highest = ready_list_get_task_id_highest_prio(); 

    /* start the task with highest priority */ 
    task_start(task_id_highest); 
}
/* fig_end si_kernel_start */

/* si_task_create: create a task from the 
   function pf, with stack starting at stack_bottom, 
   and having priority priority. */ 
void si_task_create(
    void (*task_function)(void), 
    stack_item *stack_bottom, int priority)
{
    /* task_id for created task */ 
    int task_id; 

    /* disable interrupts if kernel is running */ 
    if (Kernel_Running)
    {
        DISABLE_INTERRUPTS; 
    }

    /* create the task */ 
    task_id = task_create(task_function, stack_bottom, priority); 

    /* and insert it into ready list */ 
    ready_list_insert(task_id); 

    /* call schedule and enable interrupts if kernel 
       is running */ 
    if (Kernel_Running)
    {
        schedule(); 
        ENABLE_INTERRUPTS; 
    }
}

