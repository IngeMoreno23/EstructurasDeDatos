#include "..\..\DataStructures\Graph\Graph.hpp"
#include "..\..\DataStructures\Graph\ArchPondGraph.hpp"

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main(){
    vecGraph<int> testConstInt(3), testAddEdgeInt;
    vecGraph<std::string> testConstStr(6), testAddEdgeStr;

    // CASOS DE PRUEBA GENERALES DE LA IMPLEMENTACIÓN DE LA LISTA DE ADYACENCIA:
    std::cout<<"> Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existen ninguno de los vértices): \n";
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::cout<<"\n> Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existe vértice 2): \n";
    testAddEdgeInt.addVertex(2);     // Añadir dos vértices, 0 y 1. 
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::cout<<"\n> Impresión de la lista de adyacencia (añadiendo un arco de 2 a 2): \n";
    testAddEdgeInt.addVertex(); // Añadir vértice 2
    testAddEdgeInt.addEdge(1,2);
    testAddEdgeInt.addEdge(2,2);
    testAddEdgeInt.print();

    std::cout<<"\n> Impresión de la lista de adyacencia (quitando el arco inexistente de 1 a 1): \n";
    try{
        testAddEdgeInt.removeEdge(1,1);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar quitar el arco: "<<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::vector<std::vector<int>> container = {{1,2},{0,2,3},{0,1,4},{1,4},{2,3}};
    Graph<> testGraphContainer(container), testLoadGraph;
    std::cout<<"\n> Impresión de la lista de adyacencia creada con un contenedor como parámetro: \n";
    testGraphContainer.print();
    
    std::cout<<"\n> Recorridos DFS: \n";
    testGraphContainer.DFS(0);
    testGraphContainer.DFS(1);
    
    std::cout<<"\n> Recorridos BFS: \n";
    testGraphContainer.BFS(0);
    testGraphContainer.BFS(1);
    
    std::cout<<"\n> Recorridos DFS y BFS en grafos vacíos: \n";
    try{
        testLoadGraph.DFS(0);
        testLoadGraph.BFS(0);
    } catch(std::out_of_range& ex){
        std::cout<<"Error: "<<ex.what()<<"\n";
    }

    std::cout<<"\n> Implementación del método loadGraph con una lista de adyacencias como parámetro: \n";
    testLoadGraph.loadGraph(container);
    testLoadGraph.print();

    std::cout<<"\n> Implementación del método loadGraph con valores inválidos: \n";
    try{
        testLoadGraph.loadGraph(-2,3);
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }
    std::cout<<"\n> LoadGraph con más conexiones que vértices (imposible): \n";
    try{
        testLoadGraph.loadGraph(4,5);
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }
    std::cout<<"\n> LoadGraph con más vértices que conexiones (correcto): \n";
    testLoadGraph.loadGraph(5,4);
    testLoadGraph.print();
}

