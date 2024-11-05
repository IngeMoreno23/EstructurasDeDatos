#pragma once
#include <iostream>
#include "EdgeListEdge.hpp"
#include "EdgeListVertex.hpp"

template <typename T>
class EdgeListGraph{
    private:
        EdgeListVertex<T>* vertex; // Head of the list of vertex
    public:
        EdgeListGraph();
        // EdgeListGraph(const EdgeListGraph& otherGraph);
        // const EdgeListGraph& operator=(const EdgeListGraph& otherGraph);
        // ~EdgeListGraph();

        // void addVertex(const T& vertex);
        // void addEdge(const T& vertexOrigin, const T& vertexDestination, double weight, bool isDirected);

        // void removeVertex(const T& vertex);
        // void removeEdge(const T& vertexOrigin, const T& vertexDestination, bool isDirected);

        EdgeListVertex<T>* getVertex();
        void setVertex(EdgeListVertex<T>* vertex);

        // void BFS();
        // void DFS();

        void print();
};

/*

*/
template <typename T>
EdgeListGraph<T>::EdgeListGraph(){
    this->vertex = nullptr;
}

// GETTERS

template <typename T>
EdgeListVertex<T>* EdgeListGraph<T>::getVertex(){
    return this->vertex;
}

// SETTERS

template <typename T>
void EdgeListGraph<T>::setVertex(EdgeListVertex<T>* vertex){
    this->vertex = vertex;
}


/*
PARAMETERS: None.
METHOD: Prints the graph in the format "vertex -> edge -> edge -> ...".
ORDER OF EXECUTION: O(V + E).
RETURN: None.
*/
template <typename T>
void EdgeListGraph<T>::print(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    EdgeListVertex<T>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->print();
        currentVertex = currentVertex->getNextVertex();
    }
}