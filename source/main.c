#include <stdio.h>
#include "../include/stock.h"

void menu()
{
    int choice;

    while(1)
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
        printf("9.Exit\n");

        printf("Ener Your Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
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
                printf("Exiting The System...\n");
                break;

            default:
                printf("Invalid Choice! \n");
                break;
        }
    }
}

int main()
{
    loadStock();
    menu();
    return 0;
}