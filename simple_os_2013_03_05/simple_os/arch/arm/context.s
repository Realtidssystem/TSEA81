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
        .global context_restore

@ fig_begin context_restore
@ fig_begin context_restore_small
context_restore:
        @ copy parameter value to sp  
        mov sp, r0
        @ restore registers from stack
        ldmfd sp!, {r0-r12, r14}
@ fig_end context_restore
        @ ...
@ fig_end context_restore_small
.ifdef BUILD_ARM_BB
@ fig_begin context_restore
        @ save r0 on stack
        stmfd sp!, {r0}
@ fig_begin context_restore_small
        @ load r0 with cpsr for task
        ldr r0, [sp, #4]
        @ store r0 value in spsr  
        msr spsr, r0
@ fig_end context_restore
        @ ...
@ fig_end context_restore_small
@ fig_begin context_restore
        @ restore r0 from stack
        ldmfd sp!, {r0}
        @ make sp refer to start address of task
        add sp, sp, #4
@ fig_begin context_restore_small
        @ restore pc, and restore cpsr from spsr
        ldmfd sp!, {pc}^
@ fig_end context_restore_small
@ fig_end context_restore
.else
        ldmfd sp!, {pc}
.endif
        
        .global context_switch

@ fig_begin context_switch
@ fig_begin context_switch_small
context_switch:
@ fig_end context_switch
        @ ... 
@ fig_end context_switch_small
@ fig_begin context_switch
        @ save link register
        stmfd sp!, {lr}
@ fig_end context_switch
.ifdef BUILD_ARM_BB
@ fig_begin context_switch
        @ save r0 on stack, on a free place
        str r0, [sp, #-8]
@ fig_begin context_switch_small
        @ store spsr in r0
        mrs r0, spsr
        @ save r0 on stack
        stmfd sp!, {r0}
@ fig_end context_switch
        @ ... 
@ fig_end context_switch_small
@ fig_begin context_switch
        @ restore previously saved r0
        ldr r0, [sp, #-4]
@ fig_end context_switch
.endif
@ fig_begin context_switch
        @ save registers
        stmfd sp!, {r0-r12, r14}
        @ copy sp to address referred to by
        @ first parameter
        str sp, [r0]
        @ switch stack, copying new stack
        @ pointer in second parameter to sp
        mov sp, r1
        @ restore registers
        ldmfd sp!, {r0-r12, r14}
@ fig_end context_switch
.ifdef BUILD_ARM_BB
@ fig_begin context_switch
        @ save r0 on stack
        stmfd sp!, {r0}
@ fig_begin context_switch_small
        @ load r0 with cpsr for task
        ldr r0, [sp, #4]
        @ store r0 value in spsr  
        msr spsr, r0
@ fig_end context_switch
        @ ... 
@ fig_end context_switch_small
@ fig_begin context_switch
        @ restore r0 from stack
        ldmfd sp!, {r0}
        @ make sp refer to start address of task
        add sp, sp, #4
@ fig_begin context_switch_small
        @ restore pc, and restore cpsr from spsr
        ldmfd sp!, {pc}^
@ fig_end context_switch_small
@ fig_end context_switch
.else
        ldmfd sp!, {pc}
.endif

        .global context_switch_swi


@ fig_begin context_switch_swi
context_switch_swi:
        @ save lr on stack
        stmfd sp!, {lr}
        @ do the software interrupt
        svc 0x10
        @ restore lr
        ldmfd sp!, {lr}
        @ return to caller
        bx lr
@ fig_end context_switch_swi



