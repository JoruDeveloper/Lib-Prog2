#include "list.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <typeinfo>

int main() {
    // List<List<std::string> > L;
    List<std::string> L;
    bool flag;
    int cases, counter, N_maxCast, k_steps, t_persons;


    if(std::cin >> cases){  // leer el número de casos


        for (int i_case = 0; i_case < cases; i_case++){
            
            readRowToList(L);   // lista con {} , []
            
            counter = 0;
            
            for (int i = 0; i < L.getLength(); ++i){
                
            }
        }
    }
}