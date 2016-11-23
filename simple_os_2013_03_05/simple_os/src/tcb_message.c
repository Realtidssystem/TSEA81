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

#include "tcb_message.h"

#include "task_message.h"
#include "task_id_list.h"
#include "wait_list.h"
#include "ready_list.h"
#include "schedule.h"

void tcb_message_init(tcb_message_type *tcb_message)
{
    int i; 

    tcb_message->receive_task_id = TASK_ID_INVALID; 
    tcb_message->receive_task_id_is_waiting = 0; 

    wait_list_reset(tcb_message->wait_list_send, WAIT_LIST_SIZE); 

    for (i = 0; i < MESSAGE_LIST_SIZE; i++)
    {
	message_init(&tcb_message->message_buffer[i]); 
    }

    tcb_message->read_pos = 0; 
    tcb_message->write_pos = 0; 
    tcb_message->count = 0; 
}

void tcb_message_set_receive_task_id(tcb_message_type *tcb_message, int receive_task_id)
{
    tcb_message->receive_task_id = receive_task_id; 
}

void tcb_message_write(
    tcb_message_type *tcb_message, 
    const char message_data[], int length, int send_task_id)
{
    while(tcb_message->count == MESSAGE_LIST_SIZE)
    {
	ready_list_remove(send_task_id); 
	wait_list_insert(tcb_message->wait_list_send, WAIT_LIST_SIZE, send_task_id); 
	schedule(); 
    }
    message_write(
        &tcb_message->message_buffer[tcb_message->write_pos], 
	message_data, length, send_task_id); 
    tcb_message->write_pos++; 
    if (tcb_message->write_pos == MESSAGE_LIST_SIZE)
    {
	tcb_message->write_pos = 0; 
    }
    tcb_message->count++; 
    if (tcb_message->receive_task_id_is_waiting)
    {
	ready_list_insert(tcb_message->receive_task_id); 
	tcb_message->receive_task_id_is_waiting = 0; 
	schedule(); 
    }
}

void tcb_message_read(
    tcb_message_type *tcb_message, 
    char message_data[], int *length, int *send_task_id)
{
    int task_id_waiting; 

    while(tcb_message->count == 0)
    {
	ready_list_remove(tcb_message->receive_task_id); 
	tcb_message->receive_task_id_is_waiting = 1; 
	schedule(); 
    }
    message_read(
        &tcb_message->message_buffer[tcb_message->read_pos], 
	message_data, length, send_task_id); 
    tcb_message->read_pos++; 
    if (tcb_message->read_pos == MESSAGE_LIST_SIZE)
    {
	tcb_message->read_pos = 0; 
    }
    tcb_message->count--; 
    if (!wait_list_is_empty(tcb_message->wait_list_send, WAIT_LIST_SIZE))
    {
	task_id_waiting = wait_list_remove_highest_prio(
	    tcb_message->wait_list_send, WAIT_LIST_SIZE); 
	ready_list_insert(task_id_waiting); 
	schedule(); 
    }
}

