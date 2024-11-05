#include "Graph.hpp"

int main(){
    Graph<int> grafo1(3);
    std::vector<std::vector<int>> container = {{1,2,0,0,4},{0,2,3},{0,1,4},{1,4,0,5,2},{2,3,3,5}}; // Vector con pesos
    Graph grafo2(container);

    grafo2.DFS(0);
    std::cout<<std::endl;
    grafo2.BFS(0);
    std::cout<<"\n\n";
    grafo2.print();
}

