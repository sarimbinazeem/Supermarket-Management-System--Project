#ifndef MENU_H
#define MENU_H

#include "stock.h"
#include "sales.h"

//Menu Functions
void mainMenu(StockVariables *s, SaleVariables *sales, Sale *sle);
void adminMenu(StockVariables *s, SaleVariables *sales, Sale *sle);
void cashierMenu(StockVariables *s, SaleVariables *sales);
int login();
void reportMenu(StockVariables *stock, SaleVariables *sales);

#endif