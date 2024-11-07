#pragma once
#include <iostream>
#include <initializer_list>
#include <map>
#include <set>
#include "EdgeListEdge.hpp"
#include "EdgeListVertex.hpp"

template <class T, class U>
class EdgeListGraph{
    private:
        EdgeListVertex<T, U>* vertex; // Head of the list of vertex
    public:
        EdgeListGraph();
        EdgeListGraph(std::map<T, std::initializer_list<T>> graph);
        EdgeListGraph(std::map<T, std::initializer_list<std::pair<T, U>>> graph);
        // EdgeListGraph(const EdgeListGraph& otherGraph);
        // const EdgeListGraph& operator=(const EdgeListGraph& otherGraph);
        // ~EdgeListGraph();

        void addVertex(T& vertex); // DOOOOONE
        // void addEdge(const T& vertexOrigin, const T& vertexDestination, double weight, bool isDirected);

        void updateVertex(const T& vertex, const T& newVertex);

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

// CONSTRUCTORS

/*
PARAMETERS: None.
METHOD: Initializes the graph with a nullptr.
ORDER OF EXECUTION: O(1).
RETURN: None.
*/
template <class T, class U>
EdgeListGraph<T, U>::EdgeListGraph(){
    this->vertex = nullptr;
}

/*
PARAMETERS: std::map<T, std::initializer_list<T>> graph, where T is the type of the vertex
            and the elements of the initializer_list are the vertices that the vertex is pointing to.
METHOD: This creates a graph with all the vertices specified and not declared that are in the edges.
        The graph is created in order of the vertices and the edges also in the vertexDestination order.
        If the vertex or the edge is already in the graph, it does nothing.
ORDER OF EXECUTION: O(V + E). Where V is the number of vertices and E is the number of edges.
RETURN: None.
*/
template <class T, class U>
EdgeListGraph<T, U>::EdgeListGraph(std::map<T, std::initializer_list<T>> graph){
    this->vertex = nullptr;
    // First, create the vertices.
    std::set<T> verticesDestination;
    for(auto [vertexOrigin, vertices] : graph){
        // Verify if the vertex is already in the graph.
        EdgeListVertex<T, U>* tempVertexPtr = this->vertex;
        while(tempVertexPtr != nullptr){
            if(tempVertexPtr->getVertex() == vertexOrigin)
                break;
            tempVertexPtr = tempVertexPtr->getNextVertex();
        }
        // If does not arrive to the end (nullptr), the vertex is already in the graph.
        if(tempVertexPtr != nullptr){
            std::cerr << "The vertex " << vertexOrigin << " is already in the graph. Couldn't insert Edges\n";
            continue;
        }
        // If the vertex is not in the graph, we initialize it.
        this->addVertex(const_cast<T&>(vertexOrigin));
        // Add the verticesDestination to the set.
        for(auto vertexDestination : vertices){
            verticesDestination.insert(vertexDestination);
        }
    }
    // Then, check if the verticesDestination are in the graph and add the vertex left.
    EdgeListVertex<T, U>* tempVertexPtr = this->vertex;
    while(tempVertexPtr != nullptr){
        // If the vertex is not in the set, we add the vertex.
        verticesDestination.erase(tempVertexPtr->getVertex());
        tempVertexPtr = tempVertexPtr->getNextVertex();
    }
    for(auto vertexDestination : verticesDestination){
        this->addVertex(const_cast<T&>(vertexDestination));
    }
    // Last, add the edges.
    for(auto [vertexOrigin, vertices] : graph){
        EdgeListVertex<T, U>* tempVertexPtr = this->vertex, *vertexOriginPtr = nullptr;
        // Find vertexOrigin and vertexDestination. We are sure that they are in the graph.
        for(auto vertexDestination : vertices){
            EdgeListVertex<T, U>* vertexDestinationPtr = nullptr;
            while(tempVertexPtr != nullptr && (vertexOriginPtr == nullptr || vertexDestinationPtr == nullptr)){
                if(tempVertexPtr->getVertex() == vertexOrigin){
                    vertexOriginPtr = tempVertexPtr;
                }
                if(tempVertexPtr->getVertex() == vertexDestination){
                    vertexDestinationPtr = tempVertexPtr;
                }
                tempVertexPtr = tempVertexPtr->getNextVertex();
            }
            // Add the edges.
            vertexOriginPtr->addEdge(vertexOriginPtr, vertexDestinationPtr);
            // Reset the tempVertexPtr.
            tempVertexPtr = this->vertex;
        }
    }
    // Lastly, EdgeDestinations assignation.
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        EdgeListVertex<T, U>* currentVertexOrigin = this->vertex;
        while(currentVertexOrigin != nullptr){
            EdgeListEdge<T, U>* currentEdgeOrigin = currentVertexOrigin->getNextEdgeOrigin();
            while(currentEdgeOrigin != nullptr){
                if(currentEdgeOrigin->getVertexDestination() == currentVertex->getVertex()){
                    currentVertex->addEdgeDestination(currentEdgeOrigin);
                }
                currentEdgeOrigin = currentEdgeOrigin->getNextEdgeOrigin();
            }
            currentVertexOrigin = currentVertexOrigin->getNextVertex();
        }
        currentVertex = currentVertex->getNextVertex();
    }
}

