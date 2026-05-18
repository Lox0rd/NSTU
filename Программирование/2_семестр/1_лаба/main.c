#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOTTOM_SIZE 10

char*** read_words_to_array(const char* filename, int* top_size) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        *top_size = 0;
        return NULL;
    }
    
    int cap = 10;
    char*** top = (char***)malloc(cap * sizeof(char**));
    *top_size = 0;
    
    char word[256];
    
    while (fscanf(f, "%255s", word) == 1) {
        char* new_word = (char*)malloc(strlen(word) + 1);
        strcpy(new_word, word);
        
        //Ищем место для вставки
        int pos = 0;
        while (pos < *top_size && top[pos][0] != NULL && strcmp(new_word, top[pos][0]) > 0) {
            pos++;
        }
        
        //Вставляем в блок с индексом pos
        if (pos < *top_size) {
            char** block = top[pos];
            
            //Считаем сколько элементов в блоке
            int cnt = 0;
            while (block[cnt] != NULL) cnt++;
            
            if (cnt < BOTTOM_SIZE) {
                //Место есть - вставляем с сохранением порядка
                int ins = 0;
                while (ins < cnt && strcmp(new_word, block[ins]) > 0) ins++;
                
                for (int i = cnt; i > ins; i--) {
                    block[i] = block[i-1];
                }
                block[ins] = new_word;
            } else {
                //Переполнение - делим блок пополам
                int half = BOTTOM_SIZE / 2;
                
                //Создаем новый блок для второй половины
                char** new_block = (char**)malloc((BOTTOM_SIZE + 1) * sizeof(char*));
                for (int i = half; i < BOTTOM_SIZE; i++) {
                    new_block[i - half] = block[i];
                }
                new_block[BOTTOM_SIZE - half] = NULL;
                
                //Обрезаем текущий блок
                block[half] = NULL;
                
                //Расширяем верхний массив если нужно
                if (*top_size + 1 >= cap) {
                    cap *= 2;
                    top = (char***)realloc(top, cap * sizeof(char**));
                }
                
                //Сдвигаем элементы вверх
                for (int i = *top_size; i > pos + 1; i--) {
                    top[i] = top[i-1];
                }
                top[pos + 1] = new_block;
                (*top_size)++;
                
                //Вставляем слово в нужный блок
                if (strcmp(new_word, block[0]) < 0) {
                    //Вставляем в первый блок
                    for (int i = cnt; i > 0; i--) {
                        block[i] = block[i-1];
                    }
                    block[0] = new_word;
                } else {
                    //Вставляем во второй блок
                    int new_cnt = BOTTOM_SIZE - half;
                    for (int i = new_cnt; i > 0; i--) {
                        new_block[i] = new_block[i-1];
                    }
                    new_block[0] = new_word;
                }
            }
        } else {
            //Создаем новый блок в конце
            if (*top_size + 1 >= cap) {
                cap *= 2;
                top = (char***)realloc(top, cap * sizeof(char**));
            }
            
            char** new_block = (char**)malloc((BOTTOM_SIZE + 1) * sizeof(char*));
            new_block[0] = new_word;
            for (int i = 1; i <= BOTTOM_SIZE; i++) {
                new_block[i] = NULL;
            }
            
            top[*top_size] = new_block;
            (*top_size)++;
        }
    }
    
    fclose(f);
    return top;
}

int main() {
    int size;
    char*** words = read_words_to_array("input.txt", &size);
    
    //Вывод результата
    for (int i = 0; i < size; i++) {
        printf("Block %d: ", i);
        for (int j = 0; words[i][j] != NULL; j++) {
            printf("%s ", words[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}