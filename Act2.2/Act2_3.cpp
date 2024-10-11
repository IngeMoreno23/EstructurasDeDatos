#include <iostream>
#include <fstream>
#include "HDCLinkedList.cpp"

int main(){
    HDCLinkedList<std::string> casoPrueba({"Jun 5 04:12:47 1.6.378.65:6772 Failed password for root", "Jun 20 15:08:11 1.36.968.91:4437 Failed password for root"});
    casoPrueba.print();
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

    //
    casoPrueba.ordMerge(casoPrueba, casoPrueba.length());
    casoPrueba.print();
    //
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
    bitacoraOut.close();
    
    return 0;
}