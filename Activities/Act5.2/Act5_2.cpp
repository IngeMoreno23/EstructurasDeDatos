/*  Act3.4
Cristian Ricardo Luque Arámbula - A01741850
Oliver Moreno Ibarra - A01742930
Rodolfo Blas Romero Valdez - A01741665
Última modificación: 15/11/2024
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

    // REALIZACIÓN DEL GRAFO
    HashMap<std::string, IpFreq> adj;
    for(int i = 0; i < vertices; i++){
        std::getline(myBitacora, myLine);
        adj[myLine];
    }

    // ADICIÓN DE ARCOS Y BÚSQUEDA DE INFORMACIÓN (para agregar los fanIns)
    std::pair<std::string, std::string> ipOrDest;
    for(int i = 0; i < connections; i++){
        std::getline(myBitacora, myLine);
        ipOrDest = obtainIp(myLine);
        adj[ipOrDest.first].adjacencyList.append(ipOrDest.second);
        adj[ipOrDest.first].fanOut++;
        adj[ipOrDest.second].fanIn++;
    }

    /*
    // VISUALIZACIÓN DE HASH.
    int columnMax = 3, columnCount = 1; // Solo para que se visualicen varias ips en una misma línea
    for(const auto& vertex:adj){
        std::cout<<vertex<<"   ";
        if(columnCount == columnMax){
            std::cout<<"\n";
            columnCount = 0;
        }
        columnCount++;
    }
    std::cout<<"\n\n";

    */
    // ORDENAMIENTO DE LOS DATOS
    ordenaMerge(adj);

}