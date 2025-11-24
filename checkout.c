#include "customer.h"
#include "sales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct CartItem {
    int productId;
    int quantity;
    float price;
    char name[50];
};



int findItemByID(StockVariables *stock, int id) {
    for (int i = 0; i < stock->itemCount; i++) {
        if (stock->inventory[i].id == id) {
            return i;
        }
    }
    return -1;
}

void checkout(StockVariables *stock, SaleVariables *sales) {
    const int maxCartItems = 50;
    struct CartItem cart[maxCartItems];
    int cartCount = 0;

    if (stock->itemCount == 0) {
        printf("No products available in inventory.\n");
        return;
    }

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

        int idx = findItemByID(stock, id);
        if (idx == -1) {
            printf("Product ID %d not found!\n", id);
            continue;
        }

        if (stock->inventory[idx].quantity < qty) {
            printf("Insufficient stock for %s. Available: %d\n",
                   stock->inventory[idx].name,
                   stock->inventory[idx].quantity);
            continue;
        }

        // Add product to cart
        cart[cartCount].productId = id;
        cart[cartCount].quantity = qty;
        cart[cartCount].price = stock->inventory[idx].price;
        strcpy(cart[cartCount].name, stock->inventory[idx].name);
        cartCount++;

        // Reduce stock in main array immediately
        stock->inventory[idx].quantity -= qty;

        if (cartCount >= maxCartItems) {
            printf("Cart full! Cannot add more items.\n");
            break;
        }
    }

    if (cartCount == 0) {
        printf("No items purchased.\n");
        return;
    }

    // Print receipt and calculate total
    float total = 0;
    printf("\n--- Receipt ---\n");
    printf("ID\tName\tQty\tPrice\tTotal\n");

    for (int i = 0; i < cartCount; i++) {
        float itemTotal = cart[i].quantity * cart[i].price;
        printf("%d\t%s\t%d\t%.2f\t%.2f\n",
               cart[i].productId, cart[i].name, cart[i].quantity,
               cart[i].price, itemTotal);
        total += itemTotal;

        // Append sale to sales array
        appendSale(sales, cart[i].productId, cart[i].quantity, cart[i].price, itemTotal,cart[i].name);
    }

    printf("\nTotal Bill: %.2f\n", total);

    // Save updated stock to file
    saveStock(stock);

    // ---------------------------
    // Customer Logic
    // ---------------------------
    char customerID[10];
    printf("\nEnter Customer ID: ");
    scanf("%s", customerID);

    int vipStatus = addSpending(customerID, total);
    if (vipStatus) {
        printf("Congratulations! You are now a valued VIP customer.\n");
    }

    // Save all sales to file
    saveSales(sales->sales, sales->saleCount);
}