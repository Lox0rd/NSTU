#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Структура узла дерева
typedef struct Node {
    int is_constant;  // 1 — константа, 0 — операция
    int value;        // значение константы или код операции
    struct Node* left;
    struct Node* right;
} Node;

// Создание нового узла
Node* create_node(int is_constant, int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    node->is_constant = is_constant;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Освобождение памяти дерева
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

// Поиск оператора с наименьшим приоритетом (кроме тех, что внутри скобок)
int find_operator(const char* expr, int start, int end) {
    int balance = 0;
    int pos = -1;

    for (int i = end; i >= start; i--) {
        if (expr[i] == ')') balance++;
        else if (expr[i] == '(') balance--;

        if (balance == 0) {
            if (expr[i] == '+' || expr[i] == '-') {
                return i;  // + и - имеют наименьший приоритет
            } else if ((expr[i] == '*' || expr[i] == '/') && pos == -1) {
                pos = i;  // * и / имеют более высокий приоритет
            }
        }
    }
    return pos;
}

// Построение дерева из выражения
Node* build_tree(const char* expr, int start, int end) {
    // Пропускаем пробелы
    while (start <= end && expr[start] == ' ') start++;
    while (end >= start && expr[end] == ' ') end--;

    if (start > end) return NULL;

    // Если выражение в скобках, убираем внешние скобки
    if (expr[start] == '(' && expr[end] == ')') {
        int balance = 0;
        for (int i = start; i <= end; i++) {
            if (expr[i] == '(') balance++;
            else if (expr[i] == ')') balance--;

            if (balance == 0 && i != end) break;
        }
        if (balance == 0) {
            start++;
            end--;
        }
    }

    // Ищем оператор с наименьшим приоритетом
    int op_pos = find_operator(expr, start, end);

    if (op_pos == -1) {
        // Это константа
        int value = 0;
        for (int i = start; i <= end; i++) {
            if (isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
            }
        }
        return create_node(1, value);
    } else {
        // Создаём узел с операцией
        Node* node = create_node(0, expr[op_pos]);
        node->left = build_tree(expr, start, op_pos - 1);
        node->right = build_tree(expr, op_pos + 1, end);
        return node;
    }
}

// Вычисление значения выражения по дереву
int evaluate(Node* node) {
    if (node == NULL) return 0;

    if (node->is_constant) {
        return node->value;
    } else {
        int left_val = evaluate(node->left);
        int right_val = evaluate(node->right);

        switch (node->value) {
            case '+': return left_val + right_val;
            case '-': return left_val - right_val;
            case '*': return left_val * right_val;
            case '/':
                if (right_val != 0) return left_val / right_val;
                else {
                    printf("Ошибка: деление на ноль!\n");
                    exit(1);
                }
        }
    }
    return 0;
}

// Обход дерева с выводом (с отступами для визуализации структуры)
void print_tree(Node* node, int depth) {
    if (node == NULL) return;

    print_tree(node->right, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");

    if (node->is_constant) {
        printf("%d\n", node->value);
    } else {
        printf("%c\n", (char)node->value);
    }

    print_tree(node->left, depth + 1);
}

// Интерактивное добавление узла
Node* add_node_interactive() {
    printf("Добавить узел? (1 - да, 0 - нет): ");
    int choice;
    scanf("%d", &choice);

    if (!choice) return NULL;

    printf("Это константа? (1 - да, 0 - операция): ");
    int is_const;
    scanf("%d", &is_const);

    Node* node = NULL;
    if (is_const) {
        printf("Введите значение константы: ");
        int value;
        scanf("%d", &value);
        node = create_node(1, value);
    } else {
        printf("Введите операцию (+, -, *, /): ");
        char op;
        scanf(" %c", &op);
        node = create_node(0, op);
        printf("Левый операнд:\n");
        node->left = add_node_interactive();
        printf("Правый операнд:\n");
        node->right = add_node_interactive();
    }

    return node;
}

// Главная функция
int main() {
    char expression[100];

    printf("Введите арифметическое выражение: ");
    fgets(expression, sizeof(expression), stdin);
    expression[strcspn(expression, "\n")] = 0;  // Убираем символ новой строки

    // Строим дерево из выражения
    Node* tree = build_tree(expression, 0, strlen(expression) - 1);

    printf("\nДерево выражения:\n");
    print_tree(tree, 0);

    printf("\nРезультат вычисления: %d\n", evaluate(tree));

    // Интерактивное добавление вершины
    printf("\nИнтерактивное добавление узла:\n");
    Node* new_node = add_node_interactive();
    if (new_node != NULL) {
        printf("\nНовое дерево:\n");
        print_tree(new_node, 0);
        if (!new_node->is_constant) {
            printf("Результат вычисления нового дерева: %d\n", evaluate(new_node));
        }
    }

    free_tree(tree);
    if (new_node != NULL) free_tree(new_node);

    return 0;
}
