#include "include/customer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

struct CartItem {
    int productId;
    int quantity;
    float price;
    char name[50];
};

int loadInventory(struct Product items[], int maxItems) {
    FILE *fp = fopen("inventory.txt", "r");
    if (fp == NULL) {
        printf("Error opening inventory.txt\n");
        return 0;
    }

    int count = 0;
    while (count < maxItems && fscanf(fp, "%d %s %f %d",
        &items[count].id, items[count].name, &items[count].price, &items[count].quantity) == 4) {
        count++;
    }
    fclose(fp);
    return count;
}

void saveInventory(struct Product items[], int *count) {
    FILE *fp = fopen("inventory.txt", "w");
    if (fp == NULL) {
        printf("Error opening inventory.txt for writing!\n");
        return;
    }

    for (int i = 0; i < *count; i++) {
        fprintf(fp, "%d %s %.2f %d\n", items[i].id, items[i].name, items[i].price, items[i].quantity);
    }
    fclose(fp);
}

int findProductbyID(struct Product items[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (items[i].id == id)
            return i;
    }
    return -1;
}

void checkout() {
    const int maxProducts = 100;
    const int maxCartItems = 50;

    struct Product products[maxProducts];
    int productCount = loadInventory(products, maxProducts);

    if (productCount == 0) {
        printf("No products available in inventory.\n");
        return;
    }

    // Cart to store customer purchases
    struct CartItem cart[maxCartItems];
    int cartCount = 0;

    printf("\n--- Checkout ---\n");
    printf("Enter product ID and quantity (or 0 to finish):\n");

    while (1) {
        int id, qty;
        printf("Product ID: ");
        scanf("%d", &id);
        if (id == 0) break;

        printf("Quantity: ");
        scanf("%d", &qty);

        if (qty <= 0) {
            printf("Quantity must be positive.\n");
            continue;
        }

        int idf = findProductbyID(products, productCount, id);
        if (idf == -1) {
            printf("Product ID %d not found!\n", id);
            continue;
        }

        if (products[idf].quantity < qty) {
            printf("Insufficient stock for %s. Available: %d\n", products[idf].name, products[idf].quantity);
            continue;
        }

        // Add product to cart
        cart[cartCount].productId = id;
        cart[cartCount].quantity = qty;
        cart[cartCount].price = products[idf].price;
        strcpy(cart[cartCount].name, products[idf].name);
        cartCount++;

        if (cartCount >= maxCartItems) {
            printf("Cart full! Cannot add more items.\n");
            break;
        }
    }

    if (cartCount == 0) {
        printf("No items purchased.\n");
        return;
    }

    // Now Calculate and print receipt
    float total = 0.0;
    printf("\n--- Receipt ---\n");
    printf("ID\tName\tQty\tPrice\tTotal\n");

    for (int i = 0; i < cartCount; i++) {
        float itemTotal = cart[i].quantity * cart[i].price;
        printf("%d\t%s\t%d\t%.2f\t%.2f\n", cart[i].productId, cart[i].name, cart[i].quantity, cart[i].price, itemTotal);
        total += itemTotal;

        // Reduce stock in inventory
        int idf = findProductbyID(products, productCount, cart[i].productId);
        products[idf].quantity -= cart[i].quantity;
    }

    printf("-------------------------------\n");
    printf("Total Bill: %.2f\n", total);

    // Save updated inventory
    saveInventory(products, &productCount);
    

    printf("Thank you for shopping with us!\n");

    printf("\nEnter Customer ID: ");
    char customerID[10];
    scanf("%s", customerID);

    int vipStatus = addSpending(customerID, total);

    if (vipStatus) {
    printf("Congratulations! You are now a valued VIP customer.\n");
    }
}
