#include <iostream>
#include "list.h"
#include "node.h"

int main() {
    // Crear una lista de enteros
    List<int> myList;

    // Verificar si está vacía
    std::cout << "¿Lista vacía?: " << (myList.isEmpty() ? "Sí" : "No") << std::endl;

    // Agregar elementos a la lista
    myList.addElem(10, 0);
    myList.addElem(20, 1);
    myList.addElem(30, 2);
    myList.addElem(40, 3);

    // Imprimir los elementos
    std::cout << "Elementos de la lista: ";
    for (int i = 0; i < myList.getLength(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Buscar elemento
    std::cout << "¿Está el 20 en la lista?: " << (myList.isElem(20) ? "Sí" : "No") << std::endl;

    // Eliminar un elemento
    int pos = myList.delete_first_elem(20);
    std::cout << "Se eliminó el elemento 20 en la posición: " << pos << std::endl;

    // Imprimir la lista después de eliminar
    std::cout << "Lista después de eliminar 20: ";
    for (int i = 0; i < myList.getLength(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Modificar un nodo
    myList.modifyNode(25, 1);
    std::cout << "Lista después de modificar la posición 1 con 25: ";
    for (int i = 0; i < myList.getLength(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Invertir la lista
    myList.reverseList();
    std::cout << "Lista invertida: ";
    for (int i = 0; i < myList.getLength(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Ordenar la lista (ascendente)
    myList.bubbleSort(true);
    std::cout << "Lista ordenada ascendentemente: ";
    for (int i = 0; i < myList.getLength(); i++) {
        std::cout << myList[i] << " ";
    }
    std::cout << std::endl;

    // Vaciar la lista
    myList.empty();
    std::cout << "Lista vaciada. ¿Está vacía ahora?: " << (myList.isEmpty() ? "Sí" : "No") << std::endl;

    return 0;
}