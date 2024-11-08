#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>
#include <algorithm>

// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. Coloco el último T porque es posible que se implemente con structs, para guardar el índice al que apunta

template <class T>
class Graph{
    using adjMat = std::vector<std::vector<T>>;
    private:
        // adjMat adjacencyList;
        bool directed; 
    public:
        adjMat adjMatrix;

        Graph(bool _directed = true);
        Graph(int v);
        Graph(const adjMat& otherAdjMatrix);
        Graph(const Graph& otherGraph);
        
        const Graph& operator=(const Graph& otherGraph);

        void addEdge(int vertex, int connection, bool isDirected);
        void addEdge(int vertex, int connection, T weight, bool isDirected);
        void addVertex();
        void addVertex(const std::vector<T>& adjacency, bool isDirected);

        void removeEdge(int vertex0, int vertex1, bool isDirected);
        void removeVertex(int vertex);
        

        void DFS(int index);
        void BFS(int index);
        void print();

        bool empty();
};

template <class T>
Graph<T>::Graph(bool isDirected):directed(isDirected){
    adjMatrix = *new adjMat;
}

template <class T>
Graph<T>::Graph(int v){
    directed = true;
    for(int i = 0; i < v; i++)
    adjMatrix.push_back(std::vector<T>(v, 0));
}

template <class T> 
Graph<T>::Graph(const adjMat& otherAdjMatrix){
    adjMatrix = *new adjMat(otherAdjMatrix);
    /*
    adjMatrix = otherAdjMatrix;
    for(int i = otherAdjMatrix.size(); )
    */
    for(int i = 0; i < otherAdjMatrix.size(); i++){
        for(int j = otherAdjMatrix[i].size(); j < otherAdjMatrix.size(); j++){
            adjMatrix[i][j] = 0;
        }
    }
}

template<class T>
Graph<T>::Graph(const Graph& otherGraph){
    adjMatrix = otherGraph.adjMatrix;
}

template<class T>
const Graph<T>& Graph<T>::operator=(const Graph& otherGraph){
    if(this == &otherGraph){
        return *this;
    }
    
    delete adjMatrix;
    adjMatrix = *new adjMat(otherGraph.adjMatrix);
}


template <class T>
void Graph<T>::addEdge(int vertex, int connection, bool isDirected){
    if(vertex >= adjMatrix.size() || connection >= adjMatrix.size()){
        throw std::out_of_range("Vertex out of range");
    }
    adjMatrix[vertex][connection] = 1;
    if(!isDirected){
        adjMatrix[connection][vertex] = 1;
    }
}

template <class T>
void Graph<T>::addEdge(int vertex, int connection, T weight, bool isDirected){
    if(vertex >= adjMatrix.size() || connection >= adjMatrix.size()){
        throw std::out_of_range("Vertex out of range");
    }
    adjMatrix[vertex][connection] = weight;
    if(!isDirected){
        adjMatrix[connection][vertex] = weight;
    }
}

/*
MÉTODO: Agrega un vector del tamaño de la matriz de adyacencia, con valores 0. 
Luego agregamos un 0 a cada vector de la matriz de adyacencia.
*/
template <class T>
void Graph<T>::addVertex(){
    adjMatrix.push_back(std::vector<T>(adjMatrix.size(), 0));
    for(int i = 0; i < adjMatrix.size(); i++){
        adjMatrix[i].push_back(0);
    }
}

template <class T>
void Graph<T>::addVertex(const std::vector<T>& adjacency, bool isDirected){
    if(adjacency.size() != adjMatrix.size()){
        throw std::invalid_argument("Adjacency vector size does not match the number of vertices");
    }
    adjMatrix.push_back(adjacency);
    if(!isDirected){
        for(int i = 0; i < adjMatrix.size(); i++){
            adjMatrix[i].push_back(adjacency[i]);
        }
    }
}

template <class T>
void Graph<T>::removeEdge(int vertex0, int vertex1, bool isDirected){
    if(vertex0 >= adjMatrix.size() || vertex1 >= adjMatrix.size()){
        throw std::out_of_range("Vertex out of range");
    }
    adjMatrix[vertex0][vertex1] = 0;
    
    if(!isDirected){
        adjMatrix[vertex1][vertex0] = 0;
    }
}

template <class T>
void Graph<T>::removeVertex(int vertex){
    if(vertex >= adjMatrix.size()){
        throw std::out_of_range("Vertex out of range");
    }
    adjMatrix.erase(adjMatrix.begin() + vertex);
    for(int i = 0; i < adjMatrix.size(); i++){
        adjMatrix[i].erase(adjMatrix[i].begin() + vertex);
    }
}

template <class T>
void Graph<T>::DFS(int index){
    std::vector<bool> visited(adjMatrix.size(), false);
    std::stack<int> stack;
    stack.push(index);
    while(!stack.empty()){
        int current = stack.top();
        stack.pop();
        if(!visited[current]){
            visited[current] = true;
            std::cout << current << " ";
            for(int i = 0; i < adjMatrix.size(); i++){
                if(adjMatrix[current][i] != 0 && !visited[i]){
                    stack.push(i);
                }
            }
        }
    }
}

template <class T>
void Graph<T>::BFS(int index){
    std::vector<bool> visited(adjMatrix.size(), false);
    std::queue<int> queue;
    queue.push(index);
    while(!queue.empty()){
        int current = queue.front();
        queue.pop();
        if(!visited[current]){
            visited[current] = true;
            std::cout << current << " ";
            for(int i = 0; i < adjMatrix.size(); i++){
                if(adjMatrix[current][i] != 0 && !visited[i]){
                    queue.push(i);
                }
            }
        }
    }
}

template <class T>
void Graph<T>::print(){
    for(int i = 0; i < adjMatrix.size(); i++){
        for(int j = 0; j < adjMatrix.size(); j++){
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

template <class T>
bool Graph<T>::empty(){
    return adjMatrix.size() == 0;
}