#include "..\..\DataStructures\Graph\Graph.hpp"

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main(){
    vecGraph<int> god(3);
    std::vector<std::vector<int>> container;
    Graph<> graph(container);
    graph.print();
}
