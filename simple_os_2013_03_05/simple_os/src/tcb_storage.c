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

#include "tcb_storage.h"

#include "tcb.h"
#include "tcb_list.h"

/* fig_begin tcb_list */ 
/* the list of TCBs for all created tasks */ 
static task_control_block TCB_List[TCB_LIST_SIZE]; 
/* fig_end tcb_list */ 

void tcb_storage_init(void)
{
    tcb_list_reset(TCB_List, TCB_LIST_SIZE); 
}

int tcb_storage_install_tcb(task_control_block tcb)
{
    return tcb_list_insert(TCB_List, TCB_LIST_SIZE, tcb); 
}

task_control_block *tcb_storage_get_tcb_ref(int task_id) 
{
    return &TCB_List[task_id]; 
}

task_control_block *tcb_storage_get_tcb_list_ref(void)
{
    return &TCB_List[0]; 
}

int tcb_storage_get_tcb_list_size(void)
{
    return TCB_LIST_SIZE; 
}


