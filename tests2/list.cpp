#include <iostream>
#include "list.h"

template <class elem>
List<elem>::List() {
    first = NULL;
    last = NULL;
    length = 0;
}

template <class elem>
List<elem>::List(const List<elem> &L){
    first = NULL;
    last = NULL;
    length = 0;
    copy(L);
}

template <class elem>
List<elem>::~List() {
    empty();
}

template <class elem>
void List<elem>::copy(const List<elem> &L) {
    empty();
    Node<elem> *current = L.first;
    int pos = 0;
    while (current) {
        addElem(current->data, pos++);
        current = current->next;
    }
}

template <class elem>
bool List<elem>::isEmpty() {
    return length == 0;
}

template <class elem>
bool List<elem>::isElem(elem e) {

    Node<elem> *current = first;

    while (current) {
        if (current->data == e) return true;
        current = current->next;
    }

    return false;
}

template <class elem>
elem List<elem>::checkPos(int pos) {

    if (pos < 0 || pos >= length) return NULL;

    Node<elem> *current = first;

    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    return current->data;
}

template <class elem>
void List<elem>::addElem(elem e, int pos) {

    if (pos < 0 || pos > length) return NULL;

    Node<elem> *newNode = new Node<elem>(e);

    if (pos == 0) {
        newNode->next = first;
        first = newNode;
        if (length == 0) last = newNode;
    } else {
        Node<elem> *current = first;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == NULL) last = newNode;
    }
    length++;
}

template <class elem>
int List<elem>::delete_first_elem(elem e) {
    Node<elem> *current = first, *prev = NULL;
    int pos = 0;
    while (current) {
        if (current->data == e) {
            if (prev) prev->next = current->next;
            else first = current->next;
            if (current == last) last = prev;
            delete current;
            length--;
            return pos;
        }
        prev = current;
        current = current->next;
        pos++;
    }
    return -1;
}

template <class elem>
void List<elem>::delete_all_elem(elem e) {
    Node<elem> *current = first, *prev = NULL;
    while (current) {
        if (current->data == e) {
            Node<elem> *toDelete = current;
            if (prev) prev->next = current->next;
            else first = current->next;
            if (current == last) last = prev;
            current = current->next;
            delete toDelete;
            length--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

template <class elem>
void List<elem>::deleteNode(int pos) {
    if (pos < 0 || pos >= length) throw std::out_of_range("Posición fuera de rango");
    Node<elem> *current = first, *prev = NULL;
    for (int i = 0; i < pos; i++) {
        prev = current;
        current = current->next;
    }
    if (prev) prev->next = current->next;
    else first = current->next;
    if (current == last) last = prev;
    delete current;
    length--;
}

template <class elem>
void List<elem>::modifyNode(elem e, int pos) {
    if (pos < 0 || pos >= length) throw std::out_of_range("Posición fuera de rango");
    Node<elem> *current = first;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    current->data = e;
}

template <class elem>
void List<elem>::reverseList() {
    Node<elem> *prev = NULL, *current = first, *next = NULL;
    last = first;
    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    first = prev;
}

template <class elem>
void List<elem>::bubbleSort(bool asc) {
    if (length < 2) return;
    for (int i = 0; i < length - 1; i++) {
        Node<elem> *current = first;
        for (int j = 0; j < length - i - 1; j++) {
            if ((asc && current->data > current->next->data) || (!asc && current->data < current->next->data)) {
                std::swap(current->data, current->next->data);
            }
            current = current->next;
        }
    }
}

template <class elem>
void List<elem>::empty() {
    while (first != NULL) {
        Node<elem> *toDelete = first;
        first = first->next;
        delete toDelete;
    }
    last = NULL;
    length = 0;
}

template <class elem>
List<elem>& List<elem>::operator=(const List<elem>& L) {
    if (this != &L) copy(L);
    return *this;
}

template <class elem>
bool List<elem>::operator==(const List<elem> &L) {
    if (length != L.length) return false;
    Node<elem> *current1 = first, *current2 = L.first;
    while (current1) {
        if (current1->data != current2->data) return false;
        current1 = current1->next;
        current2 = current2->next;
    }
    return true;
}

template <class elem>
elem List<elem>::operator[](int pos) {
    return checkPos(pos);
}

template <class elem>
bool List<elem>::operator>(const List<elem> &L) {
    return length > L.length;
}

template <class elem>
bool List<elem>::operator<(const List<elem> &L) {
    return length < L.length;
}

template <class elem>
int List<elem>::getLength() {
    return length;
}
