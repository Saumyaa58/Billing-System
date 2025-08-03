#include <stdio.h>
#include <stdlib.h>
#include "product.h"

void showMainMenu() {
    int choice;

    do {
        printf("\n=========== GROCIFY BILLING SYSTEM ===========\n");
        printf("1. Add Product\n");
        printf("2. Update Product\n");
        printf("3. Check Inventory\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                updateProduct();
                break;
            case 3:
                viewInventory();
                break;
            case 4:
                printf("Exiting... Thank you for using GROCIFY!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 4);
}

int main() {
    showMainMenu();
    return 0;
}

