#include <iostream> 
#include "..\..\DataStructures\Graph\Graph.hpp"

int main()
{
    Graph<> testGraphContainer({{1,2},{0,2,3},{0,1,4},{1,4},{2,3}});

    // PRUEBA DE FUNCIONALIDADES DE LOS MÉTODOS IMPLEMENTADOS.
    Graph<> functionTestGraph;

    testGraphContainer.topologicalSort();
}