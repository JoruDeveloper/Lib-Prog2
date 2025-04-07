#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>

int main() {
    List<List<std::string> > L;
    List<std::string> LAux;
    bool flag;
    int counter;

    readColumnsToList<std::string>(L);

        // for (int i = 0; i < L.getLength(); ++i) {
            
        //     List<std::string>& current_column = L.getElemRefAt(i);

        //     for (int j = 0; j < current_column.getLength(); ++j) {
        //         std::cout << current_column.checkPos(j);
        //     }

        // }

    counter = 0;

    for (int i = 0; i < L.getLength(); ++i)
    { // Columna

        List<std::string> &current_column = L.getElemRefAt(i);

        LAux.empty();
        flag = false;

        for (int j = 1; j < current_column.getLength(); ++j){

            
            if (stringToInt(current_column.checkPos(j)) > stringToInt(current_column.checkPos(j - 1))){
                LAux.addElem(current_column.checkPos(j), LAux.getLength());
            }

        }

        if (!LAux.isEmpty())
        {
            for (int j = 0; j < LAux.getLength(); ++j)
            {
                current_column.delete_first_elem(LAux.checkPos(j));
            }
            i--;
            counter++;
        }
        else
        {
            std::cout << counter << std::endl;
            counter = 0;
        }

    }
}