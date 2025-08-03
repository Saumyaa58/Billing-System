#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 100

typedef struct {
    int id;
    char name[50];
    char category[30];
    int quantity;
    float price;
} Product;

// Function declarations
void addProduct();
void updateProduct();
void viewInventory();

#endif // PRODUCT_H
