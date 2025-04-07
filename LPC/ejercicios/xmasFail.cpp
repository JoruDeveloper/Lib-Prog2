#include "list.h"
#include <iostream>
#include <string>

int main() {
    List<List<std::string> > L;
    List<std::string> tempList;

    int columns, i, j, aux1, aux2;
    std::string apodo;

    if(std::cin >> columns){
        std::cin.ignore();
        i = 0;

        while(true){
            tempList.empty();
            j = 0;


            while ((j < columns)&&(std::cin >> apodo)){
                tempList.addElem(apodo, tempList.getLength());
                j++;
            }

            if (tempList.isEmpty()) break;

            L.addElem(tempList, i);
            i++;

            if (std::cin.fail()) {
                std::cin.clear(); // Restablecer si hubo error (ej: línea incompleta)
            }
            while (std::cin.peek() != '\n' && !std::cin.eof()) {
                std::cin.ignore(); // Limpiar caracteres extras
            }
            if (!std::cin.eof()) std::cin.ignore(); // Ignorar el '\n'
        }

        for (int i = 0; i < L.getLength(); ++i) {
            std::cout << "Fila " << i << " (" << L[i].getLength() << " palabras): \n";
            for (int j = 0; j < L[i].getLength(); ++j) {
                std::cout << L[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}
