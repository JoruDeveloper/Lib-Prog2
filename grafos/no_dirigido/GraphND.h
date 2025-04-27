#ifndef GRAPHND_H_
#define GRAPHND_H_

#include "NodeGrafVer.h"
#include "NodeGrafArc.h"
#include "EdgeTriple.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <limits> // Required for numeric_limits
#include <cstddef> // Required for NULL
#include <stdexcept> // For potential exceptions like runtime_error


// Represents an undirected graph using adjacency lists.
template <typename elem>
class GraphND {

private:
    // --- Private Helper Methods (UPPER_SNAKE_CASE) ---

    // Finds vertex node PRECEDING the one with data 'value', starts search from 'startNode'. Returns startNode if value is in the first node. Returns NULL if not found.
    NodeGrafVer<elem>* FIND_VERTEX_PREV(NodeGrafVer<elem>* startNode, const elem& value) {
        NodeGrafVer<elem>* current = startNode;
        NodeGrafVer<elem>* previous = NULL;

        if (!current) return NULL; // List is empty

        // Check if the first node is the target
        if (current->getData() == value) {
            return current; // Special case: target is the first node
        }

        previous = current;
        current = current->getNextVertex();

        while (current != NULL) {
            if (current->getData() == value) {
                return previous; // Found, return the previous node
            }
            previous = current;
            current = current->getNextVertex();
        }
        return NULL; // Not found
    }

    // Finds the vertex node containing 'value', starting search from 'startNode'. Returns the node pointer or NULL if not found.
    NodeGrafVer<elem>* FIND_VERTEX_NODE(NodeGrafVer<elem>* startNode, const elem& value) {
        NodeGrafVer<elem>* current = startNode;
        while(current != NULL) {
            if (current->getData() == value) {
                return current;
            }
            current = current->getNextVertex();
        }
        return NULL;
    }


    // Searches for an arc pointing to 'destinationValue' within the adjacency list starting at 'startArc'. Returns arc node pointer or NULL.
    NodeGrafArc<elem>* FIND_EDGE(NodeGrafArc<elem>* startArc, const elem& destinationValue) {
        NodeGrafArc<elem>* current = startArc;
        while (current != NULL) {
            if (current->getDestination() && current->getDestination()->getData() == destinationValue) {
                return current; // Found the arc
            }
            current = current->getNextArc();
        }
        return NULL; // Arc not found
    }

    // Adds a directed edge from vertex 'vA' to 'vB' with weight 'w'. Returns true on success, false otherwise.
    bool ADD_DIRECTED_EDGE(const elem& vA, const elem& vB, float w) {
        NodeGrafVer<elem>* nodeA = FIND_VERTEX_NODE(this->prim, vA);
        NodeGrafVer<elem>* nodeB = FIND_VERTEX_NODE(this->prim, vB);

        if (!nodeA || !nodeB) return false; // One or both vertices don't exist

        // Check if edge already exists (optional, handled by addEdge generally)
        // if (FIND_EDGE(nodeA->getAdjList(), vB)) return false; // Already exists

        // Insert new arc at the beginning of nodeA's adjacency list
        NodeGrafArc<elem>* newArc = new NodeGrafArc<elem>(w, nodeB, nodeA->getAdjList());
        nodeA->setAdjList(newArc);
        return true;
    }

    // Removes the directed edge from 'sourceNode' to vertex 'targetValue'. Returns true on success, false otherwise.
    bool REMOVE_DIRECTED_EDGE(NodeGrafVer<elem>* sourceNode, const elem& targetValue) {
        if (!sourceNode || !sourceNode->getAdjList()) return false; // No source or no outgoing edges

        NodeGrafArc<elem>* currentArc = sourceNode->getAdjList();
        NodeGrafArc<elem>* prevArc = NULL;

        // Check if the first arc is the one to remove
        if (currentArc->getDestination() && currentArc->getDestination()->getData() == targetValue) {
            sourceNode->setAdjList(currentArc->getNextArc()); // Bypass the first arc
            delete currentArc;
            return true;
        }

        // Search in the rest of the list
        prevArc = currentArc;
        currentArc = currentArc->getNextArc();

        while (currentArc != NULL) {
            if (currentArc->getDestination() && currentArc->getDestination()->getData() == targetValue) {
                prevArc->setNextArc(currentArc->getNextArc()); // Bypass the current arc
                delete currentArc;
                return true;
            }
            prevArc = currentArc;
            currentArc = currentArc->getNextArc();
        }

        return false; // Edge not found
    }

