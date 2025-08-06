#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "product.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>  // for checking file existence

void ensureProductFileExists() {
    FILE *file = fopen("products.txt", "r");

    if (!file) {
        file = fopen("products.txt", "w");
        if (file) {
            // You can start with an empty file or default data
            fprintf(file, "101 Soap 75.0 12\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}
bool addProduct(int id, const char *name, float price,int stock) {
        ensureProductFileExists();
    FILE *fp = fopen("products.txt", "a");  // append in text mode
    if (!fp) {
        perror("File opening failed");       // show error in terminal
        return false;
    }

    fprintf(fp, "%d %s %.2f %d \n", id, name, price,stock);
    fclose(fp);
    return true;
}

bool updateProduct(int id, const char *name, float price,int stock) {
    ensureProductFileExists();

    FILE *fp = fopen("products.txt", "r");
    if (!fp) return false;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        return false;
    }

    struct Product p;
    bool found = false;

    // Read line by line in text mode (since you're using fprintf)
    while (fscanf(fp, "%d %s %f %d", &p.id, p.name, &p.price, &p.stock) == 4) {
        if (p.id == id) {
            // Update name and price
            strncpy(p.name, name, sizeof(p.name) - 1);
            p.name[sizeof(p.name) - 1] = '\0';
            p.price = price;
            found = true;
        }
        fprintf(temp, "%d %s %.2f %d\n", p.id, p.name, p.price, p.stock);
    }

    fclose(fp);
    fclose(temp);

    remove("products.txt");
    rename("temp.txt", "products.txt");

    return found;
}


bool deleteProduct(int id) {
    FILE *fp = fopen("products.txt", "r");
    if (!fp) return false;

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        return false;
    }

    int tempId, tempStock;
    char tempName[100];
    float tempPrice;
    int found = 0;

    while (fscanf(fp, "%d %s %f %d", &tempId, tempName, &tempPrice, &tempStock) == 4) {
        if (tempId == id) {
            found = 1; // Product to delete found — skip writing it
            continue;
        }
        fprintf(temp, "%d %s %.2f %d\n", tempId, tempName, tempPrice, tempStock);
    }

    fclose(fp);
    fclose(temp);

    // Replace original file with updated version
    remove("products.txt");
    rename("temp.txt", "products.txt");

    return found == 1;
}


bool viewproduct(int id, const char* name, struct Product* result) {
    ensureProductFileExists();
    FILE* file = fopen("products.txt", "r");
    if (!file) return false;

    struct Product temp;
    while (fscanf(file, "%d %s %f %d", &temp.id, temp.name, &temp.price, &temp.stock) == 4) {
        if (temp.id == id && strcmp(temp.name, name) == 0) {
            *result = temp;
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}
