#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>

int main() {
    // List<List<std::string> > L;
    List<std::string> L, LNames;
    List<int> LNumbers;
    bool one_alive;
    int cases, counter, N_maxCast, k_steps, t_persons, t_inverted, t_deads, next_steps;


    if(std::cin >> cases){  // leer el número de casos
        std::cin.ignore();

        for (int i_case = 0; i_case < cases; i_case++){ // Para cada caso

            std::cin>>N_maxCast;
            std::cin>>k_steps;
            std::cin>>t_persons;
            std::cin.ignore();
            readRowToList(L);   // Lista con {} , []
            
            
            for (int i = 0; i < L.getLength(); ++i){
                L.modifyNode(cleanString(L[i],"{}[](),. "), i); // Lista limpia
            }
            
            for (int i = 0; i < L.getLength(); i+=2){
                LNames.addElem(L[i], LNames.getLength());
                LNumbers.addElem(stringToInt(L[i + 1]), LNumbers.getLength());
            }
            
            one_alive = false;
            int i = 0;
            t_deads = 0;

            while (!one_alive)
            {
                next_steps = k_steps;
                while (next_steps>0)
                {
                    next_steps--;
                    i = (i % (LNames.getLength() - 1)) + 1;
                }

                if (t_inverted){
                    if (!(LNumbers[i] >= findMax(LNumbers))){ // El elemento no es el mayor
                        LNames.deleteNode(i);
                        LNumbers.deleteNode(i);
                        t_deads++;
                    }
                }else{
                    if (!(LNumbers[i] <= findMin(LNumbers))){ //El elemento no es el menor
                        LNames.deleteNode(i);
                        LNumbers.deleteNode(i);
                        t_deads++;
                    }
                }

                if (t_deads = t_persons){
                    t_inverted = !t_inverted;
                    t_deads = 0;
                    }
                
                
                if (LNumbers.getLength()==1) one_alive = true;
                
            }
        }
    }
}