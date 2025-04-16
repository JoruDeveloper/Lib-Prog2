// En honor a Luigi Quero

#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include "node_bin_tree.h"
#include <iostream>
#include <list>
#include <queue>
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <cmath>

// Maldito edwin que fue ese push chimbo?

// Tkm Guille eres un sol

// No por eso me vas a caer bien egui no te equivoques

// No pelien. ATT: Sebastian

// Perdón seba :,( fue edwin te lo juro

template <class elem> class BinTree;

template <class elem>
class BinTree{
private:
    NodeBinTree<elem> *root;
    int weight;

    NodeBinTree<elem>* COPY_NODES(const NodeBinTree<elem>* sourceNode) const;
    void DESTROY_NODES(NodeBinTree<elem>* node);
    int COUNT_NODES(const NodeBinTree<elem>* node) const;
    void PRE_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const;
    void IN_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const;
    void POST_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const;
    void LEVEL_ORDER_HELPER(NodeBinTree<elem>* node, std::list<elem>& resultList) const;
    void GET_HEIGHT(NodeBinTree<elem>* node, int currentLevel, int& maxLevelReached) const;
    void GET_LEAVES(NodeBinTree<elem>* node, std::list<elem>& leafList) const;
    void CLEAR();
    NodeBinTree<elem>* BUILD_FROM_PRE_IN_RECURSIVE(std::list<elem>& preOrderList, std::list<elem>& inOrderList);
    NodeBinTree<elem>* BUILD_FROM_POST_IN_RECURSIVE(std::list<elem>& postOrderList, std::list<elem>& inOrderList);
    void INSERT_BST(NodeBinTree<elem>* &node, const elem& value);
    bool SEARCH_BST(const NodeBinTree<elem>* node, const elem& value) const;
    NodeBinTree<elem>* FIND_MIN(NodeBinTree<elem>* node) const;
    NodeBinTree<elem>* REMOVE_BST(NodeBinTree<elem>* node, const elem& value, bool& removed);
    void FIND_PATH(NodeBinTree<elem>* node, std::list<elem>& currentPath, const elem& target, bool& found) const;
    void FIND_PATHS_TO_TWO(NodeBinTree<elem>* node, std::list<elem>& path1, std::list<elem>& path2, const elem& target1, const elem& target2, bool& found1, bool& found2) const;
    void COMBINE_PATHS(std::list<elem>& resultPath, std::list<elem> path1, std::list<elem> path2) const;
    void UPDATE_LONGEST_PATH(std::list<elem>& currentLongest, std::list<elem>& path1, std::list<elem>& path2, const std::list<elem>& newBranch) const;
    void FIND_DIAMETER(NodeBinTree<elem>* node, std::list<elem>& currentLongestPath, std::list<elem>& longestBranch1, std::list<elem>& longestBranch2, std::list<elem>& currentBranch) const;
    int GET_NODE_LEVEL(NodeBinTree<elem>* node, const elem& target, int currentLevel) const;

public:
    BinTree();
    BinTree(elem e);
    BinTree(const BinTree<elem>& otherTree);
    BinTree(elem e, const BinTree<elem>& leftTree, const BinTree<elem>& rightTree);
    ~BinTree();

    BinTree<elem>& operator=(const BinTree<elem>& otherTree);
    void copyFromPointer(const BinTree<elem>* otherTreePtr);

    bool isEmpty() const;
    void makeEmpty();
    int getWeight() const;
    elem getRootInfo() const;

    BinTree<elem> getLeftSubtree() const;
    BinTree<elem> getRightSubtree() const;

    std::list<elem> preOrder() const;
    std::list<elem> inOrder() const;
    std::list<elem> postOrder() const;
    std::list<elem> levelOrder() const;
    std::list<elem> getLevel(int level) const;

    int getHeight() const;
    std::list<elem> getLeaves() const;

    void insertBST(const elem& value);
    bool searchBST(const elem& value) const;
    bool removeBST(const elem& value);

    void buildFromPreIn(std::list<elem> preOrderList, std::list<elem> inOrderList);
    void buildFromPostIn(std::list<elem> postOrderList, std::list<elem> inOrderList);

