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

#include "task_id_list.h"

void task_id_list_reset(int task_id_list[], int length)
{
    int i; 
    /* reset all elements */ 
    for (i = 0; i < length; i++) 
    {
        task_id_list[i] = TASK_ID_INVALID; 
    }
}

void task_id_list_insert(
    int task_id_list[], int length, int task_id)
{
    /* loop counter */ 
    int i; 
    /* flag to indicate if a free index in task_id_list 
       is found */ 
    int found = 0; 
    /* look for first invalid element, assuming 
       it exists */ 
    for (i = 0; i < length && !found; i++)
    {
        if (task_id_list[i] == TASK_ID_INVALID)
        {
            task_id_list[i] = task_id; 
            found = 1; 
        }
    }
}

void task_id_list_remove(
    int task_id_list[], int length, int task_id)
{
    int i; 
    int found = 0; 
    int found_index = length; 
    /* look for task_id in task_id_list */ 
    for (i = 0; i < length && !found; i++) 
    {
        if (task_id_list[i] == task_id)
        {
            found = 1; 
            found_index = i; 
        }
    }
    /* shift all elements from found_index up to the last but one item in task_id_list */ 
    for (i = found_index; i < length-1; i++)
    {
        task_id_list[i] = task_id_list[i+1]; 
    }
    /* mark last item as invalid */ 
    task_id_list[length-1] = TASK_ID_INVALID; 
}

static int task_id_list_n_items(
    int task_id_list[], int length)
{
    int n_items = 0; 
    int i; 
    for (i = 0; i < length; i++)
    {
	if (task_id_list[i] != TASK_ID_INVALID)
	{
	    n_items++; 
	}
    }
    return n_items; 
}

int task_id_list_is_empty(int task_id_list[], int length)
{
    return task_id_list_n_items(task_id_list, length) == 0; 
}

int task_id_list_remove_first(int task_id_list[], int length)
{
    /* the removed task_id */ 
    int task_id_removed; 

    /* loop counter */ 
    int i; 

    /* get first task_id */ 
    task_id_removed = task_id_list[0]; 

    /* shift all elements up to the last but one item */ 
    for (i = 0; i < length-1; i++)
    {
	task_id_list[i] = task_id_list[i+1]; 
    }

    /* mark last item as invalid */ 
    task_id_list[length-1] = TASK_ID_INVALID; 

    /* return removed task_id */
    return task_id_removed; 
}


