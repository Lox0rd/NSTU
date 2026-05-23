#include "queue.h"


Queue::Queue() : front_node(nullptr), rear_node(nullptr), count(0) {}


void Queue::push(int value) {
    Node* newNode = new Node(value);

    if (isEmpty()) {
        front_node = rear_node = newNode;
    } else {
        rear_node->next = newNode;
        newNode->prev = rear_node;
        rear_node = newNode;
    }

    count++;
}

void Queue::pop() {
    if (isEmpty()) {
        return;
    }

    Node* temp = front_node;

    if (front_node == rear_node) {
        front_node = rear_node = nullptr;
    } else {
        front_node = front_node->next;
        front_node->prev = nullptr;
    }

    delete temp;
    count--;
}

int Queue::front() const {
    if (isEmpty()) {
        static const int Def_Val = 0;
        return Def_Val;
    }
    return front_node->value;
}

bool Queue::isEmpty() const {
    return count == 0;
}

void Queue::print() const {
    std::cout << "Очередь: ";
    if (!isEmpty()) {
        Node* current = front_node;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
    }
    std::cout << std::endl;
}
