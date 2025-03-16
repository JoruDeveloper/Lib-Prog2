#include <iostream>
#include "node.h"

using namespace std; // Usar el namespace std

int main() {
    // Crear nodos de tipo int
    Node<int>* node1 = new Node<int>(NULL, NULL, 10);
    Node<int>* node2 = new Node<int>(NULL, node1, 20);
    node1->setSig(node2);

    // Crear nodos de tipo string
    Node<string>* node3 = new Node<string>(NULL, NULL, "Hello");
    Node<string>* node4 = new Node<string>(NULL, node3, "World");
    node3->setSig(node4);

    // Acceder a la información de los nodos
    cout << "Node 1 Info: " << node1->getInfo() << endl;
    cout << "Node 2 Info: " << node2->getInfo() << endl;
    cout << "Node 3 Info: " << node3->getInfo() << endl;
    cout << "Node 4 Info: " << node4->getInfo() << endl;

    // Acceder a los punteros de los nodos
    if (node1->getSig() != NULL) {
        cout << "Node 1 Sig Info: " << node1->getSig()->getInfo() << endl;
    }

    if (node4->getAnt() != NULL) {
        cout << "Node 4 Ant Info: " << node4->getAnt()->getInfo() << endl;
    }

    // Limpiar la memoria (importante para evitar fugas de memoria)
    delete node1;
    delete node2;
    delete node3;
    delete node4;

    return 0;
}