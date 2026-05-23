#ifndef AVL_TREE_H
#define AVL_TREE_H

class AVLTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        int height;

        Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node);
    int getBalance(Node* node);
    void updateHeight(Node* node);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree();

    void insert(int value);
    bool search(int value) const;

private:
    Node* insert(Node* node, int value);
    bool search(Node* node, int value) const;
    void clear(Node* node);
};

#endif
