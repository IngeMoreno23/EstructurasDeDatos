/*  Act3.4
Cristian Ricardo Luque Arámbula - A01741850
Oliver Moreno Ibarra - A01742930
Rodolfo Blas Romero Valdez - A01741665
Última modificación: 20/11/2024
*/

#include <iostream>
#include <fstream>
#include <string>   
#include <sstream>

#include "HashMap.hpp"
#include "ipHandler.cpp"

int main(){
    // LECTURA DE DATOS 
    std::ifstream myBitacora("bitacora.txt");
    if(!myBitacora.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    }

    std::string myLine;
    std::stringstream sstr;

    std::getline(myBitacora, myLine);
    sstr.str(myLine);
    size_t vertices, connections;   
    sstr>>vertices>>connections;
    HashMap<std::string, IpFreq> adj(vertices);

    // SALTO DE LÍNEAS
    for(int i = 0; i < vertices; i++){
        std::getline(myBitacora, myLine);
        adj[myLine] = IpFreq(myLine);
    }
    
    std::pair<std::string, std::string> ipOrDest;
    for(int i = 0; i < connections; i++){
        std::getline(myBitacora, myLine);
        ipOrDest = obtainIp(myLine);
        adj[ipOrDest.first].destIps.push_back(ipOrDest.second);
        ++adj[ipOrDest.first].fanOut;
        ++adj[ipOrDest.second].fanIn;
    }

    adj["224.182.134.50"].visualize();
    adj["36.66.160.248"].visualize();
    adj["1.111.91.45"].visualize();
}