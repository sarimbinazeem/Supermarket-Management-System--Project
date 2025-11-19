#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stock.h"

#define ITEMS 100

Product inventory[ITEMS];
int itemCount=0;

void loadStock()
{
    FILE *fptr = fopen("../data/stock.txt","r");

    if (fptr == NULL)
    {
        printf("Error Opening Stock File! \n");
        return;
    }

    itemCount =0; //Added So That Each Time ItemCount starts from 0 

    //Take Stock from Stock File Until it is the End Of File And Store it Inventory Structure
    while(fscanf(fptr,"%d %s %f %d", &inventory[itemCount].id,inventory[itemCount].name, 
                 inventory[itemCount].price, inventory[itemCount].quantity)!=EOF)
                 {
                    itemCount++;  
                 }

    fclose(fptr);
}

void saveStock()
{
    FILE *fptr = fopen("../data/stock.txt","w");

    if (fptr == NULL)
    {
        printf("Error Opening Stock File! \n");
        return;
    }

    for(int i=0; i<itemCount; i++)
    {
        fprintf(fptr,"%d %s %f %d",inventory[i].id,inventory[i].name, 
                inventory[i].price, inventory[i].quantity);

                fclose(fptr);
    }
}