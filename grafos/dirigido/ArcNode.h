#ifndef ARCNODE_H
#define ARCNODE_H

#include <cstddef> // For NULL
#include "VertexNode.h" // Include VertexNode definition

template <typename Elem>
class ArcNode {
private:
    float weight;                  // Weight of the arc
    VertexNode<Elem>* destinationVertex; // Pointer to the destination vertex of the arc
    ArcNode<Elem>* nextArc;        // Pointer to the next arc from the same source vertex

public:
    // -- Constructors --

    // Default constructor
    ArcNode() : weight(0.0f), destinationVertex(NULL), nextArc(NULL) {}

    // Constructor initializing weight
    ArcNode(float w) : weight(w), destinationVertex(NULL), nextArc(NULL) {}

    // Constructor initializing all members
    ArcNode(float w, VertexNode<Elem>* dest, ArcNode<Elem>* next)
        : weight(w), destinationVertex(dest), nextArc(next) {}

    // -- Getters --

    // Returns the weight of the arc.
    float getWeight() const { return weight; }

    // Returns a pointer to the destination vertex node.
    VertexNode<Elem>* getDestinationVertex() const { return destinationVertex; }

    // Returns a pointer to the next arc in the adjacency list.
    ArcNode<Elem>* getNextArc() const { return nextArc; }

    // -- Setters --

    // Sets the weight of the arc.
    void setWeight(float w) { weight = w; }

    // Sets the pointer to the destination vertex node.
    void setDestinationVertex(VertexNode<Elem>* dest) { destinationVertex = dest; }

    // Sets the pointer to the next arc in the adjacency list.
    void setNextArc(ArcNode<Elem>* next) { nextArc = next; }
};

#endif // ARCNODE_H