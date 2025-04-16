#include <iostream>
#include <list>
#include <string>
#include <exception>
#include "bin_tree.h"
#include <sstream>
#include <limits>

template <class T>
void printList(const std::list<T>& l, const std::string& title) {
    std::cout << title << ": [";
    typename std::list<T>::const_iterator it = l.begin();
    while (it != l.end()) {
        std::cout << *it;
        ++it;
        if (it != l.end()) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

int main() {

    BinTree<std::string> treeCase;                                          // Declaración de clases
    int cases = 0, n_trees = 0, height, distance, count_MUP, max_MUP;
    std::string line1, line2, line_alumn, firstOrder, secondOrder, value;
    std::list<std::string> LInorden, LPreorden, LPostorden, LAlumn;

    if (!(std::cin >> cases)) {         // Leer el número de casos
         std::cerr << "Error al leer el numero de casos." << std::endl;
         return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < cases; i++) {   // Ciclo para el número de casos
        max_MUP = 0;

        if (!(std::cin >> n_trees)) {   // Leer el número de secciones
            std::cerr << "Error al leer el numero de secciones" << std::endl;
            return 1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int j = 0; j < n_trees; j++) { // Ciclo para el número de secciones

            LInorden.clear();       // Limpiar todas las listas
            LPreorden.clear();
            LPostorden.clear();
            LAlumn.clear();

            treeCase.makeEmpty();   // Limpiar el arbol

            if (!std::getline(std::cin, line1)) {       // Leer Primera línea del caso
                 std::cerr << "Error Linea 1" << std::endl;
                 return 1;
            }

            std::istringstream ss1(line1);
            ss1 >> firstOrder;

            if (!std::getline(std::cin, line2)) {       // Leer segunda línea del caso
                 std::cerr << "Error Linea 2" << std::endl;
                 return 1;
            }

            std::istringstream ss2(line2);
            ss2 >> secondOrder;

            if (firstOrder == "INORDEN"){   // Primera linea inorden
                while (ss1 >> value){
                    LInorden.push_back(value); 
                }
            } else if (firstOrder == "PREORDEN"){
                while (ss1 >> value){
                    LPreorden.push_back(value); 
                    }
            } else if (firstOrder == "POSTORDEN"){
                while (ss1 >> value){
                    LPostorden.push_back(value);
                }
            } else 
                return 1;

            if (secondOrder == "INORDEN"){  // Segunda linea inorden
                while (ss2 >> value){
                    LInorden.push_back(value);
                }
            } else if (secondOrder == "PREORDEN"){
                while (ss2 >> value){
                    LPreorden.push_back(value);
                }
            } else if (secondOrder == "POSTORDEN"){
                while (ss2 >> value){
                    LPostorden.push_back(value);
                }
            } else
                 return 1;

            if (!std::getline(std::cin, line_alumn)) {  // Leer Linea alumnos para MUP
                 std::cerr << "Error Linea Alumnos" << std::endl;
                 return 1;
            }

            std::istringstream ss_alumn(line_alumn);    // Insertar valores a la lista
            while (ss_alumn >> value) {
                LAlumn.push_back(value);
            }

            if (!LPreorden.empty())                     // Insertar en Preorden o en Postorden
            {
                treeCase.buildFromPreIn(LPreorden, LInorden);

            }else{
                treeCase.buildFromPostIn(LPostorden, LInorden);
            }

            count_MUP = 0;
            distance = 0;
            height = 0;

            // printTreeStructure(treeCase);

            for (std::list<std::string>::iterator i = LAlumn.begin(); i != LAlumn.end(); ++i){  // Calcular MUP
                for (std::list<std::string>::iterator j = i; j != LAlumn.end(); ++j) {
                    if (i == j) continue;

                    distance = treeCase.findPathBetweenNodes(*i,*j).size() - 2;
                    height = treeCase.getHeightDifference(*i,*j);

                    count_MUP += distance * height;

                    // std::cout << "Distancia de " << *i << " hasta "<< *j << " = "<< distance << std::endl;
                    // std::cout << "Altura de " << *i << " hasta "<< *j << " = "<< height << std::endl;
                    // std::cout << "MUP = "<< count_MUP << std::endl;
                }
            }

            if(count_MUP > max_MUP){        // Asignar nuevo MUP máximo si es mayor al actual
                max_MUP = count_MUP;
            }

        }

        std::cout << max_MUP << std::endl;  // Imprimir el MUP mayor

    }

    return 0;
}

