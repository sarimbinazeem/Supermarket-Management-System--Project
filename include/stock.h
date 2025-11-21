//Header File For Stock

#ifndef STOCK_H
#define STOCK_H

//Structure Added= For Each Product
typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
}Product;

typedef struct
{
    int saleID;
    int productID;
    char productName[50];
    int quantitySold;
    float totalPrice;
    char date[30]; //Added Date Array For Timestamps
}Sale;

//Function Prototypes
void addItem();
void displayStock();
void saveStock();
void loadStock();
void updateItem();
void deleteItem();
void lowStock();
void searchItems();
void sortByName();
void sortByPrice();
void pointerPrice(Product *p, float newPrice);
void recursiveDisplay (int index);
void recordSale(int productID, int quantitySold);
void salesReport();
void cleanSystem();
int getInteger();
float getFloating();


#endif
