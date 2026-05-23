#include <iostream>
#ifndef STACK_H
#define STACK_H
class Stack {
private:
    int* data;        
    int capacity;     
    int top;          

    void resize();    

public:
    Stack();

    void push(int value);
    void pop();
    int peek();
    void print();
    bool isEmpty() const;
};

#endif
