#include "..\..\DataStructures\Graph\Graph.hpp"
#include "..\..\DataStructures\Graph\ArchPondGraph.hpp"

/*/
template <typename T, typename U>
using vecGraphArchPond = ArchPondGraph<std::vector, std::vector, ArchPond<T,U>>; // Alias template 

int main(){
    vecGraph<std::pair<int, int>> god(3);
    std::vector<std::vector<std::pair<int, double>>> 
    container = {{{1, 4.0}, {2, 3.4}},
                {{0, 5.6}, {2, 4.7}, {3, 6.8}},
                {{0 , 10.4}, {1 , 30.2}, {4 , 9.6}},
                {{1, 3.2} ,{4, 7.2}},
                {{2, 21.2}, {3, 3.4}}};

    ArchPondGraph<std::vector, std::vector, std::pair<int, double>> grx|x|aph2(container);

    graph2.DFS(0);
    std::cout<<std::endl;
    graph2.BFS(0);
    
}

*/

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main(){
    vecGraph<int> testConstInt(3), testAddEdgeInt;
    vecGraph<std::string> testConstStr(6), testAddEdgeStr;
    std::vector<std::vector<int>> container = {{1,2},{0,2,3},{0,1,4},{1,4},{2,3}};
    Graph<> testGraphContainer(container), testLoadGraph;

    std::cout<<"Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existen ninguno de los vértices): \n";
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
    }
    testAddEdgeInt.print();
    testAddEdgeInt.addVertex(3);

    std::cout<<"Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existe vértice 2): \n";
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
    }
    testAddEdgeInt.addVertex();

    std::cout<<"Impresión de la lista de adyacencia (añadiendo un arco de 2 a 2): \n";
    testAddEdgeInt.addEdge(2,2);
    testAddEdgeInt.print();

    std::cout<<"Impresión de la lista de adyacencia (añadiendo un arco de 2 a 2): \n";
    testAddEdgeInt.removeEdge(1,2);
    testAddEdgeInt.print();

    testGraphContainer.print();
    
    testAddEdgeInt.DFS(0);
    testAddEdgeInt.DFS(1);
    
    testGraphContainer.DFS(0);
    testGraphContainer.BFS(0);

    testLoadGraph.loadGraph(container);
    testLoadGraph.print();
}

