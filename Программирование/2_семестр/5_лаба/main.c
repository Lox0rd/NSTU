#include <stdio.h>
#include <stdlib.h>

typedef struct CSpis {
    int data;
    struct CSpis* next;
} CSpis;

// Типы указателей на функции
typedef int (*CompareFunc)(int, int);
typedef void (*PrintFunc)(int);
typedef CSpis* (*CreateFunc)(int);

// Базовая функция создания узла
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

// Универсальная функция вставки с возможностью кастомизации
void insert(CSpis** last, int value, CreateFunc creator) {
    CSpis* newCSpis = creator(value);

    if (*last == NULL) {
        newCSpis->next = newCSpis;  // единственный элемент указывает на себя
        *last = newCSpis;
    } else {
        newCSpis->next = (*last)->next;  // новый узел указывает на первый
        (*last)->next = newCSpis;       // последний указывает на новый
        *last = newCSpis;              // обновляем указатель на последний
    }
}

// Универсальная функция печати с возможностью кастомизации вывода
void printList(CSpis* last, PrintFunc printer) {
    if (last == NULL) {
        printf("Список пуст\n");
        return;
    }

    CSpis* current = last->next;
    do {
        printer(current->data);
        printf(" ");
        current = current->next;
    } while (current != last->next);
    printf("\n");
}

// Функция сравнения для целых чисел
int compareInt(int a, int b) {
    return a == b;
}

// Универсальная функция разности с использованием функции сравнения
CSpis* difference(CSpis* lastA, CSpis* lastB, CompareFunc comparator) {
    if (lastA == NULL) return NULL;

    CSpis* resultLast = NULL;  // указатель на последний элемент результата
    CSpis* currentA = lastA->next;

    do {
        int foundInB = 0;
        CSpis* currentB = lastB ? lastB->next : NULL;

        if (currentB) {
            do {
                if (comparator(currentB->data, currentA->data)) {
                    foundInB = 1;
                    break;
                }
                currentB = currentB->next;
            } while (currentB != lastB->next);
        }
        if (!foundInB) {
            insert(&resultLast, currentA->data, createCSpis);
        }

        currentA = currentA->next;
    } while (currentA != lastA->next);

    return resultLast;
}

// Кастомизированная функция печати
void customPrint(int value) {
    printf("[%d]", value);  // вывод в квадратных скобках
}

int main() {
    CSpis* listA = NULL;
    CSpis* listB = NULL;
    CSpis* diff = NULL;

    // Используем указатель на функцию создания
    CreateFunc creator = createCSpis;

    insert(&listA, 1, creator);
    insert(&listA, 2, creator);
    insert(&listA, 3, creator);
    insert(&listA, 4, creator);

    insert(&listB, 2, creator);
    insert(&listB, 4, creator);
    insert(&listB, 5, creator);

    // Используем разные функции печати
    PrintFunc defaultPrinter = printf;
    PrintFunc customPrinter = customPrint;

    printf("Список A (стандартный вывод): ");
    printList(listA, defaultPrinter);

    printf("Список B (кастомный вывод): ");
    printList(listB, customPrinter);

    // Используем указатель на функцию сравнения
    CompareFunc comparator = compareInt;

    // Вычисляем разность A - B
    diff = difference(listA, listB, comparator);

    printf("Разность A - B: ");
    printList(diff, defaultPrinter);

    return 0;
}
