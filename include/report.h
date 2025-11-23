#ifndef REPORT_H
#define REPORT_H

#include "stock.h"
#include "sales.h"

//----------Report Functions----------
void displayRemainingStock(StockVariables *s);
void displayDailySales(SaleVariables *sales);
void displayLowStock(StockVariables *s);
void displayValuedCustomers();
int monthStrToNum(const char *month);


#endif