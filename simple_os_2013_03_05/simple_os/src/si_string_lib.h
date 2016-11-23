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

#ifndef SI_STRING_LIB
#define SI_STRING_LIB

void si_string_copy(char *destination, char *source); 

int si_string_length(char *string); 

int si_string_compare(char *first, char *second); 

/* si_insert_string: look for first occurence of %s, replace it with replace_string */ 
void si_insert_string(char *string, char *replace_string); 

/* si_insert_int_as_hex_string: look for first occurence of %x, replace it with 
   value as a hex string */ 
void si_insert_int_as_hex(char *string, int value); 

#endif
