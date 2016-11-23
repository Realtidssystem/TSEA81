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

swi_vector:     
        ldr pc, [pc, #24]

.global setup_swi_handler

setup_swi_handler:
.ifdef BUILD_ARM_BB
        stmfd sp!, {r1-r3}
        ldr r1, =0x4020FFCC
        ldr r2, =swi_vector
        ldr r3, [r2]
        str r3, [r1]
        ldr r1, =0x4020FFEC
        str r0, [r1]
        ldmfd sp!, {r1-r3}
.endif
        mov pc, lr

int_vector:     
        ldr pc, [pc, #24]

.global setup_int_handler

setup_int_handler:
.ifdef BUILD_ARM_BB
        ldr r0, =0x4020FFDC
        ldr r1, =int_vector
        ldr r2, [r1]
        str r2, [r0]
        ldr r0, =0x4020FFFC
        ldr r1, =int_handler
        str r1, [r0]
.endif
        mov pc, lr

        .set    MODE_SUPERVISOR, 0x13
        
@ fig_begin int_handler
@ fig_begin int_handler_parts_one
int_handler:
@ fig_end int_handler_parts_one
@ fig_begin int_handler_parts_one
        @ ...
@ fig_end int_handler_parts_one
        @ adjust lr (needed in IRQ)
        sub lr,lr,#4
@ fig_begin int_handler_parts_one
        @ store lr and spsr on supervisor mode stack
        srsdb   sp!, #MODE_SUPERVISOR
        @ change mode to supervisor mode
        cps     #MODE_SUPERVISOR
@ fig_end int_handler_parts_one
@ fig_begin int_handler_parts_one
        @ ...
@ fig_end int_handler_parts_one
        @ save r0 and r1 on stack
        stmfd sp!, {r0, r1}
        @ swap previously stored lr and spsr
        ldr r0, [sp, #8]
        ldr r1, [sp, #12]
        str r0, [sp, #12]
        str r1, [sp, #8]
        @ restore r0 and r1
        ldmfd sp!, {r0, r1}

@ fig_begin int_handler_parts_one
        @ save registers
        stmfd sp!, {r0-r12, r14}
@ fig_end int_handler_parts_one
@ fig_begin int_handler_parts_one
        @ ...
@ fig_end int_handler_parts_one

        @ save lr 
        stmfd sp!, {lr}
        @ put sp in r0
        mov r0, sp
        @ add to r0, so that sp before lr was saved is
        @ passed as parameter to subroutine
        add r0, r0, #4
@ fig_begin int_handler_parts_one
        @ call routine which stores away sp
        bl int_status_save_stack_pointer
        @ set interrupt active flag
        bl int_status_set_interrupt_active
@ fig_end int_handler_parts_one

@ fig_begin int_handler_parts_two
        @ clear interrupt (timer - should be moved!)
        ldr r0, =0x48318018
        ldr r1, =0x00000011
        str r1, [r0]
        ldr r0, =0x48318018
        ldr r1, [r0]
@ fig_end int_handler_parts_two

@ fig_begin int_handler_parts_two
        @ call handler (may lead to context switch)
        bl int_handler_function
@ fig_end int_handler_parts_two

@ fig_begin int_handler_parts_two
        @ acknowledge interrupt 
        ldr r3,=0x48200048
        mov r1,#1
        str r1,[r3]
@ fig_end int_handler_parts_two

@ fig_begin int_handler_parts_three
        @ clear interrupt active flag
        bl int_status_clear_interrupt_active
@ fig_end int_handler_parts_three

@ fig_begin int_handler_parts_three
        @ ...
@ fig_end int_handler_parts_three
        @ restore lr 
        ldmfd sp!, {lr}

@ fig_begin int_handler_parts_three
        @ restore registers
        ldmfd sp!, {r0-r12, r14}
@ fig_end int_handler_parts_three
@ fig_begin int_handler_parts_three
        @ ...
@ fig_end int_handler_parts_three
        @ save r0 on stack
        stmfd sp!, {r0}
@ fig_begin int_handler_parts_three
        @ load r0 with cpsr for task
        ldr r0, [sp, #4]
        @ store r0 value in spsr  
        msr spsr, r0
@ fig_end int_handler_parts_three
@ fig_begin int_handler_parts_three
        @ ...
@ fig_end int_handler_parts_three
        @ restore r0 from stack
        ldmfd sp!, {r0}
        @ make sp refer to start address of task
        add sp, sp, #4
@ fig_begin int_handler_parts_three
        @ restore pc, and restore cpsr from spsr
        ldmfd sp!, {pc}^
@ fig_end int_handler_parts_three
@ fig_end int_handler
