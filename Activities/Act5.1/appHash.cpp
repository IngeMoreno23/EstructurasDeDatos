#include <iostream>
#include "..\..\DataStructures\Map\HashMap.hpp"

int main(){
    HashMap<> intHashMap(10);
    std::cout<<"Tamaño "<<intHashMap.capacity()<<"\n";
    intHashMap.show();
}