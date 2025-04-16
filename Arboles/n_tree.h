#ifndef N_TREE_H_
#define N_TREE_H_

#include "node_n_tree.h" // Includes corrected version
#include <iostream>
#include <list>
#include <queue>
#include <stack>     // For iterative destructor
#include <cstddef>
#include <stdexcept>
#include <vector>
#include <string>    // Needed for getLevel string conversion assumption
#include <sstream> 

// Forward Declaration
template <class elem> class NTree;

template<class elem>
class NTree
{
private:
    NodeNTree<elem> *root;
    int weight; // Added for node count tracking

    // --- Private Helper Method Declarations ---
    NodeNTree<elem>* COPY_NODES(const NodeNTree<elem>* sourceNode) const;
    void DESTROY_NODES(); // Iterative destructor helper
    int COUNT_NODES(const NodeNTree<elem>* node) const;
    void PRE_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const;
    void IN_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const;
    void POST_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const;
    void LEVEL_ORDER_HELPER(const NodeNTree<elem>* node, std::list<elem>& resultList) const;
    // Note: Assuming elem can be converted to std::string for getLevel marker logic
    void LEVEL_ORDER_EXACT_HELPER(const NodeNTree<elem>* node, std::list<std::string>& resultList) const;
    void GET_HEIGHT(const NodeNTree<elem>* node, int currentLevel, int& maxLevelReached) const;
    void GET_LEAVES(const NodeNTree<elem>* node, std::list<elem>& leafList) const;
    void CLEAR();
    NodeNTree<elem>* FIND_NODE_PREORDER(NodeNTree<elem>* node, const elem& target) const; // Search helper
    void ATTACH_CHILDREN_HELPER(NodeNTree<elem>* parentNode, std::list< NTree<elem> >& childrenList); // Child attachment helper

    // Path Helpers
    void FIND_PATH(const NodeNTree<elem>* node, std::list<elem>& currentPath, const elem& target, bool& found) const;
    void FIND_PATHS_TO_TWO(const NodeNTree<elem>* node, std::list<elem>& path1, std::list<elem>& path2, const elem& target1, const elem& target2, bool& found1, bool& found2) const;

    // Diameter Helpers
    void COMBINE_PATHS(std::list<elem>& resultPath, std::list<elem> path1, std::list<elem> path2) const;
    void UPDATE_LONGEST_PATH(std::list<elem>& currentLongest, std::list<elem>& path1, std::list<elem>& path2, const std::list<elem>& newBranch) const;
    void FIND_DIAMETER(const NodeNTree<elem>* node, std::list<elem>& currentLongestPath, std::list<elem>& longestBranch1, std::list<elem>& longestBranch2, std::list<elem>& currentBranch) const;

public:
    // --- Public Interface Declarations ---
    NTree(); // Creates an empty N-ary tree.
    NTree(elem e); // Creates a tree with a single root node.
    NTree(const NTree<elem>& otherTree); // Creates a deep copy of another tree.
    NTree(elem e, const std::list< NTree<elem> >& children); // Creates tree from root and list of child subtrees.
    ~NTree(); // Destroys the tree and frees memory.

    NTree<elem>& operator=(const NTree<elem>& otherTree); // Assigns a deep copy.
    void copyFromPointer(const NTree<elem>* otherTreePtr); // Copies from a tree pointer.

    bool isEmpty() const; // Checks if the tree is empty.
    int getWeight() const; // Returns the total number of nodes.
    elem getRootInfo() const; // Returns the info from the root node.

    std::list< NTree<elem> > getChildren() const; // Returns a list of deep copies of the root's child subtrees.

    void insertSubtree(const NTree<elem>& subtree); // Inserts a copy of subtree as the last child of the root.
    bool removeSubtree(int position); // Removes the child subtree at the given 1-based position; returns true if successful.

    std::list<elem> preOrder() const; // Returns list of elements in pre-order.
    std::list<elem> inOrder() const; // Returns list of elements in 'N-ary' in-order.
    std::list<elem> postOrder() const; // Returns list of elements in post-order.
    std::list<elem> levelOrder() const; // Returns list of elements in level-order.
    std::list<std::string> getLevel(int level) const; // Returns list of elements (as strings) at specific level.

