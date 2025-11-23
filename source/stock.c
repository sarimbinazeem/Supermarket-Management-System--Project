#include "stock.h"
#include "input.h"


//----------Duplicate Fineder----------
int isDuplicateProduct(StockVariables *s, int id, const char *name) 
{
    for(int i = 0; i < s->itemCount; i++) 
    {
        if(s->inventory[i].id == id) 
        {
            printf("Error: Product ID %d already exists.\n", id);
            return 1; 
        }
        if(strcmp(s->inventory[i].name, name) == 0)
         {
            printf("Error: Product name '%s' already exists.\n", name);
            return 1; 
        }
    }
    return 0; // no duplicates
}

//----------Capacity Handler (Dynamic Memory)----------
void capacityUpdater(StockVariables *s)
{
    //Initially We Start from 10 capacity and use malloc which asks the computer to get memory for 10 items
    if (s->capacity ==0)
    {
        s->capacity = 10;
        s->inventory = (Product*)malloc(s->capacity * sizeof(Product)); 
    }
    //If Items Added Exceeds Capacity Size We 
    else if(s->itemCount >= s->capacity)
    {
        //Double the recent capacity
        s->capacity *= 2;
        s->inventory = (Product*)realloc(s->inventory,s->capacity * sizeof(Product));
    }

 }

 //----------LOAD STOCK FROM FILE----------
int loadStock(StockVariables *s) {
    FILE *fp = fopen("stock.txt", "r");
    if (!fp) {
        printf("No stock file found. Starting empty.\n");
        s->itemCount = 0;
        return 0;
    }

    int count = 0;
    while (fscanf(fp, "%d %s %f %d",
                  &s->inventory[count].id,
                  s->inventory[count].name,
                  &s->inventory[count].price,
                  &s->inventory[count].quantity) == 4) {
        count++;
    }

    s->itemCount = count;
    fclose(fp);
    return count;
}

//----------Save Stock To File----------
void saveStock(StockVariables *s) 
{
    FILE *fp = fopen("stock.txt", "w");
    if (!fp) {
        printf("Error opening stock.txt for writing!\n");
        return;
    }

    for (int i = 0; i < s->itemCount; i++) {
        fprintf(fp, "%d %s %.2f %d\n",
                 s->inventory[i].id,
                s->inventory[i].name,
                s->inventory[i].price,
                s->inventory[i].quantity);
    }

    fclose(fp);
}

//----------Add New Items To File----------
void addItem(StockVariables *s)
{
    // Updates capacity if needed
    capacityUpdater(s);

    // Take details of new item
    Product new;
    printf("Enter Product ID: ");
    scanf("%d", &new.id);

    printf("Enter Product Name: ");
    getchar(); // clear leftover newline
    scanf("%[^\n]", new.name);

    new.price = getFloating("Enter Price: ", 1, 100000);
    new.quantity = getInteger("Enter Quantity: ", 1, 10000);

    // Check for duplicates  adding
    if (isDuplicateProduct(s, new.id, new.name)) 
    {
        printf("Cannot add product due to duplicate.\n");
         return;
    }

    // Add new product to inventory
    s->inventory[s->itemCount] = new;
    s->itemCount++;

    // Save to file
    saveStock(s);
    printf("Item Added Successfully!\n");
 
}

//----------Display Stock----------
void recursiveDisplay(StockVariables *s, int index) {
    if (index >= s->itemCount) return;

    printf("%d) %s | Price: %.2f | Quantity: %d\n",
           s->inventory[index].id,
           s->inventory[index].name,
           s->inventory[index].price,
           s->inventory[index].quantity);

    recursiveDisplay(s, index + 1);
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

//----------Cleaning Stock Memory----------
void cleanStock(StockVariables *s)
{
    //Dynamic Memory Allocations is cleaned/freed here
    if(s->inventory != NULL)
    {
        free(s->inventory);
        s->inventory = NULL;
    }  
}
