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
        printf("3.Exit\n");
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