    std::list<elem> findPathToNode(const elem& target) const;
    std::list<elem> findPathBetweenNodes(const elem& value1, const elem& value2) const;
    elem lowestCommonAncestor(const elem& value1, const elem& value2) const;
    std::list<elem> getDiameterPath() const;
    int getHeightDifference(const elem& value1, const elem& value2) const;
};

template <class elem>
NodeBinTree<elem>* BinTree<elem>::COPY_NODES(const NodeBinTree<elem>* sourceNode) const{
    if (sourceNode == NULL) return NULL;
    NodeBinTree<elem>* newNode = new NodeBinTree<elem>(sourceNode->getInfo());
    newNode->setLeft(COPY_NODES(sourceNode->getLeft()));
    newNode->setRight(COPY_NODES(sourceNode->getRight()));
    return newNode;
}

template <class elem>
void BinTree<elem>::DESTROY_NODES(NodeBinTree<elem>* node) {
    if (node != NULL) {
        DESTROY_NODES(node->getLeft());
        DESTROY_NODES(node->getRight());
        delete node;
    }
}

template <class elem>
int BinTree<elem>::COUNT_NODES(const NodeBinTree<elem>* node) const {
    if (node == NULL) return 0;
    return 1 + COUNT_NODES(node->getLeft()) + COUNT_NODES(node->getRight());
}

template <class elem>
void BinTree<elem>::PRE_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const {
    if (node != NULL) {
        resultList.push_back(node->getInfo());
        PRE_ORDER(node->getLeft(), resultList);
        PRE_ORDER(node->getRight(), resultList);
    }
}

template <class elem>
void BinTree<elem>::IN_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const {
     if (node != NULL) {
        IN_ORDER(node->getLeft(), resultList);
        resultList.push_back(node->getInfo());
        IN_ORDER(node->getRight(), resultList);
    }
}

template <class elem>
void BinTree<elem>::POST_ORDER(NodeBinTree<elem>* node, std::list<elem>& resultList) const {
     if (node != NULL) {
        POST_ORDER(node->getLeft(), resultList);
        POST_ORDER(node->getRight(), resultList);
        resultList.push_back(node->getInfo());
    }
}

template <class elem>
void BinTree<elem>::LEVEL_ORDER_HELPER(NodeBinTree<elem>* node, std::list<elem>& resultList) const {
    if (node == NULL) return;
    std::queue<NodeBinTree<elem>*> q;
    q.push(node);
    while (!q.empty()) {
        NodeBinTree<elem>* current = q.front();
        q.pop();
        resultList.push_back(current->getInfo());
        if (current->getLeft() != NULL) q.push(current->getLeft());
        if (current->getRight() != NULL) q.push(current->getRight());
    }
}

template <class elem>
void BinTree<elem>::GET_HEIGHT(NodeBinTree<elem>* node, int currentLevel, int& maxLevelReached) const {
      if (node != NULL) {
        if (currentLevel > maxLevelReached) maxLevelReached = currentLevel;
        GET_HEIGHT(node->getLeft(), currentLevel + 1, maxLevelReached);
        GET_HEIGHT(node->getRight(), currentLevel + 1, maxLevelReached);
    }
}

template <class elem>
void BinTree<elem>::GET_LEAVES(NodeBinTree<elem>* node, std::list<elem>& leafList) const {
     if (node != NULL) {
        if (node->getLeft() == NULL && node->getRight() == NULL) {
            leafList.push_back(node->getInfo());
        } else {
            GET_LEAVES(node->getLeft(), leafList);
            GET_LEAVES(node->getRight(), leafList);
        }
    }
}

template <class elem>
void BinTree<elem>::CLEAR() {
    DESTROY_NODES(root);
    this->root = NULL;
    this->weight = 0;
}