     // Recursive helper for Depth First Search. Parameters: current vertex, visited vector, path list.
    void DFS_RECURSIVE(NodeGrafVer<elem>* currentVertex, std::vector<bool>& visited, std::list<elem>& path) {
        if (!currentVertex) return;

        int currentIndex = getVertexIndex(currentVertex->getData());
        if (currentIndex == -1 || visited[currentIndex]) return; // Check validity and visited status

        visited[currentIndex] = true;
        path.push_back(currentVertex->getData());

        NodeGrafArc<elem>* arc = currentVertex->getAdjList();
        while (arc != NULL) {
            DFS_RECURSIVE(arc->getDestination(), visited, path);
            arc = arc->getNextArc();
        }
    }

    // Recursive helper for finding the longest path (max edges). Params: current, end, visited, currentPath, longestPath.
    void LONGEST_PATH_RECURSIVE(NodeGrafVer<elem>* current, const elem& endValue, std::vector<bool>& visited, std::list<elem>& currentPath, std::list<elem>& longestPath) {
        int currentIndex = getVertexIndex(current->getData());
        visited[currentIndex] = true;
        currentPath.push_back(current->getData());

        if (current->getData() == endValue) {
            if (currentPath.size() > longestPath.size()) {
                longestPath = currentPath; // Found a longer path
            }
        } else {
            NodeGrafArc<elem>* arc = current->getAdjList();
            while(arc != NULL) {
                int nextIndex = getVertexIndex(arc->getDestination()->getData());
                if (!visited[nextIndex]) {
                    LONGEST_PATH_RECURSIVE(arc->getDestination(), endValue, visited, currentPath, longestPath);
                }
                arc = arc->getNextArc();
            }
        }

        // Backtrack
        currentPath.pop_back();
        visited[currentIndex] = false;
    }

    // Recursive helper for finding the shortest path (min edges). Params: current, end, visited, currentPath, shortestPath.
    void SHORTEST_PATH_RECURSIVE(NodeGrafVer<elem>* current, const elem& endValue, std::vector<bool>& visited, std::list<elem>& currentPath, std::list<elem>& shortestPath) {
        int currentIndex = getVertexIndex(current->getData());
        visited[currentIndex] = true;
        currentPath.push_back(current->getData());

        // Pruning: if current path is already longer than best found, stop exploring this branch
        if (!shortestPath.empty() && currentPath.size() >= shortestPath.size()) {
             currentPath.pop_back();
             visited[currentIndex] = false;
             return;
        }


        if (current->getData() == endValue) {
            if (shortestPath.empty() || currentPath.size() < shortestPath.size()) {
                shortestPath = currentPath; // Found a new shortest path
            }
        } else {
            NodeGrafArc<elem>* arc = current->getAdjList();
            while(arc != NULL) {
                int nextIndex = getVertexIndex(arc->getDestination()->getData());
                if (!visited[nextIndex]) {
                   SHORTEST_PATH_RECURSIVE(arc->getDestination(), endValue, visited, currentPath, shortestPath);
                }
                arc = arc->getNextArc();
            }
        }

        // Backtrack
        currentPath.pop_back();
        visited[currentIndex] = false;
    }

    // Recursive helper for Hamiltonian Path. Params: current, visited, path, found flag.
    void HAMILTONIAN_PATH_RECURSIVE(NodeGrafVer<elem>* current, std::vector<bool>& visited, std::list<elem>& path, bool& found) {
        if (found) return; // Stop if already found one

        int currentIndex = getVertexIndex(current->getData());
        path.push_back(current->getData());
        visited[currentIndex] = true;

        if (path.size() == numVert) {
            found = true; // Found a Hamiltonian path
            return;
        }

        NodeGrafArc<elem>* arc = current->getAdjList();
        while (arc != NULL && !found) {
             NodeGrafVer<elem>* neighbor = arc->getDestination();
             int neighborIndex = getVertexIndex(neighbor->getData());
             if (!visited[neighborIndex]) {
                 HAMILTONIAN_PATH_RECURSIVE(neighbor, visited, path, found);
             }
             arc = arc->getNextArc();
        }

        // Backtrack if no path found from here or already found one
        if (!found) {
            path.pop_back();
            visited[currentIndex] = false;
        }
    }

