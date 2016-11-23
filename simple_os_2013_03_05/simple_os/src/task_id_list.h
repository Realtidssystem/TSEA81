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

#ifndef TASK_ID_LIST_H
#define TASK_ID_LIST_H

#define TASK_ID_INVALID -1

/* task_id_list_reset: reset all elements in task_id_list, assuming 
   the length of task_id_list is length */ 
void task_id_list_reset(int task_id_list[], int length); 

/* task_id_list_insert: insert task_id in task_id_list */ 
void task_id_list_insert(
    int task_id_list[], int length, int task_id); 

/* task_id_list_remove: remove task_id from task_id_list */ 
void task_id_list_remove(
    int task_id_list[], int length, int task_id); 

int task_id_list_is_empty(int task_id_list[], int length); 

int task_id_list_remove_first(int task_id_list[], int length); 

#endif
