#include "stack.h"

void Stack::push(int value) {
    data.push_back(value);
}

void Stack::pop() {
    if (!data.empty())
        data.pop_back();
}

void Stack::print() {
    std::cout << "Стек: ";
    for (int x : data)
        std::cout << x << " ";
    std::cout << std::endl;
}

int Stack::peek() {
    if (!data.empty())
        return data.back();
    return -1;
}