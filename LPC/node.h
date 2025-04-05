#ifndef NODE_H_
#define NODE_H_

#include <iostream>

template <class elem>
class Node {
    private:
        Node<elem>* next;
        Node<elem>* prev;
        elem info;
    public:
        Node();
        Node(Node<elem> *next, Node<elem> *prev, elem info);
        Node(elem info);
        ~Node(){};
        // Setters
        void setNext(Node<elem>*Node);
        void setPrev(Node<elem>*Node);
        void setInfo(elem info);
        // Getters
        Node<elem>* getNext();
        Node<elem>* getPrev();
        elem getInfo();
};

template <class elem>
Node<elem>::Node() {
    this->next = NULL;
    this->prev = NULL;
    this->info = elem();
}

template <class elem>
Node<elem>::Node(elem info) {
    this->info = info;
    this->next = NULL;
    this->prev = NULL;
}

template <class elem>
Node<elem>::Node(Node<elem>* next, Node<elem>* prev, elem info) {
    this->next = next;
    this->prev = prev;
    this->info = info;
}

// Setters
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

#endif