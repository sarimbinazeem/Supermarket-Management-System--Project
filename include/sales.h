#ifndef SALES_H
#define SALES_H

#include "stock.h"

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

//----------Sales Variable Structure----------
typedef struct
{
    Sale * sales;
    int saleCount;
    int capacity;
} SaleVariables;


//Sales Functions
void recordSale(StockVariables *s, SaleVariables *sales);
void salesReport(StockVariables *s, SaleVariables *sales);
void saveSales(Sale sales[], int saleCount);
void loadSales(Sale sales[], int *saleCount);
void resizeSales(SaleVariables *s);
void cleanSales(SaleVariables *s);

#endif