#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main() {
    List<List<std::string> > L;
    int columns, counter;

    if (std::cin >> columns && columns > 0) {
        std::cin.ignore();
        for (int i = 0; i < columns; ++i) {
            List<std::string> columnList;
            L.addElem(columnList, i);
        }

        std::string linea;
        while (std::getline(std::cin, linea)) {
            if (linea.empty()) continue;
            std::istringstream ss(linea);
            std::string apodo;
            int current_col_index = 0;

            while (ss >> apodo && current_col_index < columns) {

                    List<std::string>& target_column_list = L.getElemRefAt(current_col_index);

                    target_column_list.addElem(apodo, target_column_list.getLength());

                current_col_index++;
            }
        }

        // Contar Azotes
        for (int i = 0; i < L.getLength(); ++i) {   // Columna

            List<std::string> &current_column = L.getElemRefAt(i);
            counter = 0;

            for (int j = 0; j < current_column.getLength(); ++j){

                std::string e = current_column.checkPos(j);

                for (int k = j + 1; k < current_column.getLength(); ++k){
                    if (e == current_column.checkPos(k)){

                        counter += k - j - 1;
                        break;

                    }
                }
            }
                 std::cout << counter << std::endl;
        }

    } 

    return 0;
}