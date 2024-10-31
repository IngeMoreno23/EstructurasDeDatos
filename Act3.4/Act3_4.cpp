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

#include "List\DoubleLL.hpp"
#include "SplayTree\SplayTree.hpp"

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
    // myBitacoraList.print(); // Se puede imprimir para comprobar el orden
    // std::cout << "\n\n\n\n\n";

    // 4. Separar la lista por frecuencia de IP en un árbol desplegado
    SplayTree<IpFreq> ipTree;
    DoubleLL<std::string> temp;
    temp.clear();
    for(auto it = myBitacoraList.begin(); it != myBitacoraList.end(); ++it){
        if(!temp.isEmpty() && obtainIp(*temp.end()) != obtainIp(*it)){
            IpFreq current = IpFreq(temp.length(), temp);
            ipTree.insert(current); 
            temp.clear();
        }
        temp.append(*it);
    }

    // Añadir la ultima lista
    if (! temp.isEmpty()) {
        ipTree.insert(IpFreq(temp.length(), temp));
    }

    // 7. Crear 3 arboles, para clase A, B y C
    SplayTree<IpFreq> ipTreeA, ipTreeB, ipTreeC; 

    // 8. Insertar en los arboles todas las ips correspondientes  
ipTree.inReverseOrder([&ipTreeA, &ipTreeB, &ipTreeC](auto& ipAccFreq) {
    std::string ip = ipAccFreq.ip;
    if(ip.empty()) return true;
    
    IpFreq classIpFreq(ipAccFreq.freq, ipAccFreq.ipLL);
    int ip1 = std::stoi(ip.substr(0, ip.find('.')));
    
    if (ip1 >= 0 && ip1 <= 127) {
        ipTreeA.insert(classIpFreq);
    } else if (ip1 >= 128 && ip1 <= 191) {
        ipTreeB.insert(classIpFreq);
    } else if (ip1 >= 192 && ip1 <= 223) {
        ipTreeC.insert(classIpFreq);
    }
    return true; 
});

    // 9. Imprimir los arboles
    std::cout << "Mayor a menor A:\n";
    ipTreeA.inReverseOrder();
    std::cout << "\nMayor a menor B:\n";
    ipTreeB.inReverseOrder();
    std::cout << "\nMayor a menor C:\n";
    ipTreeC.inReverseOrder();
    

    // -----------------------------------
    return 0;
}