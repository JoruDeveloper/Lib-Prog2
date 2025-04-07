#include "list.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    List<List<std::string> > L;
    int columns;

    if(std::cin >> columns) {
        std::cin.ignore(); // Limpiar el salto de línea después de columns
        
        std::string linea;
        int fila_actual = 0;
        
        while(std::getline(std::cin, linea)) {
            if(linea.empty()) continue; // Ignorar líneas vacías
            
            List<std::string> tempList;
            std::istringstream ss(linea);
            std::string apodo;
            int palabras_leidas = 0;
            
            while(ss >> apodo && palabras_leidas < columns) {
                tempList.addElem(apodo, tempList.getLength());
                palabras_leidas++;
            }
            
            L.addElem(tempList, fila_actual);
            fila_actual++;
        }

        // Mostrar resultados
        for(int i = 0; i < L.getLength(); ++i) {
            std::cout << "Fila " << i << " (" << L[i].getLength() << " palabras): ";
            for(int j = 0; j < L[i].getLength(); ++j) {
                std::cout << L[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}