    int getHeight() const; // Returns the height of the tree.
    std::list<elem> getLeaves() const; // Returns a list of leaf elements.

    std::list<elem> findPathToNode(const elem& target) const; // Returns path from root to target node.
    std::list<elem> findPathBetweenNodes(const elem& value1, const elem& value2) const; // Returns path between two nodes.
    elem lowestCommonAncestor(const elem& value1, const elem& value2) const; // Finds the lowest common ancestor.
    std::list<elem> getDiameterPath() const; // Returns the elements forming the diameter path.

    bool attachChildrenToNode(const elem& parentValue, const std::list< NTree<elem> >& children); // Attaches copies of children to parent node.
};

// --- NTree Method Definitions ---

// --- Private Helpers ---

template <class elem>
NodeNTree<elem>* NTree<elem>::COPY_NODES(const NodeNTree<elem>* sourceNode) const {
    if (sourceNode == NULL) return NULL;
    // Copy current node info, then recursively copy first child and next sibling
    NodeNTree<elem>* newNode = new NodeNTree<elem>(sourceNode->getInfo());
    newNode->setSons(COPY_NODES(sourceNode->getSons()));
    newNode->setBro(COPY_NODES(sourceNode->getBro()));
    return newNode;
}

template <class elem>
void NTree<elem>::DESTROY_NODES() {
    // Iterative destruction using a stack (Pre-order traversal like)
    if (this->root == NULL) return;
    std::stack<NodeNTree<elem>*> s;
    s.push(this->root);
    while (!s.empty()) {
        NodeNTree<elem>* current = s.top();
        s.pop();
        // Push children (siblings first, then first child) to process parent last implicitly
        if (current->getBro() != NULL) {
            s.push(current->getBro());
        }
        if (current->getSons() != NULL) {
            s.push(current->getSons());
        }
        delete current; // Use delete
    }
    this->root = NULL; // Important after deleting all nodes
    this->weight = 0;
}

template <class elem>
int NTree<elem>::COUNT_NODES(const NodeNTree<elem>* node) const {
    if (node == NULL) return 0;
    // Count this node + nodes in first child's subtree + nodes in sibling's subtree
    return 1 + COUNT_NODES(node->getSons()) + COUNT_NODES(node->getBro());
}

template <class elem>
void NTree<elem>::PRE_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const {
    if (node != NULL) {
        resultList.push_back(node->getInfo()); // Visit Root
        NodeNTree<elem>* child = node->getSons();
        while (child != NULL) { // Recurse on children (via siblings)
            PRE_ORDER(child, resultList);
            child = child->getBro();
        }
    }
}

template <class elem>
void NTree<elem>::IN_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const {
    if (node != NULL) {
        // 1. Recurse on the first child
        IN_ORDER(node->getSons(), resultList);
        // 2. Visit the root
        resultList.push_back(node->getInfo());
        // 3. Recurse on the remaining children (siblings of the first child)
        if (node->getSons() != NULL) {
            NodeNTree<elem>* sibling = node->getSons()->getBro();
            while (sibling != NULL) {
                IN_ORDER(sibling, resultList);
                sibling = sibling->getBro();
            }
        }
    }
}

template <class elem>
void NTree<elem>::POST_ORDER(const NodeNTree<elem>* node, std::list<elem>& resultList) const {
    if (node != NULL) {
        // 1. Recurse on children (via siblings)
        NodeNTree<elem>* child = node->getSons();
        while (child != NULL) {
            POST_ORDER(child, resultList);
            child = child->getBro();
        }
        // 2. Visit the root
        resultList.push_back(node->getInfo());
    }
}

template <class elem>
void NTree<elem>::LEVEL_ORDER_HELPER(const NodeNTree<elem>* node, std::list<elem>& resultList) const {
    if (node == NULL) return;
    std::queue<const NodeNTree<elem>*> q; // Queue of const pointers
    q.push(node);
    while (!q.empty()) {
        const NodeNTree<elem>* current = q.front();
        q.pop();
        resultList.push_back(current->getInfo());
        // Enqueue all children of the current node
        NodeNTree<elem>* child = current->getSons();
        while (child != NULL) {
            q.push(child);
            child = child->getBro();
        }
    }
}