template <class elem>
NodeBinTree<elem>* BinTree<elem>::BUILD_FROM_PRE_IN_RECURSIVE(std::list<elem>& preOrderList, std::list<elem>& inOrderList) {
     if (preOrderList.empty() || inOrderList.empty()) return NULL;
    elem rootInfo = preOrderList.front();
    preOrderList.pop_front();
    NodeBinTree<elem>* newNode = new NodeBinTree<elem>(rootInfo);
    std::list<elem> leftInOrder, rightInOrder, leftPreOrder;
    typename std::list<elem>::iterator it = inOrderList.begin();
    while (it != inOrderList.end() && *it != rootInfo) leftInOrder.push_back(*it++);
    if (it != inOrderList.end()) it++;
    while (it != inOrderList.end()) rightInOrder.push_back(*it++);
    int leftSize = leftInOrder.size();
    typename std::list<elem>::iterator preIt = preOrderList.begin();
    for(int i = 0; i < leftSize && preIt != preOrderList.end(); ++i) leftPreOrder.push_back(*preIt++);
    preOrderList.erase(preOrderList.begin(), preIt);
    std::list<elem>& rightPreOrder = preOrderList;
    newNode->setLeft(BUILD_FROM_PRE_IN_RECURSIVE(leftPreOrder, leftInOrder));
    newNode->setRight(BUILD_FROM_PRE_IN_RECURSIVE(rightPreOrder, rightInOrder));
    return newNode;
}

template <class elem>
NodeBinTree<elem>* BinTree<elem>::BUILD_FROM_POST_IN_RECURSIVE(std::list<elem>& postOrderList, std::list<elem>& inOrderList) {
     if (postOrderList.empty() || inOrderList.empty()) return NULL;
    elem rootInfo = postOrderList.back();
    postOrderList.pop_back();
    NodeBinTree<elem>* newNode = new NodeBinTree<elem>(rootInfo);
    std::list<elem> leftInOrder, rightInOrder, leftPostOrder, rightPostOrder;
    typename std::list<elem>::iterator it = inOrderList.begin();
    while (it != inOrderList.end() && *it != rootInfo) leftInOrder.push_back(*it++);
    if (it != inOrderList.end()) it++;
    while (it != inOrderList.end()) rightInOrder.push_back(*it++);
    int leftSize = leftInOrder.size();
    typename std::list<elem>::iterator postIt = postOrderList.begin();
    for(int i = 0; i < leftSize && postIt != postOrderList.end(); ++i) leftPostOrder.push_back(*postIt++);
    while(postIt != postOrderList.end()) rightPostOrder.push_back(*postIt++);
    newNode->setRight(BUILD_FROM_POST_IN_RECURSIVE(rightPostOrder, rightInOrder));
    newNode->setLeft(BUILD_FROM_POST_IN_RECURSIVE(leftPostOrder, leftInOrder));
    return newNode;
}

template <class elem>
void BinTree<elem>::INSERT_BST(NodeBinTree<elem>* &node, const elem& value) {
    if (node == NULL) {
         node = new NodeBinTree<elem>(value);
         this->weight++;
    } else if (value < node->getInfo()) {
        NodeBinTree<elem>* leftChild = node->getLeft();
        INSERT_BST(leftChild, value);
        node->setLeft(leftChild);
    } else {
        NodeBinTree<elem>* rightChild = node->getRight();
        INSERT_BST(rightChild, value);
        node->setRight(rightChild);
    }
}

template <class elem>
bool BinTree<elem>::SEARCH_BST(const NodeBinTree<elem>* node, const elem& value) const {
     if (node == NULL) {
        return false;
    } else if (value == node->getInfo()) {
        return true;
    } else if (value < node->getInfo()) {
        return SEARCH_BST(node->getLeft(), value);
    } else {
        return SEARCH_BST(node->getRight(), value);
    }
}

template <class elem>
NodeBinTree<elem>* BinTree<elem>::FIND_MIN(NodeBinTree<elem>* node) const {
     if (node == NULL) return NULL;
     while (node->getLeft() != NULL) {
         node = node->getLeft();
     }
     return node;
}

