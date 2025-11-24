#include <stdio.h>

#include "screen.h"
#include "stock.h"
#include "sales.h"
#include "menu.h"
#include "input.h"
#include "checkout.h"
#include "customer.h"
#include "report.h"

int main()
{
    int log = login();

    if(log)
    {
        // Allocate memory for stock and sales
        StockVariables stock;
        stock.inventory = malloc(sizeof(Product) * MAX_ITEMS);
        stock.itemCount = 0;
        stock.capacity = MAX_ITEMS;

        SaleVariables sales;
        sales.sales = malloc(sizeof(Sale) * 100); // set your max sales
        sales.saleCount = 0;
        sales.capacity = 100;

        Sale sle;

        // Load stock and sales
        loadStock(&stock);
        resizeSales(&sales);
        loadSales(sales.sales, &sales);

        // Display main menu
        mainMenu(&stock, &sales, &sle);

        // Free memory at the end
        cleanStock(&stock);
        cleanSales(&sales);
    }
    else
    {
        printf("Login details are not verified. Try again later.\n");
    }

    return 0;

}