template <class elem>
void NTree<elem>::LEVEL_ORDER_EXACT_HELPER(const NodeNTree<elem>* node, std::list<std::string>& resultList) const {
    // Uses NULL marker in queue to detect level changes
    if (node == NULL) return;
    std::queue<const NodeNTree<elem>*> q;
    q.push(node);
    q.push(NULL); // Level End Marker

    while (q.size() > 1) { // Continue while more than just the marker is present
        const NodeNTree<elem>* current = q.front();
        q.pop();

        if (current == NULL) {
            resultList.push_back("-"); // Add level separator string
            q.push(NULL); // Add marker for the next level
        } else {
            // Convert element to string (requires elem to be convertible or overload needed)
            // This part is tricky without C++11 to_string or specific type knowledge
            // Assuming a simple stream insertion for demonstration
            // Replace with appropriate conversion for your 'elem' type
            std::ostringstream oss;
            oss << current->getInfo();
            resultList.push_back(oss.str());

            // Enqueue children
            NodeNTree<elem>* child = current->getSons();
            while (child != NULL) {
                q.push(child);
                child = child->getBro();
            }
        }
    }
}


template <class elem>
void NTree<elem>::GET_HEIGHT(const NodeNTree<elem>* node, int currentLevel, int& maxLevelReached) const {
    if (node != NULL) {
        if (currentLevel > maxLevelReached) {
            maxLevelReached = currentLevel;
        }
        // Recurse for all children
        NodeNTree<elem>* child = node->getSons();
        while (child != NULL) {
            GET_HEIGHT(child, currentLevel + 1, maxLevelReached);
            child = child->getBro();
        }
    }
}

template <class elem>
void NTree<elem>::GET_LEAVES(const NodeNTree<elem>* node, std::list<elem>& leafList) const {
    if (node != NULL) {
        if (node->getSons() == NULL) { // Leaf node condition
            leafList.push_back(node->getInfo());
        } else {
            // Recurse for all children
            NodeNTree<elem>* child = node->getSons();
            while (child != NULL) {
                GET_LEAVES(child, leafList);
                child = child->getBro();
            }
        }
    }
}

template <class elem>
void NTree<elem>::CLEAR() {
    DESTROY_NODES(); // Use the iterative helper
    // root and weight are reset inside DESTROY_NODES
}

template <class elem>
NodeNTree<elem>* NTree<elem>::FIND_NODE_PREORDER(NodeNTree<elem>* node, const elem& target) const {
    if (node == NULL) {
        return NULL;
    }
    if (node->getInfo() == target) {
        return node;
    }
    // Search children
    NodeNTree<elem>* child = node->getSons();
    while(child != NULL) {
        NodeNTree<elem>* foundNode = FIND_NODE_PREORDER(child, target);
        if (foundNode != NULL) {
            return foundNode; // Found in child's subtree
        }
        child = child->getBro(); // Check next sibling
    }
    return NULL; // Not found in this subtree
}

template <class elem>
void NTree<elem>::ATTACH_CHILDREN_HELPER(NodeNTree<elem>* parentNode, std::list< NTree<elem> >& childrenList) {
    if (parentNode == NULL || childrenList.empty()) {
        return;
    }

    // Clear existing children of the parent first? Arbol_n seemed to replace.
    // Let's assume replacement. Need a recursive delete for children first.
    std::stack<NodeNTree<elem>*> s;
    if(parentNode->getSons() != NULL) s.push(parentNode->getSons());
    parentNode->setSons(NULL); // Detach children before deleting
    while (!s.empty()) {
        NodeNTree<elem>* current = s.top(); s.pop();
        if (current->getBro() != NULL) s.push(current->getBro());
        if (current->getSons() != NULL) s.push(current->getSons());
        this->weight--; // Decrement weight for each deleted node
        delete current;
    }

    // Attach new children
    NodeNTree<elem>* lastNewSibling = NULL;
    while(!childrenList.empty()) {
        NTree<elem>& childTree = childrenList.front(); // Get reference to first child tree
        NodeNTree<elem>* newChildNode = COPY_NODES(childTree.root); // Copy it
        int childWeight = COUNT_NODES(newChildNode); // Count nodes in copied child
        this->weight += childWeight; // Add to total weight

        if (lastNewSibling == NULL) { // This is the first child
            parentNode->setSons(newChildNode);
        } else { // Link as sibling of the previous new child
            lastNewSibling->setBro(newChildNode);
        }
        lastNewSibling = newChildNode; // Update last added sibling

        childrenList.pop_front(); // Remove from input list
    }
}


