#include <iostream>
#include <list>
#include <string>
#include <exception>
#include "n_tree.h" // Asume que incluye node_n_tree.h

// Helper function to print elements of a list
template <class T>
void printList(const std::list<T>& l, const std::string& title) {
    std::cout << title << ": [";
    // C++98 requires typename for dependent types
    typename std::list<T>::const_iterator it = l.begin();
    bool first = true;
    while (it != l.end()) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << *it;
        first = false;
        ++it;
    }
    std::cout << "]" << std::endl;
}

// Overload for list<string> specifically if needed for different formatting
void printStringList(const std::list<std::string>& l, const std::string& title) {
    std::cout << title << ": [";
    std::list<std::string>::const_iterator it = l.begin();
    bool first = true;
    while (it != l.end()) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << "\"" << *it << "\""; // Add quotes for strings
        first = false;
        ++it;
    }
    std::cout << "]" << std::endl;
}


int main() {
    std::cout << "--- Testing N-ary Tree Basic Operations ---" << std::endl;
    NTree<char> tree;
    std::cout << "Initial empty tree:" << std::endl;
    std::cout << "isEmpty? " << (tree.isEmpty() ? "Yes" : "No") << std::endl; // Expected: Yes
    std::cout << "Weight: " << tree.getWeight() << std::endl; // Expected: 0

    // Test single node constructor
    NTree<char> treeA('A');
    std::cout << "\nTree with single node 'A':" << std::endl;
    std::cout << "isEmpty? " << (treeA.isEmpty() ? "Yes" : "No") << std::endl; // Expected: No
    std::cout << "Weight: " << treeA.getWeight() << std::endl; // Expected: 1
    try {
        std::cout << "Root Info: " << treeA.getRootInfo() << std::endl; // Expected: A
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // --- Test Construction / Modification ---
    std::cout << "\n--- Testing Construction / Modification ---" << std::endl;
    // Build tree using attachChildrenToNode
    //      A
    //    / | \
    //   B  C  D
    //  / \    |
    // E   F   G

    std::cout << "Building tree structure..." << std::endl;
    std::list< NTree<char> > childrenB;
    childrenB.push_back(NTree<char>('E'));
    childrenB.push_back(NTree<char>('F'));
    treeA.attachChildrenToNode('A', std::list< NTree<char> >(1, NTree<char>('B'))); // Add B as child of A
    treeA.attachChildrenToNode('A', std::list< NTree<char> >(1, NTree<char>('C'))); // Add C as child of A (should replace B?) NO, attachChildrenToNode replaces ALL children
    treeA.attachChildrenToNode('A', std::list< NTree<char> >(1, NTree<char>('D'))); // Add D as child of A (should replace C?) YES. Let's rebuild correctly.

    NTree<char> testTree('A');
    std::list< NTree<char> > childrenA;
    childrenA.push_back(NTree<char>('B'));
    childrenA.push_back(NTree<char>('C'));
    childrenA.push_back(NTree<char>('D'));
    testTree.attachChildrenToNode('A', childrenA); // Attach B, C, D to A

    std::list< NTree<char> > childrenB_correct;
    childrenB_correct.push_back(NTree<char>('E'));
    childrenB_correct.push_back(NTree<char>('F'));
    testTree.attachChildrenToNode('B', childrenB_correct); // Attach E, F to B

    std::list< NTree<char> > childrenD;
    childrenD.push_back(NTree<char>('G'));
    testTree.attachChildrenToNode('D', childrenD); // Attach G to D

    std::cout << "\nTree after building with attachChildrenToNode:" << std::endl;
    std::cout << "Weight: " << testTree.getWeight() << std::endl; // Expected: 7 (A,B,C,D,E,F,G)

    // Test Traversals
    std::cout << "\nTesting Traversals:" << std::endl;
    printList(testTree.preOrder(),   "PreOrder  "); // Expected: [A, B, E, F, C, D, G]
    printList(testTree.inOrder(),    "InOrder   "); // Expected: [E, B, F, A, C, G, D] (N-ary: 1st child -> root -> siblings)
    printList(testTree.postOrder(),  "PostOrder "); // Expected: [E, F, B, C, G, D, A]
    printList(testTree.levelOrder(), "LevelOrder"); // Expected: [A, B, C, D, E, F, G]

    // Test insertSubtree (add H as last child of A)
    std::cout << "\nInserting subtree 'H' under 'A'..." << std::endl;
    NTree<char> treeH('H');
    testTree.insertSubtree(treeH);
    std::cout << "Weight after insert: " << testTree.getWeight() << std::endl; // Expected: 8
    printList(testTree.levelOrder(), "LevelOrder after insert"); // Expected: [A, B, C, D, H, E, F, G]

    // Test removeSubtree
    std::cout << "\nRemoving 2nd child ('C') from 'A'..." << std::endl;
    if (testTree.removeSubtree(2)) { // Remove C (position 2)
         std::cout << "Removal successful." << std::endl;
         std::cout << "Weight after remove: " << testTree.getWeight() << std::endl; // Expected: 7
         printList(testTree.levelOrder(), "LevelOrder after remove"); // Expected: [A, B, D, H, E, F, G]
    } else {
         std::cout << "Removal failed." << std::endl;
    }
     std::cout << "Removing 10th child (invalid) from 'A'..." << std::endl;
     if (!testTree.removeSubtree(10)) { // Remove invalid position
          std::cout << "Removal correctly failed for invalid position." << std::endl;
     }


    // --- Test Properties ---
    std::cout << "\n--- Testing Properties ---" << std::endl;
    // Tree should now be:
    //      A
    //    / | \
    //   B  D  H
    //  / \ |
    // E   F G
    std::cout << "Current Weight: " << testTree.getWeight() << std::endl; // Expected: 7
    std::cout << "Height: " << testTree.getHeight() << std::endl; // Expected: 2
    printList(testTree.getLeaves(), "Leaves    "); // Expected: [E, F, G, H] (Order may vary)

    // Test getLevel
    std::cout << "Nodes at Level 0: "; printStringList(testTree.getLevel(0), ""); // Expected: ["A"]
    std::cout << "Nodes at Level 1: "; printStringList(testTree.getLevel(1), ""); // Expected: ["B", "D", "H"]
    std::cout << "Nodes at Level 2: "; printStringList(testTree.getLevel(2), ""); // Expected: ["E", "F", "G"]
    std::cout << "Nodes at Level 3: "; printStringList(testTree.getLevel(3), ""); // Expected: []

    // --- Test Copying / Assignment ---
    std::cout << "\n--- Testing Copying / Assignment ---" << std::endl;
    NTree<char> treeCopy(testTree);
    NTree<char> treeAssign;
    treeAssign = testTree;

    std::cout << "Inserting subtree 'I' under 'A' in original..." << std::endl;
    testTree.insertSubtree(NTree<char>('I')); // A now has children B, D, H, I

    std::cout << "Original Weight: " << testTree.getWeight() << std::endl; // Expected: 8
    std::cout << "Copy Weight (should be unchanged): " << treeCopy.getWeight() << std::endl; // Expected: 7
    std::cout << "Assign Weight (should be unchanged): " << treeAssign.getWeight() << std::endl; // Expected: 7

    printList(testTree.levelOrder(), "Original LevelOrder");
    printList(treeCopy.levelOrder(), "Copy LevelOrder    ");
    printList(treeAssign.levelOrder(), "Assign LevelOrder  ");

    // --- Test Path, LCA, Diameter ---
    // Using treeCopy which is A{ B{E,F}, D{G}, H }
    std::cout << "\n--- Testing Path, LCA, Diameter (on copied tree) ---" << std::endl;
    printList(treeCopy.findPathToNode('F'), "Path to F "); // Expected: [A, B, F]
    printList(treeCopy.findPathToNode('G'), "Path to G "); // Expected: [A, D, G]
    printList(treeCopy.findPathToNode('H'), "Path to H "); // Expected: [A, H]
    printList(treeCopy.findPathToNode('Z'), "Path to Z "); // Expected: []

    printList(treeCopy.findPathBetweenNodes('E', 'G'), "Path E <-> G"); // Expected: [E, B, A, D, G]
    printList(treeCopy.findPathBetweenNodes('F', 'H'), "Path F <-> H"); // Expected: [F, B, A, H]
    printList(treeCopy.findPathBetweenNodes('A', 'G'), "Path A <-> G"); // Expected: [A, D, G]

    try {
        std::cout << "LCA(E, G): " << treeCopy.lowestCommonAncestor('E', 'G') << std::endl; // Expected: A
        std::cout << "LCA(E, F): " << treeCopy.lowestCommonAncestor('E', 'F') << std::endl; // Expected: B
        std::cout << "LCA(D, G): " << treeCopy.lowestCommonAncestor('D', 'G') << std::endl; // Expected: D
        std::cout << "LCA(A, H): " << treeCopy.lowestCommonAncestor('A', 'H') << std::endl; // Expected: A
        // std::cout << "LCA(E, Z): " << treeCopy.lowestCommonAncestor('E', 'Z') << std::endl; // Throws exception
    } catch(const std::exception& e) {
         std::cerr << "LCA Error: " << e.what() << std::endl;
    }

    printList(treeCopy.getDiameterPath(), "Diameter Path "); // Expected: [E, B, A, D, G] or [F, B, A, D, G] (Length 5)

    // Test getChildren
    std::cout << "\nTesting getChildren for root 'A' (on copied tree)..." << std::endl;
    std::list< NTree<char> > rootChildren = treeCopy.getChildren();
    std::cout << "Number of children found: " << rootChildren.size() << std::endl; // Expected: 3
    // Print root of each child subtree
    std::list<char> childRoots;
    for (typename std::list< NTree<char> >::iterator it = rootChildren.begin(); it != rootChildren.end(); ++it) {
        try {
            childRoots.push_back(it->getRootInfo());
        } catch (const std::exception& e) {
            std::cerr << "Error getting child root: " << e.what() << std::endl;
        }
    }
    printList(childRoots, "Root nodes of children"); // Expected: [B, D, H] (Order matters!)


    std::cout << "\n--- Testing Finished ---" << std::endl;

    return 0;
}