template <class elem>
NodeBinTree<elem>* BinTree<elem>::REMOVE_BST(NodeBinTree<elem>* node, const elem& value, bool& removed) {
    if (node == NULL) return NULL;

    if (value < node->getInfo()) {
        node->setLeft(REMOVE_BST(node->getLeft(), value, removed));
    } else if (value > node->getInfo()) {
        node->setRight(REMOVE_BST(node->getRight(), value, removed));
    } else {
        removed = true;
        this->weight--;

        if (node->getLeft() == NULL) {
            NodeBinTree<elem>* temp = node->getRight();
            delete node;
            return temp;
        } else if (node->getRight() == NULL) {
            NodeBinTree<elem>* temp = node->getLeft();
            delete node;
            return temp;
        }

        NodeBinTree<elem>* temp = FIND_MIN(node->getRight());
        node->setInfo(temp->getInfo());
        bool dummy = false;
        node->setRight(REMOVE_BST(node->getRight(), temp->getInfo(), dummy));
    }
    return node;
}

template <class elem>
void BinTree<elem>::FIND_PATH(NodeBinTree<elem>* node, std::list<elem>& currentPath, const elem& target, bool& found) const {
    if (node == NULL || found) return;
    currentPath.push_back(node->getInfo());
    if (node->getInfo() == target) {
        found = true;
        return;
    }
    FIND_PATH(node->getLeft(), currentPath, target, found);
    if (found) return;
    FIND_PATH(node->getRight(), currentPath, target, found);
    if (found) return;
    currentPath.pop_back();
}

template <class elem>
void BinTree<elem>::FIND_PATHS_TO_TWO(NodeBinTree<elem>* node, std::list<elem>& path1, std::list<elem>& path2, const elem& target1, const elem& target2, bool& found1, bool& found2) const {
     if (node == NULL || (found1 && found2)) return;
     if (!found1) path1.push_back(node->getInfo());
     if (!found2) path2.push_back(node->getInfo());
     if (node->getInfo() == target1) found1 = true;
     if (node->getInfo() == target2) found2 = true;
     if (found1 && found2) return;
     FIND_PATHS_TO_TWO(node->getLeft(), path1, path2, target1, target2, found1, found2);
     if (found1 && found2) return;
     FIND_PATHS_TO_TWO(node->getRight(), path1, path2, target1, target2, found1, found2);
     if (found1 && found2) return;
     if (!found1) path1.pop_back();
     if (!found2) path2.pop_back();
}

template <class elem>
void BinTree<elem>::COMBINE_PATHS(std::list<elem>& resultPath, std::list<elem> path1, std::list<elem> path2) const {
    elem lca;
    bool lcaFound = false;
    while (!path1.empty() && !path2.empty() && path1.front() == path2.front()) {
        lca = path1.front();
        lcaFound = true;
        path1.pop_front();
        path2.pop_front();
    }
    resultPath.clear();
    if (!lcaFound && !path1.empty()) lca = path1.front();
    else if (!lcaFound && !path2.empty()) lca = path2.front();

    std::vector<elem> reversedPath1;
    while (!path1.empty()) {
        reversedPath1.push_back(path1.front());
        path1.pop_front();
    }
     for (int i = reversedPath1.size() - 1; i >= 0; --i) {
         resultPath.push_back(reversedPath1[i]);
     }

    if (lcaFound) {
        resultPath.push_back(lca);
    } else if (!resultPath.empty() && !path2.empty() && resultPath.back() == path2.front()) {
         path2.pop_front();
    } else if (lcaFound == false && resultPath.empty() && !path2.empty()){
        resultPath.push_back(path2.front());
        path2.pop_front();
    }

    while (!path2.empty()) {
        resultPath.push_back(path2.front());
        path2.pop_front();
    }
}

template <class elem>
void BinTree<elem>::UPDATE_LONGEST_PATH(std::list<elem>& currentLongest, std::list<elem>& path1, std::list<elem>& path2, const std::list<elem>& newBranch) const {
    std::list<elem> diameter1, diameter2;
    if (!path1.empty()) {
        COMBINE_PATHS(diameter1, path1, newBranch);
    } else {
        path1 = newBranch;
        return;
    }
    if (!path2.empty()) {
        COMBINE_PATHS(diameter2, path2, newBranch);
    } else {
        path2 = newBranch;
        std::list<elem> initialDiameter;
        COMBINE_PATHS(initialDiameter, path1, path2);
         if (initialDiameter.size() > currentLongest.size()) {
             currentLongest = initialDiameter;
         }
         return;
    }
    if (diameter1.size() >= diameter2.size()) {
        if (diameter1.size() > currentLongest.size()) {
            currentLongest = diameter1;
        }
    } else {
        if (diameter2.size() > currentLongest.size()) {
            currentLongest = diameter2;
        }
    }
    if(diameter1.size() >= diameter2.size()) path2 = newBranch; else path1 = newBranch;
}

