#include "HashMap.hpp"
    
int main(){

    HashMap<std::string, int> map(65536);
    map.insert("0.0.0.0", 10);
    // Si insertamos en el octeto 0011 1100, seria en decimal 60
    // El hash dará 60 % tableSize
    map.insert("0.0.0.60", 20);


    return 0;
}