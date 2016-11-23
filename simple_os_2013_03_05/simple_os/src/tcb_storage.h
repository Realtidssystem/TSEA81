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

#ifndef TCB_STORAGE_H
#define TCB_STORAGE_H

#include "tcb.h"

/* maximum number of tasks */ 
#define TCB_LIST_SIZE 20

/* tcb_storage_init: perform initialisation */ 
void tcb_storage_init(void); 

/* tcb_storage_install_tcb: installs tcb */ 
int tcb_storage_install_tcb(task_control_block tcb); 

/* pcb_storage_get_tcb_ref: get reference to TCB with
   task id task_id */ 
task_control_block *tcb_storage_get_tcb_ref(int task_id); 

/* tcb_storage_get_tcb_list_ref: return a reference to the 
   stored TCB list */ 
task_control_block *tcb_storage_get_tcb_list_ref(void); 

/* tcb_storage_get_tcb_list_size: return the length of the 
   stored TCB list */ 
int tcb_storage_get_tcb_list_size(void); 

#endif

