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

#ifndef READY_LIST_H
#define READY_LIST_H

/* ready_list_init: initialise the ready list */ 
void ready_list_init(void); 

/* ready_list_insert: inserts task_id in list of ready-to-run tasks */ 
void ready_list_insert(int task_id); 

/* ready_list_get_task_id_highest_prio: get the task id for the task
   with the highest priority, among the tasks in the ready list */ 
int ready_list_get_task_id_highest_prio(void); 

/* ready_list_remove: removes task_id from the list of ready-to-run tasks */ 
void ready_list_remove(int task_id); 

#endif

