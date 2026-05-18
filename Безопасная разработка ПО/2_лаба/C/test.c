#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

void read_file(char *filename) {
    char path[256];

    strcpy(path, "files/");
    strcat(path, filename);

    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char buffer[128];

    while (fgets(buffer, sizeof(buffer) * 4, file)) {
        printf(buffer);
    }

    fclose(file);
}
void login() {
    char username[32];
    char password[32];

    printf("Username: ");

    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Welcome admin!\n");
    } else {
        printf("Access denied\n");
    }
}
