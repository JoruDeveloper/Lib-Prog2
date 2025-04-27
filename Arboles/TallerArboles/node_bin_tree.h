#ifndef NODE_BIN_TREE_H_
#define NODE_BIN_TREE_H_

#include <iostream>
#include <cstddef>

template <class elem>
class NodeBinTree{
    private:
        NodeBinTree<elem> *left;
        NodeBinTree<elem> *right;
        elem info;
    public:
        NodeBinTree();
        NodeBinTree(elem info);
        ~NodeBinTree();

        // Setters
        void setLeft(NodeBinTree<elem>* node);
        void setRight(NodeBinTree<elem>* node);
        void setInfo(elem info);

        // Getters
        NodeBinTree<elem>* getLeft() const;
        NodeBinTree<elem>* getRight() const;
        elem getInfo() const;

};

template <class elem> NodeBinTree<elem>::NodeBinTree() : left(NULL), right(NULL) {}
template <class elem> NodeBinTree<elem>::NodeBinTree(elem info) : info(info), left(NULL), right(NULL) {}
template <class elem> NodeBinTree<elem>::~NodeBinTree() {}
template <class elem> void NodeBinTree<elem>::setLeft(NodeBinTree<elem>* node) { this->left = node; }
template <class elem> void NodeBinTree<elem>::setRight(NodeBinTree<elem>* node) { this->right = node; }
template <class elem> void NodeBinTree<elem>::setInfo(elem info) { this->info = info; }


template <class elem>
NodeBinTree<elem>* NodeBinTree<elem>::getLeft() const {
    return this->left;
}
template <class elem>
NodeBinTree<elem>* NodeBinTree<elem>::getRight() const {
    return this->right;
}
template <class elem>
elem NodeBinTree<elem>::getInfo() const {
    return this->info;
}

#endif
