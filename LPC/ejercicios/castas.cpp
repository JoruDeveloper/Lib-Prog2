#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <limits>

int main() {
    // List<List<std::string> > L;
    List<std::string> L, LNames;
    List<int> LNumbers, LTimesSelected;
    bool one_alive;
    int cases, N_maxCast, k_steps, t_persons, t_inverted, t_deads, next_steps;


    if(std::cin >> cases){  // leer el número de casos
        std::cin.ignore();

        for (int i_case = 0; i_case < cases; i_case++){ // Para cada caso

            LNames.empty();
            LNumbers.empty();
            LTimesSelected.empty();

            std::cin>>N_maxCast;
            std::cin>>k_steps;
            std::cin>>t_persons;
            // std::cin.ignore();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            readRowToList(L);   // Leer la Lista con {} , []

            // std::cout << L.getLength() << std::endl;
            // std::cout << N_maxCast <<" "<< k_steps <<" "<< t_persons << std::endl;

            for (int i = 0; i < L.getLength(); ++i){
                L.modifyNode(cleanString(L[i],"{}[](),. "), i); // Limpiar la lista
            }

            
            
            for (int i = 0; i < L.getLength(); i+=2){           // Separar la lista en sub-listas relacionadas
                LNames.addElem(L[i], LNames.getLength());                       // Lista de nombres
                LNumbers.addElem(stringToInt(L[i + 1]), LNumbers.getLength());  // Lista de sus Números de Casta
                LTimesSelected.addElem(0, LTimesSelected.getLength());          // Veces seleccionados sin morir
            }
            
            
            // for (int i = 0; i < LNames.getLength(); i++)
            // {
            //     std::cout << LNames.checkPos(i) << std::endl;
            //     std::cout << LNumbers.checkPos(i) << std::endl;
            //     std::cout << LTimesSelected.checkPos(i) << std::endl;
            //     std::cout << std::endl;
            // }
            
            one_alive = false;      // Queda uno vivo?
            int i = 0;              // Iterador de lista
            t_deads = 0;            // Número de muertos
            t_inverted = false;     // Las castas NO están invertidas, Casta menor es superior

            while (!one_alive)      // Mientras no quede uno vivo
            {
                // next_steps = k_steps;   // Establecer los pasos a dar
                // while (next_steps>0)    // Mientras queden pasos
                // {
                //     next_steps--;       // Doy un paso
                //     i = (i % (LNames.getLength() - 1)) + 1; // Avanzo hasta la posición de los pasos
                // }

                if (LNames.getLength() > 1) {
                    // std::cout << i << std::endl;
                    // std::cout << (i + k_steps) % LNames.getLength() << " = ("<< i << " + " << k_steps << ")" << " % " << LNames.getLength()<< " " ;
                    i = (i + k_steps) % LNames.getLength();
                    // std::cout << "      i =" << i;
                    // std::cout << "       "<< LNames.checkPos(i) << i << std::endl;
                } else {
                    one_alive = true;
                    continue;
                }

                if (t_inverted){        // Si las castas están invertidas
                    if ((LNumbers[i] <= findMin(LNumbers))){ // Y el elemento NO es el mayor
                        // std::cout << LNames.checkPos(i) << std::endl; // PARA DEPURAR
                        LNames.deleteNode(i);           // Elimino sus nodos relacionados (Muere)
                        LNumbers.deleteNode(i);
                        LTimesSelected.deleteNode(i);
                        t_deads++;                      // Agrego 1 al contador de muertes
                    }else{                              // Si el elemento SI es el mayor se puede salvar
                        if (LTimesSelected[i] > t_persons)  // Si ha sido seleccionado más veces de las permitidas
                        {
                            LNames.deleteNode(i);           // Elimino sus nodos relacionados (Muere)
                            LNumbers.deleteNode(i);
                            LTimesSelected.deleteNode(i);
                            t_deads++;                  // Agrego 1 al contador de muertes
                        }else{                              // Si aun puede ser seleccionado
                            LTimesSelected.modifyNode(LTimesSelected[i] + 1, i);    // Se aumenta el contador de selec
                        }
                    }
                }else{                  // Si las castas NO están invertidas
                    if ((LNumbers[i] >= findMax(LNumbers))){ //Y el elemento NO es el menor
                        LNames.deleteNode(i);           // Elimino sus nodos relacionados (Muere)
                        LNumbers.deleteNode(i);
                        LTimesSelected.deleteNode(i);
                        t_deads++;                      // Agrego 1 al contador de muertes
                    }else{                                  // Si el elemento SI es el menor
                        if (LTimesSelected[i] > t_persons)  // Si ha sido seleccionado más veces de las permitidas
                        {
                            LNames.deleteNode(i);           // Elimino sus nodos relacionados (Muere)
                            LNumbers.deleteNode(i);
                            LTimesSelected.deleteNode(i);
                            t_deads++;                      // Agrego 1 al contador de muertes
                        }else{                                          // Si aun puede ser seleccionado
                            LTimesSelected.modifyNode(LTimesSelected[i] + 1, i);    // Se aumenta el contador de selec
                        }
                    }
                }
                
                if (t_deads == t_persons){   // Si se alcanza el límite de personas que pueden morir
                    t_inverted = !t_inverted;   // Se invierten las castas
                    t_deads = 0;                // Se reinicia el contador de muertos
                }
                
                if (LNumbers.getLength()==1) one_alive = true;  // Si queda solo un supervivente
                // i = i % LNames.getLength();
                
            }

            std::cout << LNames.checkPos(0) << std::endl;
        }
    }
}