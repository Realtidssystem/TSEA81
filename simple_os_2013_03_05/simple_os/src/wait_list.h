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

#ifndef WAIT_LIST_H
#define WAIT_LIST_H

void wait_list_reset(int wait_list[], int length); 

/* wait_list_insert: inserts task_id in wait_list */ 
void wait_list_insert(int wait_list[], int length, int task_id); 

int wait_list_is_empty(int wait_list[], int length); 

int wait_list_remove_highest_prio(int wait_list[], int length); 

int wait_list_remove_one(int wait_list[], int length); 

#endif
