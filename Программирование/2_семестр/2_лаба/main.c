#include <stdio.h>
#include <stdlib.h>

typedef struct CSpis {
    int data;
    struct CSpis* next;
} CSpis;

CSpis* createCSpis(int value) {
    CSpis* newCSpis = (CSpis*)malloc(sizeof(CSpis));
    if (!newCSpis) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    newCSpis->data = value;
    newCSpis->next = NULL;
    return newCSpis;
}

void insert(CSpis** last, int value) {
    CSpis* newCSpis = createCSpis(value);

    if (*last == NULL) {
        newCSpis->next = newCSpis;  //единственный элемент указывает на себя
        *last = newCSpis;
    } else {
        newCSpis->next = (*last)->next;  //новый узел указывает на первый
        (*last)->next = newCSpis;       //последний указывает на новый
        *last = newCSpis;              //обновляем указатель на последний
    }
}

void printList(CSpis* last) {
    if (last == NULL) {
        printf("Список пуст\n");
        return;
    }

    CSpis* current = last->next;
    do {
        printf("%d ", current->data);
        current = current->next;
    } while (current != last->next);
    printf("\n");
}

CSpis* difference(CSpis* lastA, CSpis* lastB) {
    if (lastA == NULL) return NULL;

    CSpis* resultLast = NULL;  //указатель на последний элемент результата
    CSpis* currentA = lastA->next;  

    do {
        int foundInB = 0; 
        CSpis* currentB = lastB ? lastB->next : NULL;

        if (currentB) {
            do {
                if (currentB->data == currentA->data) {
                    foundInB = 1;
                    break;
                }
                currentB = currentB->next;
            } while (currentB != lastB->next);
        }
        if (!foundInB) {
            insert(&resultLast, currentA->data);
        }

        currentA = currentA->next;
    } while (currentA != lastA->next);

    return resultLast;
}

int main() {
    CSpis* listA = NULL;
    CSpis* listB = NULL;
    CSpis* diff = NULL;

    insert(&listA, 1);
    insert(&listA, 2);
    insert(&listA, 3);
    insert(&listA, 4);

    insert(&listB, 2);
    insert(&listB, 4);
    insert(&listB, 5);

    printf("Список A: ");
    printList(listA);
    printf("Список B: ");
    printList(listB);

    //Вычисляем разность A - B
    diff = difference(listA, listB);

    printf("Разность A - B: ");
    printList(diff);

    return 0;
}
