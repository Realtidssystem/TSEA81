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

#include "time_storage.h"

#include "si_time_type.h"

static int Ms_Per_Tick = 1; 

static si_time Current_Time; 

static int N_Ticks = 0; 

#define MAX_N_TICKS 0x8FFFFFFF

void time_storage_set_ms_per_tick(int ms_per_tick)
{
    Ms_Per_Tick = ms_per_tick; 
}

int time_storage_get_ms_per_tick(void)
{
    return Ms_Per_Tick; 
}

void time_storage_register_tick(void)
{
    N_Ticks++; 
    if (N_Ticks == MAX_N_TICKS)
    {
	N_Ticks = 0; 
    }
    si_time_add_n_ms(&Current_Time, Ms_Per_Tick); 
}

void time_storage_get_current_time(si_time *time)
{
    *time = Current_Time; 
}

void time_storage_init(void)
{
    si_time_set(&Current_Time, 0, 0); 
}

