#include <iostream>
#include <fstream>

int main(){
    std::ifstream bitacoraIn("bitacora.txt");
    HDCLinkedList<string> linkedList();

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

    
    return 0;
}