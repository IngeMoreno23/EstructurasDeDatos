#pragma once
#include <iostream>
#include "EdgeListEdge.hpp"

template <class T, class U>
class EdgeListVertex{
    private:
        T vertex;
        EdgeListVertex<T, U>* nextVertex;
        EdgeListEdge<T, U>* nextEdgeOrigin;
        EdgeListEdge<T, U>* nextEdgeDestination;
    public:
        EdgeListVertex();
        EdgeListVertex(T& vertex);
        // EdgeListVertex(const EdgeListVertex& otherVertex);
        // const EdgeListVertex& operator=(const EdgeListVertex& otherVertex);
        // ~EdgeListVertex();

        // void addEdge(EdgeListVertex<T, U>* vertexOriginPtr, EdgeListVertex<T, U>* vertexDestinationPtr, U& weight);
        void addEdge(EdgeListVertex<T, U>* vertexOriginPtr, EdgeListVertex<T, U>* vertexDestinationPtr);
        void addEdgeDestination(EdgeListEdge<T, U>* edgeDestination);

        // void removeEdge(T& vertexDestination);

        T& getVertex();
        EdgeListVertex<T, U>* getNextVertex();
        EdgeListEdge<T, U>* getNextEdgeOrigin();
        EdgeListEdge<T, U>* getNextEdgeDestination();
        
        void setVertex(T vertex);
        void setNextVertex(EdgeListVertex<T, U>* nextVertex);
        void setNextEdgeOrigin(EdgeListEdge<T, U>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T, U>* nextEdgeDestination);

        void print();
        void printOrigin();
        void printDestination();
};

template <class T, class U>
EdgeListVertex<T, U>::EdgeListVertex(){
    this->vertex = T();
    this->nextVertex = nullptr;
    this->nextEdgeOrigin = nullptr;
    this->nextEdgeDestination = nullptr;
}

/*
PARAMETERS: T& vertex, where T is the type of the vertex. Done by reference to change Edges.
METHOD: Prints the vertex in the format "vertex: (vertexOrigin, vertexDestination, weight)_1, ..., (vertexOrigin, vertexDestination, weight)_n".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
EdgeListVertex<T, U>::EdgeListVertex(T& vertex){
    this->vertex = vertex;
    this->nextVertex = nullptr;
    this->nextEdgeOrigin = nullptr;
    this->nextEdgeDestination = nullptr;
}

/*
PARAMETERS: T& vertex, where T is the type of the vertex. Done by reference to change Edges.
METHOD: Prints the vertex in the format "vertex: (vertexOrigin, vertexDestination, weight)_1, ..., (vertexOrigin, vertexDestination, weight)_n".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
void EdgeListVertex<T, U>::addEdge(EdgeListVertex<T, U>* vertexOriginPtr, EdgeListVertex<T, U>* vertexDestinationPtr){
    if(vertexOriginPtr->getVertex() != this->vertex){
        std::cerr << "The vertex origin does not match.\n";
        return;
    }
    // If the edge list is empty, we insert the edge at the beginning of the list.
    if(this->nextEdgeOrigin == nullptr){
        this->nextEdgeOrigin = new EdgeListEdge<T, U>(vertexOriginPtr->getVertex(), vertexDestinationPtr->getVertex());
        return;
    }
    // We will insert the edge in order by EdgeListEdge edgeDestination.
    EdgeListEdge<T, U>* currentEdgeOrigin = this->nextEdgeOrigin;
    // Special case: if the vertex to insert is less than the head of the list.
    if(vertexDestinationPtr->getVertex() < currentEdgeOrigin->getVertexDestination()){
        EdgeListEdge<T, U>* newEdge = new EdgeListEdge<T, U>(vertexOriginPtr->getVertex(), vertexDestinationPtr->getVertex());
        newEdge->setNextEdgeOrigin(currentEdgeOrigin);
        this->nextEdgeOrigin = newEdge;
        return;
    }
    // Find the edge where current.destination <= destination < current.nextDestination
    while(currentEdgeOrigin->getNextEdgeOrigin() != nullptr && currentEdgeOrigin->getNextEdgeOrigin()->getVertexDestination() <= vertexDestinationPtr->getVertex()){
        currentEdgeOrigin = currentEdgeOrigin->getNextEdgeOrigin();
    }
    // If the edge is already in the vertex, we do nothing.
    if(currentEdgeOrigin->getVertexDestination() == vertexDestinationPtr->getVertex()){
        std::cerr << "The edge is already in the vertex.\n";
        return;
    }
    // If the next edge is null, we insert the edge at the end of the list.
    if(currentEdgeOrigin->getNextEdgeOrigin() == nullptr){
        currentEdgeOrigin->setNextEdgeOrigin(new EdgeListEdge<T, U>(vertexOriginPtr->getVertex(), vertexDestinationPtr->getVertex()));
        return;
    }
    // If the edge to insert is less than the next edge, we insert the edge between the current and the next edge.
    EdgeListEdge<T, U>* newEdge = new EdgeListEdge<T, U>(vertexOriginPtr->getVertex(), vertexDestinationPtr->getVertex());
    newEdge->setNextEdgeOrigin(currentEdgeOrigin->getNextEdgeOrigin());
    currentEdgeOrigin->setNextEdgeOrigin(newEdge);
}

/*

*/
template <class T, class U>
void EdgeListVertex<T, U>::addEdgeDestination(EdgeListEdge<T, U>* edgeDestination){
    if(edgeDestination->getVertexDestination() != this->vertex){
        std::cerr << "The vertex destination is not this vertex.\n";
        return;
    }
    // If the edge list is empty, we insert the edge at the beginning of the list.
    if(this->nextEdgeDestination == nullptr){
        this->nextEdgeDestination = edgeDestination;
        return;
    }
    // We will insert the edge in order by EdgeListEdge edgeDestination.
    EdgeListEdge<T, U>* currentEdgeDestination = this->nextEdgeDestination;
    // Special case: if the vertex to insert is less than the head of the list.
    if(edgeDestination->getVertexDestination() < currentEdgeDestination->getVertexDestination()){
        edgeDestination->setNextEdgeDestination(currentEdgeDestination);
        this->nextEdgeDestination = edgeDestination;
        return;
    }
    // Find the edge where current.destination <= destination < current.nextDestination
    while(currentEdgeDestination->getNextEdgeDestination() != nullptr && currentEdgeDestination->getNextEdgeDestination()->getVertexDestination() <= edgeDestination->getVertexDestination()){
        currentEdgeDestination = currentEdgeDestination->getNextEdgeDestination();
    }
    // If the edge is already in the vertex, we do nothing.
    if(currentEdgeDestination->getVertexOrigin() == edgeDestination->getVertexOrigin()){
        std::cerr << "The edge is already in the vertex.\n";
        return;
    }
    // If the next edge is null, we insert the edge at the end of the list.
    if(currentEdgeDestination->getNextEdgeDestination() == nullptr){
        currentEdgeDestination->setNextEdgeDestination(edgeDestination);
        return;
    }
    // If the edge to insert is less than the next edge, we insert the edge between the current and the next edge.
    edgeDestination->setNextEdgeDestination(currentEdgeDestination->getNextEdgeDestination());
    currentEdgeDestination->setNextEdgeDestination(edgeDestination);
}

