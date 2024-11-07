#pragma once
#include <iostream>

template <class T, class U>
class EdgeListEdge{
    private:
        T vertexOrigin; // Origin vertex of the edge.
        T vertexDestination; // Destination vertex of the edge.
        U weight; // Weight of the edge.
        EdgeListEdge<T, U>* nextEdgeOrigin; // ptr to the next edge that has the same origin.
        EdgeListEdge<T, U>* nextEdgeDestination; // ptr to the next edge that has the same destination.
    public:
        EdgeListEdge();
        // EdgeListEdge(T& vertexOrigin, T& vertexDestination, U weight);
        // EdgeListEdge(const EdgeListEdge& otherEdge);
        // const EdgeListEdge& operator=(const EdgeListEdge& otherEdge);
        // ~EdgeListEdge();

        T getVertexOrigin();
        T getVertexDestination();
        U getWeight();
        EdgeListEdge<T, U>* getNextEdgeOrigin();
        EdgeListEdge<T, U>* getNextEdgeDestination();

        void setVertexOrigin(T vertexOrigin);
        void setVertexDestination(T vertexDestination);
        void setWeight(U weight);
        void setNextEdgeOrigin(EdgeListEdge<T, U>* nextEdgeOrigin);
        void setNextEdgeDestination(EdgeListEdge<T, U>* nextEdgeDestination);

        void print();
        void printOrigin();
        void printDestination();
};

/*
PARAMETERS: None.
METHOD: Initializes the edge with default values. In case of the weight being a number, it is initialized with 1.
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
EdgeListEdge<T, U>::EdgeListEdge(){
    this->vertexOrigin = T();
    this->vertexDestination = T();
    if constexpr (std::is_same<U, int>::value ||std::is_same<U, long>::value || std::is_same<U, long long>::value
                    || std::is_same<U, float>::value ||  std::is_same<U, double>::value){
        this->weight = U(1);
    } else {
        this->weight = U();
    }
    this->nextEdgeOrigin = nullptr;
    this->nextEdgeDestination = nullptr;
}


// GETTERS

template <class T, class U>
T EdgeListEdge<T, U>::getVertexOrigin(){
    return this->vertexOrigin;
}

template <class T, class U>
T EdgeListEdge<T, U>::getVertexDestination(){
    return this->vertexDestination;
}

template <class T, class U>
U EdgeListEdge<T, U>::getWeight(){
    return this->weight;
}

template <class T, class U>
EdgeListEdge<T, U>* EdgeListEdge<T, U>::getNextEdgeOrigin(){
    return this->nextEdgeOrigin;
}

template <class T, class U>
EdgeListEdge<T, U>* EdgeListEdge<T, U>::getNextEdgeDestination(){
    return this->nextEdgeDestination;
}

// SETTERS

template <class T, class U>
void EdgeListEdge<T, U>::setVertexOrigin(T vertexOrigin){
    this->vertexOrigin = vertexOrigin;
}

template <class T, class U>
void EdgeListEdge<T, U>::setVertexDestination(T vertexDestination){
    this->vertexDestination = vertexDestination;
}

template <class T, class U>
void EdgeListEdge<T, U>::setWeight(U weight){
    this->weight = weight;
}

template <class T, class U>
void EdgeListEdge<T, U>::setNextEdgeOrigin(EdgeListEdge<T, U>* nextEdgeOrigin){
    this->nextEdgeOrigin = nextEdgeOrigin;
}

template <class T, class U>
void EdgeListEdge<T, U>::setNextEdgeDestination(EdgeListEdge<T, U>* nextEdgeDestination){
    this->nextEdgeDestination = nextEdgeDestination;
}


/*
PARAMETERS: None.
METHOD: Prints the edge in the format "(vertexOrigin, vertexDestination, weight)".
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
void EdgeListEdge<T, U>::print(){
    std::cout<<"("<<vertexOrigin<<", "<<vertexDestination<<", "<<weight<<")";
}


template <class T, class U>
void EdgeListEdge<T, U>::printOrigin(){
    std::cout<<"("<<vertexOrigin<<", "<<weight<<")";
}


template <class T, class U>
void EdgeListEdge<T, U>::printDestination(){
    std::cout<<"("<<vertexDestination<<", "<<weight<<")";
}