// --- Path Helpers ---
template <class elem>
void NTree<elem>::FIND_PATH(const NodeNTree<elem>* node, std::list<elem>& currentPath, const elem& target, bool& found) const {
    if (node == NULL || found) return;
    currentPath.push_back(node->getInfo());
    if (node->getInfo() == target) { found = true; return; }

    NodeNTree<elem>* child = node->getSons();
    while (child != NULL && !found) {
        FIND_PATH(child, currentPath, target, found);
        child = child->getBro();
    }

    if (!found) {
        currentPath.pop_back(); // Backtrack
    }
}

template <class elem>
void NTree<elem>::FIND_PATHS_TO_TWO(const NodeNTree<elem>* node, std::list<elem>& path1, std::list<elem>& path2, const elem& target1, const elem& target2, bool& found1, bool& found2) const {
     if (node == NULL || (found1 && found2)) return;

     if (!found1) path1.push_back(node->getInfo());
     if (!found2) path2.push_back(node->getInfo());

     if (node->getInfo() == target1) found1 = true;
     if (node->getInfo() == target2) found2 = true;

     if (found1 && found2) return;

     NodeNTree<elem>* child = node->getSons();
     while (child != NULL && (!found1 || !found2)) {
         FIND_PATHS_TO_TWO(child, path1, path2, target1, target2, found1, found2);
         child = child->getBro();
     }

     if (!found1) path1.pop_back();
     if (!found2) path2.pop_back();
}

// --- Diameter Helpers ---
template <class elem>
void NTree<elem>::COMBINE_PATHS(std::list<elem>& resultPath, std::list<elem> path1, std::list<elem> path2) const {
    // Same logic as BinTree version
    elem lca; bool lcaFound = false;
    while (!path1.empty() && !path2.empty() && path1.front() == path2.front()) {
        lca = path1.front(); lcaFound = true; path1.pop_front(); path2.pop_front();
    }
    resultPath.clear();
    if (!lcaFound && !path1.empty()) lca = path1.front(); else if (!lcaFound && !path2.empty()) lca = path2.front();
    std::vector<elem> reversedPath1;
    while (!path1.empty()) { reversedPath1.push_back(path1.front()); path1.pop_front(); }
    for (int i = reversedPath1.size() - 1; i >= 0; --i) { resultPath.push_back(reversedPath1[i]); }
    if (lcaFound) { resultPath.push_back(lca); }
    else if (!resultPath.empty() && !path2.empty() && resultPath.back() == path2.front()) { path2.pop_front(); }
    else if (lcaFound == false && resultPath.empty() && !path2.empty()){ resultPath.push_back(path2.front()); path2.pop_front(); }
    while (!path2.empty()) { resultPath.push_back(path2.front()); path2.pop_front(); }
}

template <class elem>
void NTree<elem>::UPDATE_LONGEST_PATH(std::list<elem>& currentLongest, std::list<elem>& path1, std::list<elem>& path2, const std::list<elem>& newBranch) const {
    // Same logic as BinTree version
    std::list<elem> diameter1, diameter2;
    if (!path1.empty()) { COMBINE_PATHS(diameter1, path1, newBranch); } else { path1 = newBranch; return; }
    if (!path2.empty()) { COMBINE_PATHS(diameter2, path2, newBranch); } else {
        path2 = newBranch; std::list<elem> initialDiameter; COMBINE_PATHS(initialDiameter, path1, path2);
        if (initialDiameter.size() > currentLongest.size()) { currentLongest = initialDiameter; } return;
    }
    if (diameter1.size() >= diameter2.size()) { if (diameter1.size() > currentLongest.size()) { currentLongest = diameter1; } }
    else { if (diameter2.size() > currentLongest.size()) { currentLongest = diameter2; } }
    if(diameter1.size() >= diameter2.size()) path2 = newBranch; else path1 = newBranch;
}

