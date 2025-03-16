#ifndef NODE_H_
#define NODE_H_

template <class elem>
class Node {
    private:
        Node<elem>* sig;
        Node<elem>* ant;
        elem info;
    public:
        Node();
        Node(Node<elem> *sig, Node<elem> *ant, elem info);
        ~Node(){};
        // Setters
        void setSig(Node<elem>*Node);
        void setAnt(Node<elem>*Node);
        void setInfo(elem info);
        // Getters
        Node<elem>* getSig();
        Node<elem>* getAnt();
        elem getInfo();
};

template <class elem>
Node<elem>::Node() {
    this->sig = NULL;
    this->ant = NULL;
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

#endif