## This file is part of Simple_OS, a real-time operating system
## designed for research and education
## Copyright (c) 2003-2013 Ola Dahl

## The software accompanies the book Into Realtime, available at
## http://theintobooks.com

## Simple_OS is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.

## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

.text

.globl context_restore

# fig_begin context_restore
context_restore:
        # copy parameter value to esp  
        movl 4(%esp), %esp
        # restore registers
        popl %ebp
        popl %esi
        popl %edi
        popl %edx
        popl %ecx
        popl %ebx
        popl %eax
        # restore pc
        ret
# fig_end context_restore

.globl context_switch

# fig_begin context_switch
context_switch:
        # save registers
        pushl %eax
        pushl %ebx
        pushl %ecx
        pushl %edx
        pushl %edi
        pushl %esi
        pushl %ebp
        # save esp
        movl %esp, %ebp
        # rewind stack, to find first parameter
        addl $28, %ebp
        # store first parameter in eax
        movl 4(%ebp), %eax
        # copy esp to adress referred to by
        # first parameter
        movl %esp, (%eax)
        # switch stack, copying new stack
        # pointer in second parameter to esp
        movl 8(%ebp), %esp
        # restore registers
        popl %ebp
        popl %esi
        popl %edi
        popl %edx
        popl %ecx
        popl %ebx
        popl %eax
        # restore pc
        ret
# fig_end context_switch
	
	
	