template <class elem>
void BinTree<elem>::FIND_DIAMETER(NodeBinTree<elem>* node, std::list<elem>& currentLongestPath, std::list<elem>& longestBranch1, std::list<elem>& longestBranch2, std::list<elem>& currentBranch) const {
    if (node == NULL) return;
    currentBranch.push_back(node->getInfo());
    if (node->getLeft() == NULL && node->getRight() == NULL) {
        UPDATE_LONGEST_PATH(currentLongestPath, longestBranch1, longestBranch2, currentBranch);
    } else {
        std::list<elem> branch1_copy_l = longestBranch1, branch2_copy_l = longestBranch2;
        FIND_DIAMETER(node->getLeft(), currentLongestPath, branch1_copy_l, branch2_copy_l, currentBranch);
        longestBranch1 = branch1_copy_l; longestBranch2 = branch2_copy_l; // Update after left call
        std::list<elem> branch1_copy_r = longestBranch1, branch2_copy_r = longestBranch2;
        FIND_DIAMETER(node->getRight(), currentLongestPath, branch1_copy_r, branch2_copy_r, currentBranch);
        longestBranch1 = branch1_copy_r; longestBranch2 = branch2_copy_r; // Update after right call
    }
    currentBranch.pop_back();
}

template <class elem>
BinTree<elem>::BinTree() {
    this->root = NULL;
    this->weight = 0;
}

template <class elem>
BinTree<elem>::BinTree(elem e) {
    this->root = new NodeBinTree<elem>(e);
    this->weight = 1;
}

template <class elem>
BinTree<elem>::BinTree(const BinTree<elem>& otherTree) {
    this->root = NULL;
    this->weight = 0;
    *this = otherTree;
}

template <class elem>
BinTree<elem>::BinTree(elem e, const BinTree<elem>& leftTree, const BinTree<elem>& rightTree) {
    this->root = new NodeBinTree<elem>(e);
    this->root->setLeft(COPY_NODES(leftTree.root));
    this->root->setRight(COPY_NODES(rightTree.root));
    this->weight = 1 + COUNT_NODES(this->root->getLeft()) + COUNT_NODES(this->root->getRight());
}

template <class elem>
BinTree<elem>::~BinTree() {
    DESTROY_NODES(this->root);
}

template <class elem>
BinTree<elem>& BinTree<elem>::operator=(const BinTree<elem>& otherTree) {
    if (this != &otherTree) {
        CLEAR();
        this->root = COPY_NODES(otherTree.root);
        this->weight = otherTree.weight;
    }
    return *this;
}

template <class elem>
void BinTree<elem>::copyFromPointer(const BinTree<elem>* otherTreePtr) {
     if (otherTreePtr == NULL) {
         CLEAR();
     } else if (this != otherTreePtr) {
        CLEAR();
        this->root = COPY_NODES(otherTreePtr->root);
        this->weight = otherTreePtr->weight;
     }
}

template <class elem>
bool BinTree<elem>::isEmpty() const {
    return this->root == NULL;
}

template <class elem>
int BinTree<elem>::getWeight() const {
    return this->weight;
}

template <class elem>
elem BinTree<elem>::getRootInfo() const {
    if (isEmpty()) throw std::runtime_error("getRootInfo() called on empty tree");
    return this->root->getInfo();
}

template <class elem>
BinTree<elem> BinTree<elem>::getLeftSubtree() const {
    BinTree<elem> leftSubtree;
    if (!isEmpty() && this->root->getLeft() != NULL) {
        leftSubtree.root = COPY_NODES(this->root->getLeft());
        leftSubtree.weight = leftSubtree.COUNT_NODES(leftSubtree.root);
    }
    return leftSubtree;
}

