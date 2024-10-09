#include <iostream>
#include <fstream>
#include "HDCLinkedList.cpp"

int main(){
    std::ifstream bitacoraIn("bitacora.txt");
    HDCLinkedList<std::string> linkedList;

    if(!bitacoraIn.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    } else {
        std::string line;
        while(std::getline(bitacoraIn, line)){
            linkedList.append(line);
        }
        bitacoraIn.close();
    }

    linkedList.ordMerge(linkedList, linkedList.length());

    std::ofstream bitacoraOut("bitacoraOut.txt");
    if(!bitacoraOut.is_open()){
        std::cerr << "No se pudo abrir el documento bitacoraOut.txt" << std::endl;
        return 1;
    } else {
        auto it = linkedList.begin();
        do{
            bitacoraOut << *it << std::endl;
            ++it;
        } while(it != linkedList.end());

        bitacoraOut.close();
    }
    return 0;
}