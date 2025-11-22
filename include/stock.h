//Header Files
#ifndef STOCK_H
#define STOCK_H

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

//----------Sales Structure----------
typedef struct
{
    int saleID;
    int productID;
    int quantitySold;
    float totalPrice;
    char productName[50];
    char date[30]; //Added Date Array For Timestamps
}Sale;

//----------Stock Variables Structure----------
typedef struct
{
    Product *inventory;
    int itemCount;
    int capacity;
} StockVariables;

//----------Sales Variable Structure----------
typedef struct
{
    Sale * sales;
    int saleCount;
    int capacity;
} SaleVariables;


//---------- Function Prototypes----------

//Stock Functions
void loadStock(StockVariables *s);
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
void cleanSystem(StockVariables *s, SaleVariables *sales);
int getInteger();
float getFloating();
void capacityUpdater(StockVariables*s);

//Sales Functions
void recordSale(StockVariables *s, SalesVariables *sales);
void salesReport(StockVariables *s, SalesVariables *sales);
void saveSales(Sale sales[], int saleCount);
void loadSales(Sale sales[], int *saleCount);

//Menu Functions
void menu(StockVariables *s, SalesVariables *sales);
void adminMenu(StockVariables *s, SalesVariables *sales);
void customerMenu(StockVariables *s, SalesVariables *sales);

#endif
