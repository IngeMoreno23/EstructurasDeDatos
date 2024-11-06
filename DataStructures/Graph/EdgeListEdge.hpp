#pragma once
#include <iostream>

template <typename T>
class EdgeListEdge{
    private:
        T vertexOrigin; // Origin vertex of the edge.
        T vertexDestination; // Destination vertex of the edge.
        double weight;
        EdgeListEdge<T>* nextEdgeOrigin; // ptr to the next edge that has the same origin.
        EdgeListEdge<T>* nextEdgeDestination; // ptr to the next edge that has the same destination.
    public:
        EdgeListEdge();
        // EdgeListEdge(T vertexOrigin, T vertexDestination, double weight);
        // EdgeListEdge(const EdgeListEdge& otherEdge);
        // const EdgeListEdge& operator=(const EdgeListEdge& otherEdge);
        // ~EdgeListEdge();

        T getVertexOrigin();
        T getVertexDestination();
        double getWeight();
        EdgeListEdge<T>* getNextEdgeOrigin();
        EdgeListEdge<T>* getNextEdgeDestination();

        void setVertexOrigin(T vertexOrigin);
        void setVertexDestination(T vertexDestination);
        void setWeight(double weight);
        void setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination);

        void print();
        void printOrigin();
        void printDestination();
};

template <typename T>
EdgeListEdge<T>::EdgeListEdge(){
    this->vertexOrigin = T();
    this->vertexDestination = T();
    this->weight = 0;
    this->nextEdgeOrigin = nullptr;
    this->nextEdgeDestination = nullptr;
}




// GETTERS

template <typename T>
T EdgeListEdge<T>::getVertexOrigin(){
    return this->vertexOrigin;
}

template <typename T>
T EdgeListEdge<T>::getVertexDestination(){
    return this->vertexDestination;
}

template <typename T>
double EdgeListEdge<T>::getWeight(){
    return this->weight;
}

template <typename T>
EdgeListEdge<T>* EdgeListEdge<T>::getNextEdgeOrigin(){
    return this->nextEdgeOrigin;
}

template <typename T>
EdgeListEdge<T>* EdgeListEdge<T>::getNextEdgeDestination(){
    return this->nextEdgeDestination;
}

// SETTERS

template <typename T>
void EdgeListEdge<T>::setVertexOrigin(T vertexOrigin){
    this->vertexOrigin = vertexOrigin;
}

template <typename T>
void EdgeListEdge<T>::setVertexDestination(T vertexDestination){
    this->vertexDestination = vertexDestination;
}

template <typename T>
void EdgeListEdge<T>::setWeight(double weight){
    this->weight = weight;
}

template <typename T>
void EdgeListEdge<T>::setNextEdgeOrigin(EdgeListEdge<T>* nextEdgeOrigin){
    this->nextEdgeOrigin = nextEdgeOrigin;
}

template <typename T>
void EdgeListEdge<T>::setNextEdgeDestination(EdgeListEdge<T>* nextEdgeDestination){
    this->nextEdgeDestination = nextEdgeDestination;
}


/*
PARAMETERS: None.
METHOD: Prints the edge in the format "(vertexOrigin, vertexDestination, weight)".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <typename T>
void EdgeListEdge<T>::print(){
    std::cout<<"("<<vertexOrigin<<", "<<vertexDestination<<", "<<weight<<")";
}


template <typename T>
void EdgeListEdge<T>::printOrigin(){
    std::cout<<"("<<vertexOrigin<<", "<<weight<<")";
}


template <typename T>
void EdgeListEdge<T>::printDestination(){
    std::cout<<"("<<vertexDestination<<", "<<weight<<")";
}