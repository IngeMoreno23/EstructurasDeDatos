#pragma once
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
        EdgeListVertex();
        // EdgeListVertex(T vertex);
        // EdgeListVertex(const EdgeListVertex& otherVertex);
        // const EdgeListVertex& operator=(const EdgeListVertex& otherVertex);
        // ~EdgeListVertex();

        T getVertex();
        EdgeListVertex<T>* getNextVertex();
        EdgeListEdge<T>* getNextEdgeOrigin();
        EdgeListEdge<T>* getNextEdgeDestination();
        
        void setVertex(T vertex);
        void setNextVertex(EdgeListVertex<T>* nextVertex);
        void setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination);

        void print();
        void printOrigin();
        void printDestination();
};

template <typename T>
EdgeListVertex<T>::EdgeListVertex(){
    this->vertex = T();
    this->nextVertex = nullptr;
    this->nextEdgeOrigin = nullptr;
    this->nextEdgeDestination = nullptr;
}

// GETTERS

template <typename T>
T EdgeListVertex<T>::getVertex(){
    return this->vertex;
}

template <typename T>
EdgeListVertex<T>* EdgeListVertex<T>::getNextVertex(){
    return this->nextVertex;
}

template <typename T>
EdgeListEdge<T>* EdgeListVertex<T>::getNextEdgeOrigin(){
    return this->nextEdgeOrigin;
}

template <typename T>
EdgeListEdge<T>* EdgeListVertex<T>::getNextEdgeDestination(){
    return this->nextEdgeDestination;
}

// SETTERS
template <typename T>
void EdgeListVertex<T>::setVertex(T vertex){
    this->vertex = vertex;
}

template <typename T>
void EdgeListVertex<T>::setNextVertex(EdgeListVertex<T>* nextVertex){
    this->nextVertex = nextVertex;
}

template <typename T>
void EdgeListVertex<T>::setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin){
    this->nextEdgeOrigin = nextEdgeOrigin;
}

template <typename T>
void EdgeListVertex<T>::setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination){
    this->nextEdgeDestination = nextEdgeDestination;
}

/*
PARAMETERS: None.
METHOD: Prints the vertex in the format "vertex: (vertexOrigin, vertexDestination, weight)_1, ..., (vertexOrigin, vertexDestination, weight)_n".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <typename T>
void EdgeListVertex<T>::print(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeOrigin == nullptr)
        return;

    EdgeListEdge<T>* currentEdgeOrigin = this->nextEdgeOrigin;
    do{
        currentEdgeOrigin -> print();
        currentEdgeOrigin = currentEdgeOrigin->getNextEdgeOrigin();

        if(currentEdgeOrigin != nullptr)
            std::cout<<", ";

    } while(currentEdgeOrigin != nullptr);
    std::cout << ".";
}

template <typename T>
void EdgeListVertex<T>::printOrigin(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeDestination == nullptr)
        return;

    EdgeListEdge<T>* nextEdgeDestination = this->nextEdgeDestination;
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
template <typename T>
void EdgeListVertex<T>::printDestination(){
    std::cout<<vertex<<": ";

    if(this->nextEdgeOrigin == nullptr)
        return;

    EdgeListEdge<T>* nextEdgeOrigin = this->nextEdgeOrigin;
    do{
        nextEdgeOrigin -> printDestination();
        nextEdgeOrigin = nextEdgeOrigin->getNextEdgeOrigin();

        if(nextEdgeOrigin != nullptr)
            std::cout<<", ";

    } while(nextEdgeOrigin != nullptr);
    std::cout << ".";
}