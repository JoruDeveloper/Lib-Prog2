#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"
#include <stdexcept>

template <class elem>
class Queue : private List<elem> {
public:
    Queue();
    ~Queue();
    void enqueue(elem e);
    void dequeue();
    elem front();
    bool isEmpty();
};

template <class elem>
Queue<elem>::Queue() : List<elem>() {}

template <class elem>
Queue<elem>::~Queue() {
    this->empty();
}

template <class elem>
void Queue<elem>::enqueue(elem e) {
    this->addElem(e, this->getLength()); // Agrega al final de la lista
}

template <class elem>
void Queue<elem>::dequeue() {
    if (this->isEmpty()) throw std::out_of_range("La cola está vacía");
    this->deleteNode(0); // Elimina el primer elemento
}

template <class elem>
elem Queue<elem>::front() {
    if (this->isEmpty()) throw std::out_of_range("La cola está vacía");
    return this->checkPos(0); // Retorna el primer elemento
}

template <class elem>
bool Queue<elem>::isEmpty() {
    return List<elem>::isEmpty();
}

#endif
