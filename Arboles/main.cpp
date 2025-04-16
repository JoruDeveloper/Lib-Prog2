#include <iostream>
#include <list>
#include <string>
#include <exception>
#include "bin_tree.h"
#include <sstream>
#include <limits> // Necesario para std::numeric_limits

// Tu función printList (sin cambios)
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

    BinTree<std::string> treeCase; 
    int cases = 0, n_trees = 0, height, distance, count_MUP, max_MUP;
    std::string line1, line2, line_alumn, firstOrder, secondOrder, value;
    std::list<std::string> LInorden, LPreorden, LPostorden, LAlumn;

    if (!(std::cin >> cases)) {
         std::cerr << "Error al leer el numero de casos." << std::endl;
         return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (int i = 0; i < cases; i++) {

        max_MUP = 0;

        if (!(std::cin >> n_trees)) {
            std::cerr << "Error al leer el numero de arboles" << i + 1 << std::endl;
            return 1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (int j = 0; j < n_trees; j++) {

            LInorden.clear();
            LPreorden.clear();
            LPostorden.clear();
            LAlumn.clear();

            treeCase.makeEmpty();

            if (!std::getline(std::cin, line1) || line1.empty()) {
                 std::cerr << "Error al leer la primera linea de orden o esta vacia." << std::endl;
                 return 1;
            }
            std::istringstream ss1(line1);
            ss1 >> firstOrder;

            if (!std::getline(std::cin, line2) || line2.empty()) {
                 std::cerr << "Error al leer la segunda linea de orden o esta vacia." << std::endl;
                 return 1;
            }
            std::istringstream ss2(line2);
            ss2 >> secondOrder;

            if (firstOrder == "INORDEN") {
                while (ss1 >> value) { LInorden.push_back(value); }
            } else if (firstOrder == "PREORDEN") {
                while (ss1 >> value) { LPreorden.push_back(value); }
            } else if (firstOrder == "POSTORDEN") {
                while (ss1 >> value) { LPostorden.push_back(value); }
            } else {
                std::cerr << "Error: Orden desconocido en la primera linea: " << firstOrder << std::endl;
                return 1;
            }

            if (secondOrder == "INORDEN") {
                while (ss2 >> value) { LInorden.push_back(value); }
            } else if (secondOrder == "PREORDEN") {
                while (ss2 >> value) { LPreorden.push_back(value); }
            } else if (secondOrder == "POSTORDEN") {
                while (ss2 >> value) { LPostorden.push_back(value); }
            } else {
                 std::cerr << "Error: Orden desconocido en la segunda linea: " << secondOrder << std::endl;
                 return 1;
            }

            if (LInorden.empty() || (LPreorden.empty() && LPostorden.empty())) {
                 std::cerr << "Error: No se pudo leer INORDEN y PREORDEN/POSTORDEN correctamente." << std::endl;
                 return 1;
            }
             if (!LPreorden.empty() && !LPostorden.empty()) {
                 std::cerr << "Error: Se leyeron PREORDEN y POSTORDEN para el mismo arbol." << std::endl;
                 return 1;
            }

            if (!std::getline(std::cin, line_alumn) || line_alumn.empty()) {
                 std::cerr << "Error al leer la linea de alumnos o esta vacia." << std::endl;
                 return 1;
            }
            std::istringstream ss_alumn(line_alumn);
            while (ss_alumn >> value) {
                LAlumn.push_back(value);
            }

            if (!LPreorden.empty())
            {
                treeCase.buildFromPreIn(LPreorden, LInorden);

            }else{
                treeCase.buildFromPostIn(LPostorden, LInorden);
            }

            count_MUP = 0;
            distance = 0;
            height = 0;

            for (std::list<std::string>::iterator i = LAlumn.begin(); i != LAlumn.end(); ++i) {
                for (std::list<std::string>::iterator j = i; j != LAlumn.end(); ++j) {
                    if (i == j) continue;

                    distance = treeCase.findPathBetweenNodes(*i,*j).size() - 2;
                    height = treeCase.getHeightDifference(*i,*j);

                    count_MUP += distance * height;


                }
            }

            if(count_MUP > max_MUP){
                max_MUP = count_MUP;
            }

            

        }

        std::cout << max_MUP << std::endl;

    }

    return 0;
}