template <class elem>
BinTree<elem> BinTree<elem>::getRightSubtree() const {
     BinTree<elem> rightSubtree;
    if (!isEmpty() && this->root->getRight() != NULL) {
        rightSubtree.root = COPY_NODES(this->root->getRight());
        rightSubtree.weight = rightSubtree.COUNT_NODES(rightSubtree.root);
    }
    return rightSubtree;
}

template <class elem>
std::list<elem> BinTree<elem>::preOrder() const {
    std::list<elem> r; PRE_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> BinTree<elem>::inOrder() const {
    std::list<elem> r; IN_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> BinTree<elem>::postOrder() const {
    std::list<elem> r; POST_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> BinTree<elem>::levelOrder() const {
    std::list<elem> r; LEVEL_ORDER_HELPER(this->root, r); return r;
}

template <class elem>
std::list<elem> BinTree<elem>::getLevel(int level) const {
    std::list<elem> result;
    if (isEmpty() || level < 0) return result;
    std::queue<NodeBinTree<elem>*> q;
    q.push(this->root);
    q.push(NULL);
    int currentLevel = 0;
    while (!q.empty()) {
        NodeBinTree<elem>* current = q.front();
        q.pop();
        if (current == NULL) {
            currentLevel++;
            if (q.empty() || currentLevel > level) break;
            q.push(NULL);
        } else {
            if (currentLevel == level) {
                result.push_back(current->getInfo());
            }
            if (current->getLeft() != NULL) q.push(current->getLeft());
            if (current->getRight() != NULL) q.push(current->getRight());
        }
    }
    return result;
}

template <class elem>
int BinTree<elem>::getHeight() const {
    int ml = -1; GET_HEIGHT(this->root, 0, ml); return ml;
}

template <class elem>
std::list<elem> BinTree<elem>::getLeaves() const {
    std::list<elem> r; GET_LEAVES(this->root, r); return r;
}

template <class elem>
void BinTree<elem>::insertBST(const elem& value) {
    INSERT_BST(this->root, value);
}

template <class elem>
bool BinTree<elem>::searchBST(const elem& value) const {
    return SEARCH_BST(this->root, value);
}

template <class elem>
bool BinTree<elem>::removeBST(const elem& value) {
     bool removed = false;
     this->root = REMOVE_BST(this->root, value, removed);
     return removed;
}

template <class elem>
void BinTree<elem>::buildFromPreIn(std::list<elem> preOrderList, std::list<elem> inOrderList) {
     if (preOrderList.size() != inOrderList.size()) throw std::runtime_error("Mismatched list sizes in buildFromPreIn");
    CLEAR();
    this->root = BUILD_FROM_PRE_IN_RECURSIVE(preOrderList, inOrderList);
    this->weight = COUNT_NODES(this->root);
}

template <class elem>
void BinTree<elem>::buildFromPostIn(std::list<elem> postOrderList, std::list<elem> inOrderList) {
      if (postOrderList.size() != inOrderList.size()) throw std::runtime_error("Mismatched list sizes in buildFromPostIn");
    CLEAR();
    this->root = BUILD_FROM_POST_IN_RECURSIVE(postOrderList, inOrderList);
    this->weight = COUNT_NODES(this->root);
}

template <class elem>
std::list<elem> BinTree<elem>::findPathToNode(const elem& target) const {
    std::list<elem> path;
    bool found = false;
    FIND_PATH(this->root, path, target, found);
    if (!found) path.clear();
    return path;
}

template <class elem>
std::list<elem> BinTree<elem>::findPathBetweenNodes(const elem& value1, const elem& value2) const {
    std::list<elem> path1, path2, resultPath;
    bool found1 = false, found2 = false;
    FIND_PATHS_TO_TWO(this->root, path1, path2, value1, value2, found1, found2);
    if (found1 && found2) {
        COMBINE_PATHS(resultPath, path1, path2);
    }
    return resultPath;
}

template <class elem>
elem BinTree<elem>::lowestCommonAncestor(const elem& value1, const elem& value2) const {
    std::list<elem> path1, path2;
    bool found1 = false, found2 = false;
    FIND_PATHS_TO_TWO(this->root, path1, path2, value1, value2, found1, found2);
    if (!found1 || !found2) {
        throw std::runtime_error("One or both elements not found in lowestCommonAncestor");
    }
    elem lca;
    bool lcaFound = false;
    typename std::list<elem>::iterator it1 = path1.begin();
    typename std::list<elem>::iterator it2 = path2.begin();
    while (it1 != path1.end() && it2 != path2.end() && *it1 == *it2) {
        lca = *it1;
        lcaFound = true;
        it1++;
        it2++;
    }
    if (!lcaFound) {
         if(isEmpty()) throw std::runtime_error("Cannot find LCA in an empty tree");
         else throw std::runtime_error("Could not determine LCA (logic error or paths incorrect)");
    }
    return lca;
}

template <class elem>
std::list<elem> BinTree<elem>::getDiameterPath() const {
    std::list<elem> longestPath;
    if (isEmpty()) return longestPath;
    std::list<elem> branch1, branch2, currentBranch;
    FIND_DIAMETER(this->root, longestPath, branch1, branch2, currentBranch);
     if (longestPath.empty()) {
        if(branch1.size() >= branch2.size()) return branch1;
        else return branch2;
     }
    return longestPath;
}

template <class elem>
int BinTree<elem>::getHeightDifference(const elem& value1, const elem& value2) const {
    int level1 = GET_NODE_LEVEL(this->root, value1, 0);
    int level2 = GET_NODE_LEVEL(this->root, value2, 0);

    if (level1 == -1 || level2 == -1) {
        return -1;
    }

    return std::abs(level1 - level2);
}

template <class elem>
int BinTree<elem>::GET_NODE_LEVEL(NodeBinTree<elem>* node, const elem& target, int currentLevel) const {
    if (node == NULL) {
        return -1;
    }
    if (node->getInfo() == target) {
        return currentLevel;
    }
    int leftLevel = GET_NODE_LEVEL(node->getLeft(), target, currentLevel + 1);
    if (leftLevel != -1) {
        return leftLevel;
    }
    return GET_NODE_LEVEL(node->getRight(), target, currentLevel + 1);
}

template <class elem>
void BinTree<elem>::makeEmpty() {
    CLEAR();
}

// Gracias StackOverflow

template <class elem>
void printTreeStructure(const BinTree<elem>& tree) {
    if (!tree.isEmpty()) {

        std::cout << tree.getRootInfo() << std::endl;

        BinTree<elem> left = tree.getLeftSubtree();
        BinTree<elem> right = tree.getRightSubtree();


        std::string childPrefix = "";

        if (!left.isEmpty() && !right.isEmpty()) {
            printTreeRecursiveHelper(left, childPrefix, false);
            printTreeRecursiveHelper(right, childPrefix, true);
        } else if (!left.isEmpty()) {
            printTreeRecursiveHelper(left, childPrefix, true);
        } else if (!right.isEmpty()) {
            printTreeRecursiveHelper(right, childPrefix, true);
        }
    } else {
        std::cout << "<empty tree>" << std::endl;
    }
}

template <class elem>
void printTreeRecursiveHelper(const BinTree<elem>& subtree, const std::string& prefix, bool isTail) {

    std::cout << prefix << (isTail ? "└── " : "├── ") << subtree.getRootInfo() << std::endl;

    std::string childrenBasePrefix = prefix + (isTail ? "    " : "│   ");

    BinTree<elem> left = subtree.getLeftSubtree();
    BinTree<elem> right = subtree.getRightSubtree();

    if (!left.isEmpty() && !right.isEmpty()) {
        printTreeRecursiveHelper(left, childrenBasePrefix, false);
        printTreeRecursiveHelper(right, childrenBasePrefix, true);
    } else if (!left.isEmpty()) {
        printTreeRecursiveHelper(left, childrenBasePrefix, true);
    } else if (!right.isEmpty()) {
        printTreeRecursiveHelper(right, childrenBasePrefix, true);
    }
}

#endif