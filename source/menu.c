#include <stdio.h>
#include "menu.h"
#include "input.h"
#include "stock.h"
#include "sales.h"

void adminMenu(StockVariables *stock, SaleVariables *sales,Sale *sle)
{
    int choice;

    do
    {
        //Menu Displayed For Admin
        printf("\n=====Admin Menu=====\n");
        printf("1.Add Items\n");
        printf("2.Display Stock\n");
        printf("3.Update Item\n");  
        printf("4.Delete Item\n");
        printf("5.Check For Low Stock\n");
        printf("6.Search For An Item\n");
        printf("7.Sort Stock By Name\n");
        printf("8.Sort Stock By Price\n");
        printf("9.Generate Sales Report\n");
        printf("0.Exit\n");

        choice = getInteger("Enter choice: ", 0, 9);

        //Switch cases for each cases
        switch(choice)
        {
            case 1: //Add New Items
                addItem(stock);
                break;
            
            case 2: //Display ALL Stocks
                displayStock(stock);
                break;

            case 3: //update an items price and quantity
                updateItem(stock);
                break;

            case 4: //Delete an Item FROm Stock
                deleteItem(stock);
                break;

            case 5: //Check If Any Item Have Low Stock
                lowStock(stock);
                break;
            
            case 6: //Search For An Item To Get Its Details
                searchItems(stock);
                break;

            case 7: //Sort The Stock By Name
                sortByName(stock);
                break;

            case 8: //Sort The Stock By Price
                sortByPrice(stock);
                break;

            case 9: //Get Report Of The Sales Done
                salesReport(stock,sales,sle);
                break;

             case 0: //Exiting THe Program
                printf("Logging Out...\n");
                break;

            default: //Invalid Case
                printf("Invalid Choice! \n");
                break;
        }
            
    } while (choice != 0);
    
}

void customerMenu(StockVariables *stock, SaleVariables *sales)
{
    int choice;

    do
    {
        //Menu For CUstomer
        printf("\n=====Customer Menu=====\n");
        printf("1.Buy Items\n");
        printf("2.View Inventory\n");
        printf("0.Exit\n");

        choice = getInteger("Enter choice: ", 0, 9);

        //Switch Cases For All Cases
        switch(choice)
        {
             case 1: //Record The Sale Of CUstomer
                recordSale(stock,sales);
                break;
            
            case 2: //Display Inventory To Customer
                displayStock(stock);
                break;

            case 0: //Exiting The Program
                printf("Logging Out...\n");
                break;

            default: //Invalid Program
                printf("Invalid Choice! \n");
                break;
        }

    } while (choice != 0);
}

void mainMenu(StockVariables *stock , SaleVariables *sales, Sale *sle)
{
    int choice;
    do
    {
        //Main Menu
        printf("\n=========SuperMarket Management System==========\n");
        printf("1.Admin Mode\n");
        printf("2.Customer Mode \n");
        printf("0.Exit\n");
        choice = getInteger("Enter choice: ", 0, 9);


        //Switch Cases To get All Cases
        switch(choice)
        {
            case 1: //To Show Menu For Admin
                adminMenu(stock, sales,sle);
                break;

            case 2: //To Show Menu For CUstomer
                customerMenu(stock, sales);
                break;

            case 0: //To Exit The Program after saving Data to FIle
                saveSales(sales->sales ,sales ->saleCount);
                saveStock(stock);

                printf("Data Saved. Exiting The Program...\n");
                break;

            default: //Invalid Case
                printf("Invalid Choice! \n");
                break;
        }
    } while(choice != 0);
}
