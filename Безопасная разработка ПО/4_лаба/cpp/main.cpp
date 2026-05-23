#include <iostream>
#include <string>
#include <sstream>
#include "stack.h"
#include "queue.h"
#include "tree.h"

void showHelp()
{
    std::cout << "s.push <value>   - добавить элемент в стек\n";
    std::cout << "s.pop            - удалить верхний элемент из стека\n";
    std::cout << "s.peek           - посмотреть верхний элемент стека\n";
    std::cout << "s.print          - вывести стек\n";
    std::cout << "q.push <value>   - добавить элемент в очередь\n";
    std::cout << "q.pop            - удалить первый элемент из очереди\n";
    std::cout << "q.front          - посмотреть первый элемент очереди\n";
    std::cout << "q.print          - вывести очередь\n";
    std::cout << "t.push <value>   - добавить элемент в дерево\n";
    std::cout << "t.pop            - удалить элемент из дерева\n";
    std::cout << "t.print          - вывести дерево (обход)\n";
    std::cout << "t.height         - показать высоту дерева\n";
    std::cout << "help             - показать список команд\n";
    std::cout << "exit             - выход из программы\n\n";   
}

int main() {
    Stack s;
    Queue q;
    Tree t;
    std::string command;

    std::cout << "help для списка команд.\n";

    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "exit") {
            std::cout << "Выход из программы.\n";
            break;
        }
        else if (cmd == "help") {
            showHelp();
        }
        else if (cmd == "s.push") {
            int value;
            if (iss >> value) {
                s.push(value);
                std::cout << "Элемент " << value << " добавлен в стек.\n";
            }
            else {
                std::cout << "Ошибка: требуется значение.\n";
            }
        }
        else if (cmd == "s.pop") {
            s.pop();
        }
        else if (cmd == "s.peek") {
            std::cout << "Верхний элемент: " << s.peek() << "\n";
        }
        else if (cmd == "s.print") {
            s.print();
        }
        else if (cmd == "q.push") {
            int value;
            if (iss >> value) {
                q.push(value);
                std::cout << "Элемент " << value << " добавлен в очередь.\n";
            }
            else {
                std::cout << "Ошибка: требуется значение.\n";
            }
        }
        else if (cmd == "q.pop") {
            q.pop();
        }
        else if (cmd == "q.front") {
            std::cout << "Первый элемент: " << q.front() << "\n";
        }
        else if (cmd == "q.print") {
            q.print();
        }
        else if (cmd == "t.push") {
            int value;
            if (iss >> value) {
                t.push(value);
                std::cout << "Элемент " << value << " добавлен в дерево.\n";
            }
            else {
                std::cout << "Ошибка: требуется значение.\n";
            }
        }
        else if (cmd == "t.pop") {
            t.pop();
        }
        else if (cmd == "t.print") {
            t.print();
        }
        else if (cmd == "t.height") {
            std::cout << "Высота дерева: " << t.height() << "\n";
        }
        else if (!cmd.empty()) {
            std::cout << "Неизвестная команда: '" << cmd << "'. Введите 'help'\n";
        }
    }

    return 0;
}
