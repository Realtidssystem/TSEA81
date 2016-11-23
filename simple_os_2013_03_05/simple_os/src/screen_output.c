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

#include "screen_output.h"

#define VIDEO_BASE 0xB8000

/* print_char: prints character ch at row row_index
   and column col_index */ 
void print_char(int row_index, int col_index, char ch) 
{ 
    /* offset in video memory */ 
    int video_offset; 

    /* define a char pointer to video memory */ 
    char *video_array = (char *) VIDEO_BASE; 

    /* compute offset in video memory */ 
    video_offset = row_index*N_SCREEN_COLS + col_index; 
    video_offset *= 2; /* account for attribute byte */ 

    /* print the character */ 
    video_array[video_offset] = ch; 
}

/* print_string: prints string str at row row_index, 
   starting at column start_col_index */ 
void print_string(
    int row_index, int start_col_index, 
    const char str[]) 
{
    /* position in string */ 
    int pos = 0; 
    /* character to print */ 
    char ch = str[pos]; 
    /* column index */ 
    int col_index = start_col_index; 

    /* loop until null character is found */ 
    while (ch != '\0')
    {
        if (ch != '\n')
	{
            print_char(row_index, col_index, ch); 
        }
        pos++; 
        ch = str[pos]; 
        col_index++; 
    }
    
    /* fill remaining part of the line with blanks */ 
    while(col_index < N_SCREEN_COLS)
    {
        print_char(row_index, col_index, ' '); 
        col_index++; 
    }
}
