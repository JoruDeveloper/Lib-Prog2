#ifndef VERTEXNODE_H
#define VERTEXNODE_H

#include <cstddef> // For NULL

// Forward declaration of ArcNode
template <typename Elem> class ArcNode;

template <typename Elem>
class VertexNode {
private:
    Elem data;                   // The data stored in the vertex
    VertexNode<Elem>* nextVertex; // Pointer to the next vertex in the main list
    ArcNode<Elem>* adjacencyList; // Pointer to the first arc in the adjacency list

public:
    // -- Constructors --

    // Default constructor
    VertexNode() : nextVertex(NULL), adjacencyList(NULL) {}

    // Constructor initializing data
    VertexNode(const Elem& value) : data(value), nextVertex(NULL), adjacencyList(NULL) {}

    // Constructor initializing all members
    VertexNode(const Elem& value, VertexNode<Elem>* next, ArcNode<Elem>* adj)
        : data(value), nextVertex(next), adjacencyList(adj) {}

    // -- Getters --

    // Returns the data value of the vertex.
    Elem getData() const { return data; }

    // Returns a pointer to the next vertex in the list.
    VertexNode<Elem>* getNextVertex() const { return nextVertex; }

    // Returns a pointer to the start of the adjacency list (first outgoing arc).
    ArcNode<Elem>* getAdjacencyList() const { return adjacencyList; }

    // -- Setters --

    // Sets the data value of the vertex.
    void setData(const Elem& value) { data = value; }

    // Sets the pointer to the next vertex in the list.
    void setNextVertex(VertexNode<Elem>* next) { nextVertex = next; }

    // Sets the pointer to the start of the adjacency list.
    void setAdjacencyList(ArcNode<Elem>* adj) { adjacencyList = adj; }
};

#endif // VERTEXNODE_H