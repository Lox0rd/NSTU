#include "avl_tree.h"
#include <algorithm>

int AVLTree::getHeight(Node* node) {
    if (!node) return 0;
    return node->height;
}

int AVLTree::getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    updateHeight(node);
    int balance = getBalance(node);

    // Left Heavy
    if (balance > 1) {
        if (getBalance(node->left) >= 0) {
            return rotateRight(node); // LL
        } else {
            node->left = rotateLeft(node->left); // LR
            return rotateRight(node);
        }
    }

    // Right Heavy
    if (balance < -1) {
        if (getBalance(node->right) <= 0) {
            return rotateLeft(node); // RR
        } else {
            node->right = rotateRight(node->right); // RL
            return rotateLeft(node);
        }
    }

    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int value) {
    // 1. BST Insertion
    if (!node) return new Node(value);

    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    else
        return node; // No duplicates

    // 2. Update height and balance
    return balance(node);
}

void AVLTree::insert(int value) {
    root = insert(root, value);
}

bool AVLTree::search(Node* node, int value) const {
    if (!node) return false;
    if (value == node->data) return true;
    if (value < node->data)
        return search(node->left, value);
    else
        return search(node->right, value);
}

bool AVLTree::search(int value) const {
    return search(root, value);
}

void AVLTree::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

AVLTree::~AVLTree() {
    clear(root);
}
