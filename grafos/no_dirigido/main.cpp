#include "GraphND.h"      // Asegúrate que GraphND.h y los otros .h estén accesibles
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <utility>      // Para std::pair en la impresión de listas
#include <algorithm>    // Para std::sort (si se usa internamente o en pruebas)
#include <exception>    // Para std::exception

// --- Helper Function to Print Lists ---
template <typename T>
void printList(const std::list<T>& l, const std::string& label = "") {
    if (!label.empty()) {
        std::cout << label << ": ";
    }
    if (l.empty()) {
        std::cout << "[empty]" << std::endl;
        return;
    }
    typename std::list<T>::const_iterator it = l.begin();
    std::cout << "[ " << *it;
    ++it;
    for (; it != l.end(); ++it) {
        std::cout << ", " << *it;
    }
    std::cout << " ]" << std::endl;
}

// Helper para imprimir vector de distancias (Dijkstra)
void printDistances(const std::vector<float>& dist, const GraphND<int>& g) {
    std::cout << "Distances: ";
    if (dist.empty()) {
        std::cout << "[empty]" << std::endl;
        return;
    }
    std::cout << "[ ";
    const float INF = std::numeric_limits<float>::max();
    for (size_t i = 0; i < dist.size(); ++i) {
        try {
             std::cout << g.getVertexFromIndex(i) << ":";
             if (dist[i] == INF) {
                 std::cout << "INF";
             } else {
                 std::cout << dist[i];
             }
             if (i < dist.size() - 1) {
                 std::cout << ", ";
             }
        } catch (const std::out_of_range& e) {
             std::cout << "Invalid_Index(" << i << ")";
             if (i < dist.size() - 1) std::cout << ", ";
        }
    }
     std::cout << " ]" << std::endl;
}

// Helper para imprimir lista de ternas (getEdges)
void printEdges(const std::list< EdgeTriple<int> >& edges) {
     std::cout << "Edges: ";
     if (edges.empty()) {
         std::cout << "[empty]" << std::endl;
         return;
     }
     typename std::list< EdgeTriple<int> >::const_iterator it = edges.begin();
     std::cout << "[ ";
     while (it != edges.end()) {
         std::cout << "(" << it->getVertexA() << "<->" << it->getVertexB() << ", w:" << it->getWeight() << ")";
         ++it;
         if (it != edges.end()) std::cout << ", ";
     }
      std::cout << " ]" << std::endl;
}


