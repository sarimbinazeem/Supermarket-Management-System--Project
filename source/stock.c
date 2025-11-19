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
    if(itemCount>=ITEMS)
    {
        printf("Inventory Full \n");
        return;
    }

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

void displayStock()
{
    printf("\n==========Stock Available==========\n");
    for(int i=0; i<itemCount; i++)
    {
        printf("%d) %s | Price: %.2f | Quantity: %d\n",inventory[i].id, inventory[i].name
                                                     inventory[i].price,inventory[i].quantity);

    }

    printf("\n Items Displayed Successfully.\n");
}

void updateItem()
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

    printf("Updating %s\n",inventory[found].name);

    printf("Enter New Price: ");
    scanf("%f",&inventory[found].price);

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
    for(int i=0; i<itemCount; i++)
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