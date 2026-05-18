#include <iostream>
#include "stack.h"
#include "queue.h"
#include "tree.h"

int main() {
    Stack s;
    Queue q;
    Tree t;

    
    s.push(10);
    s.push(20);
    s.print();
    std::cout << "Stack peek: " << s.peek() << "\n";
    s.pop();
    s.print();


    q.push(1);
    q.push(2);
    q.push(3);
    q.print();
    std::cout << "Queue front: " << q.front() << "\n";
    q.pop();
    q.print();


    t.push(5);
    t.push(2);
    t.push(8);
    t.push(1);
    t.push(3);

    t.print();
    std::cout << "Tree height: " << t.height() << "\n";
    t.pop();
    t.print();

    return 0;
}