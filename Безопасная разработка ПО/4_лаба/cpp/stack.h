#pragma once
#include <vector>
#include <iostream>

class Stack {
private:
    std::vector<int> data;

public:
    void push(int value);
    void pop();
    void print();
    int peek();
};