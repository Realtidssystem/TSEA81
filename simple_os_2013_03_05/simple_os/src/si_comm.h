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

#ifndef SI_COMM_H
#define SI_COMM_H

#define SI_COMM_OK 0

/* si_comm_open: opens the communication */ 
void si_comm_open(void); 

/* si_comm_read: reads a message, and stores it in 
   message_data as a null-terminated string. 
   Returns SI_COMM_OK if reading was ok. */  
int si_comm_read(char message_data[], int message_data_size); 

/* si_comm_write: writes a message, defined as a 
   null-terminated string, stored in message_data. 
   Returns SI_COMM_OK if writing was ok. */ 
int si_comm_write(const char message_data[]); 

/* si_comm_close: closes the communication */ 
void si_comm_close(void); 

#endif 
