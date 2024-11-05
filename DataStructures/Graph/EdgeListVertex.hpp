#include <iostream>
#include "EdgeListEdge.hpp"

template <typename T>
class EdgeListVertex{
    private:
        T vertex;
        EdgeListVertex<T>* nextVertex;
        EdgeListEdge<T>* nextEdgeOrigin;
        EdgeListEdge<T>* nextEdgeDestination;
    public:
        EdgeListEdge();
        EdgeListEdge(T vertex);
        EdgeListEdge(const EdgeListEdge& otherVertex);
        const EdgeListEdge& operator=(const EdgeListEdge& otherVertex);
        ~EdgeListEdge();

        T getVertex();
        EdgeListVertex<T>* getNextVertex();
        EdgeListEdge<T>* getNextEdgeOrigin();
        EdgeListEdge<T>* getNextEdgeDestination();
        
        void setVertex(T vertex);
        void setNextVertex(EdgeListVertex<T>* nextVertex);
        void setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination);

        void print();
};

/*
PARAMETERS: None.
METHOD: Prints the vertex in the format "vertex: (vertexOrigin, vertexDestination, weight)_1, ..., (vertexOrigin, vertexDestination, weight)_n".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <typename T>
void EdgeListVertex<T>::print(){
    std::cout<<vertex<<": ";
    EdgeListEdge<T>* currentEdgeOrigin = this->nextEdgeOrigin;
    while(currentEdgeOrigin != nullptr){
        currentEdgeOrigin -> print();
        currentEdgeOrigin = currentEdgeOrigin->getNextEdgeOrigin();
    }
    std::cout << "\n";
}