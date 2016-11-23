@@ This file is part of Simple_OS, a real-time operating system
@@ designed for research and education
@@ Copyright (c) 2003-2013 Ola Dahl

@@ The software accompanies the book Into Realtime, available at
@@ http://theintobooks.com

@@ Simple_OS is free software: you can redistribute it and/or modify
@@ it under the terms of the GNU General Public License as published by
@@ the Free Software Foundation, either version 3 of the License, or
@@ (at your option) any later version.

@@ This program is distributed in the hope that it will be useful,
@@ but WITHOUT ANY WARRANTY; without even the implied warranty of
@@ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
@@ GNU General Public License for more details.

@@ You should have received a copy of the GNU General Public License
@@ along with this program.  If not, see <http://www.gnu.org/licenses/>.

.text
        .global context_switch_int

@ fig_begin context_switch_int
context_switch_int:
        @ save lr
        stmfd sp!, {lr}
        @ save r3
        stmfd sp!, {r3}
        @ save r0 and r1
        stmfd sp!, {r0, r1}
        @ get stack pointer saved by interrupt handler
        bl int_status_get_saved_stack_pointer
        @ store this stack pointer in r3
        mov r3, r0
        @ restore r0 and r1
        ldmfd sp!, {r0, r1}
        @ copy r3 to address referred to by
        @ first parameter
        str r3, [r0]
        @ restore r3
        ldmfd sp!, {r3}

        @ clear interrupt active flag
        bl int_status_clear_interrupt_active

        @ restore lr 
        ldmfd sp!, {lr}

        @ switch stack, copying new stack
        @ pointer in second parameter to sp
        mov sp, r1
        @ restore registers
        ldmfd sp!, {r0-r12, r14}
        @ save r0 on stack
        stmfd sp!, {r0}
        @ load r0 with cpsr for task
        ldr r0, [sp, #4]
        @ store r0 value in spsr  
        msr spsr, r0
        @ restore r0 from stack
        ldmfd sp!, {r0}
        @ make sp refer to start address of task
        add sp, sp, #4
        @ restore pc, and restore cpsr from spsr
        ldmfd sp!, {pc}^
@ fig_end context_switch_int
