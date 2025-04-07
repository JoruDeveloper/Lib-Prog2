#include "list.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    List<List<std::string> > L;
    List<std::string> repetidos;
    int columns, counter, repeticiones, line;

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
        for(int i = 0; i < L.getLength(); ++i){

            std::cout << "Fila " << i << " (" << L[i].getLength() << " palabras): ";
            for(int j = 0; j < L[i].getLength(); ++j) {
                std::cout << L[i][j] << " ";
            }
            std::cout << std::endl;
        }
        // Contar Azotes
        for(int i = 0; i < L.getLength(); i++) {

            // std::cout << i << "\n";

            List<std::string>& innerList = L.getElemRefAt(i);

            while (!innerList.isEmpty()){

                counter = -1;
                repeticiones = -1;

                // std::cout << "While " << innerList.getLength();

                for(int j = 0; j < L.getLength(); j++) {
                        // std::cout << j << "\n";
                    for (int k = 0; k < L[j].getLength(); k++){
                        // std::cout << k << "\n";
                        counter++;

                        if(innerList[line]==L[j][k]){
                            // repeticiones++;
                            std::cout << counter << "\n" << " CONTADOS" << "\n";
                        }

                        if(repeticiones>0){
                        }
                        // std::cout << "Final K ";
                    }
                
                    // std::cout << "Final J" << "\n";
                }

                innerList.deleteNode(0);
                
            }
            
        }
    }

    return 0;
    
}