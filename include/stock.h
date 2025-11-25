//Header Files
#ifndef STOCK_H
#define STOCK_H
#define MAX_ITEMS 100

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//----------Products Structure----------
typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
}Product;


//----------Stock Variables Structure----------
typedef struct
{
    Product *inventory;
    int itemCount;
    int capacity;
} StockVariables;

// Initialize stock
extern StockVariables *stock;


//---------- Function Prototypes----------

//Stock Functions
int loadStock(StockVariables *s);
void saveStock(StockVariables *s);
void addItem(StockVariables *s);
void displayStock(StockVariables *s);
void recursiveDisplay (StockVariables*s ,int index);
void pointerPrice(Product *p, float newPrice);
void updateItem(StockVariables *s);
void deleteItem(StockVariables *s);
void lowStock(StockVariables *s);
void searchItems(StockVariables *s);
void sortByName(StockVariables *s);
void sortByPrice(StockVariables *s);
void cleanStock(StockVariables *s);
void capacityUpdater(StockVariables *s);
int isDuplicateProduct(StockVariables *s, int id, const char *name);
void remainingStock(StockVariables *s);

#endif
