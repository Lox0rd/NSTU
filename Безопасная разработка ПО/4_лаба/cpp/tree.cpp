#include "tree.h"
#include <functional>

Tree::Tree() {
    root = nullptr;
}

void Tree::insert(Node*& node, int value) {
    if (!node) {
        node = new Node(value);
        return;
    }

    if (value < node->value)
        insert(node->left, value);
    else
        insert(node->right, value);
}

void Tree::push(int value) {
    insert(root, value);
}


void Tree::pop() {
    Node* parent = nullptr;
    Node* curr = root;

    if (!root) return;

    while (curr->left) {
        parent = curr;
        curr = curr->left;
    }

    if (parent)
        parent->left = curr->right;
    else
        root = curr->right;

    delete curr;
}

void Tree::print(Node* node) {
    if (!node) return;
    print(node->left);
    std::cout << node->value << " ";
    print(node->right);
}

void Tree::print() {
    std::cout << "Дерево: ";
    print(root);
    std::cout << std::endl;
}

int Tree::height() {
    std::function<int(Node*)> h = [&](Node* n) {
        if (!n) return 0;
        return 1 + std::max(h(n->left), h(n->right));
    };

    return h(root);
}