// /*

// */
// template <class T, class U>
// void EdgeListVertex<T, U>::removeEdge(T& vertexDestination){
//     if(this->nextEdgeOrigin == nullptr){
//         std::cerr << "The vertex does not have edges.\n";
//         return;
//     }
//     // Check if the edge exists.
//     EdgeListEdge<T, U>* currentEdgeOrigin = this->nextEdgeOrigin;
    

// }


// GETTERS

template <class T, class U>
T& EdgeListVertex<T, U>::getVertex(){
    return this->vertex;
}

template <class T, class U>
EdgeListVertex<T, U>* EdgeListVertex<T, U>::getNextVertex(){
    return this->nextVertex;
}

template <class T, class U>
EdgeListEdge<T, U>* EdgeListVertex<T, U>::getNextEdgeOrigin(){
    return this->nextEdgeOrigin;
}

template <class T, class U>
EdgeListEdge<T, U>* EdgeListVertex<T, U>::getNextEdgeDestination(){
    return this->nextEdgeDestination;
}

// SETTERS
template <class T, class U>
void EdgeListVertex<T, U>::setVertex(T vertex){
    this->vertex = vertex;
}

template <class T, class U>
void EdgeListVertex<T, U>::setNextVertex(EdgeListVertex<T, U>* nextVertex){
    this->nextVertex = nextVertex;
}

template <class T, class U>
void EdgeListVertex<T, U>::setNextEdgeOrigin(EdgeListEdge<T, U>* nextEdgeOrigin){
    this->nextEdgeOrigin = nextEdgeOrigin;
}

template <class T, class U>
void EdgeListVertex<T, U>::setNextEdgeDestination(EdgeListEdge<T, U>* nextEdgeDestination){
    this->nextEdgeDestination = nextEdgeDestination;
}

/*
PARAMETERS: None.
METHOD: Prints the vertex in the format "vertex: (vertexOrigin, vertexDestination, weight)_1, ..., (vertexOrigin, vertexDestination, weight)_n".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
void EdgeListVertex<T, U>::print(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeOrigin == nullptr)
        return;

    EdgeListEdge<T, U>* currentEdgeOrigin = this->nextEdgeOrigin;
    do{
        currentEdgeOrigin -> print();
        currentEdgeOrigin = currentEdgeOrigin->getNextEdgeOrigin();

        if(currentEdgeOrigin != nullptr)
            std::cout<<", ";

    } while(currentEdgeOrigin != nullptr);
    std::cout << ".";
}

template <class T, class U>
void EdgeListVertex<T, U>::printOrigin(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeDestination == nullptr)
        return;

    EdgeListEdge<T, U>* nextEdgeDestination = this->nextEdgeDestination;
    do{
        nextEdgeDestination -> printOrigin();
        nextEdgeDestination = nextEdgeDestination->getNextEdgeDestination();

        if(nextEdgeDestination != nullptr)
            std::cout<<", ";

    } while(nextEdgeDestination != nullptr);
    std::cout << ".";
}

/*
This will print the destination of the edges this vertes is origin of.
*/
template <class T, class U>
void EdgeListVertex<T, U>::printDestination(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeOrigin == nullptr)
        return;

    EdgeListEdge<T, U>* nextEdgeOrigin = this->nextEdgeOrigin;
    do{
        nextEdgeOrigin -> printDestination();
        nextEdgeOrigin = nextEdgeOrigin->getNextEdgeOrigin();

        if(nextEdgeOrigin != nullptr)
            std::cout<<", ";

    } while(nextEdgeOrigin != nullptr);
    std::cout << ".";
}