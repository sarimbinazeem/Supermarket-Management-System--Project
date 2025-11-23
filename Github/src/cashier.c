#include <stdio.h>
#include "../include/customer.h"
#include "../include/checkout.h"


void cashier_menu()
{
    int choice;

    do {
        printf("\n---Cashier Menu---");
        printf("\n1.Add Customer");
        printf("\n2.Search Customer");
        printf("\n3.Checkout (Billing)");
        // printf("\n4.View Sales Report");
        printf("\n5.Back to Main Menu");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                add_customer();      // from customer.c
                break;

            case 2:
                search_customer();   // from customer.c
                break;

            case 3:
                checkout();          // from checkout.c
                break;

            // case 4:
            //     generate_report();   // from report.c
            //     break;

            case 5:
                printf("\nReturning to main menu...\n");
                return;

            default:
                printf("\nInvalid Choice! Try again.\n");
        }

    } while(choice != 5);
}
