#include "queue.h"

void Queue::push(int value) {
    data.push_back(value);
}

void Queue::pop() {
    if (!data.empty())
        data.erase(data.begin());
}

void Queue::print() {
    std::cout << "Очередь: ";
    for (int x : data)
        std::cout << x << " ";
    std::cout << std::endl;
}

int Queue::front() {
    if (!data.empty())
        return data.front();
    return -1;
}