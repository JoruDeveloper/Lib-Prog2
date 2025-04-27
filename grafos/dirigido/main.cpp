#include <iostream>
#include <string> // Example if using strings, though using int for simplicity now
#include <list>
#include <vector>
#include <limits> // For numeric_limits if needed

#include "GraphD.h" // Includes VertexNode.h and ArcNode.h implicitly

// --- Helper Functions for Printing ---

// Helper to print elements of a list
template <typename T>
void printList(const std::list<T>& lst, const std::string& label) {
    std::cout << label << "[";
    bool first = true;
    for (typename std::list<T>::const_iterator it = lst.begin(); it != lst.end(); ++it) {
        if (!first) {
            std::cout << ", ";
        }
        std::cout << *it;
        first = false;
    }
    std::cout << "]" << std::endl;
}

// Helper to print elements of a vector
template <typename T>
void printVector(const std::vector<T>& vec, const std::string& label) {
    std::cout << label << "[";
    bool first = true;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (!first) {
            std::cout << ", ";
        }
        // Handle potential infinity representation (-1) for float distances
        if (vec[i] == -1.0f) {
             std::cout << "inf";
        } else {
             std::cout << vec[i];
        }
        first = false;
    }
    std::cout << "]" << std::endl;
}

// Helper to print ArcInfo list
template <typename elem>
void printArcInfoList(const std::list< ArcInfo<elem> >& arcs, const std::string& label) {
    std::cout << label << std::endl;
    if (arcs.empty()) {
        std::cout << "  (No arcs)" << std::endl;
        return;
    }
    for (typename std::list< ArcInfo<elem> >::const_iterator it = arcs.begin(); it != arcs.end(); ++it) {
        std::cout << "  " << it->source << " -> " << it->destination << " (Weight: " << it->weight << ")" << std::endl;
    }
}


