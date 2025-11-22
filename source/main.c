#include <stdio.h>
#include "../include/stock.h"

void adminMenu(StockVariables *stock, SaleVariables *sales)
{
    int choice;

    do
    {
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
        printf("9.Exit\n");

        printf("Ener Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        
            case 1:
                addItem(stock);
                break;
            
            case 2:
                displayStock(stock);
                break;

            case 3:
                updateItem(stock);
                break;

            case 4:
                deleteItem(stock);
                break;

            case 5:
                lowStock(stock);
                break;
            
            case 6:
                searchItems(stock);
                break;

            case 7:
                sortByName(stock);
                break;

            case 8:
                sortByPrice(stock);
                break;

            case 9:
                salesReport(stock,sales);
                break;

             case 0:
                printf("Logging Out...\n");
                break;

            default:
                printf("Invalid Choice! \n");
                break;
    } while (choice != 0)
    
}

void customerMenu(StockVariables *stock, StockVariables *sales)
{
    int choice;

    do
    {
        printf("\n=====Customer Menu=====\n");
        printf("1.Buy Items\n");
        printf("2.View Inventory\n");
        printf("0.Exit\n");

        printf("Ener Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        
            case 1:
                recordSale(stock,sales);
                break;
            
            case 2:
                displayStock(stock);
                break;

            case 0:
                printf("Logging Out...\n");
                break;

            default:
                printf("Invalid Choice! \n");
                break;
    } while (choice != 0)
}

int main()
{
    StockVariables stock ={NULL, 0,0};
    SaleVariables sales ={NULL, 0,0};

    loadStock(&stock);
    loadSales(&sales);

    int choice;
    do
    {
        printf("\n=========SuperMarket Management System==========\n");
        printf("1.Admin Mode\n");
        printf("2.Customer Mode \n");
        printf("0.Exit\n");
        printf("Enter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
                adminMenu(&stock, &sales);
                break;

            case 2:
                customerMenu(&stock, &sales);
                break;

            case 0:
                saveSales(&sales);
                saveStock(&stock);

                printf("Data Saved. Exiting The Program...\n");
                break;

            default:
                printf("Invalid Choice! \n");
                break;
        }
    } while(choice != 0);

    cleanSystem(&stock, &sales);

    return 0;
}