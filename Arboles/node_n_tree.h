#ifndef NODE_N_TREE_H_
#define NODE_N_TREE_H_

#include <iostream>

template <class elem>
class NodeNTree{
    private:
        NodeNTree<elem> *sons;
        NodeNTree<elem> *bro;
        elem info;
    public:
        NodeNTree();
        NodeNTree(elem info);
        NodeNTree(NodeNTree<elem> *sons, elem info);
        NodeNTree(NodeNTree<elem> *sons, NodeNTree<elem> *bro, elem info);
        ~NodeNTree();

        // Setters
        void setSons(NodeNTree<elem>*Node);
        void setBro(NodeNTree<elem>*Node);
        void setInfo(elem info);
        // Getters
        NodeNTree<elem>* getSons();
        NodeNTree<elem>* getBro();
        elem getInfo();

};

template <class elem>
NodeNTree<elem>::NodeNTree() {
    this->sons = NULL;
    this->bro = NULL;
    this->info = elem();
}

template <class elem>
NodeNTree<elem>::NodeNTree(elem info) {
    this->info = info;
    this->sons = NULL;
    this->bro = NULL;
}

template <class elem>
NodeNTree<elem>::NodeNTree(NodeNTree<elem>* sons, elem info) {
    this->info = info;
    this->sons = sons;
    this->bro = NULL;
}

template <class elem>
NodeNTree<elem>::NodeNTree(NodeNTree<elem>* sons, NodeNTree<elem>* bro, elem info) {
    this->info = info;
    this->sons = sons;
    this->bro = bro;
}

template <class elem>
NodeNTree<elem>::~NodeNTree() {
    delete sons;
    delete bro;
}

// Setters
template <class elem>
void NodeNTree<elem>::setSons(NodeNTree<elem>* node) {
    this->sons = node;
}

template <class elem>
void NodeNTree<elem>::setBro(NodeNTree<elem>* node) {
    this->bro = node;
}

template <class elem>
void NodeNTree<elem>::setInfo(elem info) {
    this->info = info;
}

// Getters
template <class elem>
NodeNTree<elem>* NodeNTree<elem>::getSons() {
    return this->sons;
}

template <class elem>
NodeNTree<elem>* NodeNTree<elem>::getBro() {
    return this->bro;
}

template <class elem>
elem NodeNTree<elem>::getInfo() {
    return this->info;
}

#endif