template <class elem>
void NTree<elem>::FIND_DIAMETER(const NodeNTree<elem>* node, std::list<elem>& currentLongestPath, std::list<elem>& longestBranch1, std::list<elem>& longestBranch2, std::list<elem>& currentBranch) const {
    if (node == NULL) return;
    currentBranch.push_back(node->getInfo());
    if (node->getSons() == NULL) { // Leaf node check
        UPDATE_LONGEST_PATH(currentLongestPath, longestBranch1, longestBranch2, currentBranch);
    } else {
        // Explore all children, updating branches
        NodeNTree<elem>* child = node->getSons();
         // Need separate branch states for each child exploration path
        std::list<elem> b1_for_child = longestBranch1;
        std::list<elem> b2_for_child = longestBranch2;
        while (child != NULL) {
            FIND_DIAMETER(child, currentLongestPath, b1_for_child, b2_for_child, currentBranch);
            // How to update longestBranch1/2 based on child results?
            // This logic from Arbol_n becomes complex here. A simpler diameter
            // approach might be better, but adhering to Arbol_n's logic:
            // We need to decide if the branches found down this child path
            // should replace the current longest branches *for this level*.
             longestBranch1 = b1_for_child; // Tentative update based on last child explored
             longestBranch2 = b2_for_child; // Might not be correct overall update strategy
             // Reset for next sibling? This requires careful state management.
             b1_for_child = longestBranch1; // Pass potentially updated state to next sibling
             b2_for_child = longestBranch2;
            child = child->getBro();
        }
    }
    currentBranch.pop_back();
}

// --- Public Methods Definitions ---

template <class elem>
NTree<elem>::NTree() {
    this->root = NULL;
    this->weight = 0;
}

template <class elem>
NTree<elem>::NTree(elem e) {
    this->root = new NodeNTree<elem>(e);
    this->weight = 1;
}

template <class elem>
NTree<elem>::NTree(const NTree<elem>& otherTree) {
    this->root = NULL;
    this->weight = 0;
    *this = otherTree; // Use assignment operator
}

template <class elem>
NTree<elem>::NTree(elem e, const std::list< NTree<elem> >& children) {
    this->root = new NodeNTree<elem>(e);
    this->weight = 1; // Start with root weight
    // Need mutable copy to pass to helper which modifies it
    std::list< NTree<elem> > childrenCopy = children;
    // Use a helper that correctly calculates weight delta? Simpler to recalculate.
    ATTACH_CHILDREN_HELPER(this->root, childrenCopy);
    // Recalculate weight after attaching - ATTACH_CHILDREN_HELPER now tries to update weight
    // this->weight = COUNT_NODES(this->root); // Ensure weight is correct
}

template <class elem>
NTree<elem>::~NTree() {
    DESTROY_NODES(); // Use iterative helper
}

template <class elem>
NTree<elem>& NTree<elem>::operator=(const NTree<elem>& otherTree) {
    if (this != &otherTree) {
        CLEAR();
        this->root = COPY_NODES(otherTree.root);
        this->weight = otherTree.weight; // Weight matches copied structure
    }
    return *this;
}

template <class elem>
void NTree<elem>::copyFromPointer(const NTree<elem>* otherTreePtr) {
    if (otherTreePtr == NULL) {
        CLEAR();
    } else if (this != otherTreePtr) {
        CLEAR();
        this->root = COPY_NODES(otherTreePtr->root);
        this->weight = otherTreePtr->weight;
    }
}

template <class elem>
bool NTree<elem>::isEmpty() const {
    return this->root == NULL;
}

