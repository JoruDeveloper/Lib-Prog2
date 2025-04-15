// #ifndef NODE_BIN_TREE_H_
// #define NODE_BIN_TREE_H_

// #include <iostream>

// template <class elem>
// class NodeBinTree{
//     private:
//         NodeBinTree<elem> *left;
//         NodeBinTree<elem> *right;
//         elem info;
//     public:
//         NodeBinTree();
//         NodeBinTree(elem info);
//         NodeBinTree(NodeBinTree<elem> *left, NodeBinTree<elem> *right, elem info);
//         ~NodeBinTree();

//         // Setters
//         void setLeft(NodeBinTree<elem>*Node);
//         void setRight(NodeBinTree<elem>*Node);
//         void setInfo(elem info);
//         // Getters
//         NodeBinTree<elem>* getLeft();
//         NodeBinTree<elem>* getRight();
//         elem getInfo();

// };

// template <class elem>
// NodeBinTree<elem>::NodeBinTree() {
//     this->left = NULL;
//     this->right = NULL;
//     this->info = elem();
// }

// template <class elem>
// NodeBinTree<elem>::NodeBinTree(elem info) {
//     this->info = info;
//     this->left = NULL;
//     this->right = NULL;
// }

// template <class elem>
// NodeBinTree<elem>::NodeBinTree(NodeBinTree<elem>* left, NodeBinTree<elem>* right, elem info) {
//     this->left = left;
//     this->right = right;
//     this->info = info;
// }

// template <class elem>
// NodeBinTree<elem>::~NodeBinTree() {
//     delete left;
//     delete right;
// }

// // Setters
// template <class elem>
// void NodeBinTree<elem>::setLeft(NodeBinTree<elem>* node) {
//     this->left = node;
// }

// template <class elem>
// void NodeBinTree<elem>::setRight(NodeBinTree<elem>* node) {
//     this->right = node;
// }

// template <class elem>
// void NodeBinTree<elem>::setInfo(elem info) {
//     this->info = info;
// }

// // Getters
// template <class elem>
// NodeBinTree<elem>* NodeBinTree<elem>::getLeft() {
//     return this->left;
// }

// template <class elem>
// NodeBinTree<elem>* NodeBinTree<elem>::getRight() {
//     return this->right;
// }

// template <class elem>
// elem NodeBinTree<elem>::getInfo() {
//     return this->info;
// }

// #endif

#ifndef NODE_BIN_TREE_H_
#define NODE_BIN_TREE_H_

#include <iostream>
#include <cstddef> // Required for NULL

template <class elem>
class NodeBinTree{
    private:
        NodeBinTree<elem> *left;
        NodeBinTree<elem> *right;
        elem info;
    public:
        NodeBinTree();
        NodeBinTree(elem info);
        ~NodeBinTree(); // Corrected: Does NOT delete children

        // Setters
        void setLeft(NodeBinTree<elem>* node);
        void setRight(NodeBinTree<elem>* node);
        void setInfo(elem info);

        // Getters (Marked as const)
        NodeBinTree<elem>* getLeft() const; // ADDED const
        NodeBinTree<elem>* getRight() const; // ADDED const
        elem getInfo() const; // ADDED const

};

// --- NodeBinTree Definitions ---

template <class elem> NodeBinTree<elem>::NodeBinTree() : left(NULL), right(NULL) {}
template <class elem> NodeBinTree<elem>::NodeBinTree(elem info) : info(info), left(NULL), right(NULL) {}
template <class elem> NodeBinTree<elem>::~NodeBinTree() {} // BinTree manages deletion
template <class elem> void NodeBinTree<elem>::setLeft(NodeBinTree<elem>* node) { this->left = node; }
template <class elem> void NodeBinTree<elem>::setRight(NodeBinTree<elem>* node) { this->right = node; }
template <class elem> void NodeBinTree<elem>::setInfo(elem info) { this->info = info; }

// Definitions for const getters
template <class elem>
NodeBinTree<elem>* NodeBinTree<elem>::getLeft() const { // ADDED const
    return this->left;
}
template <class elem>
NodeBinTree<elem>* NodeBinTree<elem>::getRight() const { // ADDED const
    return this->right;
}
template <class elem>
elem NodeBinTree<elem>::getInfo() const { // ADDED const
    return this->info;
}

#endif // NODE_BIN_TREE_H_