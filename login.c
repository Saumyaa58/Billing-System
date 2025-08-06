#include <stdio.h>
#include <string.h>
#include "login.h"

#define MAX_LINE_LENGTH 256

int authenticate(const char *username, const char *password) {
    FILE *file = fopen("users.txt", "r");
    if (!file) {
        return 0;  // Can't open file = failed login
    }

    char storedUser[100], storedPass[100];
    while (fscanf(file, "%s %s", storedUser, storedPass) != EOF) {
        if (strcmp(username, storedUser) == 0 && strcmp(password, storedPass) == 0) {
            fclose(file);
            return 1; // success
        }
    }

    fclose(file);
    return 0; // not found
}

int register_user(const char *username, const char *password) {
    // First, check if user already exists
    FILE *file = fopen("users.txt", "r");
    if (file) {
        char storedUser[100], storedPass[100];
        while (fscanf(file, "%s %s", storedUser, storedPass) != EOF) {
            if (strcmp(username, storedUser) == 0) {
                fclose(file);
                return 0;  // user already exists
            }
        }
        fclose(file);
    }

    // If user doesn't exist, append to file
    file = fopen("users.txt", "a");
    if (!file) {
        return 0; // can't open file to write
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    return 1; // success
}