    // Recursive helper for Min Cost Hamiltonian Path. Params: current, visited, path, currentCost, bestPath, minCost.
    void MIN_COST_HAMILTONIAN_RECURSIVE(NodeGrafVer<elem>* current, std::vector<bool>& visited, std::list<elem>& currentPath, float currentCost, std::list<elem>& bestPath, float& minCost) {
        int currentIndex = getVertexIndex(current->getData());
        currentPath.push_back(current->getData());
        visited[currentIndex] = true;

        // Pruning: If current cost exceeds best found, stop
        if (currentCost >= minCost) {
            currentPath.pop_back();
            visited[currentIndex] = false;
            return;
        }

        if (currentPath.size() == numVert) {
            // Found a potential Hamiltonian path
            // Check if it can return to start for a cycle if needed, or just update path cost
            // For path only:
             if (currentCost < minCost) {
                  minCost = currentCost;
                  bestPath = currentPath;
             }

        } else {
            NodeGrafArc<elem>* arc = current->getAdjList();
            while (arc != NULL) {
                NodeGrafVer<elem>* neighbor = arc->getDestination();
                int neighborIndex = getVertexIndex(neighbor->getData());
                if (!visited[neighborIndex]) {
                     MIN_COST_HAMILTONIAN_RECURSIVE(neighbor, visited, currentPath, currentCost + arc->getWeight(), bestPath, minCost);
                }
                arc = arc->getNextArc();
            }
        }

        // Backtrack
        currentPath.pop_back();
        visited[currentIndex] = false;
    }

    // Updates the internal mapGraph vector based on the current vertex list.
    void UPDATE_MAP() {
        mapGraph.clear();
        NodeGrafVer<elem>* current = prim;
        while (current != NULL) {
            mapGraph.push_back(current->getData());
            current = current->getNextVertex();
        }
    }


public:
    // --- Public Attributes (as requested, though private is often preferred) ---
    std::vector<elem> mapGraph;    // Map of vertex values to indices
    NodeGrafVer<elem>* prim;       // Pointer to the first vertex node
    int numVert;                   // Number of vertices
    int numEdges;                  // Number of undirected edges

    // --- Public Methods (lowerCamelCase) ---

    // Default constructor: Creates an empty graph.
    GraphND() : prim(NULL), numVert(0), numEdges(0) {}

    // Copy constructor: Creates a deep copy of another graph.
    GraphND(const GraphND<elem>& other) : prim(NULL), numVert(0), numEdges(0) {
        copyFrom(other);
    }

    // Destructor: Clears the graph, freeing all allocated memory.
    ~GraphND() {
        clear();
    }

    // Assignment operator: Assigns a deep copy of another graph.
    GraphND<elem>& operator=(const GraphND<elem>& other) {
        if (this != &other) { // Prevent self-assignment
            clear();
            copyFrom(other);
        }
        return *this;
    }

    // Checks if the graph is empty (contains no vertices). Returns true if empty, false otherwise.
    bool isEmpty() const {
        return prim == NULL;
    }

    // Adds a vertex with the given data if it doesn't already exist. Maintains sorted order. Returns true if added, false otherwise.
    void addVertex(const elem& data) {
        NodeGrafVer<elem>* current = prim;
        NodeGrafVer<elem>* previous = NULL;

        // Find insertion point or check existence
        while (current != NULL && current->getData() < data) {
            previous = current;
            current = current->getNextVertex();
        }

        // Check if vertex already exists
        if (current != NULL && current->getData() == data) {
            return; // Already exists
        }

        // Create and insert the new node
        NodeGrafVer<elem>* newNode = new NodeGrafVer<elem>(data);
        if (previous == NULL) { // Insert at the beginning
            newNode->setNextVertex(prim);
            prim = newNode;
        } else { // Insert after previous
            newNode->setNextVertex(current);
            previous->setNextVertex(newNode);
        }
        numVert++;
        UPDATE_MAP();
    }

    // Adds an undirected edge between vertex vA and vB with weight w. Returns true if successful, false otherwise.
    void addEdge(const elem& vA, const elem& vB, float w) {
         // Ensure vertices exist before proceeding
        NodeGrafVer<elem>* nodeA = FIND_VERTEX_NODE(prim, vA);
        NodeGrafVer<elem>* nodeB = FIND_VERTEX_NODE(prim, vB);

        if (!nodeA || !nodeB) {
            // Optionally throw an exception or just return
            // std::cerr << "Error: One or both vertices for edge (" << vA << ", " << vB << ") not found." << std::endl;
            return; // Vertex(es) not found
        }

        // Check if edge already exists (A->B) - sufficient for undirected check if addEdge enforces symmetry
        if (FIND_EDGE(nodeA->getAdjList(), vB)) {
            return; // Edge already exists
        }

        bool added1 = false;
        bool added2 = false;

        if (vA == vB) { // Handle self-loop
            added1 = ADD_DIRECTED_EDGE(vA, vB, w);
            if (added1) {
                numEdges++;
            }
        } else {
            added1 = ADD_DIRECTED_EDGE(vA, vB, w);
            added2 = ADD_DIRECTED_EDGE(vB, vA, w);
            if (added1 && added2) {
                numEdges++;
            } else if (added1 && !added2) {
                 // Rollback if only one direction succeeded (should not happen if vertices exist)
                 REMOVE_DIRECTED_EDGE(nodeA, vB);
            } else if (!added1 && added2) {
                 // Rollback if only one direction succeeded (should not happen if vertices exist)
                  REMOVE_DIRECTED_EDGE(nodeB, vA);
            }
        }
    }

