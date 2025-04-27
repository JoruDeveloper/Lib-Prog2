#ifndef GRAPHD_H
#define GRAPHD_H

#include <vector>
#include <list>
#include <cstddef>   // For NULL
#include <algorithm> // For std::reverse, std::find
#include <limits>    // Potentially for infinity, though using -1 as sentinel

#include "VertexNode.h"
#include "ArcNode.h"

// Helper structure to return arc information
template <typename elem>
struct ArcInfo {
    elem source;
    elem destination;
    float weight;

    ArcInfo(const elem& s = elem(), const elem& d = elem(), float w = 0.0f)
        : source(s), destination(d), weight(w) {}

     // Required for potential use in std::list::remove or std::find
    bool operator==(const ArcInfo<elem>& other) const {
        return source == other.source && destination == other.destination && weight == other.weight;
    }
};


template <typename elem>
class GraphD {
private:
    std::vector<elem> vertexMap;       // Map for index-based access
    VertexNode<elem>* firstVertex;     // Pointer to the first vertex in the list
    int numVertices;                   // Count of vertices
    int numArcs;                       // Count of arcs

    // -- Private Helper Methods (UPPER_SNAKE_CASE) --

    // Finds the vertex node *preceding* the one with 'value', or NULL if not found or list empty. If value is at head, returns firstVertex itself.
    VertexNode<elem>* FIND_VERTEX_NODE_PREDECESSOR(const elem& value) {
        VertexNode<elem>* current = firstVertex;
        VertexNode<elem>* previous = NULL;

        if (!current) { // Empty list
            return NULL;
        }
        if (current->getData() == value) { // Value is at the head
            return firstVertex; // Return head itself as special case indicator
        }

        previous = current;
        current = current->getNextVertex();

        while (current != NULL) {
            if (current->getData() == value) {
                return previous; // Found it, return the node before it
            }
             if (current->getData() > value) { // List is sorted, passed the spot
                return NULL;
            }
            previous = current;
            current = current->getNextVertex();
        }
        return NULL; // Not found
    }

    // Finds the vertex node with the given value. Returns pointer to the node or NULL.
    VertexNode<elem>* FIND_VERTEX_NODE(const elem& value) {
         VertexNode<elem>* current = firstVertex;
         while(current != NULL) {
             if (current->getData() == value) {
                 return current;
             }
              if (current->getData() > value) { // List is sorted
                return NULL;
            }
             current = current->getNextVertex();
         }
         return NULL;
    }


    // Finds an arc node in an adjacency list starting from 'startArc' pointing to 'destValue'. Returns ArcNode* or NULL.
    ArcNode<elem>* FIND_ARC_NODE(ArcNode<elem>* startArc, const elem& destValue) {
        ArcNode<elem>* current = startArc;
        while (current != NULL) {
            if (current->getDestinationVertex() && current->getDestinationVertex()->getData() == destValue) {
                return current;
            }
            current = current->getNextArc();
        }
        return NULL;
    }

    // Removes an arc pointing to 'destValue' from the adjacency list of 'sourceNode'. Returns true if removed, false otherwise.
    bool REMOVE_ARC_NODE(VertexNode<elem>* sourceNode, const elem& destValue) {
        if (!sourceNode || !sourceNode->getAdjacencyList()) {
            return false;
        }

        ArcNode<elem>* currentArc = sourceNode->getAdjacencyList();
        ArcNode<elem>* prevArc = NULL;

        // Check head of the adjacency list
        if (currentArc->getDestinationVertex() && currentArc->getDestinationVertex()->getData() == destValue) {
            sourceNode->setAdjacencyList(currentArc->getNextArc()); // Update head
            delete currentArc;
            numArcs--;
            return true;
        }

        // Check rest of the adjacency list
        prevArc = currentArc;
        currentArc = currentArc->getNextArc();
        while (currentArc != NULL) {
            if (currentArc->getDestinationVertex() && currentArc->getDestinationVertex()->getData() == destValue) {
                prevArc->setNextArc(currentArc->getNextArc()); // Unlink
                delete currentArc;
                numArcs--;
                return true;
            }
            prevArc = currentArc;
            currentArc = currentArc->getNextArc();
        }
        return false; // Arc not found
    }

