#include <iostream>
#include "..\..\DataStructures\Map\HashMap.hpp"

int main(){
    HashMap<> intHashMap(10);
    std::cout<<"Tamaño "<<intHashMap.capacity()<<"\n";
    intHashMap.show();
    intHashMap[2] = 4;
    intHashMap.show();

    intHashMap.eliminate(2);
    intHashMap.show();
}