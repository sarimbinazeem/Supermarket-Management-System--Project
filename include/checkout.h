#ifndef CHECKOUT_H
#define CHECKOUT_H

// Product structure for inventory
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

// Cart item for billing
struct CartItem {
    int productId;
    int quantity;
    float price;
    char name[50];
};

// Functions related to checkout process
int loadInventory(struct Product items[], int maxItems);
void saveInventory(struct Product items[], int *count);
int findProductbyID(struct Product items[], int count, int id);
void checkout();

#endif