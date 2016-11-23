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

#ifndef SI_MESSAGE_H
#define SI_MESSAGE_H

#include "task_message.h"

#define MESSAGE_LENGTH MAX_MESSAGE_LENGTH

void si_message_init(void); 

/* si_message_send: sends message, with length 
   characters, to task with task_id receive_task_id, 
   using an internal buffer. 
   The calling task will wait if the buffer 
   is full. */
void si_message_send(
    const char message[], int length, int receive_task_id); 

/* si_message_receive: receives message, with *length
   characters, from task with task_id *send_task_id, 
   using an internal buffer. 
   The calling task will wait if the buffer 
   is empty. */
void si_message_receive(
    char message[], int *length, int *send_task_id); 

#endif

