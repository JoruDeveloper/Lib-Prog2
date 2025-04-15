#include <iostream>
#include <list>
#include <string> // Para usar std::string en la función de impresión
#include <exception> // Para std::exception
#include "bin_tree.h" // Asume que bin_tree.h incluye node_bin_tree.h

// Helper function to print elements of a list
template <class T>
void printList(const std::list<T>& l, const std::string& title) {
    std::cout << title << ": [";
    typename std::list<T>::const_iterator it = l.begin();
    while (it != l.end()) {
        std::cout << *it;
        ++it;
        if (it != l.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {
    // --- Test Basic Operations and BST ---
    std::cout << "--- Testing Basic Operations and BST ---" << std::endl;
    BinTree<int> bst;
    std::cout << "Initial empty tree:" << std::endl;
    std::cout << "isEmpty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl; // Expected: Yes
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 0

    // Test insertBST
    std::cout << "\nInserting BST elements: 50, 30, 70, 20, 40, 60, 80" << std::endl;
    bst.insertBST(50);
    bst.insertBST(30);
    bst.insertBST(70);
    bst.insertBST(20);
    bst.insertBST(40);
    bst.insertBST(60);
    bst.insertBST(80);

    std::cout << "\nAfter insertions:" << std::endl;
    std::cout << "isEmpty? " << (bst.isEmpty() ? "Yes" : "No") << std::endl; // Expected: No
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 7
    try {
        std::cout << "Root Info: " << bst.getRootInfo() << std::endl; // Expected: 50
    } catch (const std::exception& e) {
        std::cerr << "Error getting root info: " << e.what() << std::endl;
    }

    // Test Traversals on BST
    std::cout << "\nTesting Traversals on BST:" << std::endl;
    printList(bst.preOrder(),   "PreOrder  "); // Expected: [50, 30, 20, 40, 70, 60, 80]
    printList(bst.inOrder(),    "InOrder   "); // Expected: [20, 30, 40, 50, 60, 70, 80] (Sorted)
    printList(bst.postOrder(),  "PostOrder "); // Expected: [20, 40, 30, 60, 80, 70, 50]
    printList(bst.levelOrder(), "LevelOrder"); // Expected: [50, 30, 70, 20, 40, 60, 80]

    // Test Properties
    std::cout << "\nTesting Properties on BST:" << std::endl;
    std::cout << "Height: " << bst.getHeight() << std::endl; // Expected: 2 (Root level 0)
    printList(bst.getLeaves(), "Leaves    "); // Expected: [20, 40, 60, 80] (Order depends on GET_LEAVES implementation)

    // Test getLevel
    std::cout << "Nodes at Level 0: "; printList(bst.getLevel(0), ""); // Expected: [50]
    std::cout << "Nodes at Level 1: "; printList(bst.getLevel(1), ""); // Expected: [30, 70]
    std::cout << "Nodes at Level 2: "; printList(bst.getLevel(2), ""); // Expected: [20, 40, 60, 80]
    std::cout << "Nodes at Level 3: "; printList(bst.getLevel(3), ""); // Expected: []

    // Test BST Search
    std::cout << "\nTesting BST Search:" << std::endl;
    std::cout << "Search 40: " << (bst.searchBST(40) ? "Found" : "Not Found") << std::endl; // Expected: Found
    std::cout << "Search 90: " << (bst.searchBST(90) ? "Found" : "Not Found") << std::endl; // Expected: Not Found

    // Test BST Remove
    std::cout << "\nTesting BST Remove:" << std::endl;
    std::cout << "Removing 20 (leaf): " << (bst.removeBST(20) ? "Success" : "Failed") << std::endl;
    printList(bst.inOrder(), "InOrder after removing 20 "); // Expected: [30, 40, 50, 60, 70, 80]
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 6

    std::cout << "Removing 70 (two children): " << (bst.removeBST(70) ? "Success" : "Failed") << std::endl;
    printList(bst.inOrder(), "InOrder after removing 70 "); // Expected: [30, 40, 50, 60, 80] (70 replaced by 80)
    printList(bst.levelOrder(), "LevelOrder after removing 70"); // Structure changes
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 5

    std::cout << "Removing 30 (one child): " << (bst.removeBST(30) ? "Success" : "Failed") << std::endl;
    printList(bst.inOrder(), "InOrder after removing 30 "); // Expected: [40, 50, 60, 80]
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 4

    std::cout << "Removing 50 (root, two children): " << (bst.removeBST(50) ? "Success" : "Failed") << std::endl;
    printList(bst.inOrder(), "InOrder after removing 50 "); // Expected: [40, 60, 80]
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 3
    try {
        std::cout << "New Root Info: " << bst.getRootInfo() << std::endl; // Expected: 60 (successor of 50)
    } catch (const std::exception& e) {
        std::cerr << "Error getting root info: " << e.what() << std::endl;
    }

    std::cout << "Removing 99 (not present): " << (bst.removeBST(99) ? "Success" : "Failed") << std::endl; // Expected: Failed
    std::cout << "Weight: " << bst.getWeight() << std::endl; // Expected: 3

    // --- Test Copying and Assignment ---
    std::cout << "\n--- Testing Copying and Assignment ---" << std::endl;
    BinTree<int> bstCopy(bst); // Copy constructor
    BinTree<int> bstAssign;
    bstAssign = bst;        // Assignment operator

    std::cout << "Original Weight: " << bst.getWeight() << std::endl;
    std::cout << "Copy Weight: " << bstCopy.getWeight() << std::endl;
    std::cout << "Assign Weight: " << bstAssign.getWeight() << std::endl;

    std::cout << "Modifying original BST by inserting 70..." << std::endl;
    bst.insertBST(70);
    std::cout << "Original Weight after insert: " << bst.getWeight() << std::endl; // Expected: 4
    std::cout << "Copy Weight (should be unchanged): " << bstCopy.getWeight() << std::endl; // Expected: 3
    std::cout << "Assign Weight (should be unchanged): " << bstAssign.getWeight() << std::endl; // Expected: 3
    printList(bst.inOrder(), "Original InOrder ");
    printList(bstCopy.inOrder(), "Copy InOrder     ");
    printList(bstAssign.inOrder(), "Assign InOrder   ");

    // --- Test Reconstruction ---
    std::cout << "\n--- Testing Reconstruction ---" << std::endl;
    BinTree<char> treePreIn;
    std::list<char> pre;
    pre.push_back('A'); pre.push_back('B'); pre.push_back('D'); pre.push_back('E');
    pre.push_back('C'); pre.push_back('F');
    std::list<char> in;
    in.push_back('D'); in.push_back('B'); in.push_back('E'); in.push_back('A');
    in.push_back('F'); in.push_back('C');

    std::cout << "Building tree from Pre/In..." << std::endl;
    printList(pre, "PreOrder List ");
    printList(in,  "InOrder List  ");
    treePreIn.buildFromPreIn(pre, in);
    std::cout << "Weight after build: " << treePreIn.getWeight() << std::endl; // Expected: 6
    printList(treePreIn.preOrder(),   "Result PreOrder  ");
    printList(treePreIn.inOrder(),    "Result InOrder   ");
    printList(treePreIn.postOrder(),  "Result PostOrder "); // Expected: [D, E, B, F, C, A]
    printList(treePreIn.levelOrder(), "Result LevelOrder"); // Expected: [A, B, C, D, E, F]
    std::cout << "Height: " << treePreIn.getHeight() << std::endl; // Expected: 2

    BinTree<char> treePostIn;
    std::list<char> post;
    post.push_back('D'); post.push_back('E'); post.push_back('B'); post.push_back('F');
    post.push_back('C'); post.push_back('A');
    // Use the same 'in' list

    std::cout << "\nBuilding tree from Post/In..." << std::endl;
    printList(post, "PostOrder List");
    printList(in,   "InOrder List  "); // Same as before
    treePostIn.buildFromPostIn(post, in);
    std::cout << "Weight after build: " << treePostIn.getWeight() << std::endl; // Expected: 6
    printList(treePostIn.preOrder(),   "Result PreOrder  "); // Expected: [A, B, D, E, C, F]
    printList(treePostIn.inOrder(),    "Result InOrder   "); // Expected: [D, B, E, A, F, C]
    printList(treePostIn.postOrder(),  "Result PostOrder "); // Expected: [D, E, B, F, C, A]
    printList(treePostIn.levelOrder(), "Result LevelOrder"); // Expected: [A, B, C, D, E, F]

    // --- Test Path, LCA, Diameter ---
    // Use the tree built from Pre/In (treePreIn)
    std::cout << "\n--- Testing Path, LCA, Diameter (on treePreIn) ---" << std::endl;
    printList(treePreIn.findPathToNode('E'), "Path to E "); // Expected: [A, B, E]
    printList(treePreIn.findPathToNode('F'), "Path to F "); // Expected: [A, C, F]
    printList(treePreIn.findPathToNode('G'), "Path to G "); // Expected: [] (Not found)

    printList(treePreIn.findPathBetweenNodes('D', 'F'), "Path D <-> F"); // Expected: [D, B, A, C, F]
    printList(treePreIn.findPathBetweenNodes('E', 'F'), "Path E <-> F"); // Expected: [E, B, A, C, F]
    printList(treePreIn.findPathBetweenNodes('B', 'D'), "Path B <-> D"); // Expected: [B, D]

    try {
        std::cout << "LCA(D, F): " << treePreIn.lowestCommonAncestor('D', 'F') << std::endl; // Expected: A
        std::cout << "LCA(E, D): " << treePreIn.lowestCommonAncestor('E', 'D') << std::endl; // Expected: B
        std::cout << "LCA(A, F): " << treePreIn.lowestCommonAncestor('A', 'F') << std::endl; // Expected: A
        // std::cout << "LCA(D, G): " << treePreIn.lowestCommonAncestor('D', 'G') << std::endl; // Expected: throws exception
    } catch(const std::exception& e) {
         std::cerr << "LCA Error: " << e.what() << std::endl;
    }

    printList(treePreIn.getDiameterPath(), "Diameter Path "); // Expected: [D, B, A, C, F] or [E, B, A, C, F] (length 5)

    // --- Test Manual Construction and Subtrees ---
     std::cout << "\n--- Testing Manual Construction and Subtrees ---" << std::endl;
     BinTree<int> leftSub(20);
     BinTree<int> rightSub(30);
     BinTree<int> manualTree(10, leftSub, rightSub); // Root 10, left 20, right 30

     std::cout << "Manual Tree Weight: " << manualTree.getWeight() << std::endl; // Expected: 3
     printList(manualTree.inOrder(), "Manual Tree InOrder "); // Expected: [20, 10, 30]

     BinTree<int> gotLeft = manualTree.getLeftSubtree();
     std::cout << "Got Left Subtree Weight: " << gotLeft.getWeight() << std::endl; // Expected: 1
     try {
        std::cout << "Got Left Subtree Root: " << gotLeft.getRootInfo() << std::endl; // Expected: 20
     } catch (const std::exception& e) { std::cerr << e.what() << std::endl; }

     BinTree<int> gotRight = manualTree.getRightSubtree();
     std::cout << "Got Right Subtree Weight: " << gotRight.getWeight() << std::endl; // Expected: 1
      try {
        std::cout << "Got Right Subtree Root: " << gotRight.getRootInfo() << std::endl; // Expected: 30
     } catch (const std::exception& e) { std::cerr << e.what() << std::endl; }


    std::cout << "\n--- Testing Finished ---" << std::endl;

    return 0;
}
