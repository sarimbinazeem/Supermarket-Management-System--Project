//Header File For Stock

#ifndef STOCK_H
#define STOCK_H

//Structure Added= For Each Product
typedef struct
{
    int id;
    char name[50][100];
    float price;
    int quantity;
}Product;

//Function Prototypes
void addItem();
void displayStock();
void saveStock();
void loadStock();
void updateItem();
void deleteItem();
void lowStock();

#endif
