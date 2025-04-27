#ifndef EDGE_TRIPLE_H_
#define EDGE_TRIPLE_H_

#include <cstddef> // Para NULL en C++98

// Represents an edge with its two vertices and weight.
template <typename elem>
class EdgeTriple {
private:
    elem vertexA;
    elem vertexB;
    float weight;

public:
    // Default constructor.
    EdgeTriple() : weight(0.0f) {}

    // Constructor with parameters.
    EdgeTriple(elem vA, elem vB, float w) : vertexA(vA), vertexB(vB), weight(w) {}

    // Gets the first vertex.
    elem getVertexA() const { return vertexA; }
    // Gets the second vertex.
    elem getVertexB() const { return vertexB; }
    // Gets the edge weight.
    float getWeight() const { return weight; }

    // Sets the first vertex.
    void setVertexA(elem vA) { vertexA = vA; }
    // Sets the second vertex.
    void setVertexB(elem vB) { vertexB = vB; }
    // Sets the edge weight.
    void setWeight(float w) { weight = w; }

    // Compares this triple with another for equality.
    bool operator==(const EdgeTriple<elem>& other) const {
        // Consider edges undirected for comparison if needed, assuming A<->B is same as B<->A
        // This basic version checks for exact match including order A,B
         return ( (this->vertexA == other.vertexA && this->vertexB == other.vertexB) ||
                  (this->vertexA == other.vertexB && this->vertexB == other.vertexA) // Check reverse for undirected nature
                ) && this->weight == other.weight;
         // If direction matters (e.g., getting directed edges), use:
         // return this->vertexA == other.vertexA && this->vertexB == other.vertexB && this->weight == other.weight;
    }
};

#endif // EDGE_TRIPLE_H_