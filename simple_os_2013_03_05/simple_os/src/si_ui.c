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

#include "si_ui.h"

#include "simple_os.h"

#include "si_comm.h"

#include "console.h"

#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif

#define SI_UI_MESSAGE_BUFFER_SIZE 10000

/* buffer with messages to send */ 
static char Message_Buffer[SI_UI_MESSAGE_BUFFER_SIZE]; 

/* semaphore to ensure only one task accesses the communication link, 
   during sending and receiving */ 
static si_semaphore Si_Ui_Mutex; 

/* position where to start writing the next message into the buffer */ 
static int Message_Pos; 

/* string where temporary strings are stored before sending */ 
static char Message_String[SI_UI_MAX_MESSAGE_SIZE]; 

/* command delimiter, which must be used also in the GUI client */ 
static char Command_Delim; 

/* si_ui_init: initialise communication */ 
void si_ui_init(void)
{
    Command_Delim = ';'; 
    /* open communication channel */ 
    si_comm_open(); 
    /* initialise message buffer semaphore */ 
    si_sem_init(&Si_Ui_Mutex, 1); 
    /* start writing at the beginning of the message buffer */
    Message_Pos = 0; 
}

static void remove_trailing_command_delim(char buffer [])
{
    int len; 
    len = si_string_length(buffer); 
    if (buffer[len-1] == Command_Delim)
    {
        buffer[len-1] = '\0'; 
    }
}

/* send_buffer: sends the contents of the message buffer 
   NOTE: it is assumed that the buffer is reserved when this function 
   is called */ 
static void send_buffer(void)
{
    int si_comm_return_value; 

    int n_tries; 
    const int max_n_tries = 10000; 
    const int delay_ms_between_tries = 100; 

    remove_trailing_command_delim(Message_Buffer); 

    n_tries = 0; 

    do
    {
        /* write message buffer contents to communication channel */ 
        si_comm_return_value = si_comm_write(Message_Buffer); 

        n_tries++; 

        /* wait and let other tasks try if writing is not ok */ 
        if (si_comm_return_value != SI_COMM_OK)
        {
            /* release buffer, wait a while, and then reserve buffer again */ 
            si_sem_signal(&Si_Ui_Mutex); 
            si_wait_n_ms(delay_ms_between_tries); 
            si_sem_wait(&Si_Ui_Mutex); 
        }
    } while (n_tries < max_n_tries && si_comm_return_value != SI_COMM_OK); 

    if (si_comm_return_value != SI_COMM_OK)
    {
        console_put_string("si_ui: NOTE: communication problem - number of write tries"); 
        console_put_hex(n_tries); 
        console_put_string("\n"); 
    }
}

/* append_to_buffer: appends message to the message buffer */ 
static void append_to_buffer(char message[])
{
#if defined BUILD_X86_HOST || defined BUILD_X86_64_HOST
    size_t i; 
#endif
#ifdef BUILD_ARM_BB
    int i; 
#endif
    int buffer_full = 0; 

    for (i = 0; i < si_string_length(message) && !buffer_full; i++)
    {
        Message_Buffer[Message_Pos] = message[i]; 
        Message_Pos++; 
        /* check if we are overflowing the buffer */ 
        if (Message_Pos >= SI_UI_MESSAGE_BUFFER_SIZE - 1)
        {
            console_put_string("NOTE: message buffer OVERFLOW\n"); 
            /* add string terminator */    
            Message_Buffer[Message_Pos] = '\0'; 
            buffer_full = 1; 
            /* reset buffer, so that next write is from the buffer start position */ 
            Message_Pos = 0; 
        }
    }

    if (!buffer_full)
    {
        /* add command delimiter */ 
        Message_Buffer[Message_Pos] = Command_Delim; 
        Message_Pos++; 
        /* add string terminator, in case no more strings are addded to the buffer */ 
        Message_Buffer[Message_Pos] = '\0'; 
        // printf("MB: %s\n", Message_Buffer); 
    }
}

