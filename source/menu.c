#include <stdio.h>
#include "menu.h"
#include "input.h"
#include "stock.h"
#include "sales.h"
#include "report.h"
#include "screen.h"
#include "customer.h"
#include "checkout.h"


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
        printf("5.Search For An Item\n");
        printf("6.Sort Stock By Name\n");
        printf("7.Sort Stock By Price\n");
        printf("0.Exit\n");

        choice = getInteger("Enter choice: ", 0, 9);
        
system("cls");
        //Switch cases for each cases
        switch(choice)
        {
            case 1: //Add New Items
                addItem(stock);
                pauseScreen();
                system("cls");
                break;
            
            case 2: //Display ALL Stocks
                displayStock(stock);
                pauseScreen();
                system("cls");
                break;

            case 3: //update an items price and quantity
                updateItem(stock);
                pauseScreen();
                system("cls");
                break;

            case 4: //Delete an Item FROm Stock
                deleteItem(stock);
                pauseScreen();
                system("cls");
                break;
            
            case 5: //Search For An Item To Get Its Details
                searchItems(stock);
                pauseScreen();
                system("cls");
                break;

            case 6: //Sort The Stock By Name
                sortByName(stock);
                pauseScreen();
                system("cls");
                break;

            case 7: //Sort The Stock By Price
                sortByPrice(stock);
                pauseScreen();
                system("cls");
                break;

             case 0: //Exiting THe Program
                printf("Logging Out...\n");
                 pauseScreen();
                system("cls");
                break;

            default: //Invalid Case
                printf("Invalid Choice! \n");
                pauseScreen();
                system("cls");
                break;
        }
            
    } while (choice != 0);
    
}

void cashierMenu(StockVariables *stock, SaleVariables *sales)
{
    int choice;

    do
    {
        //Menu For CUstomer
        printf("\n=====Cashier Menu=====\n");
        printf("1.Add Customers\n");
        printf("2.Search Customer\n");
        printf("3.Checkout\n");
        printf("4.Sales Report\n");
        printf("0.Back To Main Menu\n");

        choice = getInteger("Enter choice: ", 0, 9);

        //Switch Cases For All Cases
        switch(choice)
        {
            case 1:
                add_customer();      // from customer.c
                pauseScreen();
                system("cls");
                break;

            case 2:
                search_customer();   // from customer.c
                pauseScreen();
                system("cls");
                break;

            case 3:
                 checkout(stock,sales);           // from checkout.c
                pauseScreen();
                system("cls");
                break;

             case 4: //Record The Sale Of CUstomer
                reportMenu(stock , sales);
                 pauseScreen();
                system("cls");
                break;
            

            case 0: //Exiting The Program
                printf("Returning...\n");
                pauseScreen();
                system("cls");
                break;

            default: //Invalid Program
                printf("Invalid Choice! \n");
                pauseScreen();
                system("cls");
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
        printf("2.Cashier Mode \n");
        printf("0.Exit\n");
        choice = getInteger("Enter choice: ", 0, 9);


        //Switch Cases To get All Cases
        switch(choice)
        {
            case 1: //To Show Menu For Admin
                adminMenu(stock, sales,sle);
                pauseScreen();
                system("cls");
                break;

            case 2: //To Show Menu For Cashiers
                cashierMenu(stock, sales);
                pauseScreen();
                system("cls");
                break;

            case 0: //To Exit The Program after saving Data to FIle
                saveSales(sales->sales ,sales ->saleCount);
                saveStock(stock);

                printf("Data Saved. Exiting The Program...\n");
                break;

            default: //Invalid Case
                printf("Invalid Choice! \n");
                pauseScreen();
                system("cls");
                break;
        }
    } while(choice != 0);
}

int login()
{
    char username[15];
    char password[15];
    int attempts =0;

    while(attempts<3)
    {
        printf("\n==========SuperMarket Login Authentication==========\n");
        printf("Enter Username: ");
        scanf (" %14s", &username);
        printf("Enter Password: ");
        scanf (" %14s", &password);

        if (strcmp (username, "admin")== 0 && strcmp(password, "1234")==0)
        {
            printf ("Login details verified\n Welcome Back\n");
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

void reportMenu(StockVariables *stock, SaleVariables *sales)
{
    int choice;
    do
    {
        printf("\n--- REPORT MENU ---\n");
        printf("1. Display Remaining Stock\n");
        printf("2. Display Daily Sales\n");
        printf("3. Display Low-Stock Items\n");
        printf("4. Display Valued Customers\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayRemainingStock(stock);
            pauseScreen();
                system("cls");
            break;
        case 2:
            displayDailySales(sales);
            pauseScreen();
                system("cls");
            break;
        case 3:
            displayLowStock(stock);
            pauseScreen();
             system("cls");
            break;
        case 4:
            displayValuedCustomers();
            pauseScreen();
             system("cls");
            break;

        case 5:
            printf("Returning...\n");
            pauseScreen();
            system("cls");
            return;

        default:
            printf("Invalid choice! Try again.\n");
            pauseScreen();
                system("cls");
        }
    } while (choice != 5);

}

