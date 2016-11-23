#include "barb_draw.h"

#include <stdio.h>

/* draw_barber_shop: makes a graphical printout of the barbershop,
   its customers in the chairs, and all waiting customers */

static char Barber_Shop_Array[2][N_CHAIRS]; 

void draw_barber_shop(barber_shop_type barber_shop)
{
    int i;
    int j; 

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < N_CHAIRS; j++)
        {
            Barber_Shop_Array[i][j] = ' '; 
        }
    }

    for (j = 0; j < N_CHAIRS; j++)
    {
        if (barber_shop->free_chair[j])
        {
            /* F for free, B for busy */ 
            Barber_Shop_Array[0][j] = 'F'; 
        }
        else
        {
            Barber_Shop_Array[0][j] = 'B'; 
            Barber_Shop_Array[1][j] = (char) barber_shop->time_left[j] + '0'; 
        }
    }

    if (barber_shop->barber_sleeping)
    {
        printf("   "); 
    }
    printf("A barber shop with "); 
    printf("%d waiting customers and a ", barber_shop->n_waiting); 
    if (barber_shop->barber_sleeping)
    {
        printf("sleeping barber\n"); 
    }
    else
    {
        printf("barber which is awake\n"); 
    }

    printf("------------------------------------------------------------------\n"); 
    for (i = 0; i < 2; i++)
    {
        printf("                        "); 
        for (j = 0; j < N_CHAIRS; j++)
        {
            printf("-%c-", Barber_Shop_Array[i][j]); 
        }
        printf("\n"); 
    }
    printf("\n"); 
    fflush(stdout); 
}
