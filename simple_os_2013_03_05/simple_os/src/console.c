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

#include "console.h"

#if defined BUILD_X86_HOST || BUILD_X86_64_MAC_HOST

#include <stdio.h>

#endif 

#if defined BUILD_X86_FD_TARGET || defined BUILD_I386_FD_TARGET 

#include "screen_output.h"

#endif 

#ifdef BUILD_ARM_BB

#define UART_THR_ADDR 0x49020000
#define UART_RHR_ADDR 0x49020000
#define UART_LSR_ADDR 0x49020014

volatile unsigned char * const UART_THR = (unsigned char *) UART_THR_ADDR; 
volatile unsigned char * const UART_RHR = (unsigned char *) UART_RHR_ADDR; 
volatile unsigned char * const UART_LSR = (unsigned char *) UART_LSR_ADDR; 

#define LSR_TX_FIFO_E 0x20
#define LSR_RX_FIFO_E 0x01

#endif

#ifdef BUILD_ARM_RPB_A8

#define UART_THR_ADDR 0x10009000
#define UART_RHR_ADDR 0x49020000
#define UART_LSR_ADDR 0x49020014

volatile unsigned char * const UART_THR = (unsigned char *) UART_THR_ADDR; 
volatile unsigned char * const UART_RHR = (unsigned char *) UART_RHR_ADDR; 
volatile unsigned char * const UART_LSR = (unsigned char *) UART_LSR_ADDR; 

#define LSR_TX_FIFO_E 0x20
#define LSR_RX_FIFO_E 0x01

#endif

#if defined BUILD_X86_HOST || defined BUILD_X86_64_MAC_HOST

void console_put_char(char c)
{
    putchar(c); 
}

#endif 

#if defined BUILD_X86_FD_TARGET || defined BUILD_I386_FD_TARGET 

static int Current_Row; 
static int Current_Col; 

#define MAX_ROW N_SCREEN_ROWS
#define MAX_COL N_SCREEN_COLS

void console_put_char(char c)
{
    if (c !='\n')
    {
        print_char(Current_Row, Current_Col, c); 
    }
    Current_Col++; 
    if (Current_Col >= MAX_COL)
    {    
        Current_Col = 0; 
        Current_Row++; 
        if (Current_Row >= MAX_ROW)
	{
            Current_Row = 0; 
	}
    }
}

#endif 

#ifdef BUILD_ARM_BB

void console_put_char(char c)
{
    while (((*UART_LSR) & LSR_TX_FIFO_E) == 0)
    {
        // do nothing (yet, perhaps add timeout later)
    }
    *UART_THR = c; 
}

int console_get_char(char *c)
{
    if (((*UART_LSR) & LSR_TX_FIFO_E) == LSR_TX_FIFO_E)
    {
        *c = *UART_RHR; 
        return 0; 
    }
    else
    {
        *c = '\0'; // any value could do here
	return -1; // no data available
    }
}

#endif 

#ifdef BUILD_ARM_RPB_A8

void console_put_char(char c)
{
    *UART_THR = c; 
}

int console_get_char(char *c)
{
    if (((*UART_LSR) & LSR_TX_FIFO_E) == LSR_TX_FIFO_E)
    {
        *c = *UART_RHR; 
        return 0; 
    }
    else
    {
        *c = '\0'; // any value could do here
	return -1; // no data available
    }
}

#endif 

void console_put_string(const char *s) 
{
#if defined BUILD_X86_FD_TARGET || defined BUILD_I386_FD_TARGET 
    Current_Row = 12; 
    Current_Col = 20; 
#endif
    while(*s != '\0') 
    { 
        console_put_char(*s); 
        s++; 
    }
#ifdef BUILD_ARM_BB
    if (*(s-1) == '\n')
    {
        console_put_char('\r'); 
    }
#endif
}

static char hex_chars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 

void console_put_hex(int number)
{
    console_put_char(' '); 
    console_put_char('0'); 
    console_put_char('x'); 
    console_put_char(hex_chars[(number & 0xF0000000) >> 28]); 
    console_put_char(hex_chars[(number & 0x0F000000) >> 24]); 
    console_put_char(hex_chars[(number & 0x00F00000) >> 20]); 
    console_put_char(hex_chars[(number & 0x000F0000) >> 16]); 
    console_put_char(hex_chars[(number & 0x0000F000) >> 12]); 
    console_put_char(hex_chars[(number & 0x00000F00) >> 8]); 
    console_put_char(hex_chars[(number & 0x000000F0) >> 4]); 
    console_put_char(hex_chars[(number & 0x0000000F)]); 
    console_put_char(' '); 
}


void console_put_mem(mem_address start_address)
{
    int *mem_ref = (int *) start_address; 
    int i; 
    console_put_string("mem from address: "); 
    console_put_hex(start_address); 
    for (i = 0; i < 15; i++)
    {    
	if (i == 13 || i == 14)
	{
            console_put_string("m"); 
    	    console_put_char((char) (i + '0')); 
   	    console_put_string(": "); 
            console_put_hex(*mem_ref); 
	}
        mem_ref++; 
    }
    console_put_string("\n"); 
}

#ifdef BUILD_ARM_BB
int get_cpsr(void); 

void console_put_cpsr(void)
{
    int cpsr_value = get_cpsr(); 
    console_put_hex(cpsr_value); 
}
#endif
