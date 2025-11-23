#ifndef CUSTOMER_H
#define CUSTOMER_H


struct Customer {
    char id[10];
    float totalSpent;
    int isVIP;
};


int loadCustomer(char *custID, struct Customer *cust);
void updateCustomer(struct Customer *cust);
int addSpending(char *custID, float amount);
void add_customer();
void search_customer();

#endif
