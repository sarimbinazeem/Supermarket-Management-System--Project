#include "sales.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void recordSale(StockVariables *s, SaleVariables *sales)
{
    int id, qty;
    Id = getInt("Enter Product ID: ", 1, 99999);

    int index = -1;

    for(int i=0; i<itemCount;i++)
    {
        if(inventory[i].id == productId)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        printf("Product Not Found ! \n");
        return;
    }

    qty = getInt("Enter Quantity: ", 1, 10000);


    if(inventory[index].quantity < qty)
    {
        printf("Not Enough Stock! \n");
        return;
    }

    inventory[index].quantity -= quantity;
    float total = inventory[index].price * quantity;

    Sale s;
    s.id = (*saleCount ==0) ? 1: sales[*saleCount -1].id +1;  //If there is no items then ID is 1, Otherwise it is One more of the ID then the previous ID
    s.productID = id;
    s.quantitySold = qty;
    s.totalPrice = total;

    time_t t; //Declaring Time Variale
    time(&t); //Gets Input Of Time From System
    char *timestamp = ctime(&t); //Converts Time Into String
    strcpy(s.date, *timestamp);
    s.date[strlen(s.date)-1] ='\0' //Removes Newline From String (That Is Automatically Added From ctime)

    sales[*saleCount] = s;
    (*saleCount)++;

    printf("\nBill Generated!\n");
    printf("Item: %s\n", inventory[index].name);
    printf("Quantity: %d\n", qty);
    printf("Total Price: %.2f\n\n", total);
}

void salesReport(StockVariables *s, SaleVariables *sales)
{
    if(saleCount ==0)
    {
        printf("\n No Sale Recorded! \n");
        return;
    }

    float grand =0;
    int sold = 0;

    printf("\n========== Sales Report ===========\n\n");
    for(int i=0 ; i<saleCount ;i++)
    {
        int index = -1;
        for(int j=0 ;j<itemCount;j++)
        {
            if(inventory[j].productID == sales[i].productID)
            {
                index =j;
                break;
            }
        }

         if(index == -1)
         {
            printf("Product Not Found! \n");
            break;
         }

        printf("Product: %s | Quantity: %d | Total: %.2f | Date: %s \n", inventory[index].name, sales[index].quantitySold, sales[index].totalPrice,sales[index].date);

        grand += sales[i].totalPrice;
        sold += sales[i].quantitySold;
    }
   
    printf("\n Total Revenue Generated: %.2f\n",grand);
    printf(" Total Items Sold: %d\n",sold);
    printf("\n----------------------------------\n");
    

}


void saveSales(Sale sales[], int saleCount)
{
    FILE *fptr = fopen("data/sales.txt","w");

    if(fptr == NULL)
    {
        printf("ERROR! Cant Open Sales File\n");
        return;
    }
     for (int i = 0; i < saleCount; i++) 
    {
        fprintf(fptr, "%d,%d,%d,%.2f,%s\n",
            sales[i].saleID, sales[i].productID, sales[i].quantitySold,
            sales[i].totalPrice, sales[i].date);
        }
        
        fclose(fptr);
    }

void loadSales(Sale sales[], int *saleCount)
{
    FILE *fptr = fopen("data/sales.txt","r");

    if(fptr == NULL)
    {
        printf("ERROR! Cant Open Sales File\n");
        return;
    }

    *saleCount =0;

    while(fscanf(fp, "%d %d %d %f %[^\n]", &sales[*saleCount].saleID, &sales[*saleCount].productID, &sales[*saleCount].quantitySold, &sales[*saleCount].totalPrice, sales[*saleCount].date) != EOF)
    {
         (*saleCount)++;
    }

    fclose(fptr);
}

void cleanSales(SaleVariables *s)
{
    if(s->sales != NULL)
    {
        free(s->sales);
    }

    printf("\nSystem Cleared! Exiting...\n");
}

void resizeSales(SaleVariables *s)
{
    //Initially We Start from 10 capacity and use malloc which asks the computer to get memory for 10 items
    if (s->capacity ==0)
    {
        s->capacity = 10;
        s->sales = (Sale*)malloc(s->capacity * sizeof(Sale));  //sizeof(Product) initially zero
    }

    //If Items Added Exceeds Capacity Size We 
    else if(s->saleCount >= s->capacity)
    {
        //Double the recent capacity
        s->capacity *= 2;
        s->sales = (Sale*)realloc(s->sales,s->capacity * sizeof(Sale));
    }
}