#include "stack.h"
#include <iostream>

int main() {
    Stack<int> pila;

    // Verificar si la pila está vacía
    std::cout << "¿Está vacía la pila? " << (pila.isEmpty() ? "Sí" : "No") << std::endl;

    // Agregar elementos a la pila
    pila.push(10);
    pila.push(20);
    pila.push(30);
    
    std::cout << "Elemento en la cima: " << pila.top() << std::endl;

    // Eliminar un elemento
    pila.pop();
    std::cout << "Elemento en la cima después de pop: " << pila.top() << std::endl;

    // Verificar si la pila está vacía después de algunas operaciones
    std::cout << "¿Está vacía la pila? " << (pila.isEmpty() ? "Sí" : "No") << std::endl;

    // Eliminar todos los elementos
    pila.pop();
    pila.pop();
    
    // Intentar hacer pop en una pila vacía
    try {
        pila.pop();
    } catch (const std::out_of_range &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
