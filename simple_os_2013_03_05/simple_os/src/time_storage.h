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

#ifndef TIME_STORAGE_H
#define TIME_STORAGE_H

#include "si_time_type.h"

/* time_storage_set_ms_per_tick: sets number of 
   milliseconds in one tick */ 
void time_storage_set_ms_per_tick(int ms_per_tick); 

/* time_storage_get_ms_per_tick: returns number of 
   milliseconds in one tick */ 
int time_storage_get_ms_per_tick(void); 

/* time_storage_register_tick: registers a tick, 
   e.g. for the purpose of keeping track of the 
   current time */ 
void time_storage_register_tick(void); 

/* time_storage_get_current_time: returns the current 
   time in *time */ 
void time_storage_get_current_time(si_time *time); 

/* time_storage_init: performs initialisation */ 
void time_storage_init(void); 

#endif 
