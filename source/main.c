#include <stdio.h>

#include "stock.h"
#include "sales.h"
#include "menu.h"

int main()
{
    //Initializing Every Variable to 0
    StockVariables stock ={NULL, 0,0};
    SaleVariables sales ={NULL, 0,0};

    //Loading The Stock and SALES if any
    loadStock(&stock);
    loadSales(&sales);

    //Displaying The Main Menu
    mainMenu(&stock, &sales);

    //Cleaning The Stock and Sales From The Memory At the End
    cleanStock(&stock);
    cleanSales(&sales);

    return 0;
}