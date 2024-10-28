#include <iostream>
#include "..\..\List\DoubleLL.hpp"

int main(){
// -----------------------------------

    std::cout << "\n\n";
    std::cout << "Oliver \n\n" << std::endl;
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
    std::map<int, DoubleLL<std::string>, std::greater<int>> myMap;
    DoubleLL<std::string> temp;
    temp.empty();
    for(auto it=myBitacoraList.begin(); it!=myBitacoraList.end(); ++it){
        if(!temp.isEmpty() && obtainIp(*temp.end()) != obtainIp(*it)){
            myMap[temp.length()] = temp;
            temp.empty();
        }
        temp.append(*it);
    }
    // Añadir la ultima lista
    if (!temp.isEmpty()) {
        myMap[temp.length()] = temp;
    }

    // for(auto& [key, value] : myMap){
    //     std::cout << "Key: " << key << "\nValue:\n";
    //     value.print();
    //     std::cout << "\n";
    // }


    // 5. Crear un struct con frecuencia y ip de las 5 ips más frecuentes

    IpFreq myIpFreq[5];
    int i = 0;
    for (auto& [key, value] : myMap){
        if (i < 5){
            myIpFreq[i].freq = key;
            myIpFreq[i].ip = obtainIp(*value.begin());
            i++;
        }
    }
    for(int i=0; i<5; i++){
        std::cout << "Frecuencia: " << myIpFreq[i].freq << " IP: " << myIpFreq[i].ip << std::endl;
    }

    // 6. Crear un árbol splay con las ips

    SplayTree<IpFreq> mySplayTree;
    for(int i=0; i<5; i++){
        mySplayTree.insert(myIpFreq[i]);
    }

    // 7. Imprimir el árbol en inOrder
    std::cout << "\n";
    std::cout << "InOrder:\n";
    mySplayTree.inOrder();
    std::cout << "PreOrder:\n";
    mySplayTree.preOrder();
    std::cout << "PostOrder:\n";
    mySplayTree.postOrder();



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

}