    // Removes the vertex with the given data and all incident edges.
    void removeVertex(const elem& data) {
        NodeGrafVer<elem>* prevVertex = NULL;
        NodeGrafVer<elem>* toDelete = prim;

        // Find the vertex and its predecessor
        while(toDelete != NULL && toDelete->getData() != data) {
            prevVertex = toDelete;
            toDelete = toDelete->getNextVertex();
        }

        if (!toDelete) return; // Vertex not found

        // --- Step 1: Remove all edges pointing TO the vertex to be deleted ---
        NodeGrafVer<elem>* currentVert = prim;
        while (currentVert != NULL) {
            if (currentVert != toDelete) { // Don't try to remove edges from the node itself yet
                 REMOVE_DIRECTED_EDGE(currentVert, data);
                 // Note: REMOVE_DIRECTED_EDGE does not decrement numEdges, handled later
            }
            currentVert = currentVert->getNextVertex();
        }

        // --- Step 2: Remove all edges STARTING FROM the vertex to be deleted ---
        NodeGrafArc<elem>* currentArc = toDelete->getAdjList();
        NodeGrafArc<elem>* nextArc = NULL;
        while (currentArc != NULL) {
            nextArc = currentArc->getNextArc();
             // We already removed the reverse edges in Step 1 for non-loops.
             // For loops, the edge points back to 'toDelete', which will be cleaned below.
             // We must decrement numEdges for each distinct edge removed.
             if (currentArc->getDestination() != toDelete) { // Avoid double counting for loops
                 numEdges--; // Decrement for the A->B edge being removed
             } else {
                 numEdges--; // Decrement for the A->A loop edge being removed
             }
             delete currentArc;
            currentArc = nextArc;
        }
        toDelete->setAdjList(NULL); // Clear the adjacency list pointer

        // --- Step 3: Remove the vertex node itself from the main list ---
        if (prevVertex == NULL) { // Deleting the first vertex
            prim = toDelete->getNextVertex();
        } else {
            prevVertex->setNextVertex(toDelete->getNextVertex());
        }
        delete toDelete;
        numVert--;
        UPDATE_MAP();
    }


    // Removes the undirected edge between vA and vB.
    void removeEdge(const elem& vA, const elem& vB) {
        NodeGrafVer<elem>* nodeA = FIND_VERTEX_NODE(prim, vA);
        NodeGrafVer<elem>* nodeB = FIND_VERTEX_NODE(prim, vB);

        if (!nodeA || !nodeB) return; // Vertices not found

        bool removed1 = false;
        bool removed2 = false;

        if (vA == vB) {
            removed1 = REMOVE_DIRECTED_EDGE(nodeA, vB);
            if (removed1) {
                numEdges--;
            }
        } else {
             removed1 = REMOVE_DIRECTED_EDGE(nodeA, vB);
             removed2 = REMOVE_DIRECTED_EDGE(nodeB, vA);
             // Decrement edge count only if *both* directed edges were present and removed
             if (removed1 || removed2) { // If at least one direction existed
                  // We assume if one existed, the graph *should* have had the other for undirected
                  // If the graph state was inconsistent, this might over/under decrement.
                  // Safest is to decrement only if both were removed:
                  // if (removed1 && removed2) numEdges--;
                  // However, the original logic seemed to decrement if the edge 'conceptually' existed:
                   numEdges--; // Assuming edge existed conceptually if remove succeeded in either direction
             }
        }
    }

