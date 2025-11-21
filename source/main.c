#include <stdio.h>
#include "../include/stock.h"

void menu()
{
    int choice;

    while(1)
    
        printf("\n==========Supermarket Management System==========\n");
        printf("1.Add Items\n");
        printf("2.Display Stock\n");
        printf("3.Update Item\n");  
        printf("4.Delete Item\n");
        printf("5.Check For Low Stock\n");
        printf("6.Search For An Item\n");
        printf("7.Sort Stock By Name\n");
        printf("8.Sort Stock By Price\n");
        printf("9.Record Sale\n");
        printf("10.Generate Sales Report\n");
        printf("11.Load Stock From File: \n");
        printf("12.Save Stock To File: \n");
        printf("13.Exit\n");

        printf("Ener Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        
            case 1:
                addItem();
                break;
            
            case 2:
                displayStock();
                break;

            case 3:
                updateItem();
                break;

            case 4:
                deleteItem();
                break;

            case 5:
                lowStock();
                break;
            
            case 6:
                searchItems();
                break;

            case 7:
                sortByName();
                break;

            case 8:
                sortByPrice();
                break;

            case 9:
                int qty, productId;

                printf("Enter Product ID: ");
                scanf("%d",&productId);

                printf("Enter Quantity: ");
                scanf("%d",&quantity);

                recordSale(productId,quantity);
                break;

            case 10:
                salesReport();
                break;

            case 11:
                loadStock();

            case 12:
                saveStock();

             case 13:
                printf("Exiting The System...\n");
                break;

            default:
                printf("Invalid Choice! \n");
                break;
        
    
}

int main()
{
    loadStock();
    menu();
    cleanSystem();

    return 0;
}