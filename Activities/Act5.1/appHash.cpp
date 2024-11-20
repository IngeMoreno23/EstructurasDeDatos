#include <iostream>
#include "..\..\DataStructures\Map\HashMap.hpp"

int main(){
    HashMap<> intHashMap(10);
    std::cout<<"Tamaño "<<intHashMap.capacity()<<"\n";
    intHashMap.show();
    intHashMap[2] = 10;
    intHashMap.show();
    intHashMap[13] = 4;
    intHashMap.show();
}