#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "test.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Использование: %s <файл>\n", argv[0]);
        return 1;
    }

    char *test= (char *)malloc(256);
    strcpy(test, "Пример утечки");


    login();
    read_file(argv[1]);

    return 0;
}