template <class elem>
int NTree<elem>::getWeight() const {
    return this->weight;
}

template <class elem>
elem NTree<elem>::getRootInfo() const {
    if (isEmpty()) throw std::runtime_error("getRootInfo called on empty tree");
    return this->root->getInfo();
}

template <class elem>
std::list< NTree<elem> > NTree<elem>::getChildren() const {
    std::list< NTree<elem> > childrenList;
    if (!isEmpty()) {
        NodeNTree<elem>* currentChildNode = this->root->getSons();
        while (currentChildNode != NULL) {
            // Create a temporary tree root for the child subtree
            NTree<elem> childTree;
            // Need to copy the *subtree* rooted at currentChildNode
            // Temporarily detach siblings for correct copying? Arbol_n's approach was complex.
            // Let's try a cleaner copy:
            childTree.root = COPY_NODES(currentChildNode); // Copy the whole child structure
            if(childTree.root) {
               childTree.root->setBro(NULL); // Ensure copied child root has no siblings
               childTree.weight = childTree.COUNT_NODES(childTree.root); // Set weight
               childrenList.push_back(childTree);
            }
            currentChildNode = currentChildNode->getBro(); // Move to next sibling in original tree
        }
    }
    return childrenList;
}


template <class elem>
void NTree<elem>::insertSubtree(const NTree<elem>& subtree) {
    if (isEmpty() || subtree.isEmpty()) return; // Cannot insert into empty tree or insert empty tree

    NodeNTree<elem>* newSubtreeRoot = COPY_NODES(subtree.root);
    if (newSubtreeRoot == NULL) return; // Nothing to insert if copy failed

    int addedWeight = COUNT_NODES(newSubtreeRoot); // Weight of the copied subtree

    NodeNTree<elem>* child = this->root->getSons();
    if (child == NULL) { // Root has no children yet
        this->root->setSons(newSubtreeRoot);
    } else { // Find the last sibling
        while (child->getBro() != NULL) {
            child = child->getBro();
        }
        child->setBro(newSubtreeRoot); // Append new subtree
    }
    this->weight += addedWeight; // Update weight
}

template <class elem>
bool NTree<elem>::removeSubtree(int position) {
    if (isEmpty() || position < 1 || this->root->getSons() == NULL) {
        return false; // Invalid position or no children
    }

    NodeNTree<elem>* nodeToRemove = NULL;
    NodeNTree<elem>* prevSibling = NULL;
    int currentPos = 1;

    if (position == 1) { // Removing the first child
        nodeToRemove = this->root->getSons();
        this->root->setSons(nodeToRemove->getBro()); // Update root's first child
    } else { // Removing a subsequent child
        prevSibling = this->root->getSons();
        currentPos = 2;
        while (prevSibling != NULL && currentPos < position) {
            prevSibling = prevSibling->getBro();
            currentPos++;
        }
        // If prevSibling is NULL or we didn't reach the position's predecessor
        if (prevSibling == NULL || prevSibling->getBro() == NULL) {
            return false; // Position out of bounds
        }
        nodeToRemove = prevSibling->getBro();
        prevSibling->setBro(nodeToRemove->getBro()); // Link previous to next
    }

    // Now destroy the removed subtree
    if (nodeToRemove != NULL) {
        nodeToRemove->setBro(NULL); // Isolate the subtree before destroying
        // Need a recursive destructor helper that takes a node*
        std::stack<NodeNTree<elem>*> s;
        s.push(nodeToRemove);
        int removedWeight = 0;
        while(!s.empty()){
            NodeNTree<elem>* curr = s.top(); s.pop();
            if(curr->getBro() != NULL) s.push(curr->getBro());
            if(curr->getSons() != NULL) s.push(curr->getSons());
            delete curr;
            removedWeight++;
        }
        this->weight -= removedWeight; // Update weight
        return true;
    }
    return false; // Should not happen if logic above is correct
}


