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

#include "task_message.h"

#include "task_id_list.h"

void message_init(task_message_type *message)
{
    int i; 

    for (i = 0; i < MAX_MESSAGE_LENGTH; i++)
    {
	message->message_data[i] = '\0'; 
    }
    message->length = 0; 
    message->send_task_id = TASK_ID_INVALID; 
}

void message_write(
    task_message_type *message, 
    const char message_data[], int length, int send_task_id)
{
    int i; 
    int n_chars_to_write; 
    
    if (length > MAX_MESSAGE_LENGTH)
    {
	n_chars_to_write = MAX_MESSAGE_LENGTH; 
    }
    else
    {
	n_chars_to_write = length; 
    }
 

    for (i = 0; i < n_chars_to_write; i++)
    {
	message->message_data[i] = message_data[i]; 
    }
    message->length = n_chars_to_write; 
    message->send_task_id = send_task_id; 
}

void message_read(
     task_message_type *message, 
     char message_data[], int *length, int *send_task_id)
{
    int i; 

    for (i = 0; i < message->length; i++)
    {
	message_data[i] = message->message_data[i]; 
    }
    *length = message->length; 
    *send_task_id = message->send_task_id; 
}

