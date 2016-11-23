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

#ifndef TCB_MESSAGE_H
#define TCB_MESSAGE_H

#include "task_message.h"
#include "tcb_storage.h"

#define WAIT_LIST_SIZE TCB_LIST_SIZE

#define MESSAGE_LIST_SIZE 2

/* data type for messages, associated to each TCB */ 
typedef struct
{
    /* task_id for receiving task */ 
    int receive_task_id; 
    /* flag to indicate if the receiving task 
       is waiting */ 
    int receive_task_id_is_waiting; 

    /* wait list for sending tasks */
    int wait_list_send[WAIT_LIST_SIZE]; 

    /* buffered messages */ 
    task_message_type message_buffer[MESSAGE_LIST_SIZE]; 

    /* positions for reading and writing buffered 
       messages */ 
    int read_pos; 
    int write_pos; 

    /* number of buffered messages */ 
    int count; 
} tcb_message_type; 

void tcb_message_init(tcb_message_type *tcb_message); 

void tcb_message_set_receive_task_id(tcb_message_type *tcb_message, int receive_task_id); 

void tcb_message_write(
    tcb_message_type *tcb_message, 
    const char message_data[], int length, int send_task_id); 

void tcb_message_read(
    tcb_message_type *tcb_message, 
    char message_data[], int *length, int *send_task_id); 

#endif

