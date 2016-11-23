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

#include "si_message.h"

#include "task_message.h"
#include "tcb_message.h"
#include "tcb_storage.h"
#include "interrupt.h"
#include "task.h"

/* message data for each TCB */ 
static tcb_message_type TCB_Message_List[TCB_LIST_SIZE]; 

/* si_message_init: initialisation of message 
   handling */ 
void si_message_init(void)
{
    int i; 
    for (i = 0; i < TCB_LIST_SIZE; i++)
    {
        tcb_message_init(&TCB_Message_List[i]); 
        tcb_message_set_receive_task_id(&TCB_Message_List[i], i); 
    }
}

void si_message_send(
    const char message[], int length, int receive_task_id)
{
    tcb_message_type* tcb_message; 
    int send_task_id; 

    DISABLE_INTERRUPTS; 
    send_task_id = task_get_task_id_running(); 
    tcb_message = &TCB_Message_List[receive_task_id]; 
    tcb_message_write(tcb_message, message, length, send_task_id); 
    ENABLE_INTERRUPTS; 
}


void si_message_receive(
    char message[], int *length, int *send_task_id)
{
    tcb_message_type* tcb_message; 
    int receive_task_id; 

    DISABLE_INTERRUPTS; 
    receive_task_id = task_get_task_id_running(); 
    tcb_message = &TCB_Message_List[receive_task_id]; 
    tcb_message_read(tcb_message, message, length, send_task_id); 
    ENABLE_INTERRUPTS; 
}

