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
        // EdgeListVertex(T vertex);
        // EdgeListVertex(const EdgeListVertex& otherVertex);
        // const EdgeListVertex& operator=(const EdgeListVertex& otherVertex);
        // ~EdgeListVertex();

        T getVertex();
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

// GETTERS

template <class T, class U>
T EdgeListVertex<T, U>::getVertex(){
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