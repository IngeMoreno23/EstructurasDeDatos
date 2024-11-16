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

#include "..\..\DataStructures\List\DoubleLL.hpp"
#include "..\..\DataStructures\Tree\SplayTree\SplayTree.hpp"
#include "..\..\DataStructures\Graph\Graph.hpp"
#include "ipHandler.cpp"

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 


int main(){
    // LECTURA DE DATOS 
    std::ifstream myBitacora("bitacora.txt");
    if(!myBitacora.is_open()){
        std::cerr << "No se pudo abrir el documento bitacora.txt" << std::endl;
        return 1;
    }

    vecGraph<std::string> ipComm;
    std::string myLine;
    std::stringstream sstr;

    std::getline(myBitacora, myLine);
    sstr.str(myLine);
    size_t vertices, connections;
    sstr>>vertices>>connections;

    // REALIZACIÓN DEL GRAFO
    std::vector<IpFreq> adj;
    for(int i = 0; i < vertices; i++){
        std::getline(myBitacora, myLine);
        adj.push_back(IpFreq(myLine));
    }

    // ADICIÓN DE ARCOS Y BÚSQUEDA DE INFORMACIÓN (para agregar los fanIns)
    std::pair<std::string, std::string> ipOrDest;
    for(int i = 0; i < connections; i++){
        std::getline(myBitacora, myLine);
        ipOrDest = obtainIp(myLine);
        auto location = std::find(adj.begin(), adj.end(), ipOrDest.first);
        if(location != adj.end()){
            location -> addConnection(ipOrDest.second);
        }
        location = std::find(adj.begin(), adj.end(), ipOrDest.second);
        if(location != adj.end()){
            location -> fanIn++;
            std::cout<<"";
        }
    }

    // VISUALIZACIÓN DE GRAFO.
    int columnMax = 3, columnCount = 0; // Solo para que se visualicen varias ips en una misma línea
    for(const auto& vertex:adj){
        std::cout<<vertex<<"   ";
        if(columnCount == columnMax){
            std::cout<<"\n";
            columnCount = 0;
        }
        columnCount++;
    }
    std::cout<<"\n\n";

    // ORDENAMIENTO DE LOS DATOS
    ordenaMerge(adj, adj.size());
    
    // DESPLIEGUE POR CANTIDAD DE ACCESOS
    int showIp = 5;
    for(auto it = adj.rbegin(); it != adj.rend() && showIp != 0; ++it, showIp--){
        std::cout<<*it<<"\n";
    }
    std::cout<<"\n";

    std::sort(adj.begin(), adj.end(), [](const IpFreq& a, const IpFreq& b) {
        return (a.fanOut != b.fanOut) ? a.fanOut < b.fanOut : a.ip < b.ip;
    });
    
    showIp = 5;
    for(auto it = adj.rbegin(); it != adj.rend() && showIp != 0; ++it, showIp--){
        std::cout<<*it<<"\n";
    }
    std::cout<<"\n";


}