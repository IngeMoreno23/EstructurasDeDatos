#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>

#include "BaseLL.hpp"
#include "SimpleLL.hpp"
#include "algoritmos.cpp"

std::string lastIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }

    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]-1);

}

std::string nextIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }

    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]+1);
}

int main(){
    std::ifstream bitacoraIn("bitacora.txt");
    DoubleLL<std::string> linkedList;

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

    DoubleLL<std::string>::Iterator itHalf=linkedList.begin()+linkedList.length()/2;
    ordMerge(linkedList, itHalf, linkedList.length());
    std::string ipInicial, ipFinal;

    std::cout<<"Ingresa a partir de cuál IP se desea filtrar: ";
    std::cin>>ipInicial;
    ipInicial=lastIP(ipInicial);

    std::cout<<"Ingrese la mayor IP que se desea mostrar: ";
    std::cin>>ipFinal;
    ipFinal=nextIP(ipFinal);
        
    int posInic=busquedaBinaria(linkedList, ipInicial), posFin=busquedaBinaria(linkedList, ipFinal);
    class DoubleLL<std::string>::Iterator it=linkedList.begin()+posInic, itFinal= linkedList.begin()+posFin;
    if(posInic != posFin && !(it != itFinal)){
        --itFinal;
    }
    std::map <int, DoubleLL<std::string>, std::greater<int>> frequenceLists;
    std::ofstream bitacoraOut("bitacoraOut.txt");
    std::ofstream bitacoraOutAccessDesc("bitacoraOutAccessDesc.txt");

    if(!bitacoraOut.is_open()){
        std::cerr << "No se pudo abrir el documento bitacoraOut.txt" << std::endl;
        return 1;
    } else if (posInic <= posFin){
        DoubleLL<std::string> temp; 
        while(it != itFinal){
            temp.append(*it);
            bitacoraOut << *it << std::endl;
            ++it;
            if(*temp.end() != *it){
                frequenceLists[temp.length()].merge(temp);
            }
        }
        for(auto& element: frequenceLists){
            bitacoraOutAccessDesc<<element.second.turnToText();
        }
        bitacoraOut.close();
        bitacoraOutAccessDesc.close();        
    }

    return 0;

}