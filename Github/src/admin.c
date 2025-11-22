#include<stdio.h> 
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

void adminMenu(struct Product items[], int *count);
void addProduct(struct Product items[], int *count);
void viewInventory(struct Product items[], int *count);
void saveInventory(struct Product items[], int *count);

void adminMenu(struct Product items[], int *count) {
    int choice;

    do {
        printf("--ADMIN MENU --\n");
        printf("1.Add Product\n");
        printf("2.View Inventory\n");
        printf("3.Save Inventory\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addProduct(items, count);
                break;
            case 2:
                viewInventory(items, count);  
                break;
            case 3:
                saveInventory(items, count);
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
        
    } while (choice != 3);
}

void addProduct(struct Product items[], int *count)
{
    printf("Enter Product ID: ");
    scanf("%d", &items[*count].id);

    printf("Enter Product Name: ");
    scanf("%s", items[*count].name);

    printf("Enter Price: ");
    scanf("%f", &items[*count].price);

    printf("Enter Quantity: ");
    scanf("%d", &items[*count].quantity);

    (*count)++;

    printf("\nProduct added successfully!\n");
}

void viewInventory(struct Product items[], int *count) {
    printf("ID\tName\tPrice\tQuantity\n");

    for (int i = 0; i < *count; i++) {
        printf("%d\t%s\t%.2f\t%d\n", 
            items[i].id, 
            items[i].name, 
            items[i].price, 
            items[i].quantity
        );
    }
}

void saveInventory(struct Product items[], int *count)
{
    FILE *fpt = fopen("inventory.txt", "w");

    if (fpt == NULL) {
        printf("Error opening file");
        return;
    }

    int i;
    for (i = 0; i < *count; i++) {
        fprintf(fpt, "%d %s %.2f %d\n",   
            items[i].id,
            items[i].name,
            items[i].price,
            items[i].quantity
        );
    }

    fclose(fpt);   
    printf("Inventory saved successfully!\n");
}