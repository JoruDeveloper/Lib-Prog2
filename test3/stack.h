#ifndef STACK_H_
#define STACK_H_

#include "list.h"
#include <stdexcept>
#include <iostream>

template <class elem>
class Stack : private List<elem> {
public:
    Stack();
    ~Stack();
    void push(elem e);
    void pop();
    elem top();
    bool isEmpty();
};

template <class elem>
Stack<elem>::Stack() : List<elem>() {}

template <class elem>
Stack<elem>::~Stack() {
    this->empty();
}

template <class elem>
void Stack<elem>::push(elem e) {
    this->addElem(e, 0);
}

template <class elem>
void Stack<elem>::pop() {
    if (this->isEmpty()) throw std::out_of_range("La pila está vacía");
    this->deleteNode(0);
}

template <class elem>
elem Stack<elem>::top() {
    if (this->isEmpty()) throw std::out_of_range("La pila está vacía");
    return this->checkPos(0);
}

template <class elem>
bool Stack<elem>::isEmpty() {
    return this->List<elem>::isEmpty();
}

#endif
