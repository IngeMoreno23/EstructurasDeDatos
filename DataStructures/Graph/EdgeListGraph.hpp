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
        void printOrigin();
        void printDestination();
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
    std::cout<<"Graph.- Vertex: (origin, destination, weight)\n";
    EdgeListVertex<T>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->print();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}

/*
Who is pointing to me
*/
template <typename T>
void EdgeListGraph<T>::printOrigin(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    std::cout<<"Graph.- Vertex: (origin, weight) - Who is pointing to me:\n";
    EdgeListVertex<T>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->printOrigin();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}

/*
Who am I pointing to.

*/
template <typename T>
void EdgeListGraph<T>::printDestination(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    std::cout<<"Graph.- Vertex: (destination, weight) - Who am I pointing to:\n";
    EdgeListVertex<T>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->printDestination();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}