void si_ui_draw_begin(void)
{
    si_sem_wait(&Si_Ui_Mutex); 

    /* start from the beginning */ 
    Message_Pos = 0; 
        
    append_to_buffer("draw_begin"); 

    si_sem_signal(&Si_Ui_Mutex); 
}

void si_ui_draw_end(void)
{
    si_sem_wait(&Si_Ui_Mutex); 

    append_to_buffer("draw_end"); 

    /* add a string containing only a newline, to keep the Java client happy, 
       NOTE: this may need to change, if problems occur e.g. when using a mix of 
       Windows and Linux */ 
    append_to_buffer("\n"); 

    /* send the buffer */ 
    send_buffer(); 

    si_sem_signal(&Si_Ui_Mutex); 
}

void si_ui_draw_string(char string[], int x_coord, int y_coord)
{
    si_sem_wait(&Si_Ui_Mutex); 

    si_string_copy(Message_String, "draw_string:%x:%x:%s"); 
    si_insert_int_as_hex(Message_String, x_coord); 
    si_insert_int_as_hex(Message_String, y_coord); 
    si_insert_string(Message_String, string); 

    append_to_buffer(Message_String); 

    si_sem_signal(&Si_Ui_Mutex); 
}
     
void si_ui_draw_image(char image_name[], int x_coord, int y_coord)
{
    si_sem_wait(&Si_Ui_Mutex); 

    si_string_copy(Message_String, "draw_image:%s:%x:%x"); 
    si_insert_string(Message_String, image_name); 
    si_insert_int_as_hex(Message_String, x_coord); 
    si_insert_int_as_hex(Message_String, y_coord); 

    append_to_buffer(Message_String); 

    si_sem_signal(&Si_Ui_Mutex); 
}


void si_ui_show_error(char message[])
{
    si_ui_draw_begin(); 

    si_sem_wait(&Si_Ui_Mutex); 

    si_string_copy(Message_String, "show_error:%s"); 
    si_insert_string(Message_String, message); 

    append_to_buffer(Message_String); 

    si_sem_signal(&Si_Ui_Mutex); 

    si_ui_draw_end(); 
}

void si_ui_set_size(int x_size, int y_size)
{
    si_ui_draw_begin(); 

    si_sem_wait(&Si_Ui_Mutex); 

    si_string_copy(Message_String, "set_size:%x:%x"); 
    si_insert_int_as_hex(Message_String, x_size); 
    si_insert_int_as_hex(Message_String, y_size); 

    append_to_buffer(Message_String); 

    si_sem_signal(&Si_Ui_Mutex); 

    si_ui_draw_end(); 
}

void si_ui_receive(char message[])
{
    int si_comm_return_value; 

    int n_tries; 

    const int max_n_tries = 10000; 
    const int delay_ms_between_tries = 250; 

    n_tries = 0; 

    si_sem_wait(&Si_Ui_Mutex); 

    do
    {
        si_comm_return_value = si_comm_read(message, SI_UI_MAX_MESSAGE_SIZE); 

        n_tries++; 

        /* wait and let other tasks try if reading is not ok */ 
        if (si_comm_return_value != SI_COMM_OK)
        {
            si_sem_signal(&Si_Ui_Mutex); 
            si_wait_n_ms(delay_ms_between_tries); 
            si_sem_wait(&Si_Ui_Mutex); 
        }
    } while (n_tries < max_n_tries && si_comm_return_value != SI_COMM_OK); 

    if (si_comm_return_value != SI_COMM_OK)
    {
        console_put_string("si_ui: NOTE: communication problem - number of read tries"); 
        console_put_hex(n_tries); 
        console_put_string("\n"); 
    }

    si_sem_signal(&Si_Ui_Mutex); 
}

void si_ui_close(void)
{
    si_comm_close(); 
}
