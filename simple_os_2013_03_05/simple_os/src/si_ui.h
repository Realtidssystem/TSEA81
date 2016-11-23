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

#ifndef SI_UI_H
#define SI_UI_H

#define SI_UI_MAX_MESSAGE_SIZE 1000

/* si_ui_init: initialise communication */ 
void si_ui_init(void); 

/* si_ui_draw_begin: initialises a sequence of commands, which shall be given using 
   si_ui_draw_string or si_ui_draw_image */ 
void si_ui_draw_begin(void); 

/* si_ui_draw_end: ends a sequence of commands, and performs the actual sending
   of the commands */ 
void si_ui_draw_end(void); 


/* si_ui_draw_string and si_ui_draw_image prepares for drawing. 
   The functions shall be called after a call to si_ui_draw_begin, 
   and before a call to si_ui_draw_end, which activates the drawing. */ 

/* si_ui_draw_string: prepares for drawing of string at position (x_coord, y_coord) */ 
void si_ui_draw_string(char string[], int x_coord, int y_coord); 

/* si_ui_draw_image: prepares for drawing of image_name at position (x_coord, y_coord) */ 
void si_ui_draw_image(char image_name[], int x_coord, int y_coord); 


/* si_ui_show_error: displays an error message */ 
void si_ui_show_error(char message[]); 

/* si_ui_set_size: sets the size of the GUI window */ 
void si_ui_set_size(int x_size, int y_size); 


/* si_ui_receive: receives a message in message. 
   It is assumed that the message array is of size 
   SI_UI_MAX_MESSAGE_SIZE */ 
void si_ui_receive(char message[]); 

void si_ui_close(void); 

#endif
