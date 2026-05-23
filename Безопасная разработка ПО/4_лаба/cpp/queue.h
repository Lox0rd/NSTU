#include <iostream>
#ifndef QUEUE_H
#define QUEUE_H

class Queue {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;

        Node(int val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* front_node;
    Node* rear_node;
    int count;

public:
    Queue();

    void push(int value);
    void pop();
    int front() const;
    bool isEmpty() const;
    void print() const;
};

#endif
