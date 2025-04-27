#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

int main() {
    List<List<std::string> > L;
    List<int> LnumeroCasos;
    std::string casos;
    int columns;

    if (std::cin >> columns && columns > 0) {   // Leo el número de columnas
        std::cin.ignore();

        for(int i = 0; i < columns;++i){        // Leo k para todos los casos y los almaceno en mi lista numero de casos
            std::cin >> casos;
            std::cin.ignore();
            LnumeroCasos.addElem(stringToInt(casos), LnumeroCasos.getLength());
        }

        for (int i = 0; i < columns; ++i) {     // Almaceno cada columna como una sub-lista de mi lista de listas L
            List<std::string> columnList;
            L.addElem(columnList, i);
        }

        std::string linea;
        while (std::getline(std::cin, linea)) { // Lleno de contenido las sub-listas
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

        for(int i = 0; i < columns ; ++i){      // Inicia mi algoritmo para n columnas ( colums = n )

            List<std::string> columnList = L.getElemRefAt(i);   // Inicializo la sub-lista de cada columna en columnList
            bool one_alive = false;                             // Declaro que NO hay solo 1 vivo
            bool is_inverted = false;                           // Declaro que mi bandera NO está invertida
            int pos = 0;                                        // Declaro la posición de inicio
            while(!one_alive){

                if(columnList.getLength()>1){                   // La lista aún tiene elementos

                    if(!is_inverted){
                        pos = (pos + LnumeroCasos[i] ) % columnList.getLength();    // Avanzo k posiciones
                        
                    }else{
                        pos = (pos - LnumeroCasos[i]);

                        while(pos<0){
                            pos = columnList.getLength() + pos;                     // Retrocedo k posiciones
                        }

                    }

                    columnList.deleteNode(pos);         // Elimino el nodo seleccionado
                    is_inverted = !is_inverted;         // Invierto mi bandera

                }else{                                          // La lista ya NO tiene elementos
                    one_alive = true;
                }

            }

            std::cout<<columnList.checkPos(0)<<std::endl;   // Imprimo el resultado
            columnList.empty();                             // Vacío la lista por si acaso
        }

    } 

    L.empty();              // Vacío las listas por si acaso
    LnumeroCasos.empty();

    return 0;
}