int main() {
    std::cout << "--- GraphND Test Suite ---" << std::endl;

    // === 1. Basic Vertex Operations ===
    std::cout << "\n=== 1. Vertex Operations Test ===\n";
    GraphND<int> g1;
    std::cout << "Graph created. Is empty? " << (g1.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Initial order: " << g1.order() << ", Num Vertices: " << g1.getNumVertices() << std::endl;

    g1.addVertex(10);
    g1.addVertex(5);
    g1.addVertex(15);
    g1.addVertex(10); // Add duplicate
    g1.addVertex(20);

    std::cout << "Added 10, 5, 15, 10(dup), 20." << std::endl;
    std::cout << "Is empty? " << (g1.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Order: " << g1.order() << ", Num Vertices: " << g1.getNumVertices() << std::endl;
    printList(g1.getVertices(), "Vertices (should be sorted)");
    std::cout << "Internal map: ";
    for(size_t i=0; i<g1.mapGraph.size(); ++i) std::cout << g1.mapGraph[i] << " ";
    std::cout << std::endl;

    std::cout << "Index of vertex 15: " << g1.getVertexIndex(15) << std::endl;
    std::cout << "Index of vertex 99 (not present): " << g1.getVertexIndex(99) << std::endl;
    try {
        std::cout << "Vertex at index 0: " << g1.getVertexFromIndex(0) << std::endl;
        std::cout << "Vertex at index 3: " << g1.getVertexFromIndex(3) << std::endl;
       // std::cout << "Vertex at index 99 (invalid): " << g1.getVertexFromIndex(99) << std::endl; // Uncomment to test exception
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught expected exception: " << e.what() << std::endl;
    }

    std::cout << "Removing vertex 15..." << std::endl;
    g1.removeVertex(15);
    std::cout << "Order after removing 15: " << g1.order() << std::endl;
    printList(g1.getVertices(), "Vertices after removing 15");

     std::cout << "Removing vertex 5 (first)..." << std::endl;
    g1.removeVertex(5);
    std::cout << "Order after removing 5: " << g1.order() << std::endl;
    printList(g1.getVertices(), "Vertices after removing 5");

     std::cout << "Removing vertex 20 (last)..." << std::endl;
    g1.removeVertex(20);
    std::cout << "Order after removing 20: " << g1.order() << std::endl;
    printList(g1.getVertices(), "Vertices after removing 20");

    std::cout << "Clearing graph..." << std::endl;
    g1.clear();
    std::cout << "Is empty after clear? " << (g1.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Order after clear: " << g1.order() << std::endl;


    // === 2. Edge Operations ===
    std::cout << "\n=== 2. Edge Operations Test ===\n";
    GraphND<int> g2;
    g2.addVertex(1); g2.addVertex(2); g2.addVertex(3); g2.addVertex(4); g2.addVertex(5);
    std::cout << "Added vertices 1, 2, 3, 4, 5." << std::endl;
    std::cout << "Initial edge count: " << g2.getNumEdges() << std::endl;

    g2.addEdge(1, 2, 1.0f);
    g2.addEdge(1, 3, 1.5f);
    g2.addEdge(2, 3, 0.5f);
    g2.addEdge(3, 4, 2.0f);
    g2.addEdge(4, 4, 3.0f); // Self-loop
    g2.addEdge(1, 2, 9.9f); // Add duplicate edge (should be ignored)
    g2.addEdge(5, 1, 5.1f);
    // g2.addEdge(1, 99, 1.0f); // Add edge with non-existent vertex (should fail gracefully)

    std::cout << "Added edges (1,2, 1.0), (1,3, 1.5), (2,3, 0.5), (3,4, 2.0), (4,4, 3.0), (1,2, 9.9 - dup), (5,1, 5.1)." << std::endl;
    std::cout << "Edge count: " << g2.getNumEdges() << std::endl;

    std::cout << "Edge exists (1, 2)? " << (g2.edgeExists(1, 2) ? "Yes" : "No") << std::endl;
    std::cout << "Edge exists (2, 1)? " << (g2.edgeExists(2, 1) ? "Yes" : "No") << std::endl; // Should be yes due to symmetry
    std::cout << "Edge exists (1, 4)? " << (g2.edgeExists(1, 4) ? "Yes" : "No") << std::endl;
    std::cout << "Edge exists (4, 4)? " << (g2.edgeExists(4, 4) ? "Yes" : "No") << std::endl;

    std::cout << "Weight (1, 2): " << g2.getEdgeWeight(1, 2) << std::endl;
    std::cout << "Weight (2, 1): " << g2.getEdgeWeight(2, 1) << std::endl;
    std::cout << "Weight (1, 4): " << g2.getEdgeWeight(1, 4) << std::endl;
    std::cout << "Weight (4, 4): " << g2.getEdgeWeight(4, 4) << std::endl;

    printList(g2.getNeighbors(1), "Neighbors of 1");
    printList(g2.getNeighbors(3), "Neighbors of 3");
    printList(g2.getNeighbors(4), "Neighbors of 4");
    printList(g2.getNeighbors(5), "Neighbors of 5");

    std::cout << "Degree of 1: " << g2.vertexDegree(1) << std::endl;
    std::cout << "Degree of 3: " << g2.vertexDegree(3) << std::endl;
    std::cout << "Degree of 4: " << g2.vertexDegree(4) << std::endl; // Check if loop counted once or twice based on implementation
    std::cout << "Degree of 5: " << g2.vertexDegree(5) << std::endl;


    printEdges(g2.getEdges());

    std::cout << "Removing edge (1, 3)..." << std::endl;
    g2.removeEdge(1, 3);
    std::cout << "Edge count after removing (1,3): " << g2.getNumEdges() << std::endl;
    std::cout << "Edge exists (1, 3)? " << (g2.edgeExists(1, 3) ? "Yes" : "No") << std::endl;
    printList(g2.getNeighbors(1), "Neighbors of 1 after removing (1,3)");

    std::cout << "Removing edge (4, 4)..." << std::endl;
    g2.removeEdge(4, 4);
    std::cout << "Edge count after removing (4,4): " << g2.getNumEdges() << std::endl;
    std::cout << "Edge exists (4, 4)? " << (g2.edgeExists(4, 4) ? "Yes" : "No") << std::endl;
    printList(g2.getNeighbors(4), "Neighbors of 4 after removing (4,4)");

    std::cout << "Removing vertex 2 (should remove edges (1,2) and (2,3))..." << std::endl;
    g2.removeVertex(2);
    std::cout << "Edge count after removing vertex 2: " << g2.getNumEdges() << std::endl;
    std::cout << "Order after removing vertex 2: " << g2.order() << std::endl;
    printList(g2.getVertices(), "Vertices after removing 2");
    printList(g2.getNeighbors(1), "Neighbors of 1 after removing 2");
    printList(g2.getNeighbors(3), "Neighbors of 3 after removing 2");
    printEdges(g2.getEdges());


    // === 3. Graph Properties ===
     std::cout << "\n=== 3. Graph Properties Test ===\n";
     GraphND<int> g3; // Disconnected graph
     g3.addVertex(1); g3.addVertex(2); g3.addVertex(3); g3.addVertex(4);
     g3.addEdge(1, 2, 1.0);
     g3.addEdge(3, 4, 1.0);
     std::cout << "Graph g3 (1-2, 3-4):" << std::endl;
     printEdges(g3.getEdges());
     std::cout << "Is g3 connected? " << (g3.isConnected() ? "Yes" : "No") << std::endl; // Should be No
     std::cout << "Is g3 complete? " << (g3.isComplete() ? "Yes" : "No") << std::endl;  // Should be No

     GraphND<int> g4; // Complete graph K3
     g4.addVertex(1); g4.addVertex(2); g4.addVertex(3);
     g4.addEdge(1, 2, 1.0);
     g4.addEdge(1, 3, 1.0);
     g4.addEdge(2, 3, 1.0);
     std::cout << "\nGraph g4 (K3):" << std::endl;
     printEdges(g4.getEdges());
     std::cout << "Is g4 connected? " << (g4.isConnected() ? "Yes" : "No") << std::endl; // Should be Yes
     std::cout << "Is g4 complete? " << (g4.isComplete() ? "Yes" : "No") << std::endl;  // Should be Yes


    // === 4. Traversals ===
    std::cout << "\n=== 4. Traversals Test ===\n";
    GraphND<int> g5;
    g5.addVertex(0); g5.addVertex(1); g5.addVertex(2); g5.addVertex(3); g5.addVertex(4);
    g5.addEdge(0, 1, 1); g5.addEdge(0, 2, 1);
    g5.addEdge(1, 3, 1); g5.addEdge(1, 4, 1);
    g5.addEdge(2, 4, 1);
    std::cout << "Graph g5 for traversals:" << std::endl;
    printEdges(g5.getEdges());

    printList(g5.bfs(0), "BFS starting from 0");
    printList(g5.bfs(3), "BFS starting from 3");
    printList(g5.dfs(0), "DFS starting from 0");
    printList(g5.dfs(3), "DFS starting from 3");

    // === 5. Dijkstra ===
    std::cout << "\n=== 5. Dijkstra Test ===\n";
    GraphND<int> g6;
    g6.addVertex(0); g6.addVertex(1); g6.addVertex(2); g6.addVertex(3); g6.addVertex(4); g6.addVertex(5);
    g6.addEdge(0, 1, 7); g6.addEdge(0, 2, 9); g6.addEdge(0, 5, 14);
    g6.addEdge(1, 2, 10); g6.addEdge(1, 3, 15);
    g6.addEdge(2, 3, 11); g6.addEdge(2, 5, 2);
    g6.addEdge(3, 4, 6);
    g6.addEdge(4, 5, 9);
    std::cout << "Graph g6 for Dijkstra:" << std::endl;
    printEdges(g6.getEdges());
    std::vector<float> distances = g6.dijkstra(0);
    printDistances(distances, g6);

    // === 6. Path Finding ===
    std::cout << "\n=== 6. Path Finding Test ===\n";
    // Using g5 graph from traversals
     std::cout << "Using Graph g5:" << std::endl;
    printEdges(g5.getEdges());
    printList(g5.shortestPathLength(0, 4), "Shortest Path Length (0 to 4)");
    printList(g5.shortestPathLength(0, 3), "Shortest Path Length (0 to 3)");
    printList(g5.longestPathLength(0, 4), "Longest Path Length (0 to 4)");
    printList(g5.longestPathLength(0, 3), "Longest Path Length (0 to 3)");


    // === 7. Hamiltonian Paths ===
    std::cout << "\n=== 7. Hamiltonian Path Test ===\n";
    GraphND<int> g7; // Path graph 0-1-2-3
    g7.addVertex(0); g7.addVertex(1); g7.addVertex(2); g7.addVertex(3);
    g7.addEdge(0, 1, 1); g7.addEdge(1, 2, 5); g7.addEdge(2, 3, 1);
     std::cout << "Graph g7 (0-1-2-3):" << std::endl;
    printEdges(g7.getEdges());
    printList(g7.findHamiltonianPath(0), "Hamiltonian Path from 0 in g7"); // Should find 0-1-2-3
    printList(g7.findMinCostHamiltonianPath(0), "Min Cost Hamiltonian Path from 0 in g7"); // Should be 0-1-2-3, cost 7

    GraphND<int> g8; // Complete K4
    g8.addVertex(0); g8.addVertex(1); g8.addVertex(2); g8.addVertex(3);
    g8.addEdge(0, 1, 10); g8.addEdge(0, 2, 1); g8.addEdge(0, 3, 5);
    g8.addEdge(1, 2, 2); g8.addEdge(1, 3, 7);
    g8.addEdge(2, 3, 3);
    std::cout << "\nGraph g8 (K4):" << std::endl;
    printEdges(g8.getEdges());
    printList(g8.findHamiltonianPath(0), "Hamiltonian Path from 0 in g8"); // Many possible
    printList(g8.findMinCostHamiltonianPath(0), "Min Cost Hamiltonian Path from 0 in g8"); // Example: 0-2-1-3 cost 1+2+7=10 or 0-2-3-1 cost 1+3+7=11 or 0-3-2-1 cost 5+3+2=10, etc.


    // === 8. Copy / Assignment / Equality ===
    std::cout << "\n=== 8. Copy/Assignment/Equality Test ===\n";
    GraphND<int> g_orig;
    g_orig.addVertex(100); g_orig.addVertex(200); g_orig.addEdge(100, 200, 55.5f);
    std::cout << "Original Graph:" << std::endl;
    printEdges(g_orig.getEdges());

    GraphND<int> g_copy = g_orig; // Copy constructor
    std::cout << "Copied Graph (constructor):" << std::endl;
    printEdges(g_copy.getEdges());

    GraphND<int> g_assign;
    g_assign.addVertex(999); // Add something to be overwritten
    g_assign = g_orig; // Assignment operator
    std::cout << "Assigned Graph:" << std::endl;
    printEdges(g_assign.getEdges());

    std::cout << "Modifying original: add vertex 300, edge (100, 300)" << std::endl;
    g_orig.addVertex(300);
    g_orig.addEdge(100, 300, 1.0f);

    std::cout << "Original Graph after modification:" << std::endl;
    printEdges(g_orig.getEdges());
    std::cout << "Copied Graph (should be unchanged):" << std::endl;
    printEdges(g_copy.getEdges());
    std::cout << "Assigned Graph (should be unchanged):" << std::endl;
    printEdges(g_assign.getEdges());

    std::cout << "Is original equal to copy? " << (g_orig.isEqualTo(g_copy) ? "Yes" : "No") << std::endl; // No
    std::cout << "Is copy equal to assigned? " << (g_copy.isEqualTo(g_assign) ? "Yes" : "No") << std::endl; // Yes

    // === 9. Load From Triples ===
    std::cout << "\n=== 9. Load From Triples Test ===\n";
    std::list< EdgeTriple<int> > triples;
    triples.push_back(EdgeTriple<int>(10, 20, 1.1f));
    triples.push_back(EdgeTriple<int>(20, 30, 2.2f));
    triples.push_back(EdgeTriple<int>(10, 30, 3.3f));

    GraphND<int> g_load;
    g_load.loadFromTriples(triples);
    std::cout << "Graph loaded from triples:" << std::endl;
     printList(g_load.getVertices(), "Loaded Vertices");
    printEdges(g_load.getEdges());
     std::cout << "Loaded Order: " << g_load.order() << ", Edges: " << g_load.getNumEdges() << std::endl;


    std::cout << "\n--- Test Suite Complete ---" << std::endl;
    return 0;
}