int main() {
    std::cout << "--- GraphD Test Program ---" << std::endl;

    // === Test Basic Construction and Empty State ===
    std::cout << "\n=== Testing Construction & Empty State ===" << std::endl;
    GraphD<int> g1;
    std::cout << "g1 created (Default Constructor)." << std::endl;
    std::cout << "g1.isEmpty(): " << (g1.isEmpty() ? "true" : "false") << " (Expected: true)" << std::endl;
    std::cout << "g1.order() (Vertices): " << g1.order() << " (Expected: 0)" << std::endl;
    std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 0)" << std::endl;
    try {
        // Trying to get first vertex on empty graph might be problematic depending on elem type
        // int first = g1.getFirstVertexValue(); // This might fail or return default(int)=0
        // std::cout << "g1.getFirstVertexValue(): " << first << " (Behavior depends on implementation)" << std::endl;
         std::cout << "g1.getFirstVertexValue(): (Skipping on empty graph)" << std::endl;
    } catch (...) { // Catch potential issues
        std::cout << "g1.getFirstVertexValue(): Exception caught (as expected for empty graph)" << std::endl;
    }

    // === Test Vertex Operations ===
    std::cout << "\n=== Testing Vertex Operations ===" << std::endl;
    g1.addVertex(10);
    g1.addVertex(30);
    g1.addVertex(20); // Test sorted insertion
    g1.addVertex(40);
    g1.addVertex(10); // Test duplicate add (should do nothing)
    std::cout << "Added vertices 10, 30, 20, 40, 10 (duplicate)." << std::endl;
    std::cout << "g1.isEmpty(): " << (g1.isEmpty() ? "true" : "false") << " (Expected: false)" << std::endl;
    std::cout << "g1.order() (Vertices): " << g1.order() << " (Expected: 4)" << std::endl;
    printList(g1.getVertices(), "g1.getVertices(): ");
    printVector(g1.getMap(), "g1.getMap(): ");
    std::cout << "g1.getMapIndex(30): " << g1.getMapIndex(30) << " (Expected: index of 30)" << std::endl;
    std::cout << "g1.getMapIndex(99): " << g1.getMapIndex(99) << " (Expected: -1)" << std::endl;
    int index_of_20 = g1.getMapIndex(20);
    if (index_of_20 != -1) {
        std::cout << "g1.getMapVertex(" << index_of_20 << "): " << g1.getMapVertex(index_of_20) << " (Expected: 20)" << std::endl;
    }
     std::cout << "g1.getMapVertex(99): " << g1.getMapVertex(99) << " (Expected: default(int)=0 or error)" << std::endl;
     std::cout << "g1.getFirstVertexValue(): " << g1.getFirstVertexValue() << " (Expected: 10)" << std::endl;


    // === Test Arc Operations ===
    std::cout << "\n=== Testing Arc Operations ===" << std::endl;
    g1.addArc(10, 20, 1.5f);
    g1.addArc(10, 30, 2.0f);
    g1.addArc(20, 40, 3.0f);
    g1.addArc(30, 40, 1.0f);
    g1.addArc(40, 10, 4.0f); // Cycle
    g1.addArc(30, 10, 0.5f);
    g1.addArc(10, 20, 9.9f); // Test duplicate arc add (should do nothing)
    g1.addArc(10, 99, 1.0f); // Test arc with non-existent dest vertex (should do nothing)
    g1.addArc(99, 20, 1.0f); // Test arc with non-existent source vertex (should do nothing)
    std::cout << "Added arcs: 10->20(1.5), 10->30(2.0), 20->40(3.0), 30->40(1.0), 40->10(4.0), 30->10(0.5)." << std::endl;
    std::cout << "Tried adding duplicates/invalid arcs." << std::endl;
    std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 6)" << std::endl;

    std::cout << "g1.arcExists(10, 20): " << (g1.arcExists(10, 20) ? "true" : "false") << " (Expected: true)" << std::endl;
    std::cout << "g1.arcExists(20, 10): " << (g1.arcExists(20, 10) ? "true" : "false") << " (Expected: false)" << std::endl;
    std::cout << "g1.arcExists(10, 99): " << (g1.arcExists(10, 99) ? "true" : "false") << " (Expected: false)" << std::endl;

    std::cout << "g1.getArcWeight(10, 20): " << g1.getArcWeight(10, 20) << " (Expected: 1.5)" << std::endl;
    std::cout << "g1.getArcWeight(30, 40): " << g1.getArcWeight(30, 40) << " (Expected: 1.0)" << std::endl;
    std::cout << "g1.getArcWeight(20, 10): " << g1.getArcWeight(20, 10) << " (Expected: -1.0)" << std::endl;

    printList(g1.getSuccessors(10), "g1.getSuccessors(10): "); // Order depends on addArc implementation (adds to head)
    printList(g1.getSuccessors(40), "g1.getSuccessors(40): ");
    printList(g1.getSuccessors(50), "g1.getSuccessors(50): "); // Non-existent vertex

    printList(g1.getPredecessors(10), "g1.getPredecessors(10): ");
    printList(g1.getPredecessors(40), "g1.getPredecessors(40): ");
    printList(g1.getPredecessors(50), "g1.getPredecessors(50): ");

    std::cout << "g1.inDegree(10): " << g1.inDegree(10) << " (Expected: 2)" << std::endl;
    std::cout << "g1.outDegree(10): " << g1.outDegree(10) << " (Expected: 2)" << std::endl;
    std::cout << "g1.inDegree(40): " << g1.inDegree(40) << " (Expected: 2)" << std::endl;
    std::cout << "g1.outDegree(40): " << g1.outDegree(40) << " (Expected: 1)" << std::endl;

    printArcInfoList(g1.getArcs(), "g1.getArcs():");

    // === Test Graph Algorithms ===
    std::cout << "\n=== Testing Graph Algorithms ===" << std::endl;
    printList(g1.bfs(10), "g1.bfs(10): ");
    printList(g1.bfs(30), "g1.bfs(30): ");
     printList(g1.bfs(99), "g1.bfs(99) (invalid start): "); // Test invalid start

    printList(g1.dfs(10), "g1.dfs(10): ");
    printList(g1.dfs(30), "g1.dfs(30): ");
     printList(g1.dfs(99), "g1.dfs(99) (invalid start): ");

    printVector(g1.dijkstra(10), "g1.dijkstra(10) distances: ");
    printVector(g1.dijkstra(30), "g1.dijkstra(30) distances: ");

    printList(g1.shortestPathByWeight(10, 40), "g1.shortestPathByWeight(10, 40): "); // Should be 10->30->40 (cost 3.0)
    printList(g1.shortestPathByWeight(10, 10), "g1.shortestPathByWeight(10, 10): "); // Path to self
    printList(g1.shortestPathByWeight(40, 30), "g1.shortestPathByWeight(40, 30): "); // Cycle might affect this, 40->10->30 (cost 6.0)
    printList(g1.shortestPathByWeight(10, 99), "g1.shortestPathByWeight(10, 99) (unreachable): "); // Unreachable

    printList(g1.longestPathByWeight(10, 40), "g1.longestPathByWeight(10, 40): "); // WARNING: Only reliable for DAGs. Cycle 40->10 exists. Result might be unexpected.
    printList(g1.longestPathByWeight(10, 10), "g1.longestPathByWeight(10, 10): ");

    printList(g1.shortestPathByEdges(10, 40), "g1.shortestPathByEdges(10, 40): "); // 10->20->40 or 10->30->40 (length 3)
    printList(g1.shortestPathByEdges(40, 30), "g1.shortestPathByEdges(40, 30): "); // 40->10->30 (length 3)

    printList(g1.longestPathByEdges(10, 40), "g1.longestPathByEdges(10, 40): "); // e.g., 10->30->10->20->40 is not simple. 10->30->40 (len 3) or 10->20->40 (len 3) or potentially others if cycles allowed in definition? Backtracking avoids cycles in path.
    printList(g1.longestPathByEdges(40, 40), "g1.longestPathByEdges(40, 40): "); // Path to self

    // === Test Graph Properties ===
    std::cout << "\n=== Testing Graph Properties ===" << std::endl;
    std::cout << "g1.isComplete(): " << (g1.isComplete() ? "true" : "false") << " (Expected: false)" << std::endl;
    // Test completeness on a small graph
    GraphD<int> g_comp;
    g_comp.addVertex(1); g_comp.addVertex(2); g_comp.addVertex(3);
    g_comp.addArc(1, 2, 1); g_comp.addArc(1, 3, 1);
    g_comp.addArc(2, 1, 1); g_comp.addArc(2, 3, 1);
    g_comp.addArc(3, 1, 1); g_comp.addArc(3, 2, 1);
    std::cout << "g_comp.isComplete() (3 nodes, 6 arcs): " << (g_comp.isComplete() ? "true" : "false") << " (Expected: true)" << std::endl;

    std::cout << "g1.isStronglyConnectedDfs(): " << (g1.isStronglyConnectedDfs() ? "true" : "false") << " (Expected: true - 10,20,30,40 form cycle)" << std::endl;
    std::cout << "g1.isStronglyConnectedKosaraju(): " << (g1.isStronglyConnectedKosaraju() ? "true" : "false") << " (Expected: true - WARNING: Flawed Implementation Test)" << std::endl;

    // Create a non-strongly connected graph
    GraphD<int> g_nsc;
    g_nsc.addVertex(1); g_nsc.addVertex(2); g_nsc.addVertex(3);
    g_nsc.addArc(1, 2, 1); g_nsc.addArc(2, 3, 1);
    std::cout << "g_nsc.isStronglyConnectedDfs(): " << (g_nsc.isStronglyConnectedDfs() ? "true" : "false") << " (Expected: false)" << std::endl;
    std::cout << "g_nsc.isStronglyConnectedKosaraju(): " << (g_nsc.isStronglyConnectedKosaraju() ? "true" : "false") << " (Expected: false - WARNING: Flawed Implementation Test)" << std::endl;


    // === Test Hamiltonian Paths ===
    std::cout << "\n=== Testing Hamiltonian Paths ===" << std::endl;
    // g1 (10,20,30,40 cycle) has Hamiltonian paths/cycles. e.g., 10->20->40->10(cycle), path 10->30->40 not Hamiltonian. Path 30->10->20->40 IS Hamiltonian.
    printList(g1.findHamiltonianPath(30), "g1.findHamiltonianPath(30): "); // Should find 30->10->20->40 or similar
    printList(g1.findHamiltonianPath(), "g1.findHamiltonianPath() (any start): "); // Should find one

    // Test on a graph with no Hamiltonian path
    GraphD<int> g_noham;
    g_noham.addVertex(1); g_noham.addVertex(2); g_noham.addVertex(3); g_noham.addVertex(4);
    g_noham.addArc(1, 2, 1); g_noham.addArc(1, 3, 1); g_noham.addArc(4, 1, 1);
    printList(g_noham.findHamiltonianPath(), "g_noham.findHamiltonianPath(): "); // Expected empty list

    // Test costed Hamiltonian paths (using g1)
    printList(g1.findMinCostHamiltonianPath(30), "g1.findMinCostHamiltonianPath(30): "); // e.g., 30->10(0.5)->20(1.5)->40(3.0) = Cost 5.0
    printList(g1.findMaxCostHamiltonianPath(10), "g1.findMaxCostHamiltonianPath(10): "); // e.g., 10->30(2.0)->40(1.0)->10(cycle) -> path 10->30->40 fails. Path 10->20->40->10(cycle)-> path 10->20->40 is not ham. Path 10->30->10 fails. Path 20->40->10->30 Cost 3+4+2=9. Let's trace 10 start: 10->30->.. fails. 10->20->40... fails. Maybe no Ham path starts at 10? Find any max cost path: 20->40->10->30 cost 9.0? Let's check 30->10->20->40 cost 0.5+1.5+3=5.0. Let's check 40->10->20->.. fails. 40->10->30->.. fails. Max cost path might be 20->40->10->30.

    printList(g1.findMinCostHamiltonianPath(), "g1.findMinCostHamiltonianPath() (any start): "); // Should be cost 5.0 path
    printList(g1.findMaxCostHamiltonianPath(), "g1.findMaxCostHamiltonianPath() (any start): "); // Should be cost 9.0 path


    // === Test Utilities ===
    std::cout << "\n=== Testing Utilities ===" << std::endl;
    // Copy Constructor Test
    GraphD<int> g_copy(g1);
    std::cout << "Created g_copy using copy constructor." << std::endl;
    std::cout << "g1.isEqualTo(g_copy): " << (g1.isEqualTo(g_copy) ? "true" : "false") << " (Expected: true)" << std::endl;
    g_copy.addVertex(50);
    std::cout << "Added vertex 50 to g_copy." << std::endl;
    std::cout << "g1.isEqualTo(g_copy): " << (g1.isEqualTo(g_copy) ? "true" : "false") << " (Expected: false)" << std::endl;

    // Assignment Operator Test
    GraphD<int> g_assign;
    g_assign.addVertex(999);
    g_assign = g1;
    std::cout << "Assigned g1 to g_assign." << std::endl;
     std::cout << "g_assign.order(): " << g_assign.order() << " (Expected: 4)" << std::endl;
    std::cout << "g1.isEqualTo(g_assign): " << (g1.isEqualTo(g_assign) ? "true" : "false") << " (Expected: true)" << std::endl;

    // Transpose Test
    GraphD<int> g_transposed;
    g1.transpose(g_transposed);
    std::cout << "Created g_transposed by transposing g1." << std::endl;
    printList(g_transposed.getVertices(), "g_transposed.getVertices(): ");
    printArcInfoList(g_transposed.getArcs(), "g_transposed.getArcs(): ");

    // Load From Arcs Test
    std::list< ArcInfo<int> > arc_list;
    arc_list.push_back(ArcInfo<int>(1, 2, 10.0f));
    arc_list.push_back(ArcInfo<int>(2, 3, 20.0f));
    arc_list.push_back(ArcInfo<int>(1, 3, 35.0f)); // Note: duplicate vertex adds handled
    GraphD<int> g_loaded;
    g_loaded.loadFromArcs(arc_list);
    std::cout << "Created g_loaded using loadFromArcs." << std::endl;
    printList(g_loaded.getVertices(), "g_loaded.getVertices(): ");
    printArcInfoList(g_loaded.getArcs(), "g_loaded.getArcs(): ");

    // === Test Removal ===
    std::cout << "\n=== Testing Removal ===" << std::endl;
    std::cout << "Current g1 size: " << g1.size() << std::endl;
    std::cout << "g1.arcExists(10, 30): " << (g1.arcExists(10, 30) ? "true" : "false") << std::endl;
    g1.removeArc(10, 30);
    std::cout << "Removed arc 10 -> 30." << std::endl;
    std::cout << "g1.arcExists(10, 30): " << (g1.arcExists(10, 30) ? "true" : "false") << " (Expected: false)" << std::endl;
    std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 5)" << std::endl;
    g1.removeArc(55, 66); // Remove non-existent arc
     std::cout << "Tried removing non-existent arc 55 -> 66." << std::endl;
     std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 5)" << std::endl;

    std::cout << "Current g1 order: " << g1.order() << std::endl;
    std::cout << "g1 contains vertex 20." << std::endl;
    std::cout << "g1.arcExists(10, 20): " << (g1.arcExists(10, 20) ? "true" : "false") << std::endl; // Outgoing from 10
    std::cout << "g1.arcExists(20, 40): " << (g1.arcExists(20, 40) ? "true" : "false") << std::endl; // Outgoing from 20
    // Need to check incoming to 20. No direct way other than getPredecessors or getArcs. Arc 10->20 exists.

    g1.removeVertex(20);
    std::cout << "Removed vertex 20." << std::endl;
    std::cout << "g1.order() (Vertices): " << g1.order() << " (Expected: 3)" << std::endl;
    std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 3 - Arcs 10->20 and 20->40 removed)" << std::endl;
    printList(g1.getVertices(), "g1.getVertices() after removing 20: ");
    printArcInfoList(g1.getArcs(), "g1.getArcs() after removing 20:");
    std::cout << "g1.arcExists(10, 20): " << (g1.arcExists(10, 20) ? "true" : "false") << " (Expected: false)" << std::endl;
    std::cout << "g1.arcExists(20, 40): " << (g1.arcExists(20, 40) ? "true" : "false") << " (Expected: false)" << std::endl; // Vertex 20 doesn't exist
     std::cout << "g1.getMapIndex(20): " << g1.getMapIndex(20) << " (Expected: -1)" << std::endl;

    g1.removeVertex(99); // Remove non-existent vertex
    std::cout << "Tried removing non-existent vertex 99." << std::endl;
    std::cout << "g1.order() (Vertices): " << g1.order() << " (Expected: 3)" << std::endl;


    // === Test Clear ===
    std::cout << "\n=== Testing Clear ===" << std::endl;
    g1.clear();
    std::cout << "Called g1.clear()." << std::endl;
    std::cout << "g1.isEmpty(): " << (g1.isEmpty() ? "true" : "false") << " (Expected: true)" << std::endl;
    std::cout << "g1.order() (Vertices): " << g1.order() << " (Expected: 0)" << std::endl;
    std::cout << "g1.size() (Arcs): " << g1.size() << " (Expected: 0)" << std::endl;
    printList(g1.getVertices(), "g1.getVertices() after clear: ");
    printArcInfoList(g1.getArcs(), "g1.getArcs() after clear:");


    std::cout << "\n--- Testing Complete ---" << std::endl;

    // Destructors called automatically when main ends
    return 0;
}