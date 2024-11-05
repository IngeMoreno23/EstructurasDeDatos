#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>
#include "ArchPond.hpp"

// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. Coloco el último T porque es posible que se implemente con structs, para guardar el índice al que apunta
template <
    template <typename...> class vertContainer = std::vector, 
    template <typename...> class adjContainer = std::vector, 
    typename T = ArchPond<int, double>>
// Valores por defecto

class ArchPondGraph{
    using container = vertContainer<adjContainer<T>>;
    private:
        // container adjacencyList;
    public:
        container adjacencyList;

        ArchPondGraph();
        ArchPondGraph(bool _directed = true);
        ArchPondGraph(int v);
        ArchPondGraph(const container& adjList);
        ArchPondGraph(const ArchPondGraph& otherArchPondGraph);
        
        const ArchPondGraph& operator=(const ArchPondGraph& otherArchPondGraph);

        void loadArchPondGraph(int vertices, int connections);
        void loadArchPondGraph(const container& adjList);

        void addEdge(int vertex, int connection, bool directed);
        void addVertex();
        void addVertex(const adjContainer<T>&& adjacency);

        void removeEdge(int vertex0, int vertex1);

        void DFS(int index);
        void BFS(int index);
        void print();

        bool empty();
};

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
ArchPondGraph<vertContainer, adjContainer, T>::ArchPondGraph(){
    adjacencyList = *new container(); // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos. Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
ArchPondGraph<vertContainer, adjContainer, T>::ArchPondGraph(const container& adjList){
    adjacencyList = *new container(adjList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
ArchPondGraph<vertContainer, adjContainer, T>::ArchPondGraph(const ArchPondGraph& otherArchPondGraph){
    delete adjacencyList; 
    adjacencyList = *new container(otherArchPondGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
const ArchPondGraph<vertContainer, adjContainer, T>& ArchPondGraph<vertContainer, adjContainer, T>::operator=(const ArchPondGraph& otherArchPondGraph){
    delete adjacencyList; 
    adjacencyList = *new container(otherArchPondGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
ArchPondGraph<vertContainer, adjContainer, T>::ArchPondGraph(int v){

    adjacencyList = *new container();
    for(int vx = 0; vx < v; vx++){
        adjacencyList.push_back(adjContainer<T>());
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::addEdge(int vertex, int connection, bool directed){
    if (std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection) != adjacencyList[vertex].end()){
        adjacencyList[vertex].push_back(connection); // Esto asume que la estructura de datos utilizada tiene método push_back y tiene sobrecarga de []
    }
    if(directed){
        if (std::find(adjacencyList[connection].begin(), adjacencyList[connection].end(), vertex) != adjacencyList[vertex].end()){
            adjacencyList[connection].push_back(vertex); 
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::addVertex(){
    adjacencyList.push_back(adjContainer<T>());
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::addVertex(const adjContainer<T>&& adjacency){
    adjacencyList.push_back(std::move(adjacency));
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::removeEdge(int vertex0, int vertex1){
    for(const auto vertex:adjacencyList[vertex0]){
        if(vertex == vertex1){
            adjacencyList[vertex0].erase(vertex);
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::loadArchPondGraph(const container& adjList){
    if(*(this->adjacencyList) == &adjList){
        return;
    }
    delete adjacencyList;

    // opt 1. Las estructuras de datos utilizadas deben tener el operador de asignación sobrecargado.
    this -> adjacencyList = *new container(adjList);
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::loadArchPondGraph(int vertices, int connections){
    delete adjacencyList;
    adjacencyList = *new container(); // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int v = 0; v < vertices; v++){
        adjacencyList.push_back(adjContainer<T>(connections)); 
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::print(){
    for(const auto& vector:adjacencyList){ 
        for(const auto& elem:vector){
            std::cout<<elem;
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::BFS(int index){
    if(index < 0 || index >= adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }

    std::vector<bool> visited(adjacencyList.size(), false);
    std::queue<int> queue;

    visited[index] = true;
    queue.push(index);
    while(!queue.empty()){
        index = queue.front();
        std::cout<<index<<"\n";
        queue.pop();
        for(const auto& element:adjacencyList[index]){
            if(!visited[element]){
                queue.push(element);
                visited[element] = true;
            }
        }
    }    
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void ArchPondGraph<vertContainer, adjContainer, T>::DFS(int index){
    if(index < 0 || index > adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }

    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<int> stack;

    stack.push(index);
    visited[index] = true;

    while(!stack.empty()){
        index = stack.top();
        std::cout << index << "\n";
        stack.pop();
        for(const auto& element:adjacencyList[index]){
            if(!visited[element]){
                visited[element] = true;
                stack.push(element);
            }
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool ArchPondGraph<vertContainer, adjContainer, T>::empty(){
    return adjacencyList.size() == 0;
}
