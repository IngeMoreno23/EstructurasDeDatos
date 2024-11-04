#include <vector>
#include <iostream>
#include <stack>
#include <queue>

// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. 
template <
    template <typename...> class vertContainer = std::vector, 
    template <typename...> class adjContainer = std::vector, 
    typename T = int>
// Valores por defecto

class Graph{
    using container = vertContainer<adjContainer<T>>;
    private:
        // container nodes;
    public:
        container nodes;

        Graph();
        Graph(int v);
        Graph(const container& adjList);
        Graph(const Graph& otherGraph);
        
        const Graph& operator=(const Graph& otherGraph);

        void loadGraph(int vertices, int connections);
        void loadGraph(const container& adjList);

        void addEdge(int vertex, int connection);
        void addVertex();
        void addVertex(const adjContainer<T>& adjacency);

        void DFS(const container& extContainer);
        void BFS(const container& extContainer);
        void print();

        bool empty();
};

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(){
    nodes = *new container(); // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos. Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const container& adjList){
    nodes = *new container(adjList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
    
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const Graph& otherGraph){
    delete nodes; 
    nodes = *new container(otherGraph.nodes);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
const Graph<vertContainer, adjContainer, T>& Graph<vertContainer, adjContainer, T>::operator=(const Graph& otherGraph){
    delete nodes; 
    nodes = *new container(otherGraph.nodes);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(int v){

    nodes = *new container();
    for(int vx = 0; vx < v; vx++){
        nodes.push_back(adjContainer<T>());
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addEdge(int vertex, int connection){
    if (std::find(nodes[vertex].begin(), nodes[vertex].end(), connection) != nodes[vertex].end()){
        nodes[vertex].push_back(connection); // Esto asume que la estructura de datos utilizada tiene método push_back y tiene sobrecarga de []
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(){
    nodes.push_back(adjContainer<T>());
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(const adjContainer<T>& adjacency){
    nodes.push_back(adjContainer<T>());
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(const container& adjList){
    if(*(this->nodes) == &adjList){
        return;
    }
    delete nodes;

    // opt 1. Las estructuras de datos utilizadas deben tener el operador de asignación sobrecargado.
    this -> nodes = *new container(adjList);
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(int vertices, int connections){
    delete nodes;
    nodes = *new container(); // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int v = 0; v < vertices; v++){
        nodes.push_back(adjContainer<T>(connections)); 
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::print(){
    for(const auto& vector:nodes){ 
        for(const auto& elem:vector){
            std::cout<<elem;
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::DFS(const container& extContainer){
    std::vector<bool> visited(container.size(), false);
    std::queue<int> queue;
    
    while(!queue.empty()){
        queue.push();
    }
    extContainer[0];
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool Graph<vertContainer, adjContainer, T>::empty(){
    return container.size() == 0;
}