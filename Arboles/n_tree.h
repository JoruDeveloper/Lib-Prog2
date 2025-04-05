#ifndef N_TREE_H_
#define N_TREE_H_

#include <iostream>
#include "node_n_tree.h"

template<class elem>
class NTree
{
private:
    NodeNTree<elem> *root;

public:
    n_tree(/* args */);
    ~n_tree();
};

#endif