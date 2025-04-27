#ifndef NODE_GRAF_ARC_H_
#define NODE_GRAF_ARC_H_

#include <cstddef> // Para NULL

// Forward declaration
template <typename elem> class NodeGrafVer;

// Represents a node in the adjacency list (an edge).
template <typename elem>
class NodeGrafArc {
private:
    float weight;
    NodeGrafVer<elem>* destination; // Pointer to the destination vertex node
    NodeGrafArc<elem>* nextArc;     // Pointer to the next arc in the same adjacency list

public:
    // Default constructor.
    NodeGrafArc() : weight(0.0f), destination(NULL), nextArc(NULL) {}

    // Constructor with weight.
    NodeGrafArc(float w) : weight(w), destination(NULL), nextArc(NULL) {}

    // Constructor with all parameters.
    NodeGrafArc(float w, NodeGrafVer<elem>* dest, NodeGrafArc<elem>* next)
        : weight(w), destination(dest), nextArc(next) {}

    // Gets the weight of the arc.
    float getWeight() const { return weight; }
    // Gets the destination vertex node.
    NodeGrafVer<elem>* getDestination() const { return destination; }
    // Gets the next arc in the adjacency list.
    NodeGrafArc<elem>* getNextArc() const { return nextArc; }

    // Sets the weight of the arc.
    void setWeight(float w) { weight = w; }
    // Sets the destination vertex node.
    void setDestination(NodeGrafVer<elem>* dest) { destination = dest; }
    // Sets the next arc in the adjacency list.
    void setNextArc(NodeGrafArc<elem>* next) { nextArc = next; }
};

#endif // NODE_GRAF_ARC_H_