    // Checks if a directed edge exists from vA to vB. Returns true if it exists, false otherwise.
    bool edgeExists(const elem& vA, const elem& vB) const {
         NodeGrafVer<elem>* nodeA = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, vA); // C++98 const_cast needed for private find
         if (!nodeA) return false;
         return const_cast<GraphND<elem>*>(this)->FIND_EDGE(nodeA->getAdjList(), vB) != NULL;
    }

    // Gets the weight of the directed edge from vA to vB. Returns weight if exists, -1.0f otherwise.
    float getEdgeWeight(const elem& vA, const elem& vB) const {
        NodeGrafVer<elem>* nodeA = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, vA);
         if (!nodeA) return -1.0f;
         NodeGrafArc<elem>* arc = const_cast<GraphND<elem>*>(this)->FIND_EDGE(nodeA->getAdjList(), vB);
        return (arc != NULL) ? arc->getWeight() : -1.0f;
    }

    // Returns the order (number of vertices) of the graph.
    int order() const {
        return numVert;
    }

    // Returns the number of vertices in the graph.
    int getNumVertices() const {
        return numVert;
    }

    // Returns the number of undirected edges in the graph.
    int getNumEdges() const {
        return numEdges;
    }

    // Gets the data of the first vertex in the graph's internal list. Throws runtime_error if empty.
    elem getFirstVertex() const {
        if (isEmpty()) {
            throw std::runtime_error("getFirstVertex() called on empty graph");
        }
        return prim->getData();
    }

    // Returns a list of the data of all vertices adjacent to the given vertex. Returns empty list if vertex not found or no neighbors.
    std::list<elem> getNeighbors(const elem& vertexData) const {
        std::list<elem> neighbors;
        NodeGrafVer<elem>* node = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, vertexData);
        if (node) {
            NodeGrafArc<elem>* arc = node->getAdjList();
            while (arc != NULL) {
                if (arc->getDestination()) {
                    neighbors.push_back(arc->getDestination()->getData());
                }
                arc = arc->getNextArc();
            }
        }
        return neighbors;
    }

    // Removes all vertices and edges from the graph.
    void clear() {
        NodeGrafVer<elem>* currentVertex = prim;
        NodeGrafVer<elem>* nextVertex = NULL;

        while (currentVertex != NULL) {
            NodeGrafArc<elem>* currentArc = currentVertex->getAdjList();
            NodeGrafArc<elem>* nextArc = NULL;
            // Delete all arcs in the adjacency list
            while (currentArc != NULL) {
                nextArc = currentArc->getNextArc();
                delete currentArc;
                currentArc = nextArc;
            }
            // Move to the next vertex and delete the current one
            nextVertex = currentVertex->getNextVertex();
            delete currentVertex;
            currentVertex = nextVertex;
        }
        prim = NULL;
        numVert = 0;
        numEdges = 0;
        mapGraph.clear();
    }

    // Checks if the graph has the number of edges required for a complete graph. Returns true if counts match, false otherwise. Note: Doesn't verify structure.
    bool isComplete() const {
        if (numVert < 2) return true; // 0 or 1 vertex is trivially complete
        long long maxEdges = static_cast<long long>(numVert) * (numVert - 1) / 2; // Use long long to avoid overflow
        return numEdges == maxEdges;
    }

     // Checks if the graph is connected using BFS. Returns true if connected, false otherwise.
    bool isConnected() const {
        if (isEmpty() || numVert == 1) return true; // Empty or single vertex graph is connected

        std::list<elem> visited = bfs(getFirstVertex()); // Perform BFS from the first vertex
        return visited.size() == numVert; // Connected if BFS visited all vertices
    }

    // Returns the degree (number of incident edges) of the specified vertex. Returns 0 if vertex not found.
    int vertexDegree(const elem& vertexData) const {
        // For undirected graphs, the number of neighbours is the degree.
        // Be careful with self-loops: they add 2 to the degree usually,
        // but getNeighbors currently only lists the neighbor once.
        // A more accurate degree count might iterate the adj list and add 2 for a loop.
        NodeGrafVer<elem>* node = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, vertexData);
        int degree = 0;
        if (node) {
            NodeGrafArc<elem>* arc = node->getAdjList();
            while (arc != NULL) {
                 degree++;
                 // If self-loops should count as 2, add check:
                 // if (arc->getDestination() == node) degree++;
                arc = arc->getNextArc();
            }
        }
        return degree;
        // Or simply: return getNeighbors(vertexData).size(); if self-loops count as 1.

    }

    // Returns a list containing the data of all vertices in the graph.
    std::list<elem> getVertices() const {
        std::list<elem> vertices;
        NodeGrafVer<elem>* current = prim;
        while (current != NULL) {
            vertices.push_back(current->getData());
            current = current->getNextVertex();
        }
        return vertices;
    }

    // Returns a list of EdgeTriple objects representing all undirected edges.
    std::list< EdgeTriple<elem> > getEdges() const {
        std::list< EdgeTriple<elem> > edges;
        std::vector<bool> visitedEdges; // Need a way to mark edges as added to avoid duplicates {A,B} and {B,A}
        // This requires a more complex tracking, e.g., mapping pairs of vertices to visited status.
        // Simpler approach: only add edge (A,B) if A < B (requires comparable elem type)

        NodeGrafVer<elem>* currentVert = prim;
        while (currentVert != NULL) {
            NodeGrafArc<elem>* currentArc = currentVert->getAdjList();
            elem sourceData = currentVert->getData();
            while (currentArc != NULL) {
                 if (currentArc->getDestination()) {
                     elem destData = currentArc->getDestination()->getData();
                      // Add edge only once, e.g., if source <= destination (handles loops too)
                      // Requires operator<= for elem type
                      // if (!(destData < sourceData)) { // Assumes operator< exists
                      //     edges.push_back(EdgeTriple<elem>(sourceData, destData, currentArc->getWeight()));
                      // }
                      // Simpler: Add all directed edges found, let caller handle duplicates if needed,
                      // or implement robust visited tracking.
                      // For now, adding based on A->B representation:
                      edges.push_back(EdgeTriple<elem>(sourceData, destData, currentArc->getWeight()));

                 }
                currentArc = currentArc->getNextArc();
            }
            currentVert = currentVert->getNextVertex();
        }
         // If strict undirected unique edges are needed, filter the list 'edges' here
         // before returning to remove duplicates like (B,A,w) if (A,B,w) exists.
        return edges;
    }

    // Performs a deep copy of the 'other' graph into this graph.
    void copyFrom(const GraphND<elem>& other) {
        if (this == &other) return; // Avoid self-copy

        clear(); // Clear current graph content

        if (other.isEmpty()) return; // Nothing to copy

        // Step 1: Copy all vertices
        NodeGrafVer<elem>* otherCurrentVert = other.prim;
        while (otherCurrentVert != NULL) {
            this->addVertex(otherCurrentVert->getData()); // Use addVertex to maintain order and update map
            otherCurrentVert = otherCurrentVert->getNextVertex();
        }

        // Step 2: Copy all edges
        otherCurrentVert = other.prim;
         while (otherCurrentVert != NULL) {
             NodeGrafArc<elem>* otherCurrentArc = otherCurrentVert->getAdjList();
             elem sourceData = otherCurrentVert->getData();
             while (otherCurrentArc != NULL) {
                  if (otherCurrentArc->getDestination()) {
                      elem destData = otherCurrentArc->getDestination()->getData();
                      // Use ADD_DIRECTED_EDGE because addEdge checks for existence and increments numEdges
                      // We want to replicate the structure exactly, including the two directed edges per undirected one.
                      // We only add A->B here; the B->A will be added when iterating over B's vertex.
                      // Need to manage numEdges manually or adjust addEdge.
                      // Let's use addEdge but be mindful it handles symmetry.
                      // Only add if source <= destination to avoid adding twice via addEdge? Requires comparable elem.

                      // Safer: directly use ADD_DIRECTED_EDGE and manage numEdges
                       this->ADD_DIRECTED_EDGE(sourceData, destData, otherCurrentArc->getWeight());
                       // Don't increment numEdges here, let the final count match 'other'.

                  }
                 otherCurrentArc = otherCurrentArc->getNextArc();
             }
             otherCurrentVert = otherCurrentVert->getNextVertex();
         }
         // Set edge count explicitly after copying structure
         this->numEdges = other.numEdges;

         // Update map after all additions (already done by addVertex)
         // UPDATE_MAP(); // Map updated progressively by addVertex
    }


    // Loads the graph from a list of edge triples. Assumes vertices are implicitly defined by the edges.
    void loadFromTriples(const std::list< EdgeTriple<elem> >& triples) {
        clear();
        // Use an intermediate structure like std::set if elem is comparable, or std::list+find otherwise,
        // to efficiently add unique vertices first. C++98 doesn't have std::unordered_set.
        // Simple approach: Iterate triples, add both vertices for each triple. addVertex handles duplicates.
         typename std::list< EdgeTriple<elem> >::const_iterator it; // C++98 style iterator
         for (it = triples.begin(); it != triples.end(); ++it) {
            addVertex(it->getVertexA());
            addVertex(it->getVertexB());
        }
        // Now add the edges
        for (it = triples.begin(); it != triples.end(); ++it) {
            addEdge(it->getVertexA(), it->getVertexB(), it->getWeight());
        }
    }


    // Performs Breadth-First Search starting from 'startVertex'. Returns list of visited vertices in BFS order.
    std::list<elem> bfs(const elem& startVertex) const {
        std::list<elem> path;
        std::queue<NodeGrafVer<elem>*> q;
        std::vector<bool> visited(numVert, false);

        NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);
        if (!startNode) return path; // Start vertex not found

        int startIndex = getVertexIndex(startVertex);
        if (startIndex == -1) return path; // Should not happen if FIND_VERTEX_NODE succeeded

        q.push(startNode);
        visited[startIndex] = true;

        while (!q.empty()) {
            NodeGrafVer<elem>* current = q.front();
            q.pop();
            path.push_back(current->getData());

            NodeGrafArc<elem>* arc = current->getAdjList();
            while (arc != NULL) {
                 NodeGrafVer<elem>* neighbor = arc->getDestination();
                 if (neighbor) {
                     int neighborIndex = getVertexIndex(neighbor->getData());
                     if (neighborIndex != -1 && !visited[neighborIndex]) {
                         visited[neighborIndex] = true;
                         q.push(neighbor);
                     }
                 }
                arc = arc->getNextArc();
            }
        }
        return path;
    }


    // Performs Depth-First Search starting from 'startVertex'. Returns list of visited vertices in DFS order.
    std::list<elem> dfs(const elem& startVertex) const {
        std::list<elem> path;
        std::vector<bool> visited(numVert, false);
        NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);

        if (startNode) {
             // Need const_cast because private helpers aren't const
             const_cast<GraphND<elem>*>(this)->DFS_RECURSIVE(startNode, visited, path);
        }
        return path;
    }


    // Computes shortest paths from 'startVertex' using Dijkstra's algorithm. Returns vector of distances (indexed by mapGraph). Uses numeric_limits max for infinity.
    std::vector<float> dijkstra(const elem& startVertex) const {
        const float INF = std::numeric_limits<float>::max();
        std::vector<float> dist(numVert, INF);
        // C++98 doesn't have std::priority_queue easily usable with custom comparators or pairs without more boilerplate.
        // Simulate using a vector and finding min distance vertex each time.
        std::vector<bool> visited(numVert, false);

        int startIndex = getVertexIndex(startVertex);
        if (startIndex == -1) {
             // Return vector of Infs or throw error if start node not found
             return dist;
        }

        dist[startIndex] = 0.0f;

        for (int count = 0; count < numVert; ++count) {
            // Find vertex with minimum distance among unvisited vertices
            float minDist = INF;
            int u = -1; // index of min dist vertex

            for (int v_idx = 0; v_idx < numVert; ++v_idx) {
                if (!visited[v_idx] && dist[v_idx] <= minDist) {
                    minDist = dist[v_idx];
                    u = v_idx;
                }
            }

            if (u == -1) break; // No reachable unvisited vertices left

            visited[u] = true;
            elem u_val = getVertexFromIndex(u); // Get vertex value from index
            NodeGrafVer<elem>* u_node = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, u_val);

            if (!u_node) continue; // Should exist if index is valid

            // Update distances of adjacent vertices
            NodeGrafArc<elem>* arc = u_node->getAdjList();
            while(arc != NULL) {
                NodeGrafVer<elem>* v_node = arc->getDestination();
                 if (v_node) {
                     int v_idx = getVertexIndex(v_node->getData());
                     float weight = arc->getWeight();
                     if (v_idx != -1 && !visited[v_idx] && dist[u] != INF && dist[u] + weight < dist[v_idx]) {
                         dist[v_idx] = dist[u] + weight;
                     }
                 }
                arc = arc->getNextArc();
            }
        }
        return dist;
    }


    // Finds the path with the minimum number of edges between 'startVertex' and 'endVertex'. Returns list of vertices in the path.
    std::list<elem> shortestPathLength(const elem& startVertex, const elem& endVertex) const {
        std::list<elem> shortestPath;
        std::list<elem> currentPath;
        std::vector<bool> visited(numVert, false);
        NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);

        if (startNode) {
            const_cast<GraphND<elem>*>(this)->SHORTEST_PATH_RECURSIVE(startNode, endVertex, visited, currentPath, shortestPath);
        }
        return shortestPath;
    }

    // Finds the path with the maximum number of edges between 'startVertex' and 'endVertex'. Returns list of vertices in the path.
    std::list<elem> longestPathLength(const elem& startVertex, const elem& endVertex) const {
         std::list<elem> longestPath;
         std::list<elem> currentPath;
         std::vector<bool> visited(numVert, false);
         NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);

         if (startNode) {
             const_cast<GraphND<elem>*>(this)->LONGEST_PATH_RECURSIVE(startNode, endVertex, visited, currentPath, longestPath);
         }
         return longestPath;
    }

    // Finds *a* Hamiltonian path starting from 'startVertex' (visits every vertex exactly once). Returns the path or empty list if none found.
    std::list<elem> findHamiltonianPath(const elem& startVertex) const {
        std::list<elem> path;
        std::vector<bool> visited(numVert, false);
        bool found = false;
        NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);

        if (startNode) {
            const_cast<GraphND<elem>*>(this)->HAMILTONIAN_PATH_RECURSIVE(startNode, visited, path, found);
        }

        return found ? path : std::list<elem>(); // Return path if found, else empty list
    }

     // Finds the Hamiltonian path with the minimum total weight starting from 'startVertex'. Returns the path or empty list if none found.
     std::list<elem> findMinCostHamiltonianPath(const elem& startVertex) const {
        std::list<elem> bestPath;
        std::list<elem> currentPath;
        std::vector<bool> visited(numVert, false);
        float minCost = std::numeric_limits<float>::max();
        NodeGrafVer<elem>* startNode = const_cast<GraphND<elem>*>(this)->FIND_VERTEX_NODE(prim, startVertex);

        if (startNode) {
            const_cast<GraphND<elem>*>(this)->MIN_COST_HAMILTONIAN_RECURSIVE(startNode, visited, currentPath, 0.0f, bestPath, minCost);
        }

        return (minCost == std::numeric_limits<float>::max()) ? std::list<elem>() : bestPath;
    }

    // Compares this graph with another for structural equality. Returns true if identical, false otherwise.
    bool isEqualTo(const GraphND<elem>& other) const {
        if (this->numVert != other.numVert || this->numEdges != other.numEdges) {
            return false;
        }
        if (this->isEmpty() && other.isEmpty()) {
            return true;
        }
        if (this->mapGraph != other.mapGraph) { // Quick check using maps
            return false;
        }

        // More thorough check: Iterate through vertices and compare adjacency lists
        NodeGrafVer<elem>* thisCurrent = this->prim;
        NodeGrafVer<elem>* otherCurrent = other.prim;

        while(thisCurrent != NULL && otherCurrent != NULL) {
             if (thisCurrent->getData() != otherCurrent->getData()) return false; // Vertices differ

             // Compare adjacency lists (needs careful comparison, order might differ)
             NodeGrafArc<elem>* thisArc = thisCurrent->getAdjList();
             std::list< std::pair<elem, float> > thisNeighbors; // Use pair for neighbor+weight
             while(thisArc != NULL) {
                 if(thisArc->getDestination()) thisNeighbors.push_back(std::make_pair(thisArc->getDestination()->getData(), thisArc->getWeight()));
                 thisArc = thisArc->getNextArc();
             }

             NodeGrafArc<elem>* otherArc = otherCurrent->getAdjList();
             std::list< std::pair<elem, float> > otherNeighbors;
             while(otherArc != NULL) {
                  if(otherArc->getDestination()) otherNeighbors.push_back(std::make_pair(otherArc->getDestination()->getData(), otherArc->getWeight()));
                 otherArc = otherArc->getNextArc();
             }

             if (thisNeighbors.size() != otherNeighbors.size()) return false;

             // Check if neighbors lists contain the same elements (regardless of order)
             // Requires sorting or N^2 comparison. Sorting requires operator< for pair/elem.
             thisNeighbors.sort(); // Requires std::pair::operator<
             otherNeighbors.sort();
             if(thisNeighbors != otherNeighbors) return false;


            thisCurrent = thisCurrent->getNextVertex();
            otherCurrent = otherCurrent->getNextVertex();
        }

        // Check if one list finished before the other (shouldn't happen if numVert matched)
        return thisCurrent == NULL && otherCurrent == NULL;
    }


    // Returns the internal map vector.
    const std::vector<elem>& getMap() const {
        return mapGraph;
    }

    // Gets the index corresponding to a vertex value in the map. Returns -1 if not found.
    int getVertexIndex(const elem& vertexData) const {
        // C++98 doesn't have std::find easily applicable here without iterators
        for (size_t i = 0; i < mapGraph.size(); ++i) {
            if (mapGraph[i] == vertexData) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }

    // Gets the vertex value corresponding to a given index in the map. Throws out_of_range if index is invalid.
    elem getVertexFromIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= mapGraph.size()) {
            throw std::out_of_range("Index out of range in getVertexFromIndex");
        }
        return mapGraph[index];
    }

};

#endif // GRAPHND_H_