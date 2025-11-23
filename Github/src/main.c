#include "../include/admin.h"
#include "../include/cashier.h"
#include "../include/checkout.h"
#include "../include/customer.h"
#include "../include/report.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Product items[100];
int count = 0;

int login()
void displaymenu()

int main()
{
    if(login())
        displaymenu();
    else{
        printf ("Login details are not verified\nTry Again Later");
    }
    return 0;
}

int login()
{
    char username[15];
    int password[15];
    int attempts =0;

    while(attempts<3)
    {
        printf("Enter Username: ");
        scanf (" %[A-Za-z]", &username);
        printf("Enter Password: ");
        scanf ("%d", &password);

        if (strcmp (username, "admin")== 0 && strcmp(password, "1234")==0)
        {
            printf ("Login details verified\n Welcome Back");
            return 1;
        }
        else {
            printf("\nIncorrect Username or Password");
            attempts++;
        }
    }
    printf("\nToo many failed attempts\n");
    return 0;
}

void displaymenu()
{
    int choice;
    do{
       printf("\n--- SUPERMARKET MANAGEMENT SYSTEM ---");
        printf("\n1.Admin Menu");
        printf("\n2.Cashier Menu");
        printf("\n3.Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
            case 1:
                admin_menu();
                break;
            case 2:
                cashier_menu();
                break;
            case 3:
                printf("\nExiting System...");
                break;
            default:
                printf("\nInvalid choice! Please try again.");
        }
    } while (choice != 3);
}