/*  Act3.4
Cristian Ricardo Luque Arámbula - A01741850
Oliver Moreno Ibarra - A01742930
Rodolfo Blas Romero Valdez - A01741665
Última modificación: 28/10/2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

#include "..\..\DataStructures\List\DoubleLL.hpp"
#include "..\..\DataStructures\Tree\SplayTree\SplayTree.hpp"

#include "ipHandler.cpp"
#include "parameterConfiguration.cpp"

int main(){
    // 1. Leer el archivo bitacora.txt
    std::ifstream myBitacora("bitacora.txt");
    if(!myBitacora.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    }

    // 2. Crear una lista doblemente ligada con los registros de la bitácora
    std::string myLine;
    DoubleLL<std::string> myBitacoraList;
    while(std::getline(myBitacora, myLine)){
        myBitacoraList.append(myLine);
    }
    myBitacora.close();

    // 3. Ordenar la lista con el algoritmo Merge Sort
    ordMerge(myBitacoraList, myBitacoraList.begin(), myBitacoraList.length());
    myBitacoraList.print();
    std::cout << "\n\n\n\n\n";

    // 4. Separar la lista por frecuencia de IP en un mapa
    std::map<int, DoubleLL<std::string>> myMap;
    DoubleLL<std::string> temp;
    temp.clear();
    for(auto it = myBitacoraList.begin(); it != myBitacoraList.end(); ++it){
        if(!temp.isEmpty() && obtainIp(*temp.end()) != obtainIp(*it)){
            myMap[temp.length()] = temp;
            temp.clear();
        }
        temp.append(*it);
    }
    // Añadir la ultima lista
    if (! temp.isEmpty()) {
        myMap[temp.length()] = temp;
    }

    // 5. Crear un struct con frecuencia y las 5 (dato guardado como NUM_IP_SHOW) ips más frecuentes
    IpFreq myIpFreq[NUM_IP_SHOW];
    int i = 0;
    for (auto& [key, value] : myMap){
        if (i < 5){
            myIpFreq[i].freq = key;
            myIpFreq[i].ip = obtainIp(*value.begin());
            i++;
        }
    }
    for(int i=0; i < NUM_IP_SHOW; i++){
        std::cout << "Frecuencia: " << myIpFreq[i].freq << " IP: " << myIpFreq[i].ip << std::endl;
    }

    // 6. Crear un árbol splay con las ips
    SplayTree<IpFreq> mySplayTree;
    for(int i=0; i < NUM_IP_SHOW; i++){
        mySplayTree.insert(myIpFreq[i]);
    }

/*
    // 7. Imprimir el árbol
    std::cout << "\n";
    std::cout << "InOrder:\n";
    mySplayTree.inOrder();
    std::cout << "PreOrder:\n";
    mySplayTree.preOrder();
    std::cout << "PostOrder:\n";
    mySplayTree.postOrder();
*/

    // 7. Crear 3 arboles, para clase A, B y C
    SplayTree<IpFreq> mySplayTreeA; // 0.0.0.0 - 127.255.255.255
    SplayTree<IpFreq> mySplayTreeB; // 128.0.0.0 - 191.255.255.255
    SplayTree<IpFreq> mySplayTreeC; // 192.0.0.0 - 223.255.255.255

    // 8. Insertar en los arboles todas las ips correspondientes
    for(auto& [key, value] : myMap){
        std::string ip = obtainIp(*value.begin());
        IpFreq classIpFrec;
        classIpFrec.freq = key;
        classIpFrec.ip = ip;
        if(ip == "") continue;
        int ip1 = std::stoi(ip.substr(0, ip.find('.')));
        if (ip1 >= 0 && ip1 <= 127){
            mySplayTreeA.insert(classIpFrec);
        } else if (ip1 >= 128 && ip1 <= 191){
            mySplayTreeB.insert(classIpFrec);
        } else if (ip1 >= 192 && ip1 <= 223){
            mySplayTreeC.insert(classIpFrec);
        }
    }

    // 9. Imprimir los arboles
    std::cout << "\n";
    std::cout << "Mayor a menor A:\n";
    mySplayTreeA.inReverseOrder();
    std::cout << "Mayor a menor B:\n";
    mySplayTreeB.inReverseOrder();
    std::cout << "Mayor a menor C:\n";
    mySplayTreeC.inReverseOrder();
    

    // -----------------------------------
    return 0;
}