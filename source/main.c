#include <stdio.h>
#include "../include/stock.h"

void adminMenu(StockVariables *stock, SaleVariables *sales)
{
    int choice;

    do
    {
        printf("\n==========Supermarket Management System==========\n");
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

int main()
{
    StockVariables s ={NULL, 0,0};

    loadStock(&s);
    menu(&s);
    cleanSystem(&s);

    return 0;
}