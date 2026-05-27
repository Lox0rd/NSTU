#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int is_leaf;
    union {
        char* data;
        struct {
            struct TreeNode* left;
            struct TreeNode* right;
        } children;
    } content;
} TreeNode;

TreeNode* create_leaf(const char* str) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->is_leaf = 1;
    node->content.data = strdup(str);
    return node;
}

TreeNode* create_internal() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->is_leaf = 0;
    node->content.children.left = NULL;
    node->content.children.right = NULL;
    return node;
}

void free_tree(TreeNode* node) {
    if (node == NULL) return;

    if (node->is_leaf) {
        free(node->content.data);
    } else {
        free_tree(node->content.children.left);
        free_tree(node->content.children.right);
    }
    free(node);
}

TreeNode* insert_string(TreeNode* root, const char* str) {
    if (root == NULL) {
        return create_leaf(str);
    }

    if (root->is_leaf) {
        TreeNode* new_root = create_internal();

        if (strcmp(root->content.data, str) <= 0) {
            new_root->content.children.left = root;
            new_root->content.children.right = create_leaf(str);
        } else {
            new_root->content.children.left = create_leaf(str);
            new_root->content.children.right = root;
        }
        return new_root;
    }

    TreeNode* leftmost = root->content.children.left;
    while (!leftmost->is_leaf) {
        leftmost = leftmost->content.children.left;
    }

    if (strcmp(leftmost->content.data, str) >= 0) {
        root->content.children.left = insert_string(root->content.children.left, str);
    } else {
        root->content.children.right = insert_string(root->content.children.right, str);
    }
    return root;
}

void inorder_traversal(TreeNode* node) {
    if (node == NULL) return;

    if (node->is_leaf) {
        printf("%s ", node->content.data);
    } else {
        inorder_traversal(node->content.children.left);
        inorder_traversal(node->content.children.right);
    }
}

int main() {
    TreeNode* root = NULL;

    root = insert_string(root, "banana");
    root = insert_string(root, "apple");
    root = insert_string(root, "cherry");
    root = insert_string(root, "date");

    inorder_traversal(root);
    printf("\n");

    free_tree(root);
    return 0;
}