/*
PARAMETERS: T& vertex, where T is the type of the vertex.
METHOD: Inserts a vertex in the graph in order. If the vertex is already in the graph, it does nothing.
ORDER OF EXECUTION: O(V). Where V is the number of vertices in the graph.
RETURN: None.
*/
template <class T, class U>
void EdgeListGraph<T, U>::addVertex(T& vertex){
    if(this->vertex == nullptr){
        EdgeListVertex<T, U>* newVertex = new EdgeListVertex<T, U>(vertex);
        this->vertex = newVertex;
        return;
    }
    // We will insert the vertex in order by T.
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    // Special case: if the vertex to insert is less than the head of the list.
    if(vertex < currentVertex->getVertex()){
        EdgeListVertex<T, U>* newVertex = new EdgeListVertex<T, U>(vertex);
        newVertex->setNextVertex(currentVertex);
        this->vertex = newVertex;
        return;
    }
    // While the next vertex is not null and the vertex to insert is greater than the next vertex.
    // This will stop when current >= vertex > current->next.
    while(currentVertex->getNextVertex() != nullptr && currentVertex->getNextVertex()->getVertex() <= vertex){
        currentVertex = currentVertex->getNextVertex();
    }
    // If the vertex to insert is equal to the current vertex, we do nothing.
    if(currentVertex->getVertex() == vertex){
        return;
    }
    // If the next vertex is null, we insert the vertex at the end of the list.
    if(currentVertex->getNextVertex() == nullptr){
        EdgeListVertex<T, U>* newVertex = new EdgeListVertex<T, U>(vertex);
        currentVertex->setNextVertex(newVertex);
        return;
    }
    // If the vertex to insert is less than the next vertex, we insert the vertex between the current and the next vertex.
    EdgeListVertex<T, U>* newVertex = new EdgeListVertex<T, U>(vertex);
    newVertex->setNextVertex(currentVertex->getNextVertex());
    currentVertex->setNextVertex(newVertex);
}

/*

*/
template <class T, class U>
void EdgeListGraph<T, U>::updateVertex(const T& vertex, const T& newVertex){
    if(this->vertex == nullptr){
        std::cerr << "The graph is empty.\n";
        return;
    }
    EdgeListVertex<T, U>* currentVertex = this->vertex;
    while(currentVertex != nullptr){
        if(currentVertex->getVertex() == vertex){
            // Verify if the newVertex is already in the graph.
            EdgeListVertex<T, U>* currentVertex2 = this->vertex;
            while(currentVertex2 != nullptr){
                if(currentVertex2->getVertex() == newVertex){
                    std::cerr << "The vertex " << newVertex << " is already in the graph.\n";
                    return;
                }
                currentVertex2 = currentVertex2->getNextVertex();
            }
            // If the vertex is not in the graph, we update it.
            currentVertex->setVertex(newVertex);
            return;
        }
        currentVertex = currentVertex->getNextVertex();
    }
    std::cerr << "The vertex " << vertex << " is not in the graph.\n";

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