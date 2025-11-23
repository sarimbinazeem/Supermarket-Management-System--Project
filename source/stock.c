#include "stock.h"
#include "input.h"

//----------Capacity Handler (Dynamic Memory)----------
void capacityUpdater(StockVariables *s)
{
    //Initially We Start from 10 capacity and use malloc which asks the computer to get memory for 10 items
    if (s->capacity ==0)
    {
        s->capacity = 10;
        s->inventory = (Product*)malloc(s->capacity * sizeof(Product)); 

    //If Items Added Exceeds Capacity Size We 
    else if(s->itemCount >= s->capacity)
    {
        //Double the recent capacity
        s->capacity *= 2;
        s->inventory = (Product*)realloc(s->inventory,s->capacity * sizeof(Product));
    }

 }

 //----------LOAD STOCK FROM FILE----------
void loadStock(StockVariables *s)
{
    FILE *fptr = fopen("stock.txt","r");

    if (fptr == NULL)
    {
        printf("Error Opening Stock File! \n");
        return;
    }

    //Load Runs At The Start Of The Main So We Initialize From 0
    s->itemCount = 0;
    s->capacity =0;

    int id, quantity;
    char name[50];
    float price;

    //Take Stock from Stock File Until it is the End Of File And Store it Inventory Structure
    while(fscanf(fptr,"%d %[^\n] %f %d", &id,name,  &price, &quantity)!=EOF)
                 {
                    capacityUpdater(s);

                    s->inventory[s->itemCount].id =id;
                    strcpy(s->inventory[s->itemCount].name,name);
                    s->inventory[s->itemCount].price =price;
                    s->inventory[s->itemCount].quantity = quantity;
                    s->itemCount++;  
                 }

    fclose(fptr);

    printf("Stock Loaded Successfully! \n");
}


//----------Save Stock To File----------
void saveStock(StockVariables *s)
{
    FILE *fptr = fopen("stock.txt","w");

    if (fptr == NULL)
    {
        printf("Error Opening Stock File! \n");
        return;
    }

    //Prints All The Items Present In Stock File
    for(int i=0; i<s->itemCount; i++)
    {
        fprintf(fptr,"%d %s %.2f %d\n",s->inventory[i].id,s->inventory[i].name, s->inventory[i].price, s->inventory[i].quantity);
    }

    fclose(fptr);
    printf("Stock Saved Successfully! \n");
}


//----------Add New Items To File----------
void addItem(StockVariables *s)
{
    //Updates Capacity
    capacityUpdater(s);

    //Take Details Of New Item
    Product new;
    printf("Enter Product ID: ");
    scanf("%d",&new.id);

    printf("Enter Product Name: ");
    getchar();
    scanf("%[^\n]",new.name);   

    new.price = getFloating("Enter Price: ", 1, 100000);
    new.quantity = getInteger("Enter Quantity: ", 1, 10000);
    
    //Add New Structure to Inventory Structre
    s->inventory[s->itemCount] = new;
    s->itemCount++;

    //Save
    saveStock(s);
    printf("Item Added Successfully! \n");
}

//----------Display Stock----------
void recursiveDisplay (StockVariables *s,int index)
{
    if(index>=s->itemCount)
    {
        return; //Base Case
    }

     printf("%d) %s | Price: %.2f | Quantity: %d\n",s->inventory[index].id, s->inventory[index].name, s->inventory[index].price,s->inventory[index].quantity);

     recursiveDisplay(s,index +1); //recursive call (Move To Next Index)


}

void displayStock(StockVariables *s)
{
    printf("\n==========Stock Available==========\n");
    //Apply Recursive Display Function
    recursiveDisplay(s,0);
    printf("\n Items Displayed Successfully.\n");
}

//----------Updating Item Price And Quantity----------
void pointerPrice(Product *p, float newPrice)
{
    p -> price = newPrice;
}

void updateItem(StockVariables *s)
{
    float newPrice;
    int id;

    id = getInteger("Enter Product ID: ", 1, 99999);

    //Find If The ID exists
    int found = -1;

    for(int j=0; j<s->itemCount; j++)
    {
        if(s->inventory[j].id == id)
        {
            found = j;
            break;
        }
    }

    
    if(found == -1)
    {
        printf("Item Not Found! \n");
        return;
    }

    printf("Updating %s\n",s->inventory[found].name);

    newPrice = getFloating("Enter new price: ", 1, 100000);

    //Updates Price By Pointer Price Function
    pointerPrice(&s->inventory[found], newPrice);

    int qty = getInteger("Enter new quantity: ", 0, 10000);
    s->inventory[found].quantity = qty;

    //Save Stock
    saveStock(s);
    printf("Item Updated! \n");
    
}

//----------Delete Items----------  
void deleteItem(StockVariables *s)
{
    int id;
    id = getInteger("Enter Product ID: ", 1, 99999);

    //Find if the ID EXISTS
    int found = -1;
    for(int i=0; i<s->itemCount; i++)
    {
        if(s->inventory[i].id == id)
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

    //Delete  The ID through Looping
    for(int i= found ; i<s->itemCount-1; i++)
    {
        s->inventory[i] = s->inventory[i+1]; 
    }

    s->itemCount--;
    //save
    saveStock(s);

    printf("Item Deleted! \n");
}

//----------Low Stock Warning----------
void lowStock(StockVariables *s)
{
    int flag =0;
    //Checking If ANy ITEM Have lesser than 5 stock
    for(int i=0; i< s->itemCount; i++)
    {
        if(s->inventory[i].quantity < 5)
        {
            flag =1;
            printf("WARNING: Low Stock! %s have %d quantity.\n",s->inventory[i].name,s->inventory[i].quantity);
        }
    }

    //Full Stock Case
    if(!flag)
    {
        printf("All Items Are Fully Stocked! \n");
    }
}

//----------Searching ITEMS----------
void searchItems(StockVariables *s)
{
    int flag =0;
    char search[50];

    printf("Enter Product Name To Search: ");
    getchar();
    scanf("%[^\n]",search);
    
    //Checking Item Existence And Printing Its Details
    for(int i=0; i<s->itemCount ;i++)
    {
        if(strcasecmp(s->inventory[i].name,search) ==0)
        {
            flag =1;
            printf("Item Found! \n");
            printf("ID:%d \n",s->inventory[i].id);
            printf("Name:%s \n",s->inventory[i].name);
            printf("Price:%.2f \n",s->inventory[i].price);
            printf("Quantity:%d \n",s->inventory[i].quantity);
            break;
        }
    }

    //No ITems Found Case
    if(!flag)
    {
        printf("Item Not Found! \n");
    }

}

//----------Sort Stock By Name ----------
void sortByName(StockVariables *s)
{
    for(int i=0; i<s->itemCount-1; i++)
    {
        for(int j=i+1; j<s->itemCount; j++)
        {
            //Bubble Sorting
            if(strcmp(s->inventory[i].name,s->inventory[j].name) > 0)
            {
                Product temp = s->inventory[i];
                s->inventory[i] = s->inventory[j];
                s->inventory[j] = temp;
            }
        }
    }


    printf("Stock Sorted By Name. \n");
}

//----------Sort Stock By Price----------
void sortByPrice(StockVariables *s)
{
    for(int i=0; i<s->itemCount-1; i++)
    {
        for(int j=i+1; j<s->itemCount; j++)
        {
            //Bubble Sorting
            if(s->inventory[i].price>s->inventory[j].price)
            {
                Product temp = s->inventory[i];
                s->inventory[i] = s->inventory[j];
                s->inventory[j] = temp;
            }
        }
    }

    printf("Stock Sorted By Price. \n");

}

void cleanStock(StockVariables *s)
{
    //Dynamic Memory Allocations is cleaned/freed here
    if(s->inventory != NULL)
    {
        free(s->inventory);
        s->inventory = NULL;
    }  
}