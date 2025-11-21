#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //For Timestamps
#include "../include/stock.h"

Product *inventory = NULL; //It starts from pointing to nothing
int itemCount=0;
int capacity =0; 

void capacityUpdater()
{
    //Initially We Start from 10 capacity and use malloc which asks the computer to get memory for 10 items
    if (capacity ==0)
    {
        capacity = 10;
        inventory = (Product*)malloc(capacity * sizeof(Product))  //sizeof(Product) initially zero
    }

    //If Items Added Exceeds Capacity Size We 
    else if(itemCount >= capacity)
    {
        //Double the recent capacity
        capacity *= 2;
        inventory = (Product*)realloc(inventory,capacity * sizeof(Product));
    }

 }

void loadStock()
{
    FILE *fptr = fopen("../data/stock.txt","r");

    if (fptr == NULL)
    {
        printf("Error Opening Stock File! \n");
        return;
    }

    //Load Runs At The Start Of The Main So We Initialize From 0
    itemCount = 0;
    capacity =0;

    int id, quantity;
    char name[50];
    float price;

    itemCount =0; //Added So That Each Time ItemCount starts from 0 

    //Take Stock from Stock File Until it is the End Of File And Store it Inventory Structure
    while(fscanf(fptr,"%d %s %f %d", &id,name,  &price, &quantity)!=EOF)
                 {
                    capacityUpdater();

                    inventory[itemCount].id =id;
                    strcpy(inventory[itemCount].name,name);
                    inventory[itemCount].price =price;
                    inventory[itemCount].quantity = quantity;
                    itemCount++;  
                 }

    fclose(fptr);

    printf("Stock Loaded Successfully! \n");
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
        fprintf(fptr,"%d %s %.2f %d",inventory[i].id,inventory[i].name, 
                inventory[i].price, inventory[i].quantity);

                fclose(fptr);
    }

    printf("Stock Saved Successfully! \n");
}

void addItem()
{

    capacityUpdater();

    Product new;
    printf("Enter Product ID: ");
    scanf("%d",new.id);

    printf("Enter Product Name: ");
    scanf("%[^\n]",new.name);
    getchar();

    printf("Enter Product Price: ");
    scanf("%f",new.price);

    printf("Enter Product Quantity: ");
    scanf("%d",new.quantity);
    
    inventory[itemCount] = new;
    itemCount++;

    saveStock();
    printf("Item Added Successfully! \n");
}

void recursiveDisplay (int index)
{
    if(index>=itemCount)
    {
        return; //Base Case
    }

     printf("%d) %s | Price: %.2f | Quantity: %d\n",inventory[index].id, inventory[index].name, inventory[index].price,inventory[index].quantity);

     recursiveDisplay(index +1); //recursive call


}
void displayStock()
{
    printf("\n==========Stock Available==========\n");
    recursiveDisplay(0);
    printf("\n Items Displayed Successfully.\n");
}

void pointerPrice(Product *p, float newPrice)
{
    p -> price = newPrice;
}
void updateItem()
{
    float newPrice;
    int id;
    printf("Enter Product ID: ");
    scanf("%d",&id);

    int found = -1
    for(int i=0; i<itemCount; i++)
    {
        if(inventory[i].id == id)
        {
            found = i;
            break;
        }
    }

    
    if(found == -1)
    {
        printf("Item Not Found! \n");
        return;
    }

    printf("Updating %s\n",inventory[found].name);

    printf("Enter New Price: ");
    scanf("%f",&newPrice);

    pointerPrice(&inventory[found], newPrice);

    printf("Enter New Quantity: ");
    scanf("%d",&inventory[found].quantity);

    saveStock();
    printf("Item Updated! \n");
    
}

