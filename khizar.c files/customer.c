#include <stdio.h>
#include <string.h>
#include "customer.h"

// Load customer from customers.txt
int loadCustomer(const char *custID, struct Customer *cust) {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        return 0;   // No customer file exists yet
    }

    while (fscanf(file, "%s %f %d", 
                  cust->id, &cust->totalSpent, &cust->isVIP) == 3) 
    {
        if (strcmp(cust->id, custID) == 0) {
            fclose(file);
            return 1;   // Found
        }
    }

    fclose(file);
    return 0;   // Not found
}

// Update or add customer in customers.txt
void updateCustomer(struct Customer *cust) {
    FILE *file = fopen("customers.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL) return;

    int found = 0;

    if (file != NULL) {
        struct Customer c;

        while (fscanf(file, "%s %f %d", 
                      c.id, &c.totalSpent, &c.isVIP) == 3) 
        {
            if (strcmp(c.id, cust->id) == 0) {
                fprintf(temp, "%s %.2f %d\n", 
                        cust->id, cust->totalSpent, cust->isVIP);
                found = 1;
            } else {
                fprintf(temp, "%s %.2f %d\n", 
                        c.id, c.totalSpent, c.isVIP);
            }
        }

        fclose(file);
    }

    if (!found) {
        fprintf(temp, "%s %.2f %d\n", 
                cust->id, cust->totalSpent, cust->isVIP);
    }

    fclose(temp);

    remove("customers.txt");
    rename("temp.txt", "customers.txt");
}

// Add customer spending after checkout
int addSpending(const char *custID, float amount) {
    struct Customer cust;
    int found = loadCustomer(custID, &cust);

    if (!found) {
        strcpy(cust.id, custID);
        cust.totalSpent = amount;
        cust.isVIP = 0;
    } else {
        cust.totalSpent += amount;
    }

    // VIP threshold
    if (cust.totalSpent >= 10000.0) {
        cust.isVIP = 1;
    }

    updateCustomer(&cust);

    return cust.isVIP;
}

// Add new customer manually
void add_customer() {
    struct Customer cust;

    printf("Enter new Customer ID (max 9 chars): ");
    scanf("%9s", cust.id);

    struct Customer temp;

    if (loadCustomer(cust.id, &temp)) {
        printf("Customer %s already exists.\n", cust.id);
        return;
    }

    cust.totalSpent = 0.0;
    cust.isVIP = 0;

    updateCustomer(&cust);

    printf("Customer %s added successfully.\n", cust.id);
}

// Search customer
void search_customer() {
    char id[10];

    printf("Enter Customer ID to search: ");
    scanf("%9s", id);

    struct Customer cust;

    if (loadCustomer(id, &cust)) {
        printf("\nCustomer Found:\n");
        printf("ID: %s\n", cust.id);
        printf("Total Spent: %.2f\n", cust.totalSpent);
        printf("VIP: %s\n", cust.isVIP ? "YES" : "NO");
    } else {
        printf("Customer %s not found.\n", id);
    }
}