#include "report.h"
#include "stock.h"
#include "sales.h"
#include "customer.h"
#include "checkout.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//---------- Display Remaining Stock ----------
void displayRemainingStock(StockVariables *s)
{
    printf("\n========== Remaining Stock ==========\n");
    for (int i = 0; i < s->itemCount; i++)
    {
        printf("ID: %d | Name: %s | Price: %.2f | Quantity: %d\n",
               s->inventory[i].id,
               s->inventory[i].name,
               s->inventory[i].price,
               s->inventory[i].quantity);
    }
}

//---------- Display Low-Stock Items ----------
void displayLowStock(StockVariables *s)
{
    printf("\n========== Low-Stock Items ==========\n");
    int flag = 0;
    for (int i = 0; i < s->itemCount; i++)
    {
        if (s->inventory[i].quantity < 5)
        {
            flag = 1;
            printf("WARNING: %s (ID: %d) only %d left in stock!\n",
                   s->inventory[i].name,
                   s->inventory[i].id,
                   s->inventory[i].quantity);
        }
    }
    if (!flag)
        printf("All items are sufficiently stocked.\n");
}

//---------- Display Daily Sales ----------
void displayDailySales(SaleVariables *sales) {
    if (sales->saleCount == 0) {
        printf("No sales recorded today.\n");
        return;
    }

    // Get today's date string in "YYYY-MM-DD" format
    time_t t = time(NULL);
    struct tm today = *localtime(&t);
    char todayStr[11]; // YYYY-MM-DD + null
    sprintf(todayStr, "%04d-%02d-%02d", today.tm_year + 1900, today.tm_mon + 1, today.tm_mday);

    printf("\n======= Daily Sales Report =======\n");
    float totalRevenue = 0;
    int totalItemsSold = 0;
    int found = 0;

    for (int i = 0; i < sales->saleCount; i++) {
        // Assume sales->sales[i].date is stored in "YYYY-MM-DD" format
        char saleDate[11];
        strncpy(saleDate, sales->sales[i].date, 10);
        saleDate[10] = '\0';

        if (strcmp(saleDate, todayStr) == 0) {
            found = 1;
            printf("Product ID: %d | Product: %s | Quantity: %d | Total: %.2f\n",
                   sales->sales[i].productID,
                   sales->sales[i].productName,
                   sales->sales[i].quantitySold,
                   sales->sales[i].totalPrice);

            totalRevenue += sales->sales[i].totalPrice;
            totalItemsSold += sales->sales[i].quantitySold;
        }
    }

    if (!found) {
        printf("No sales recorded today.\n");
    } else {
        printf("\nTotal Items Sold Today: %d\n", totalItemsSold);
        printf("Total Revenue Today: %.2f\n", totalRevenue);
    }

    printf("=================================\n");
}


int monthStrToNum(const char *month) 
{
    if (strcmp(month, "Jan") == 0) 
    return 1;

    if (strcmp(month, "Feb") == 0)
     return 2;

    if (strcmp(month, "Mar") == 0) 
    return 3;

    if (strcmp(month, "Apr") == 0) 
    return 4;

    if (strcmp(month, "May") == 0) 
    return 5;

    if (strcmp(month, "Jun") == 0) 
    return 6;

    if (strcmp(month, "Jul") == 0) 
    return 7;

    if (strcmp(month, "Aug") == 0) 
    return 8;

    if (strcmp(month, "Sep") == 0) 
    return 9;

    if (strcmp(month, "Oct") == 0) 
    return 10;

    if (strcmp(month, "Nov") == 0) 
    return 11;

    if (strcmp(month, "Dec") == 0) 
    return 12;

    
    return 0; // invalid
}

//---------- Display Valued Customers (VIP >= 10000) ----------
void displayValuedCustomers()
{
    FILE *fp = fopen("customers.txt", "r");
    if (!fp)
    {
        printf("No customer records found.\n");
        return;
    }

    printf("\n========== Valued Customers ==========\n");

    char id[10];
    float totalSpent;
    int isVIP;
    int found = 0;

    while (fscanf(fp, "%s %f %d", id, &totalSpent, &isVIP) == 3)
    {
        if (isVIP == 1)
        {
            found = 1;
            printf("Customer ID: %s | Total Spent: %.2f\n", id, totalSpent);
        }
    }

    if (!found)
        printf("No valued customers yet.\n");

    fclose(fp);
}


    