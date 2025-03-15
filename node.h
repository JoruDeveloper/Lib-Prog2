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
        ~Node();
        // Setters
        void setSig(Node<elem>*Node);
        void setAnt(Node<elem>*Node);
        void setInfo(elem info);
        // Getters
        Node<elem>* getSig();
        Node<elem>* getAnt();
        elem getInfo();
};

#endif