#ifndef LIST_H_
#define LIST_H_
#include "node.h"
#include <stdexcept>
#include <iostream>

template <class elem>
class List{
    private:
        Node<elem> *first;
        Node<elem> *last;
        int length;

    public:
    List();
    List(const List<elem> &L);
    ~List();
    void copy(const List<elem> &L);
    bool isEmpty();
    bool isElem(elem e);
    elem checkPos(int pos);
    void addElem(elem e, int pos);
    int delete_first_elem(elem e); // Elimina el primer elemento e y retorna su posición
    void delete_all_elem(elem e); // Elimina todos los elementos e
    void deleteNode(int pos);
    void modifyNode(elem e, int pos);
    void reverseList();
    void bubbleSort(bool asc);
    void empty();
    // Operadores Miembros
    List<elem>& operator=(const List<elem>&L);
    bool operator==(const List<elem> &L);
    elem operator[](int pos);
    bool operator>(const List<elem> &L);
    bool operator<(const List<elem> &L);
    // Set Get
    int getLength();
};

template <class elem>
List<elem>::List() {
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
}

template <class elem>
List<elem>::List(const List<elem> &L){
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
    this->copy(L);
}

template <class elem>
List<elem>::~List() {
    this->empty();
}

template <class elem>
void List<elem>::copy(const List<elem> &L) {
    this->empty();
    Node<elem> *current = L.first;
    int pos = 0;
    while (current) {
        this->addElem(current->getInfo(), pos++);
        current = current->getNext();
    }
}

template <class elem>
bool List<elem>::isEmpty() {
    return this->length == 0;
}

template <class elem>
bool List<elem>::isElem(elem e) {
    Node<elem> *current = this->first;
    while (current) {
        if (current->getInfo() == e) return true;
        current = current->getNext();
    }
    return false;
}

template <class elem>
elem List<elem>::checkPos(int pos) {
    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    return current->getInfo();
}

template <class elem>
void List<elem>::addElem(elem e, int pos) {
    if (pos < 0 || pos > this->length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *newNode = new Node<elem>(e);
    if (pos == 0) {
        newNode->setNext(this->first);
        newNode->setPrev(NULL);
        if (this->first) this->first->setPrev(newNode);
        this->first = newNode;
        if (this->length == 0) this->last = newNode;
    } else {
        Node<elem> *current = this->first;
        for (int i = 0; i < pos - 1; i++) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        newNode->setPrev(current);
        if (newNode->getNext()) newNode->getNext()->setPrev(newNode);
        else this->last = newNode;
        current->setNext(newNode);
    }
    this->length++;
}

template <class elem>
int List<elem>::delete_first_elem(elem e) {
    Node<elem> *current = this->first;
    int pos = 0;

    while (current) {
        if (current->getInfo() == e) {
            if (current->getPrev()) current->getPrev()->setNext(current->getNext());
            else this->first = current->getNext(); // Si es el primero, actualizar `first`

            if (current->getNext()) current->getNext()->setPrev(current->getPrev());
            else this->last = current->getPrev(); // Si es el último, actualizar `last`

            delete current;
            this->length--;
            return pos;
        }
        current = current->getNext();
        pos++;
    }
    return -1;
}

template <class elem>
void List<elem>::delete_all_elem(elem e) {
    Node<elem> *current = this->first;
    while (current) {
        if (current->getInfo() == e) {
            Node<elem> *toDelete = current;
            if (current->getPrev()) current->getPrev()->setNext(current->getNext());
            else this->first = current->getNext();

            if (current->getNext()) current->getNext()->setPrev(current->getPrev());
            else this->last = current->getPrev();

            current = current->getNext();
            delete toDelete;
            this->length--;
        } else {
            current = current->getNext();
        }
    }
}

template <class elem>
void List<elem>::deleteNode(int pos) {
    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    if (current->getPrev()) current->getPrev()->setNext(current->getNext());
    else this->first = current->getNext();
    if (current->getNext()) current->getNext()->setPrev(current->getPrev());
    else this->last = current->getPrev();
    delete current;
    this->length--;
}

template <class elem>
void List<elem>::modifyNode(elem e, int pos) {
    if (pos < 0 || pos >= length) throw std::out_of_range("Posici\u00f3n fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->getNext();
    }
    current->setInfo(e);
}

template <class elem>
void List<elem>::reverseList() {
    Node<elem> *current = this->first, *next = NULL;
    this->last = this->first;
    while (current) {
        next = current->getNext();
        current->setNext(current->getPrev());
        current->setPrev(next);
        if (next == NULL) this->first = current;
        current = next;
    }
}

template <class elem>
void List<elem>::bubbleSort(bool asc) {
    if (this->length < 2) return;
    for (int i = 0; i < this->length - 1; i++) {
        Node<elem> *current = first;
        for (int j = 0; j < this->length - i - 1; j++) {
            if ((asc && current->getInfo() > current->getNext()->getInfo()) || (!asc && current->getInfo() < current->getNext()->getInfo())) {
                elem temp = current->getInfo();
                current->setInfo(current->getNext()->getInfo());
                current->getNext()->setInfo(temp);
            }
            current = current->getNext();
        }
    }
}

template <class elem>
void List<elem>::empty() {
    while (this->first != NULL) {
        Node<elem> *toDelete = this->first;
        this->first = this->first->getNext();
        delete toDelete;
    }
    this->last = NULL;
    this->length = 0;
}

template <class elem>
List<elem>& List<elem>::operator=(const List<elem>& L) {
    if (this != &L) this->copy(L);
    return *this;
}

template <class elem>
bool List<elem>::operator==(const List<elem> &L) {
    if (this->length != L.length) return false;
    Node<elem> *current1 = this->first, *current2 = L.first;
    while (current1 && current2) {
        if (current1->getInfo() != current2->getInfo()) return false;
        current1 = current1->getNext();
        current2 = current2->getNext();
    }
    if((current1==NULL)&&(current2==NULL)) return true;

    return false;
}

template <class elem>
elem List<elem>::operator[](int pos) {
    return this->checkPos(pos);
}

template <class elem>
bool List<elem>::operator>(const List<elem> &L) {
    return this->length > L.length;
}

template <class elem>
bool List<elem>::operator<(const List<elem> &L) {
    return this->length < L.length;
}

template <class elem>
int List<elem>::getLength() {
    return this->length;
}

#endif