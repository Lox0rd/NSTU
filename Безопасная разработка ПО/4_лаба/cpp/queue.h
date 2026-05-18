#pragma once
#include <vector>
#include <iostream>

class Queue {
private:
    std::vector<int> data;

public:
    void push(int value);
    void pop();
    void print();
    int front();
};