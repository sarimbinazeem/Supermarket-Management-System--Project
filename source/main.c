#include <stdio.h>

#include "stock.h"
#include "sales.h"
#include "menu.h"

int main()
{
    StockVariables stock ={NULL, 0,0};
    SaleVariables sales ={NULL, 0,0};

    loadStock(&stock);
    loadSales(&sales);

    mainMenu(&stock, &sales);

    cleanStock(&stock);
    cleanSales(&sales);

    return 0;
}