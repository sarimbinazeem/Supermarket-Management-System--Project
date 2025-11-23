#include "sales.h"
#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//----------RECORD SALE----------
void recordSale(StockVariables *s, SaleVariables *sales)
{
	if(sales->saleCount >= sales->capacity) 
	{
   	 resizeSales(sales);
	}
    int id, qty;
    id = getInteger("Enter Product ID: ", 1, 99999);

    int index = -1;

    for(int i=0; i<s->itemCount;i++)
    {
        if(s->inventory[i].id == id)
        {
            index = i;
            break;
        }
    }

    //No ID found case
    if(index == -1)
    {
        printf("Product Not Found ! \n");
        return;
    }

    qty = getInteger("Enter Quantity: ", 1, 10000);

    //Not ENough Stock Case
    if(s->inventory[index].quantity < qty)
    {
        printf("Not Enough Stock! \n");
        return;
    }

    //Deducting Quantity
    s->inventory[index].quantity -= qty;
    //Total Price Of The Sale
    float total = s->inventory[index].price * qty;

    //Making A Temporary Sale Structure
    Sale sl;
    sl.saleID = (sales->saleCount ==0) ? 1: sales->sales[sales->saleCount -1].saleID +1;  //If there is no items then ID is 1, Otherwise it is One more of the ID then the previous ID
    sl.productID = id;
    sl.quantitySold = qty;
    sl.totalPrice = total;

    time_t t; //Declaring Time Variale
    time(&t); //Gets Input Of Time From System
    char *timestamp = ctime(&t); //Converts Time Into String
    strcpy(sl.date, timestamp);
	sl.date[strlen(sl.date)-1] = '\0'; //Removes Newline From String (That Is Automatically Added From ctime)

    //Transfering Temporary Sale Structure To sales array
    sales->sales[sales->saleCount] = sl;
    sales->saleCount++;

    //Final SUmmary
    printf("\nBill Generated!\n");
    printf("Item: %s\n", s->inventory[index].name);
    printf("Quantity: %d\n", qty);
    printf("Total Price: %.2f\n\n", total);
}

//----------Creating Report Of All Sales----------
void salesReport(StockVariables *s, SaleVariables *sales)
{
    //Zero Sales Case
    if(sales->saleCount ==0)
    {
        printf("\n No Sale Recorded! \n");
        return;
    }

    float grand =0;
    int sold = 0;

    printf("\n========== Sales Report ===========\n\n");
    for(int i=0 ; i<sales->saleCount ;i++)
    {
        int index = -1;
        for(int j=0 ;j<s->itemCount;j++)
        {
            //Finding Which Item is SOld
            if(s->inventory[j].id == sales->sales[i].productID)
            {
                index =j;
                break;
            }
        }

         if(index == -1)
         {
            printf("Product Not Found! \n");
            continue;
         }

         //Summary Of Each Product
        printf("Product: %s | Quantity: %d | Total: %.2f | Date: %s \n", s->inventory[index].name, sales->sales[i].quantitySold, sales->sales[i].totalPrice,sales->sales[i].date);

        grand += sales->sales[i].totalPrice;
        sold += sales->sales[i].quantitySold;
    }
   
    //Final Report
    printf("\n Total Revenue Generated: %.2f\n",grand);
    printf(" Total Items Sold: %d\n",sold);
    printf("\n----------------------------------\n");
    

}

//----------Saving Sale To File----------
void saveSales(Sale sales[], int saleCount)
{
    FILE *fptr = fopen("sales.txt","w");

    if(fptr == NULL)
    {
        printf("ERROR! Cant Open Sales File\n");
        return;
    }

    //Saving Sales To Text File
     for (int i = 0; i < saleCount; i++) 
    {
        fprintf(fptr, "%d,%d,%d,%.2f,%s\n",sales[i].saleID, sales[i].productID, sales[i].quantitySold,sales[i].totalPrice, sales[i].date);
    }
        
        fclose(fptr);
}


//----------Load Sales From File----------
void loadSales(Sale sales[], SaleVariables * sle)
{
    FILE *fptr = fopen("sales.txt","r");

    if(fptr == NULL)
    {
        printf("ERROR! Cant Open Sales File\n");
        return;
    }

    sle->saleCount =0;

    //Taking Entries From Text Til End Of File
    while(fscanf(fptr, "%d,%d,%d,%f,%[^\n]", &sales[sle->saleCount].saleID, &sales[sle->saleCount].productID, &sales[sle->saleCount].quantitySold, &sales[sle->saleCount].totalPrice, sales[sle->saleCount].date) != EOF)
    {
         sle->saleCount++;
    }
    
	if(sle->saleCount >= sle->capacity)
	 {
  		  resizeSales(sle);
	}
    fclose(fptr);
}

//---------Cleaning Memory----------
void cleanSales(SaleVariables *s)
{
    //Cleaning Any Memory Of Sale Structure At the End
    if(s->sales != NULL)
    {
        free(s->sales);
        s->sales = NULL;
    }

    printf("\nSystem Cleared! Exiting...\n");
}


//----------Resizing Capacity Function---------
void resizeSales(SaleVariables *s)
{
    //Initially We Start from 10 capacity and use malloc which asks the computer to get memory for 10 items
    if (s->capacity ==0)
    {
        s->capacity = 10;
        s->sales = (Sale*)malloc(s->capacity * sizeof(Sale));  
    }

    //If Items Added Exceeds Capacity Size We 
    else if(s->saleCount >= s->capacity)
    {
        //Double the recent capacity
        s->capacity *= 2;
        s->sales = (Sale*)realloc(s->sales,s->capacity * sizeof(Sale));
    }
}

void appendSale(SaleVariables *sales, int productID, int quantity, float price, float totalPrice, const char *productName) {
    if (sales->saleCount >= sales->capacity) {
        // Resize if needed
        sales->capacity *= 2;
        sales->sales = realloc(sales->sales, sizeof(Sale) * sales->capacity);
    }

    Sale *s = &sales->sales[sales->saleCount];
    s->productID = productID;
    s->quantitySold = quantity;
    s->totalPrice = totalPrice;
    strcpy(s->productName, productName);

    // Store date as YYYY-MM-DD
    time_t t = time(NULL);
    struct tm tm_now = *localtime(&t);
    sprintf(s->date, "%04d-%02d-%02d", tm_now.tm_year + 1900, tm_now.tm_mon + 1, tm_now.tm_mday);

    sales->saleCount++;
}