template <class elem>
std::list<elem> NTree<elem>::preOrder() const {
    std::list<elem> r; PRE_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> NTree<elem>::inOrder() const {
    std::list<elem> r; IN_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> NTree<elem>::postOrder() const {
    std::list<elem> r; POST_ORDER(this->root, r); return r;
}

template <class elem>
std::list<elem> NTree<elem>::levelOrder() const {
    std::list<elem> r; LEVEL_ORDER_HELPER(this->root, r); return r;
}

template <class elem>
std::list<std::string> NTree<elem>::getLevel(int level) const {
    std::list<std::string> resultWithMarkers;
    std::list<std::string> result;
    LEVEL_ORDER_EXACT_HELPER(this->root, resultWithMarkers);

    int currentLevel = 0;
    typename std::list<std::string>::const_iterator it = resultWithMarkers.begin();
    while(it != resultWithMarkers.end()){
        if (*it == "-") {
            currentLevel++;
        } else if (currentLevel == level) {
            result.push_back(*it);
        } else if (currentLevel > level) {
            break;
        }
        ++it;
    }
    return result;
}

template <class elem>
int NTree<elem>::getHeight() const {
    int maxLevel = -1; // Empty tree height = -1
    GET_HEIGHT(this->root, 0, maxLevel); // Root at level 0
    return maxLevel;
}

template <class elem>
std::list<elem> NTree<elem>::getLeaves() const {
    std::list<elem> r; GET_LEAVES(this->root, r); return r;
}

template <class elem>
std::list<elem> NTree<elem>::findPathToNode(const elem& target) const {
    std::list<elem> path; bool found = false;
    FIND_PATH(this->root, path, target, found);
    if (!found) path.clear();
    return path;
}

template <class elem>
std::list<elem> NTree<elem>::findPathBetweenNodes(const elem& value1, const elem& value2) const {
    std::list<elem> p1, p2, res; bool f1=false, f2=false;
    FIND_PATHS_TO_TWO(this->root, p1, p2, value1, value2, f1, f2);
    if (f1 && f2) { COMBINE_PATHS(res, p1, p2); }
    return res;
}

template <class elem>
elem NTree<elem>::lowestCommonAncestor(const elem& value1, const elem& value2) const {
    std::list<elem> path1, path2; bool f1=false, f2=false;
    FIND_PATHS_TO_TWO(this->root, path1, path2, value1, value2, f1, f2);
    if (!f1 || !f2) throw std::runtime_error("LCA: One or both elements not found");
    elem lca; bool lcaFound = false;
    typename std::list<elem>::iterator it1 = path1.begin(), it2 = path2.begin();
    while (it1 != path1.end() && it2 != path2.end() && *it1 == *it2) {
        lca = *it1; lcaFound = true; ++it1; ++it2;
    }
    if (!lcaFound) throw std::runtime_error("LCA: Could not determine LCA");
    return lca;
}

template <class elem>
std::list<elem> NTree<elem>::getDiameterPath() const {
    std::list<elem> longestPath; if (isEmpty()) return longestPath;
    std::list<elem> branch1, branch2, currentBranch;
    FIND_DIAMETER(this->root, longestPath, branch1, branch2, currentBranch);
    if (longestPath.empty()) { return (branch1.size() >= branch2.size()) ? branch1 : branch2; }
    return longestPath;
}

template <class elem>
bool NTree<elem>::attachChildrenToNode(const elem& parentValue, const std::list< NTree<elem> >& children) {
    if (children.empty()) return true; // Nothing to attach

    NodeNTree<elem>* parentNode = FIND_NODE_PREORDER(this->root, parentValue);
    if (parentNode == NULL) {
        // Handle case where parentValue is meant to be the root and tree is empty
        if (isEmpty()) {
            this->root = new NodeNTree<elem>(parentValue);
            this->weight = 1;
            parentNode = this->root;
        } else {
            return false; // Parent node not found in non-empty tree
        }
    }

    // Make mutable copy as helper modifies list
    std::list< NTree<elem> > childrenCopy = children;
    ATTACH_CHILDREN_HELPER(parentNode, childrenCopy);
    // Weight is updated inside ATTACH_CHILDREN_HELPER now
    return true;
}

#endif // N_TREE_H_