#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Структура узла дерева
typedef struct TreeNode {
    int is_leaf;  //1 — узел содержит данные, 0 — содержит указатели
    union {
        char* data;  //строка данных (для концевых вершин)
        struct {
            struct TreeNode* left;
            struct TreeNode* right;
        } children;  //указатели на поддеревья (для внутренних вершин)
    } content;
} TreeNode;

//Создание нового концевого узла (с данными)
TreeNode* create_leaf(const char* str) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->is_leaf = 1;
    node->content.data = strdup(str);  //копируем строку
    return node;
}

//Создание нового внутреннего узла (с указателями)
TreeNode* create_internal() {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->is_leaf = 0;
    node->content.children.left = NULL;
    node->content.children.right = NULL;
    return node;
}

//Освобождение памяти, занятой деревом
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

//Основная функция вставки строки в дерево
TreeNode* insert_string(TreeNode* root, const char* str) {
    //Случай 1: дерево пустое
    if (root == NULL) {
        return create_leaf(str);
    }

    //Случай 2: текущий узел — концевой
    if (root->is_leaf) {
        //Создаём новый внутренний узел
        TreeNode* new_root = create_internal();

        //Определяем порядок: старая строка vs новая
        if (strcmp(root->content.data, str) <= 0) {
            //Старая строка <= новая: старая — слева, новая — справа
            new_root->content.children.left = root;
            new_root->content.children.right = create_leaf(str);
        } else {
            //Новая строка < старая: новая — слева, старая — справа
            new_root->content.children.left = create_leaf(str);
            new_root->content.children.right = root;
        }
        return new_root;
    }

    //Случай 3: текущий узел — внутренний
    //Находим самую левую концевую вершину в левом поддереве
    TreeNode* leftmost = root->content.children.left;
    while (!leftmost->is_leaf) {
        leftmost = leftmost->content.children.left;
    }

    //Сравниваем новую строку с данными левой концевой вершины
    if (strcmp(leftmost->content.data, str) >= 0) {
        //Новая строка <= левая концевая: вставляем в левое поддерево
        root->content.children.left = insert_string(root->content.children.left, str);
    } else {
        //Новая строка > левая концевая: вставляем в правое поддерево
        root->content.children.right = insert_string(root->content.children.right, str);
    }
    return root;
}

//Функция обхода дерева в порядке концевых вершин (симметричный обход)
void inorder_traversal(TreeNode* node) {
    if (node == NULL) return;

    if (node->is_leaf) {
        printf("%s ", node->content.data);
    } else {
        inorder_traversal(node->content.children.left);
        inorder_traversal(node->content.children.right);
    }
}

//Пример использования
int main() {
    TreeNode* root = NULL;

    //Вставляем строки
    root = insert_string(root, "banana");
    root = insert_string(root, "apple");
    root = insert_string(root, "cherry");
    root = insert_string(root, "date");

    //Выводим упорядоченные строки
    inorder_traversal(root);
    printf("\n");

    //Освобождаем память
    free_tree(root);
    return 0;
}
