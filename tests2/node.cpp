#include <iostream>
#include "node.h"


template <class elem>
Node<elem>::Node() {
    this->next = NULL;
    this->prev = NULL;
    this->info = elem();
}

template <class elem>
Node<elem>::Node(Node<elem>* next, Node<elem>* prev, elem info) {
    this->next = next;
    this->prev = prev;
    this->info = info;
}

template <class elem>
void Node<elem>::setNext(Node<elem>* node) {
    this->next = node;
}

template <class elem>
void Node<elem>::setPrev(Node<elem>* node) {
    this->prev = node;
}

template <class elem>
void Node<elem>::setInfo(elem info) {
    this->info = info;
}

// Getters
template <class elem>
Node<elem>* Node<elem>::getNext() {
    return this->next;
}

template <class elem>
Node<elem>* Node<elem>::getPrev() {
    return this->prev;
}

template <class elem>
elem Node<elem>::getInfo() {
    return this->info;
}