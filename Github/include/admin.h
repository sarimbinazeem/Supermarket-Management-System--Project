#ifndef ADMIN_H
#define ADMIN_H

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

#endif