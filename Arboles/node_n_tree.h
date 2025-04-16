#ifndef NODE_N_TREE_H_
#define NODE_N_TREE_H_

#include <iostream>
#include <cstddef> // Required for NULL

template <class elem>
class NodeNTree{
    private:
        NodeNTree<elem> *sons; // Pointer to the first child
        NodeNTree<elem> *bro;  // Pointer to the next sibling
        elem info;
    public:
        NodeNTree();
        NodeNTree(elem info);
        // Removed constructors taking pointers directly for clarity; use setters.
        // NodeNTree(NodeNTree<elem> *sons, elem info);
        // NodeNTree(NodeNTree<elem> *sons, NodeNTree<elem> *bro, elem info);
        ~NodeNTree(); // MODIFIED: Empty destructor

        // Setters
        void setSons(NodeNTree<elem>* node);
        void setBro(NodeNTree<elem>* node);
        void setInfo(elem info);

        // Getters (Marked as const)
        NodeNTree<elem>* getSons() const; // ADDED const
        NodeNTree<elem>* getBro() const;  // ADDED const
        elem getInfo() const;             // ADDED const
};

// --- NodeNTree Definitions ---

template <class elem>
NodeNTree<elem>::NodeNTree() {
    // Definition style changed
    this->sons = NULL;
    this->bro = NULL;
    // this->info = elem(); // Requires default constructible elem
}

template <class elem>
NodeNTree<elem>::NodeNTree(elem info) {
    // Definition style changed
    this->info = info;
    this->sons = NULL;
    this->bro = NULL;
}

// Removed other constructor definitions as they were removed from declaration

template <class elem>
NodeNTree<elem>::~NodeNTree() {
    // Destructor is empty; NTree manages node deletion.
}

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

template <class elem>
NodeNTree<elem>* NodeNTree<elem>::getSons() const { // ADDED const
    return this->sons;
}

template <class elem>
NodeNTree<elem>* NodeNTree<elem>::getBro() const { // ADDED const
    return this->bro;
}

template <class elem>
elem NodeNTree<elem>::getInfo() const { // ADDED const
    return this->info;
}

#endif // NODE_N_TREE_H_