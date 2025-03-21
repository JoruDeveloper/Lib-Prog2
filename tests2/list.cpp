#include <iostream>
#include "list.h"

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
        this->addElem(current->info, pos++);
        current = current->next;
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
        if (current->info == e) return true;
        current = current->next;
    }

    return false;
}

template <class elem>
elem List<elem>::checkPos(int pos) {

    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posición fuera de rango");

    Node<elem> *current = this->first;

    for (int i = 0; i < pos; i++) {
        current = current->next;
    }

    return current->info;
}

template <class elem>
void List<elem>::addElem(elem e, int pos) {

    if (pos < 0 || pos > this->length) throw std::out_of_range("Posición fuera de rango");

    Node<elem> *newNode = new Node<elem>(e);

    if (pos == 0) {
        newNode->next = this->first;
        newNode->prev = NULL;
        this->first->prev = newNode;
        this->first = newNode;
        if (this->length == 0) this->last = newNode;
    } else {
        Node<elem> *current = this->first;
        for (int i = 0; i < pos - 1; i++) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;

        if (newNode->next == NULL ){ 
            this->last = newNode;
        } else {
            newNode->next->prev = newNode;
            current->next = newNode;
        }
    }
    this->length++;
}

template <class elem>
int List<elem>::delete_first_elem(elem e) { // Arreglar lógica nodo prev
    Node<elem> *current = this->first, *prev = NULL;
    int pos = 0;
    while (current) {
        if (current->info == e) {
            if (prev) prev->next = current->next;           // Posición != 0
            else this->first = current->next;               // Posición = 0
            if (current == this->last) this->last = prev;   // Posición = n
            delete current;
            this->length--;
            return pos;
        }
        prev = current;
        current = current->next;
        pos++;
    }
    return -1;
}

template <class elem>
void List<elem>::delete_all_elem(elem e) {  // Arreglar lógica nodo prev
    Node<elem> *current = this->first, *prev = NULL;
    while (current) {
        if (current->info == e) {
            Node<elem> *toDelete = current;
            if (prev) prev->next = current->next;           // Posición != 0
            else this->first = current->next;               // Posición = 0
            if (current == this->last) this->last = prev;   // Posición = n
            current = current->next;
            delete toDelete;
            this->length--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

template <class elem>
void List<elem>::deleteNode(int pos) {
    if (pos < 0 || pos >= this->length) throw std::out_of_range("Posición fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    if(current->next!=NULL){
        current->prev->next = current->next;
        current->next->prev = current->prev;
    } else {
        current->prev->next = current->next;
    }
    delete current;
    this->length--;
}

template <class elem>
void List<elem>::modifyNode(elem e, int pos) {
    if (pos < 0 || pos >= length) throw std::out_of_range("Posición fuera de rango");
    Node<elem> *current = this->first;
    for (int i = 0; i < pos; i++) {
        current = current->next;
    }
    current->info = e;
}

template <class elem>
void List<elem>::reverseList() {
    Node<elem> *current = this->first, *next = NULL;
    this->last = this->first;
    while (current) {
        next = current->next;
        current->next = current->prev;
        current->prev = next;
        if (next==NULL) this->first = current;
        current = next;
    }
}

template <class elem>
void List<elem>::bubbleSort(bool asc) {
    if (this->length < 2) return;
    for (int i = 0; i < this->length - 1; i++) {
        Node<elem> *current = first;
        for (int j = 0; j < this->length - i - 1; j++) {
            if ((asc && current->info > current->next->info) || (!asc && current->info < current->next->info)) {
                elem temp = current->info;
                current->info = current->next->info;
                current->next->info = temp;
            }
            current = current->next;
        }
    }
}

template <class elem>
void List<elem>::empty() {
    while (this->first != NULL) {
        Node<elem> *toDelete = this->first;
        this->first = this->first->next;
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
    while (current1&&current2) {
        if (current1->info != current2->info) return false;
        current1 = current1->next;
        current2 = current2->next;
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
