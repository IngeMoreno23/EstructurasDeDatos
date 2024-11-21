#include <iostream>
#include "HashMap.hpp"

int main(){

    // Caso prueba 1: constructor con parámetros (tamaño de la tabla)
    HashMap<> intHashMap(10);
    std::cout<<"Tamaño "<<intHashMap.capacity()<<"\n";
    intHashMap.show();

    // Caso prueba 2: hash()
    intHashMap[13] = 10;
    intHashMap.show();

    // Caso prueba 3: hash() con reacomodo lineal
    intHashMap[2] = 4;
    intHashMap.show();

    // Caso prueba 4: insert(), con recorrido sobre una celda eliminada
    intHashMap.eliminate(2);
    intHashMap.show();

    intHashMap.insert(3,4);
    intHashMap.show();

    intHashMap.insert(3,6);
    intHashMap.show();

    for(int i = 0; i < 15; i++){
        intHashMap[i] = rand();
        intHashMap.show();
    }
    
    intHashMap.show();
    return 0;
}