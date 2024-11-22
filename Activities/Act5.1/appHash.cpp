#include <iostream>
#include <sstream>
#include "HashMap.hpp"

/*
PARAMETROS: int& val.
MÉTODO: Verifica que la entrada del usuario sea de tipo int y la regresa en el argumento val.
ORDER: O(1).
RETORNA: bool.
*/
bool aceptaEnteros(int& val){
    std::stringstream buffer(""); 
    std::string tempInput;
    std::getline(std::cin, tempInput);
    buffer<<tempInput; 
    std::cin.clear();
    if(!(buffer >> val)){
        return false; 
    }
    return true;
}


int main(){

    // Caso prueba 1: constructor con parámetros (tamaño de la tabla)
    HashMap<> intHashMap(10);
    std::cout<<"Tamaño "<<intHashMap.capacity()<<"\n";

    for(int i = 0; i < 15; i++){
        intHashMap[rand()] = rand();
    }
    
    intHashMap.show();

    int n = 0; 
    while(std::cout<<"\nNúmero de elementos a insertar en la tabla: " && !aceptaEnteros(n))
    {
        std::cout<<"Error. Solo enteros:\n";
    } 
    try{ 
        HashMap<> myHashMap(n);
        for(int i = 0; i < n; i++){
            int key = 0, value = 0;
            std::cout<<"Inserte el key <int>: "; 
            std::cin>>key;
            std::cout<<"Inserte el valor <int>: ";
            std::cin>>value;
            myHashMap[key] = value;
        }
        myHashMap.show();
    } catch(std::exception& ex){
        std::cout<<"Error: "<< ex.what();
    } 

    HashMap<> otherHash; // constructor por defecto. 
    try{
        int key = 0, value = 0;
        std::cout<<"Inserte el key <int>: "; 
        std::cin>>key;
        std::cout<<"Inserte el valor <int>: ";
        std::cin>>value;
        otherHash.insert(key, value);
        otherHash.show();
    } catch(std::exception& ex){
        std::cout<<"Error: "<< ex.what();
    }

    return 0;
}