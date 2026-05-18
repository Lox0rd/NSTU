#include <iostream>
#include "stack.h"
#include "queue.h"
#include "tree.h"

void printMenu() {
    std::cout << "\n=== Выберите структуру данных ===\n";
    std::cout << "1. Стек\n";
    std::cout << "2. Очередь\n";
    std::cout << "3. Дерево\n";
    std::cout << "0. Выход\n";
    std::cout << "Ваш выбор: ";
}

void stackMenu(Stack& s) {
    int choice, value;
    do {
        std::cout << "\n--- Стек ---\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Посмотреть верхний элемент\n";
        std::cout << "4. Вывести стек\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите значение: ";
                std::cin >> value;
                s.push(value);
                std::cout << "Элемент " << value << " добавлен в стек.\n";
                break;
            case 2:
                s.pop();
                break;
            case 3:
                std::cout << "Верхний элемент: " << s.peek();
                break;
            case 4:
                s.print();
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void queueMenu(Queue& q) {
    int choice, value;
    do {
        std::cout << "\n--- Очередь ---\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Посмотреть первый элемент\n";
        std::cout << "4. Вывести очередь\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите значение: ";
                std::cin >> value;
                q.push(value);
                std::cout << "Элемент " << value << " добавлен в очередь.\n";
                break;
            case 2:
                q.pop();
                break;
            case 3:
                q.front();
                std::cout << "Первый элемент элемент: " << q.front();
                break;
            case 4:
                q.print();
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void treeMenu(Tree& t) {
    int choice, value;
    do {
        std::cout << "\n--- Дерево ---\n";
        std::cout << "1. Добавить элемент\n";
        std::cout << "2. Удалить элемент\n";
        std::cout << "3. Вывести дерево (обход)\n";
        std::cout << "4. Показать высоту дерева\n";
        std::cout << "0. Назад\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Введите значение: ";
                std::cin >> value;
                t.push(value);
                std::cout << "Элемент " << value << " добавлен в дерево.\n";
                break;
            case 2:
                t.pop();
                break;
            case 3:
                t.print();
                break;
            case 4:
                std::cout << "Высота дерева: " << t.height() << "\n";
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (choice != 0);
}

int main() {
    Stack s;
    Queue q;
    Tree t;
    int mainChoice;
    do {
        printMenu();
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                stackMenu(s);
                break;
            case 2:
                queueMenu(q);
                break;
            case 3:
                treeMenu(t);
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    } while (mainChoice != 0);

    return 0;
}
