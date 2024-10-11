#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "BaseLL.hpp"
#include "algoritmos.cpp"

/*

std::string lastIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }
    for (int i=numsIP-1; i>0; i--){
        if(arr[i] != 0){
            arr[i]=arr[i]-=1;
            return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]);
        } else if(arr[i]<=0){
            arr[i]=0;
            arr[i-1]-=1;
        }
    }
    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]);

}

std::string nextIP(std::string& ip){
    std::stringstream ssCurrentIP(ip);
    int numsIP=4;
    int arr[4];
    for (int i=0; i<numsIP; i++){
        ssCurrentIP>>arr[i];
        ssCurrentIP.ignore();
    }
    for (int i=numsIP-1; i>0; i--){
        if(arr[i] != 999){
            arr[i]=arr[i]++;
            return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]);
        } else if(arr[i]>=255){
            arr[i]=255;
            arr[i-1]++;
        }
    }
    return std::to_string(arr[0])+"."+std::to_string(arr[1])+"."+std::to_string(arr[2])+"."+std::to_string(arr[3]);
}
*/
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

    ordMerge(linkedList, linkedList.length());
    std::string ipInicial, ipFinal;

    std::cout<<"Ingresa a partir de cuál IP se desea filtrar: ";
    std::cin>>ipInicial;
    ipInicial=lastIP(ipInicial);

    std::cout<<"Ingrese la mayor IP que se desea mostrar: ";
    std::cin>>ipFinal;
    ipFinal=nextIP(ipFinal);

    int posInic=busquedaBinaria(linkedList, ipInicial), posFin=busquedaBinaria(linkedList, ipFinal);
    
    std::ofstream bitacoraOut("bitacoraOut.txt");

    class DoubleLL<std::string>::Iterator it=linkedList.begin()+posInic, itFinal= linkedList.begin()+posFin;

    if(!bitacoraOut.is_open()){
        std::cerr << "No se pudo abrir el documento bitacoraOut.txt" << std::endl;
        return 1;
    } else if (posInic <= posFin){

        while(it != itFinal){
            bitacoraOut << *it << std::endl;
            ++it;
        }

        bitacoraOut.close();
    }

    return 0;

}