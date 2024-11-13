#include <iostream> 
#include "..\..\DataStructures\Graph\Graph.hpp"

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main()
{
    vecGraph<int> testGraphContainer({{1,2},{0,2,3},{0,1,4},{1,4},{2,3}}), testGraphContainer2({{1},{2},{3},{4},{0}}), testGraphContainer3({{1},{2},{1},{0},{0}});

    // PRUEBA DE FUNCIONALIDADES DE LOS MÉTODOS IMPLEMENTADOS.
    Graph<> functionTestGraph;

    testGraphContainer.topologicalSort();
    std::cout<<"\n\n";
    std::cout<<bipartiteGraph(testGraphContainer2.adjacencyList);
    std::cout<<"\n\n";
    std::cout<<bipartiteGraph(testGraphContainer3.adjacencyList);
}