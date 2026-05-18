#pragma once
#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    Node* root;

    void insert(Node*& node, int value);
    void print(Node* node);

public:
    Tree();
    void push(int value);
    void pop();
    void print();
    int height();
};