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

#ifndef SI_TIME_TYPE_H
#define SI_TIME_TYPE_H

/* data type for time */ 
typedef struct
{
    int n_sec; /* number of seconds */ 
    int n_ms;  /* number of milliseconds */ 
} si_time;

/* si_time_set: sets n_sec and n_ms in *time */ 
void si_time_set(si_time *time, int n_sec, int n_ms); 

/* si_time_add_n_ms: adds n_ms milliseconds 
   to *time */ 
void si_time_add_n_ms(si_time *time, int n_ms); 

/* si_time_add_n_sec: adds n_sec seconds 
   to *time */ 
void si_time_add_n_sec(si_time *time, int n_sec); 

/* si_time_diff_n_ms: returns the difference between 
   *time_1 and *time_2, expressed in milliseconds */ 
int si_time_diff_n_ms(si_time *time_1, si_time *time_2); 

#endif  

