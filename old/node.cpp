#include "node.h"

template <class elem>
Node<elem>::Node(){
    this->sig = NULL;
    this->ant = NULL;
    this->info = NULL;
}

template <class elem>
Node<elem>::Node() {
    this->sig = nullptr;
    this->ant = nullptr;
    this->info = elem();
}

template <class elem>
Node<elem>::Node(Node<elem>* sig, Node<elem>* ant, elem info) {
    this->sig = sig;
    this->ant = ant;
    this->info = info;
}

template <class elem>
void Node<elem>::setSig(Node<elem>* node) {
    this->sig = node;
}

template <class elem>
void Node<elem>::setAnt(Node<elem>* node) {
    this->ant = node;
}

template <class elem>
void Node<elem>::setInfo(elem info) {
    this->info = info;
}

// Getters
template <class elem>
Node<elem>* Node<elem>::getSig() {
    return this->sig;
}

template <class elem>
Node<elem>* Node<elem>::getAnt() {
    return this->ant;
}

template <class elem>
elem Node<elem>::getInfo() {
    return this->info;
}