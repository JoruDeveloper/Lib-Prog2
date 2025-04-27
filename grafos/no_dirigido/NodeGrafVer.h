#ifndef NODE_GRAF_VER_H_
#define NODE_GRAF_VER_H_

#include "NodeGrafArc.h" // Include arc definition
#include <cstddef>      // For NULL
#include <limits>

// Represents a node in the main vertex list.
template <typename elem>
class NodeGrafVer {
private:
    elem data;
    NodeGrafVer<elem>* nextVertex; // Pointer to the next vertex in the main list
    NodeGrafArc<elem>* adjList;    // Pointer to the head of the adjacency list for this vertex

public:
    // Default constructor.
    NodeGrafVer() : nextVertex(NULL), adjList(NULL) {
        // Default initialize data for basic types like int, float, etc.
        // Be cautious if 'elem' is a complex type without a default constructor.
        if (std::numeric_limits<elem>::is_specialized) {
             data = elem(); // Default constructor for numerical types
        }
        // For non-numeric or custom types, ensure 'elem' has a usable default constructor
        // or handle initialization appropriately based on 'elem's type.
    }


    // Constructor with data.
    NodeGrafVer(elem d) : data(d), nextVertex(NULL), adjList(NULL) {}

    // Constructor with all parameters.
    NodeGrafVer(elem d, NodeGrafVer<elem>* next, NodeGrafArc<elem>* adj)
        : data(d), nextVertex(next), adjList(adj) {}

    // Gets the data stored in the vertex.
    elem getData() const { return data; }
    // Gets the next vertex in the main list.
    NodeGrafVer<elem>* getNextVertex() const { return nextVertex; }
    // Gets the head of the adjacency list.
    NodeGrafArc<elem>* getAdjList() const { return adjList; }

    // Sets the data for the vertex.
    void setData(elem d) { data = d; }
    // Sets the next vertex in the main list.
    void setNextVertex(NodeGrafVer<elem>* next) { nextVertex = next; }
    // Sets the head of the adjacency list.
    void setAdjList(NodeGrafArc<elem>* adj) { adjList = adj; }
};

#endif // NODE_GRAF_VER_H_