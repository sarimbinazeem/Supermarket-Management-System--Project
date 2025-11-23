#include <stdio.h>
#include <string.h>

struct Customer {
    char id[10];          
    float totalSpent;     
    int isVIP;            
};


int loadCustomer(char *custID, struct Customer *cust) {
    FILE *file = fopen("customers.txt", "r");
    if (file == NULL) {
        return 0;
    }

    while (fscanf(file, "%s %f %d", cust->id, &cust->totalSpent, &cust->isVIP) == 3) {
        if (strcmp(cust->id, custID) == 0) {
            fclose(file);
            return 1;  
        }
    }

    fclose(file);
    return 0;  
}

// Function to update or add customer spending in file
void updateCustomer(struct Customer *cust) {
    FILE *file = fopen("customers.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    int found = 0;

    if (file != NULL && temp != NULL) {
        struct Customer c;
        while (fscanf(file, "%s %f %d", c.id, &c.totalSpent, &c.isVIP) == 3) {
            if (strcmp(c.id, cust->id) == 0) {
                fprintf(temp, "%s %.2f %d\n", cust->id, cust->totalSpent, cust->isVIP);
                found = 1;
            } else {
                fprintf(temp, "%s %.2f %d\n", c.id, c.totalSpent, c.isVIP);
            }
        }
        fclose(file);

        // If not found, add new record
        if (!found) {
            fprintf(temp, "%s %.2f %d\n", cust->id, cust->totalSpent, cust->isVIP);
        }

        fclose(temp);

        // Replace old file with updated temp file
        remove("customers.txt");
        rename("temp.txt", "customers.txt");
    } else if (temp != NULL) {
        fprintf(temp, "%s %.2f %d\n", cust->id, cust->totalSpent, cust->isVIP);
        fclose(temp);
    }
}

// Function called after checkout to add spending and check VIP status
// Returns 1 if VIP, else 0
int addSpending(char *custID, float amount) {
    struct Customer cust;
    int found = loadCustomer(custID, &cust);

    if (!found) {
        strcpy(cust.id, custID);
        cust.totalSpent = amount;
        cust.isVIP = 0;
    } else {
        cust.totalSpent += amount;
    }

    if (cust.totalSpent >= 10000.0) {
        cust.isVIP = 1;
    }

    // Save updated record
    updateCustomer(&cust);

    return cust.isVIP;
}

void add_customer() {
    struct Customer cust;
    printf("Enter new Customer ID (max 9 chars): ");
    scanf("%9s", cust.id);

    // Check if customer already exists
    struct Customer tempCust;
    if (loadCustomer(cust.id, &tempCust)) {
        printf("Customer with ID %s already exists!\n", cust.id);
        return;
    }

    cust.totalSpent = 0.0;
    cust.isVIP = 0;

    updateCustomer(&cust);

    printf("Customer %s added successfully.\n", cust.id);
}


void search_customer() {
    char searchID[10];
    printf("Enter Customer ID to search: ");
    scanf("%9s", searchID);

    struct Customer cust;
    if (loadCustomer(searchID, &cust)) {
        printf("Customer found:\n");
        printf("ID: %s\n", cust.id);
        printf("Total Spent: %.2f\n", cust.totalSpent);
        printf("VIP Status: %s\n", cust.isVIP ? "YES" : "NO");
    } else {
        printf("Customer with ID %s not found.\n", searchID);
    }
}
