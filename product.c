#include <stdio.h>
#include <string.h>
#include "product.h"

Product products[MAX_PRODUCTS];
int productCount = 0;

void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory Full!\n");
        return;
    }

    Product p;
    printf("\n--- Add Product ---\n");
    printf("Enter ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Category: ");
    scanf(" %[^\n]", p.category);
    printf("Enter Price: ");
    scanf("%f", &p.price);
    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);

    products[productCount++] = p;
    printf("Product Added Successfully!\n");
}

void updateProduct() {
    int id, found = 0;
    printf("\n--- Update Product ---\n");
    printf("Enter Product ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < productCount; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %[^\n]", products[i].name);
            printf("Enter new Category: ");
            scanf(" %[^\n]", products[i].category);
            printf("Enter new Price: ");
            scanf("%f", &products[i].price);
            printf("Enter new Quantity: ");
            scanf("%d", &products[i].quantity);
            printf("Product Updated Successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Product not found.\n");
    }
}

void viewInventory() {
    printf("\n--- Inventory ---\n");
    if (productCount == 0) {
        printf("No products available.\n");
        return;
    }

    for (int i = 0; i < productCount; i++) {
        printf("\nID: %d\nName: %s\nCategory: %s\nPrice: %.2f\nQuantity: %d\n",
               products[i].id, products[i].name, products[i].category,
               products[i].price, products[i].quantity);
    }
}
