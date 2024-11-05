#include "..\..\DataStructures\Graph\Graph.hpp"

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main(){
    vecGraph<int> god(3);
    std::vector<std::vector<int>> container(2);
    Graph<> graph2(container);
    std::cout<<graph2.nodes.size()<<"\n";
    std::cout<<god.nodes.size();
}