void deleteItem()
{
    int id;
    printf("Enter Product ID: ");
    scanf("%d",&id);

    int found = -1
    for(int i=0; i<itemCount; i++)
    {
        if(inventory[i].id == id)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Item Not Found! \n");
        return;
    }

    for(int i= found ; i<itemCount-1; i++)
    {
        inventory[i] = inventory[i+1]; 
    }

    itemCount--;
    saveStock();

    printf("Item Deleted! \n");
}

void lowStock()
{
    int flag =0;
    for(int i=0; i<itemCount; i++)
    {
        if(inventory[i].quantity < 5)
        {
            flag =1;
            printf("WARNING: Low Stock! %s have %d quantity.\n",inventory[i].name,inventory[i].quantity);
        }
    }

    if(!flag)
    {
        printf("All Items Are Fully Stocked! \n");
    }
}

void searchItems()
{
    int flag =0;
    char search[50];

    printf("Enter Product Name To Search: ");
    scanf("%[^\n]",search);

    for(int i=0; i<itemCount ;i++)
    {
        if(strcmp(inventory[i].name,search) ==0)
        {
            flag =1;
            printf("Item Found! \n");
            printf("ID:%d \n",inventory[i].id);
            printf("Name:%s \n",inventory[i].name);
            printf("Price:%.2f \n",inventory[i].price);
            printf("Quantity:%d \n",inventory[i].quantity);
            break;
        }
    }

    if(!flag)
    {
        printf("Item Not Found! \n");
    }

}

void sortByName()
{
    for(int i=0; i<itemCount-1; i++)
    {
        for(int j=1; j<itemCount; j++)
        {
            if(strcmp(inventory[i].name,inventory[j].name) > 0)
            {
                Product temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }

    printf("Stock Sorted By Name. \n");
}

void sortByPrice()
{
    for(int i=0; i<itemCount-1; i++)
    {
        for(int j=1; j<itemCount; j++)
        {
            if(inventory[i].price>inventory[j].price)
            {
                Product temp = inventory[i];
                inventory[i] = inventory[j];
                inventory[j] = temp;
            }
        }
    }

    printf("Stock Sorted By Price. \n");

}

void recordSale(int productId, int quantity)
{
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

    if(inventory[index].quantity < qty)
    {
        printf("Not Enough Stock! \n");
        return;
    }

    inventory[index].quantity -= quantity;
    saveStock();

    float total = inventory[index].price * quantity;

    time_t t; //Declaring Time Variale
    time(&t); //Gets Input Of Time From System
    char *timestamp = ctime(&t); //Converts Time Into String
    timestamp[strlen(timestamp)-1] ='\0' //Removes Newline From String (That Is Automatically Added From ctime)

    FILE *fptr = fopen("../data/sales.txt","a");

    if(fptr == NULL)
    {
        printf("ERROR! Cant Open Sales File\n");
        return;
    }
    fprintf(fp,"%d %s %d %.2f %s\n",productId,inventory[index].name,quantity,total,timestamp);

    fclose(fptr);

    printf("Sale Recorded Successfully\n");
}

void salesReport()
{
    FILE *fptr = fopen("../data/sales.txt","r");

    if(fptr == NULL)
    {
        printf("Sales File Error In Opening! \n");
        return;
    }

    int productId, quantity;
    char prod[50] ,date[50];
    float total,grand =0;
    int itemsSold =0;

    printf("\n==========Sales Report===========\n\n");
    while(fscanf(fp,"%d %s %d %f %[^\n]",&productId,name,&quantity,&total,date)!= EOF)
    {
        printf("Product: %s | Quantity: %d | Total: %.2f | Date: %s \n",name,quantity,total,date);

        grand += total;
        itemsSold += quantity;
    }

    printf("\nTotal Items Sold: %d\n",itemsSold);
    printf("Total Revenue Generated: %d\n",grand);
    printf("\n----------------------------------\n");

    fclose(fptr);
}

void cleanSystem()
{
    //Dynamic Memory Allocations is cleaned/freed here
    itemCount = 0;
    printf("\nSystem Cleared! Exiting...\n");
}