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

#include "task.h"

#include "arch_types.h"
#include "tcb.h"
#include "tcb_storage.h"
#include "context.h"
#include "exceptions.h"
#include "console.h"
#include "int_status.h"
#include "interrupt.h"

/* the running task */ 
static int Task_Id_Running; 

void task_init(void)
{
    /* initialise list of all TCBs */ 
    tcb_storage_init(); 
#ifdef BUILD_ARM_BB
    setup_swi_handler((mem_address) context_switch); 
#endif
    Task_Id_Running = -1; 
}

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

static void enable_int_function(void)
{
    ENABLE_INTERRUPTS; 
}

#endif

/* fig_begin prepare_stack_arm */ 
static void prepare_stack(
    stack_item *stack, mem_address *sp, 
    void (*task_function)(void), 
    int n_saved_registers, int n_bytes_per_register)
{
    int i;
    stack_item *stack_ref; 
    stack_ref = stack; 
/* fig_begin prepare_stack_code_arm */ 
    *stack_ref = (stack_item) task_function; 
/* fig_end prepare_stack_code_arm */ 
/* fig_end prepare_stack_arm */ 
#ifdef BUILD_ARM_BB
/* fig_begin prepare_stack_arm */ 
/* fig_begin prepare_stack_code_arm */ 
    stack_ref--;
    /* store a value of cpsr, interrupts 
       enabled, supervisor mode */ 
    *stack_ref = 0x00000013; 
/* fig_end prepare_stack_code_arm */ 
/* fig_end prepare_stack_arm */ 
#endif 
#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST
    stack_ref--; 
    *stack_ref = (stack_item) enable_int_function; 
#endif
/* fig_begin prepare_stack_arm */ 
/* fig_begin prepare_stack_code_arm */ 
    for (i = 0; i < n_saved_registers; i++)
    {
        stack_ref--; 
        *stack_ref = 0; 
    }
/* fig_end prepare_stack_code_arm */ 
    *sp = (mem_address) stack; 
/* fig_end prepare_stack_arm */ 
#ifdef BUILD_ARM_BB
/* fig_begin prepare_stack_arm */ 
    *sp -= 4; 
/* fig_end prepare_stack_arm */ 
#endif
#if defined BUILD_X86_HOST
    *sp -= 4; 
#endif
#if defined BUILD_X86_64_HOST
    *sp -= 8; 
#endif
/* fig_begin prepare_stack_arm */ 
    *sp -= n_saved_registers * n_bytes_per_register; 
}
/* fig_end prepare_stack_arm */ 

int task_create(
    void (*task_function)(void), 
    stack_item *stack_bottom, int priority)
{
    mem_address task_sp;            /* a stack pointer */ 
    int task_id;            /* task id */ 
    task_control_block tcb; /* TCB to be installed */ 

#ifdef BUILD_ARM_BB
    int n_saved_registers = 14; 
    int n_bytes_per_register = 4; 
#endif
#ifdef BUILD_X86_HOST
    int n_saved_registers = 7; 
    int n_bytes_per_register = 4; 
#endif
#ifdef BUILD_X86_64_HOST
    int n_saved_registers = 5; 
    int n_bytes_per_register = 8; 
#endif
#ifdef BUILD_X86_MAC_HOST
    int n_saved_registers = 5; 
    int n_bytes_per_register = 8; 
#endif

    prepare_stack(stack_bottom, &task_sp, task_function, 
		  n_saved_registers, n_bytes_per_register); 

    /* initialise the tcb */ 
    tcb_init(&tcb, task_sp, priority); 

    /* install the tcb */ 
    task_id = tcb_storage_install_tcb(tcb); 

    /* return task id of created task */ 
    return task_id; 
}

int task_get_task_id_running()
{
    return Task_Id_Running; 
}

/* fig_begin task_start */ 
void task_start(int task_id)
{
    /* a pointer to a TCB */ 
    task_control_block *tcb_ref; 

    /* get a pointer to the TCB associated with 
       task identity task_id */ 
    tcb_ref = tcb_storage_get_tcb_ref(task_id); 

    /* set Task_Id_Running to task id of new task */ 
    Task_Id_Running = task_id; 

    /* restore context for the task with this 
       TCB */ 
    context_restore(tcb_ref->stack_pointer); 
}
/* fig_end task_start */ 

/* fig_begin task_switch_soft_kernel */ 
void task_switch(int task_id_old, int task_id_new)
{
    /* a pointer to the old stack pointer */ 
    mem_address *old_stack_pointer; 
    /* the new stack pointer */ 
    mem_address new_stack_pointer; 

    /* pointers to TCB for the two tasks */ 
    task_control_block *old_tcb_ref; 
    task_control_block *new_tcb_ref;

    /* get references to the TCBs */ 
    old_tcb_ref = tcb_storage_get_tcb_ref(task_id_old); 
    new_tcb_ref = tcb_storage_get_tcb_ref(task_id_new);  
   
    /* set pointer to old stack pointer */ 
    old_stack_pointer = &old_tcb_ref->stack_pointer; 
    /* set new stack pointer */ 
    new_stack_pointer = new_tcb_ref->stack_pointer; 

    /* set Task_Id_Running to task id of new task */ 
    Task_Id_Running = task_id_new; 
/* fig_end task_switch_soft_kernel */ 

#ifdef BUILD_ARM_BB
    if (int_status_is_interrupt_active())
    {
        /* task switch from interrupt */ 
        // console_put_string("TS-INT old-new "); 
        // console_put_hex(task_id_old); 
        // console_put_hex(task_id_new); 
        context_switch_int(old_stack_pointer, new_stack_pointer);
    }
    else
    {
        /* task switch using software interrupt */ 
        // console_put_string("TS-SWI old-new "); 
        // console_put_hex(task_id_old); 
        // console_put_hex(task_id_new); 
        /* fig_begin context_switch_swi */ 
        context_switch_swi(old_stack_pointer, new_stack_pointer);
        /* fig_end context_switch_swi */ 
    }
#else
/* fig_begin task_switch_soft_kernel */ 

    /* do the task switch on the host */ 
    context_switch(old_stack_pointer, new_stack_pointer);
/* fig_end task_switch_soft_kernel */ 
#endif
}
