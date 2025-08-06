#ifndef PRODUCT_H
#define PRODUCT_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NAME_SIZE 100

struct Product {
    int id;
    char name[NAME_SIZE];
    float price;
    int stock;
};
bool addProduct(int id, const char *name, float price,int stock);
bool updateProduct(int id, const char *name, float price,int stock);
bool deleteProduct(int id);
bool viewproduct(int id, const char* name, struct Product* result);
#ifdef __cplusplus
}
#endif

#endif // PRODUCT_H