    // Recursive helper for Depth First Search traversal.
    void DFS_HELPER(const elem& currentVertexValue, std::vector<bool>& visited, std::list<elem>& traversal) {
        int currentIndex = getMapIndex(currentVertexValue);
        if (currentIndex < 0 || visited[currentIndex]) { // Check bounds and visited status
            return;
        }

        visited[currentIndex] = true;
        traversal.push_back(currentVertexValue);

        std::list<elem> successors = getSuccessors(currentVertexValue);
        for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
            DFS_HELPER(*it, visited, traversal);
        }
    }

    // Recursive helper for finding the longest path (by number of edges).
    void LONGEST_PATH_HELPER(const elem& currentValue, const elem& endValue, std::vector<bool>& visitedInPath, std::list<elem>& currentPath, std::list<elem>& longestPathFound) {
        int currentIndex = getMapIndex(currentValue);
         if (currentIndex < 0) return; // Should not happen if graph is consistent

        visitedInPath[currentIndex] = true;
        currentPath.push_back(currentValue);

        if (currentValue == endValue) {
            if (currentPath.size() > longestPathFound.size()) {
                longestPathFound = currentPath;
            }
        } else {
            std::list<elem> successors = getSuccessors(currentValue);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                 int nextIndex = getMapIndex(*it);
                 if (nextIndex >= 0 && !visitedInPath[nextIndex]) {
                    LONGEST_PATH_HELPER(*it, endValue, visitedInPath, currentPath, longestPathFound);
                 }
            }
        }

        // Backtrack
        currentPath.pop_back();
        visitedInPath[currentIndex] = false;
    }

    // Recursive helper for finding the shortest path (by number of edges).
     void SHORTEST_PATH_HELPER(const elem& currentValue, const elem& endValue, std::vector<bool>& visitedInPath, std::list<elem>& currentPath, std::list<elem>& shortestPathFound) {
        int currentIndex = getMapIndex(currentValue);
         if (currentIndex < 0) return;

        visitedInPath[currentIndex] = true;
        currentPath.push_back(currentValue);

         // Pruning: If current path is already longer than best found, stop exploring this branch
         if (!shortestPathFound.empty() && currentPath.size() >= shortestPathFound.size()) {
              currentPath.pop_back();
              visitedInPath[currentIndex] = false;
              return;
         }


        if (currentValue == endValue) {
            if (shortestPathFound.empty() || currentPath.size() < shortestPathFound.size()) {
                shortestPathFound = currentPath;
            }
        } else {
            std::list<elem> successors = getSuccessors(currentValue);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                 int nextIndex = getMapIndex(*it);
                 if (nextIndex >= 0 && !visitedInPath[nextIndex]) {
                     SHORTEST_PATH_HELPER(*it, endValue, visitedInPath, currentPath, shortestPathFound);
                 }
            }
        }

        // Backtrack
        currentPath.pop_back();
        visitedInPath[currentIndex] = false;
    }

    // Recursive helper for finding *a* Hamiltonian Path.
    void HAMILTONIAN_PATH_HELPER(const elem& currentValue, std::vector<bool>& visited, std::list<elem>& currentPath, bool& found) {
        if (found) return; // Stop if already found

        int currentIndex = getMapIndex(currentValue);
        if (currentIndex < 0 || visited[currentIndex]) return; // Already visited in this path

        visited[currentIndex] = true;
        currentPath.push_back(currentValue);

        if (currentPath.size() == (size_t)numVertices) {
            found = true; // Found a Hamiltonian path
        } else {
            std::list<elem> successors = getSuccessors(currentValue);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end() && !found; ++it) {
                HAMILTONIAN_PATH_HELPER(*it, visited, currentPath, found);
            }
        }

        // Backtrack only if path wasn't completed down this branch
        if (!found) {
            currentPath.pop_back();
            visited[currentIndex] = false;
        }
    }

    // Recursive helper for finding the Minimum Cost Hamiltonian Path.
    void MIN_COST_HAMILTONIAN_HELPER(const elem& currentValue, std::vector<bool>& visited, std::list<elem>& currentPath, float currentCost, std::list<elem>& bestPath, float& minCostFound) {
        int currentIndex = getMapIndex(currentValue);
        if (currentIndex < 0 || visited[currentIndex]) return;

         // Pruning (optional but good): If current cost exceeds best found, stop.
         if (minCostFound >= 0 && currentCost >= minCostFound) {
             return;
         }

        visited[currentIndex] = true;
        currentPath.push_back(currentValue); // Path is built forward here

        if (currentPath.size() == (size_t)numVertices) {
             if (minCostFound < 0 || currentCost < minCostFound) {
                 minCostFound = currentCost;
                 bestPath = currentPath;
             }
        } else {
            std::list<elem> successors = getSuccessors(currentValue);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                 float weight = getArcWeight(currentValue, *it);
                 if (weight >= 0) { // Check if arc exists
                     MIN_COST_HAMILTONIAN_HELPER(*it, visited, currentPath, currentCost + weight, bestPath, minCostFound);
                 }
            }
        }

        // Backtrack
        currentPath.pop_back();
        visited[currentIndex] = false;
        // Note: Cost is NOT decremented here as it was passed by value or recalculated in recursive call
    }


    // Recursive helper for finding the Maximum Cost Hamiltonian Path.
     void MAX_COST_HAMILTONIAN_HELPER(const elem& currentValue, std::vector<bool>& visited, std::list<elem>& currentPath, float currentCost, std::list<elem>& bestPath, float& maxCostFound) {
        int currentIndex = getMapIndex(currentValue);
        if (currentIndex < 0 || visited[currentIndex]) return;


        visited[currentIndex] = true;
        currentPath.push_back(currentValue); // Path is built forward

        if (currentPath.size() == (size_t)numVertices) {
             if (maxCostFound < 0 || currentCost > maxCostFound) {
                 maxCostFound = currentCost;
                 bestPath = currentPath;
             }
        } else {
            std::list<elem> successors = getSuccessors(currentValue);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                 float weight = getArcWeight(currentValue, *it);
                 if (weight >= 0) { // Check if arc exists
                     MAX_COST_HAMILTONIAN_HELPER(*it, visited, currentPath, currentCost + weight, bestPath, maxCostFound);
                 }
            }
        }

        // Backtrack
        currentPath.pop_back();
        visited[currentIndex] = false;
    }


    // Updates the internal vertex map based on the current vertex list.
    void UPDATE_MAP() {
        vertexMap.clear();
        VertexNode<elem>* current = firstVertex;
        while (current != NULL) {
            vertexMap.push_back(current->getData());
            current = current->getNextVertex();
        }
    }

