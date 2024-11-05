#include <iostream>
#include "EdgeListEdge.hpp"
#include "EdgeListVertex.hpp"

template <typename T>
class EdgeListGraph{
    private:
        EdgeListVertex<T>* vertex; // Head of the list of vertex
    public:
        EdgeListGraph();
        void print();
};

/*
PARAMETERS: None.
METHOD: Prints the graph in the format "vertex -> edge -> edge -> ...".
ORDER OF EXECUTION: O(V + E).
RETURN: None.
*/
template <typename T>
void EdgeListGraph<T>::print(){
    EdgeListVertex<T>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->print();
        currentVertex = currentVertex->getNextVertex();
    }
}