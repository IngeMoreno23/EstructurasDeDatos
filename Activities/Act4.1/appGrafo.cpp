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
    vecGraph<int> god(3);
    std::vector<std::vector<int>> container = {{1,2},{0,2,3},{0,1,4},{1,4},{2,3}};
    Graph<> graph2(container);

    god.addEdge(1, 2);
    god.print();
    god.addEdge(2,2);
    god.print();
    god.removeEdge(1,2);
    god.print();
    god.DFS(0);
    god.DFS(1);
    graph2.DFS(0);
    graph2.BFS(0);
}