public:
    // -- Constructors and Destructor --

    // Default constructor for an empty graph.
    GraphD() : firstVertex(NULL), numVertices(0), numArcs(0) {}

    // Copy constructor.
    GraphD(const GraphD<elem>& other) : firstVertex(NULL), numVertices(0), numArcs(0) {
        copyGraph(other); // Use helper
    }

    // Destructor.
    ~GraphD() {
        clear();
    }

    // Assignment operator.
    GraphD<elem>& operator=(const GraphD<elem>& other) {
        if (this != &other) { // Prevent self-assignment
            clear();
            copyGraph(other);
        }
        return *this;
    }

    // -- Basic Queries --

    // Checks if the graph has no vertices. Returns true if empty, false otherwise.
    bool isEmpty() const {
        return firstVertex == NULL;
    }

    // Returns the number of vertices in the graph.
    int order() const {
        return numVertices;
    }

    // Returns the number of arcs in the graph.
    int size() const {
        return numArcs;
    }

    // -- Vertex Operations --

    // Adds a vertex with the given value if it doesn't exist. Maintains sorted order. Returns void.
    void addVertex(const elem& value) {
        VertexNode<elem>* newNode = NULL; // Initialize to NULL
        VertexNode<elem>* current = firstVertex;
        VertexNode<elem>* previous = NULL;

        // Find insertion point or check for existence
        while (current != NULL && current->getData() < value) {
            previous = current;
            current = current->getNextVertex();
        }

        // Check if vertex already exists
        if (current != NULL && current->getData() == value) {
            return; // Vertex already exists, do nothing
        }

        // Create the new node
        newNode = new VertexNode<elem>(value);

        // Insert the new node
        newNode->setNextVertex(current); // Link newNode to the rest of the list (or NULL if end)
        if (previous == NULL) { // Insertion at the head
            firstVertex = newNode;
        } else { // Insertion in the middle or at the end
            previous->setNextVertex(newNode);
        }

        numVertices++;
        UPDATE_MAP(); // Update the map after adding a vertex
    }

    // Removes the vertex with the given value and all incident arcs. Returns void.
    void removeVertex(const elem& value) {
        VertexNode<elem>* nodeToRemove = NULL;
        VertexNode<elem>* prevNode = NULL;

        // 1. Find the node to remove and its predecessor
        VertexNode<elem>* findResult = FIND_VERTEX_NODE_PREDECESSOR(value);

        if (!findResult) return; // Vertex not found

        if (findResult == firstVertex && firstVertex->getData() == value) { // Found at head
             nodeToRemove = firstVertex;
             prevNode = NULL; // Indicate it's the head
        } else if (findResult->getNextVertex() && findResult->getNextVertex()->getData() == value) { // Found after predecessor
             nodeToRemove = findResult->getNextVertex();
             prevNode = findResult;
        } else {
             return; // Should not happen if FIND_VERTEX_NODE_PREDECESSOR is correct, but safety check
        }


        // 2. Remove all INCOMING arcs to 'nodeToRemove'
        VertexNode<elem>* iteratorNode = firstVertex;
        while (iteratorNode != NULL) {
            if (iteratorNode != nodeToRemove) { // Don't try to remove arcs from the node itself yet
                // REMOVE_ARC_NODE handles decrementing numArcs if successful
                REMOVE_ARC_NODE(iteratorNode, value);
            }
            iteratorNode = iteratorNode->getNextVertex();
        }

        // 3. Remove all OUTGOING arcs from 'nodeToRemove'
        ArcNode<elem>* currentArc = nodeToRemove->getAdjacencyList();
        ArcNode<elem>* nextArc = NULL;
        while (currentArc != NULL) {
            nextArc = currentArc->getNextArc();
            delete currentArc;
            numArcs--; // Decrement arc count for each outgoing arc deleted
            currentArc = nextArc;
        }
        nodeToRemove->setAdjacencyList(NULL); // Clear the list pointer

        // 4. Unlink the vertex node from the main list
        if (prevNode == NULL) { // Removing the head node
            firstVertex = nodeToRemove->getNextVertex();
        } else { // Removing a middle or tail node
            prevNode->setNextVertex(nodeToRemove->getNextVertex());
        }

        // 5. Delete the vertex node
        delete nodeToRemove;
        numVertices--;
        UPDATE_MAP(); // Update map after removing a vertex
    }


    // -- Arc Operations --

    // Adds a directed arc from sourceValue to destValue with the given weight. Returns void.
    void addArc(const elem& sourceValue, const elem& destValue, float weight) {
        // 1. Find source and destination vertex nodes
        VertexNode<elem>* sourceNode = FIND_VERTEX_NODE(sourceValue);
        VertexNode<elem>* destNode = FIND_VERTEX_NODE(destValue);

        // 2. Check if both vertices exist
        if (!sourceNode || !destNode) {
            return; // One or both vertices not found
        }

        // 3. Check if arc already exists
        if (FIND_ARC_NODE(sourceNode->getAdjacencyList(), destValue) != NULL) {
            return; // Arc already exists
        }

        // 4. Create and insert the new arc node at the head of the source's adjacency list
        ArcNode<elem>* newArc = new ArcNode<elem>(weight, destNode, sourceNode->getAdjacencyList());
        sourceNode->setAdjacencyList(newArc);
        numArcs++;
    }

     // Removes the directed arc from sourceValue to destValue. Returns void.
    void removeArc(const elem& sourceValue, const elem& destValue) {
        VertexNode<elem>* sourceNode = FIND_VERTEX_NODE(sourceValue);
        if (sourceNode) {
            // REMOVE_ARC_NODE handles decrementing numArcs
            REMOVE_ARC_NODE(sourceNode, destValue);
        }
    }

    // Checks if a directed arc exists from sourceValue to destValue. Returns true if it exists, false otherwise.
    bool arcExists(const elem& sourceValue, const elem& destValue) {
        VertexNode<elem>* sourceNode = FIND_VERTEX_NODE(sourceValue);
        if (!sourceNode) {
            return false;
        }
        return FIND_ARC_NODE(sourceNode->getAdjacencyList(), destValue) != NULL;
    }

    // Gets the weight of the arc from sourceValue to destValue. Returns weight if arc exists, -1.0f otherwise.
    float getArcWeight(const elem& sourceValue, const elem& destValue) {
        VertexNode<elem>* sourceNode = FIND_VERTEX_NODE(sourceValue);
        if (!sourceNode) {
            return -1.0f;
        }
        ArcNode<elem>* arc = FIND_ARC_NODE(sourceNode->getAdjacencyList(), destValue);
        return (arc != NULL) ? arc->getWeight() : -1.0f;
    }


    // -- Graph Properties and Queries --

    // Returns a list of vertex values that have an arc pointing *to* the given vertex value.
    std::list<elem> getPredecessors(const elem& value) {
        std::list<elem> predecessors;
        VertexNode<elem>* targetNode = FIND_VERTEX_NODE(value); // Ensure target exists
        if (!targetNode) return predecessors; // Return empty list if target doesn't exist

        VertexNode<elem>* currentVertex = firstVertex;
        while (currentVertex != NULL) {
            // Check if currentVertex points to value
            if (FIND_ARC_NODE(currentVertex->getAdjacencyList(), value) != NULL) {
                predecessors.push_back(currentVertex->getData());
            }
            currentVertex = currentVertex->getNextVertex();
        }
        return predecessors;
    }

    // Returns a list of vertex values that the given vertex value has an arc pointing *to*.
    std::list<elem> getSuccessors(const elem& value) {
        std::list<elem> successors;
        VertexNode<elem>* sourceNode = FIND_VERTEX_NODE(value);
        if (sourceNode) {
            ArcNode<elem>* currentArc = sourceNode->getAdjacencyList();
            while (currentArc != NULL) {
                 if(currentArc->getDestinationVertex()) { // Check if destination ptr is valid
                    successors.push_back(currentArc->getDestinationVertex()->getData());
                 }
                currentArc = currentArc->getNextArc();
            }
        }
        return successors;
    }

    // Returns a list containing the data of all vertices in the graph.
    std::list<elem> getVertices() {
        std::list<elem> vertices;
        VertexNode<elem>* current = firstVertex;
        while (current != NULL) {
            vertices.push_back(current->getData());
            current = current->getNextVertex();
        }
        return vertices;
    }

    // Returns a list containing information (source, destination, weight) for all arcs in the graph.
    std::list< ArcInfo<elem> > getArcs() {
        std::list< ArcInfo<elem> > arcs;
        VertexNode<elem>* currentVertex = firstVertex;
        while (currentVertex != NULL) {
            ArcNode<elem>* currentArc = currentVertex->getAdjacencyList();
            while (currentArc != NULL) {
                 if(currentArc->getDestinationVertex()){ // Check validity
                    arcs.push_back(ArcInfo<elem>(currentVertex->getData(),
                                                currentArc->getDestinationVertex()->getData(),
                                                currentArc->getWeight()));
                 }
                currentArc = currentArc->getNextArc();
            }
            currentVertex = currentVertex->getNextVertex();
        }
        return arcs;
    }

    // Gets the value of the first vertex in the graph's internal list. Throws exception if empty.
    elem getFirstVertexValue() const {
        if (isEmpty()) {
             // C++98 doesn't have standard exceptions like std::logic_error without <stdexcept>
             // Returning a default value or handling error differently might be needed.
             // For now, let's assume elem has a default constructor.
             return elem();
        }
        return firstVertex->getData();
    }

     // Checks if the graph is complete (every vertex has an arc to every other vertex). Assumes no self-loops. Returns bool.
    bool isComplete() const {
        if (numVertices <= 1) return true; // Conventionally, small graphs are complete
        // A complete directed graph (without self-loops) has V*(V-1) arcs.
        return numArcs == numVertices * (numVertices - 1);
    }

    // Checks if the graph is strongly connected using multiple DFS runs (O(V*(V+E))). Returns bool.
    bool isStronglyConnectedDfs() {
        if (isEmpty()) return true; // Empty graph is trivially strongly connected
        if (numVertices == 1) return true; // Single vertex graph

        std::list<elem> vList = getVertices();
        for (typename std::list<elem>::iterator it = vList.begin(); it != vList.end(); ++it) {
            // Perform DFS from vertex *it
            std::list<elem> reachable = dfs(*it);
            // Check if all vertices were reached
            if (reachable.size() != (size_t)numVertices) {
                return false; // If any DFS doesn't reach all vertices, it's not strongly connected
            }
        }
        return true; // If all DFS runs reached all vertices
    }

    // Checks strong connectivity using a simplified (and potentially incorrect) Kosaraju-like approach. Returns bool.
    bool isStronglyConnectedKosaraju() {
         // WARNING: This implementation is based on the flawed logic from the original example code.
         // It is NOT a correct implementation of Kosaraju's algorithm and may give incorrect results.
         // A correct implementation requires tracking DFS finishing times.
        if (isEmpty() || numVertices == 1) return true;

        GraphD<elem> transposedGraph;
        transpose(transposedGraph); // Calculate the transpose

        // 1. DFS on original graph from the first vertex
        std::list<elem> dfs1Result = dfs(firstVertex->getData());
        bool allReachable1 = (dfs1Result.size() == (size_t)numVertices);

        if (!allReachable1) return false; // If not all reachable in G, cannot be strongly connected

         // Get the last vertex visited in the first DFS (this is part of the flawed logic)
         elem lastVisited = elem(); // Requires default constructible elem
         if (!dfs1Result.empty()) {
             // C++98 way to get last element of std::list
             typename std::list<elem>::iterator lastIt = dfs1Result.end();
             --lastIt;
             lastVisited = *lastIt;
         } else {
             return false; // Should not happen if allReachable1 is true and numVertices > 0
         }


        // 2. DFS on transposed graph from the 'lastVisited' vertex
        std::list<elem> dfs2Result = transposedGraph.dfs(lastVisited);
        bool allReachable2 = (dfs2Result.size() == (size_t)numVertices);

        // The flawed logic returns true only if both reachability checks pass
        return allReachable1 && allReachable2;
    }

    // Returns the in-degree (number of incoming arcs) of the specified vertex.
    int inDegree(const elem& value) {
        // Easy way is to count predecessors, but potentially inefficient
        return getPredecessors(value).size();
        // More efficient way would be to cache or calculate differently if needed often.
    }

    // Returns the out-degree (number of outgoing arcs) of the specified vertex.
    int outDegree(const elem& value) {
        // Easy way is to count successors
        return getSuccessors(value).size();
    }

    // -- Traversal and Path Algorithms --

    // Performs Breadth-First Search starting from startValue. Returns list of visited vertices in BFS order.
    std::list<elem> bfs(const elem& startValue) {
        std::list<elem> traversal;
        std::list<elem> queue; // Use std::list as a queue
        std::vector<bool> visited(numVertices, false);

        int startIndex = getMapIndex(startValue);
        if (startIndex < 0) return traversal; // Start vertex not found

        queue.push_back(startValue);
        visited[startIndex] = true;

        while (!queue.empty()) {
            elem currentVal = queue.front();
            queue.pop_front();
            traversal.push_back(currentVal);

            std::list<elem> successors = getSuccessors(currentVal);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                int nextIndex = getMapIndex(*it);
                if (nextIndex >= 0 && !visited[nextIndex]) {
                    visited[nextIndex] = true;
                    queue.push_back(*it);
                }
            }
        }
        return traversal;
    }

    // Performs Depth-First Search starting from startValue. Returns list of visited vertices in DFS order.
    std::list<elem> dfs(const elem& startValue) {
        std::list<elem> traversal;
        if (numVertices == 0) return traversal; // Handle empty graph
        std::vector<bool> visited(numVertices, false);
        DFS_HELPER(startValue, visited, traversal);
        return traversal;
    }

    // Calculates shortest path distances from startValue using Dijkstra's algorithm (list-based, O(V*E)). Returns vector of distances (-1 if unreachable).
    std::vector<float> dijkstra(const elem& startValue) {
        std::vector<float> distances(numVertices, -1.0f); // Use -1 as infinity/unreachable
        std::vector<bool> visited(numVertices, false);    // Track finalized nodes (incorrect use here, should be set/in-queue)
        std::list<elem> pending; // Nodes to process (acting like a queue, not priority queue)

        int startIndex = getMapIndex(startValue);
        if (startIndex < 0) return distances; // Start vertex not found

        distances[startIndex] = 0.0f;
        pending.push_back(startValue);
        // visited[startIndex] = true; // Incorrect place to mark visited in list-based Dijkstra

        while (!pending.empty()) {
            elem currentVal = pending.front(); // Not guaranteed to be min distance node
            pending.pop_front();
            int currentIndex = getMapIndex(currentVal);

            // If already finalized, skip (needed for correctness with list instead of PQ)
             if(visited[currentIndex]) continue;
             visited[currentIndex] = true; // Mark as finalized *after* extracting

             if (distances[currentIndex] < 0) continue; // Skip if unreachable (shouldn't happen if added to pending correctly)


            std::list<elem> successors = getSuccessors(currentVal);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                elem neighborVal = *it;
                int neighborIndex = getMapIndex(neighborVal);
                if (neighborIndex < 0) continue; // Neighbor not in map? Should not happen

                float weight = getArcWeight(currentVal, neighborVal);
                if (weight < 0) continue; // Arc doesn't exist

                 // Check if neighbor finalized. If yes, skip.
                 // This check differs from standard PQ Dijkstra where we only check distance.
                // if(visited[neighborIndex]) continue; // This is too strict, prevents finding shorter paths later


                float newDist = distances[currentIndex] + weight;

                // Relaxation
                if (distances[neighborIndex] < 0 || newDist < distances[neighborIndex]) {
                    distances[neighborIndex] = newDist;
                    // Add neighbor to pending list to be processed.
                    // Avoid duplicates if already pending? std::find is O(N) on list.
                    // Simple approach: just add it. It will be processed eventually.
                    // This leads to the O(V*E) complexity if not optimized.
                    pending.push_back(neighborVal);
                }
            }
        }
        return distances;
    }

    // Finds the shortest path by weight between startValue and endValue. Returns list of vertices in path.
    std::list<elem> shortestPathByWeight(const elem& startValue, const elem& endValue) {
        std::list<elem> path;
        if(numVertices == 0) return path;

        std::vector<float> distances(numVertices, -1.0f);
        std::vector<int> predecessors(numVertices, -1); // Store index of predecessor
        std::vector<bool> visited(numVertices, false);
        std::list<elem> pending;

        int startIndex = getMapIndex(startValue);
        int endIndex = getMapIndex(endValue);
        if (startIndex < 0 || endIndex < 0) return path; // Start or end not found

        distances[startIndex] = 0.0f;
        pending.push_back(startValue);

         while (!pending.empty()) {
            elem currentVal = pending.front(); // Not guaranteed min dist
            pending.pop_front();
            int currentIndex = getMapIndex(currentVal);

            if(visited[currentIndex]) continue;
            visited[currentIndex] = true;

            if (currentIndex == endIndex) break; // Found the shortest path to end node (maybe, due to list)

             if (distances[currentIndex] < 0) continue;

            std::list<elem> successors = getSuccessors(currentVal);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                 elem neighborVal = *it;
                 int neighborIndex = getMapIndex(neighborVal);
                 if (neighborIndex < 0) continue;

                 float weight = getArcWeight(currentVal, neighborVal);
                 if (weight < 0) continue;

                float newDist = distances[currentIndex] + weight;

                if (distances[neighborIndex] < 0 || newDist < distances[neighborIndex]) {
                    distances[neighborIndex] = newDist;
                    predecessors[neighborIndex] = currentIndex;
                    pending.push_back(neighborVal);
                }
            }
        }

        // Reconstruct path if end was reached
        if (distances[endIndex] >= 0) {
            int current = endIndex;
            while (current != -1) {
                path.push_front(getMapVertex(current)); // Add to front to reverse
                current = predecessors[current];
                // Safety break for potential cycles if predecessors[startIndex] is not -1
                 if (current == startIndex && predecessors[current] != -1 && path.front() != startValue) break;
            }
             // Add start node if reconstruction didn't reach it (e.g., start == end)
             if (path.empty() && startValue == endValue) path.push_front(startValue);

        }

        return path;
    }

    // Finds the longest path by weight (only reliable for DAGs). Returns list of vertices in path.
    std::list<elem> longestPathByWeight(const elem& startValue, const elem& endValue) {
        // WARNING: This is generally NP-hard. The Dijkstra-like approach used here
        // is only guaranteed to work correctly on Directed Acyclic Graphs (DAGs).
        // It might fail or loop indefinitely on graphs with positive cycles.
         std::list<elem> path;
        if(numVertices == 0) return path;

        std::vector<float> distances(numVertices, -1.0f); // -1 indicates unreached/negative infinity concept
        std::vector<int> predecessors(numVertices, -1);
        std::vector<bool> visited(numVertices, false); // Needed to detect positive cycles if adapted
        std::list<elem> pending; // Using list as queue

        int startIndex = getMapIndex(startValue);
        int endIndex = getMapIndex(endValue);
        if (startIndex < 0 || endIndex < 0) return path;

        distances[startIndex] = 0.0f;
        pending.push_back(startValue);

        // Simple list-based approach (like Bellman-Ford relaxation order isn't guaranteed)
        // This will likely find *some* path, but not necessarily the longest if cycles exist.
         while (!pending.empty()) {
            elem currentVal = pending.front();
            pending.pop_front();
            int currentIndex = getMapIndex(currentVal);

             // Note: visited check omitted here, unlike shortest path. This allows paths to be revisited
             // which is necessary for longest path potentially, but also allows infinite loops on positive cycles.
             // A proper topological sort based approach is needed for DAGs.

            if (distances[currentIndex] < 0) continue; // Skip if effectively unreachable

            std::list<elem> successors = getSuccessors(currentVal);
            for (typename std::list<elem>::iterator it = successors.begin(); it != successors.end(); ++it) {
                elem neighborVal = *it;
                int neighborIndex = getMapIndex(neighborVal);
                 if (neighborIndex < 0) continue;

                float weight = getArcWeight(currentVal, neighborVal);
                 if (weight < 0) continue; // Arc doesn't exist

                float newDist = distances[currentIndex] + weight;

                // Update if this path is LONGER
                if (distances[neighborIndex] < 0 || newDist > distances[neighborIndex]) {
                    distances[neighborIndex] = newDist;
                    predecessors[neighborIndex] = currentIndex;
                    // Add to pending even if already processed, as longer path might be found
                     pending.push_back(neighborVal);
                }
            }
        }

        // Reconstruct path (same logic as shortest path)
        if (distances[endIndex] >= 0) { // Check if end was reached at all
            int current = endIndex;
            while (current != -1) {
                path.push_front(getMapVertex(current));
                current = predecessors[current];
                 if (current == startIndex && predecessors[current] != -1 && path.front() != startValue) break;
            }
             if (path.empty() && startValue == endValue) path.push_front(startValue);
        }

        return path;
    }

    // Finds the longest path by number of edges between startValue and endValue. Returns list of vertices.
    std::list<elem> longestPathByEdges(const elem& startValue, const elem& endValue) {
        std::list<elem> currentPath;
        std::list<elem> longestPathFound;
         if(numVertices == 0) return longestPathFound;
        std::vector<bool> visitedInPath(numVertices, false);
        LONGEST_PATH_HELPER(startValue, endValue, visitedInPath, currentPath, longestPathFound);
        return longestPathFound;
    }

    // Finds the shortest path by number of edges between startValue and endValue. Returns list of vertices.
    std::list<elem> shortestPathByEdges(const elem& startValue, const elem& endValue) {
        std::list<elem> currentPath;
        std::list<elem> shortestPathFound;
         if(numVertices == 0) return shortestPathFound;
        std::vector<bool> visitedInPath(numVertices, false);
        // Using backtracking helper from original code. BFS is usually preferred.
        SHORTEST_PATH_HELPER(startValue, endValue, visitedInPath, currentPath, shortestPathFound);
        return shortestPathFound;
    }

    // Finds *a* Hamiltonian path starting from any vertex if one exists. Returns the path or empty list.
    std::list<elem> findHamiltonianPath() {
        std::list<elem> path;
        if (numVertices == 0) return path;
        std::vector<bool> visited(numVertices, false);
        bool found = false;

        std::list<elem> startCandidates = getVertices();
        for (typename std::list<elem>::iterator it = startCandidates.begin(); it != startCandidates.end() && !found; ++it) {
            // Reset visited status for each new starting attempt
             std::fill(visited.begin(), visited.end(), false);
             path.clear();
            HAMILTONIAN_PATH_HELPER(*it, visited, path, found);
        }

        return found ? path : std::list<elem>(); // Return the found path or an empty list
    }

    // Finds *a* Hamiltonian path starting from startValue if one exists. Returns the path or empty list.
    std::list<elem> findHamiltonianPath(const elem& startValue) {
        std::list<elem> path;
        if (numVertices == 0) return path;
        std::vector<bool> visited(numVertices, false);
        bool found = false;
        HAMILTONIAN_PATH_HELPER(startValue, visited, path, found);
        return found ? path : std::list<elem>();
    }

     // Finds the Hamiltonian path with the minimum total weight, starting from any vertex. Returns path or empty list.
    std::list<elem> findMinCostHamiltonianPath() {
        std::list<elem> currentPath;
        std::list<elem> bestPath;
        if (numVertices == 0) return bestPath;

        std::vector<bool> visited(numVertices, false);
        float minCost = -1.0f; // Using -1 to indicate "not found yet"

        std::list<elem> startCandidates = getVertices();
        for (typename std::list<elem>::iterator it = startCandidates.begin(); it != startCandidates.end(); ++it) {
            std::fill(visited.begin(), visited.end(), false);
            currentPath.clear();
            // Start recursion for this candidate
            MIN_COST_HAMILTONIAN_HELPER(*it, visited, currentPath, 0.0f, bestPath, minCost);
        }
        // bestPath holds the result (might be empty if no path found)
        return bestPath;
    }


    // Finds the Hamiltonian path with the minimum total weight, starting from startValue. Returns path or empty list.
    std::list<elem> findMinCostHamiltonianPath(const elem& startValue) {
        std::list<elem> currentPath;
        std::list<elem> bestPath;
        if (numVertices == 0) return bestPath;

        std::vector<bool> visited(numVertices, false);
        float minCost = -1.0f;
        MIN_COST_HAMILTONIAN_HELPER(startValue, visited, currentPath, 0.0f, bestPath, minCost);
        return bestPath;
    }


    // Finds the Hamiltonian path with the maximum total weight, starting from any vertex. Returns path or empty list.
    std::list<elem> findMaxCostHamiltonianPath() {
         std::list<elem> currentPath;
        std::list<elem> bestPath;
        if (numVertices == 0) return bestPath;

        std::vector<bool> visited(numVertices, false);
        float maxCost = -1.0f; // Using -1 to indicate "not found yet" / initial max

        std::list<elem> startCandidates = getVertices();
        for (typename std::list<elem>::iterator it = startCandidates.begin(); it != startCandidates.end(); ++it) {
            std::fill(visited.begin(), visited.end(), false);
            currentPath.clear();
            MAX_COST_HAMILTONIAN_HELPER(*it, visited, currentPath, 0.0f, bestPath, maxCost);
        }
        return bestPath;
    }

    // Finds the Hamiltonian path with the maximum total weight, starting from startValue. Returns path or empty list.
    std::list<elem> findMaxCostHamiltonianPath(const elem& startValue) {
        std::list<elem> currentPath;
        std::list<elem> bestPath;
        if (numVertices == 0) return bestPath;

        std::vector<bool> visited(numVertices, false);
        float maxCost = -1.0f;
        MAX_COST_HAMILTONIAN_HELPER(startValue, visited, currentPath, 0.0f, bestPath, maxCost);
        return bestPath;
    }


    // -- Graph Utilities --

    // Clears the graph, deleting all vertices and arcs and freeing memory. Returns void.
    void clear() {
        VertexNode<elem>* currentVertex = firstVertex;
        VertexNode<elem>* nextVertex = NULL;

        while (currentVertex != NULL) {
            // Delete arcs first
            ArcNode<elem>* currentArc = currentVertex->getAdjacencyList();
            ArcNode<elem>* nextArc = NULL;
            while (currentArc != NULL) {
                nextArc = currentArc->getNextArc();
                delete currentArc;
                currentArc = nextArc;
            }
            // Move to next vertex and delete current one
            nextVertex = currentVertex->getNextVertex();
            delete currentVertex;
            currentVertex = nextVertex;
        }
        firstVertex = NULL;
        numVertices = 0;
        numArcs = 0;
        vertexMap.clear();
    }

    // Copies the structure and content of another graph into this one. Returns void.
    void copyGraph(const GraphD<elem>& other) {
         if (this == &other) return; // Handle self-copy if called directly
         clear(); // Ensure current graph is empty

         if (other.isEmpty()) {
             return; // Nothing to copy
         }

         // 1. Copy vertices (maintaining order)
         VertexNode<elem>* otherCurrentV = other.firstVertex;
         VertexNode<elem>* thisLastV = NULL;
         while (otherCurrentV != NULL) {
             VertexNode<elem>* newNode = new VertexNode<elem>(otherCurrentV->getData());
             if (thisLastV == NULL) {
                 firstVertex = newNode; // First node
             } else {
                 thisLastV->setNextVertex(newNode);
             }
             thisLastV = newNode;
             otherCurrentV = otherCurrentV->getNextVertex();
         }
         this->numVertices = other.numVertices;
         UPDATE_MAP(); // Create map based on copied vertices


         // 2. Copy arcs
         otherCurrentV = other.firstVertex;
         VertexNode<elem>* thisCurrentV = this->firstVertex;

         while (otherCurrentV != NULL && thisCurrentV != NULL) {
             ArcNode<elem>* otherCurrentA = otherCurrentV->getAdjacencyList();
             ArcNode<elem>* thisLastA = NULL; // Track last added arc for this vertex

             while (otherCurrentA != NULL) {
                 // Find the destination node in *this* graph's structure
                 VertexNode<elem>* thisDestNode = FIND_VERTEX_NODE(otherCurrentA->getDestinationVertex()->getData());
                  if (thisDestNode) { // Should always be found if vertices copied correctly
                     ArcNode<elem>* newArc = new ArcNode<elem>(otherCurrentA->getWeight(), thisDestNode, NULL);

                     // Insert arc into thisCurrentV's adjacency list (maintaining original relative order is hard, just add to head)
                     newArc->setNextArc(thisCurrentV->getAdjacencyList());
                     thisCurrentV->setAdjacencyList(newArc);

                     this->numArcs++;
                  } else {
                     // Handle error: destination vertex not found in the copied structure
                  }
                 otherCurrentA = otherCurrentA->getNextArc();
             }
             otherCurrentV = otherCurrentV->getNextVertex();
             thisCurrentV = thisCurrentV->getNextVertex();
         }
          // numArcs should ideally match other.numArcs if copy is perfect
          // Note: Re-adding arcs increments numArcs, so starting from 0 is correct.
          // If there was an error, numArcs might differ. A final check/assignment could be added:
          // this->numArcs = other.numArcs; // If trusting the source count
    }


    // Loads graph data from a list of ArcInfo structures. Returns void.
    void loadFromArcs(const std::list< ArcInfo<elem> >& arcs) {
        // Could clear the graph first if desired: // clear();
        for (typename std::list< ArcInfo<elem> >::const_iterator it = arcs.begin(); it != arcs.end(); ++it) {
            addVertex(it->source);      // Ensures source vertex exists
            addVertex(it->destination); // Ensures destination vertex exists
            addArc(it->source, it->destination, it->weight); // Adds the arc
        }
    }

    // Compares this graph with another for equality (same vertices, same arcs, same weights). Returns bool.
    bool isEqualTo(const GraphD<elem>& other) const {
        // 1. Check counts
        if (this->numVertices != other.numVertices || this->numArcs != other.numArcs) {
            return false;
        }
        if (this->isEmpty() && other.isEmpty()) {
            return true;
        }
         if (this->isEmpty() || other.isEmpty()) { // One empty, one not
             return false;
         }

        // 2. Check vertex map (quick check since lists are sorted)
        if (this->vertexMap != other.vertexMap) {
            return false;
        }

        // 3. Check arcs exhaustively (since adjacency list order might differ)
        VertexNode<elem>* thisCurrentV = this->firstVertex;
        while (thisCurrentV != NULL) {
            ArcNode<elem>* thisCurrentA = thisCurrentV->getAdjacencyList();
            while (thisCurrentA != NULL) {
                 if(thisCurrentA->getDestinationVertex()) {
                     elem sourceVal = thisCurrentV->getData();
                     elem destVal = thisCurrentA->getDestinationVertex()->getData();
                     float thisWeight = thisCurrentA->getWeight();

                     // Check if the same arc exists in the other graph with the same weight
                     float otherWeight = other.getArcWeight(sourceVal, destVal);
                     if (otherWeight < 0 || otherWeight != thisWeight) { // Arc doesn't exist or weight differs
                         return false;
                     }
                 }
                thisCurrentA = thisCurrentA->getNextArc();
            }
            thisCurrentV = thisCurrentV->getNextVertex();
        }

        // If all checks passed, graphs are equal
        return true;
    }

    // Computes the transpose of this graph and stores it in targetGraph. Returns void.
    void transpose(GraphD<elem>& targetGraph) const {
        targetGraph.clear(); // Clear the target graph first

        // 1. Add all vertices from this graph to the target graph
        VertexNode<elem>* currentV = this->firstVertex;
        while (currentV != NULL) {
            targetGraph.addVertex(currentV->getData());
            currentV = currentV->getNextVertex();
        }

        // 2. Add reversed arcs to the target graph
        currentV = this->firstVertex;
        while (currentV != NULL) {
            ArcNode<elem>* currentA = currentV->getAdjacencyList();
            while (currentA != NULL) {
                 if(currentA->getDestinationVertex()){
                    // Add arc: Destination -> Source
                    targetGraph.addArc(currentA->getDestinationVertex()->getData(),
                                       currentV->getData(),
                                       currentA->getWeight());
                 }
                currentA = currentA->getNextArc();
            }
            currentV = currentV->getNextVertex();
        }
    }

    // -- Map Access --

    // Returns a const reference to the internal vertex map vector.
    const std::vector<elem>& getMap() const {
        return vertexMap;
    }

    // Gets the index corresponding to a vertex value in the map. Returns index or -1 if not found.
    int getMapIndex(const elem& value) const {
        // Manual search required for C++98 compatibility with std::vector without std::find
        for (size_t i = 0; i < vertexMap.size(); ++i) {
            if (vertexMap[i] == value) {
                return (int)i;
            }
        }
        return -1; // Not found
    }

    // Gets the vertex value at a specific index in the map. Returns value (requires bounds checking).
    elem getMapVertex(int index) const {
        // Basic bounds check
        if (index >= 0 && (size_t)index < vertexMap.size()) {
            return vertexMap[index];
        }
        // Return default value if index is out of bounds
        // Requires elem to be default constructible. Error handling could be improved.
        return elem();
    }

};

#endif // GRAPHD_H