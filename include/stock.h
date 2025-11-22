//Header File For Stock

#ifndef STOCK_H
#define STOCK_H


//Structure Added For Each Product
typedef struct
{
    int id;
    char name[50];
    float price;
    int quantity;
}Product;


typedef struct
{
    Product *inventory;
    int itemCount;
    int capacity;
} StockVariables;



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
void capacityUpdater(StockVariables*s)
void addItem(StockVariables *s);
void displayStock(StockVariables *s);
void saveStock(StockVariables *s);
void loadStock(StockVariables *s);
void updateItem(StockVariables *s);
void deleteItem(StockVariables *s);
void lowStock(StockVariables *s);
void searchItems(StockVariables *s);
void sortByName(StockVariables *s);
void sortByPrice(StockVariables *s);
void pointerPrice(Product *p, float newPrice);
void recursiveDisplay (StockVariables*s ,int index);
void recordSale(StockVariables *s,int productID, int quantitySold);
void salesReport();
void cleanSystem(StockVariables *s);
int getInteger();
float getFloating();


#endif
