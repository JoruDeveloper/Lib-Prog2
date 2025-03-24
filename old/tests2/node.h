#ifndef NODE_H_
#define NODE_H_

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

#endif