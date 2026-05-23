#include "stack.h"


Stack::Stack() : capacity(4), top(-1) {
    data = new int[capacity];
}

void Stack::push(int value) {
    if (top == capacity - 1) {
        resize();
    }
    data[++top] = value;
}

void Stack::pop() {
    if (!isEmpty()) {
        top--;
    }
}

int Stack::peek() {
    if (!isEmpty()) {
        return data[top];
    }
    throw std::out_of_range("Стек пуст, нет верхнего элемента!");
}

void Stack::print() {
    std::cout << "Стек: ";
    for (int i = 0; i <= top; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}


bool Stack::isEmpty() const {
    return top == -1;
}

void Stack::resize() {
    capacity *= 2;
    int* newData = new int[capacity];

    for (int i = 0; i <= top; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
}
