#pragma once
#include <iostream>
#include "EdgeListEdge.hpp"
#include "EdgeListVertex.hpp"

template <class T, class U>
class EdgeListGraph{
    private:
        EdgeListVertex<T, U>* vertex; // Head of the list of vertex
    public:
        EdgeListGraph();
        // EdgeListGraph(const EdgeListGraph& otherGraph);
        // const EdgeListGraph& operator=(const EdgeListGraph& otherGraph);
        // ~EdgeListGraph();

        // void addVertex(const T& vertex);
        // void addEdge(const T& vertexOrigin, const T& vertexDestination, double weight, bool isDirected);

        // void removeVertex(const T& vertex);
        // void removeEdge(const T& vertexOrigin, const T& vertexDestination, bool isDirected);

        EdgeListVertex<T, U>* getVertex();
        void setVertex(EdgeListVertex<T, U>* vertex);

        // void BFS();
        // void DFS();

        void print();
        void printOrigin();
        void printDestination();
};

/*

*/
template <class T, class U>
EdgeListGraph<T, U>::EdgeListGraph(){
    this->vertex = nullptr;
}

// GETTERS

template <class T, class U>
EdgeListVertex<T, U>* EdgeListGraph<T, U>::getVertex(){
    return this->vertex;
}

// SETTERS

template <class T, class U>
void EdgeListGraph<T, U>::setVertex(EdgeListVertex<T, U>* vertex){
    this->vertex = vertex;
}


/*
PARAMETERS: None.
METHOD: Prints the graph in the format "vertex -> edge -> edge -> ...".
ORDER OF EXECUTION: O(V + E).
RETURN: None.
*/
template <class T, class U>
void EdgeListGraph<T, U>::print(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    std::cout<<"Graph.- Vertex: (origin, destination, weight)\n";
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->print();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}

/*
Who is pointing to me
*/
template <class T, class U>
void EdgeListGraph<T, U>::printOrigin(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    std::cout<<"Graph.- Vertex: (origin, weight) - Who is pointing to me:\n";
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->printOrigin();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}

/*
Who am I pointing to.

*/
template <class T, class U>
void EdgeListGraph<T, U>::printDestination(){
    if(this->vertex == nullptr){
        std::cout<<"Empty graph.\n";
        return;
    }
    std::cout<<"Graph.- Vertex: (destination, weight) - Who am I pointing to:\n";
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        currentVertex->printDestination();
        currentVertex = currentVertex->getNextVertex();
        std::cout<<"\n";
    }
}