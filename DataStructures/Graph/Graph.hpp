#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>
#include <algorithm>

// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. Coloco el último T porque es posible que se implemente con structs, para guardar el índice al que apunta
template <
    template <typename...> class vertContainer = std::vector, 
    template <typename...> class adjContainer = std::vector, 
    typename T = int>
// Valores por defecto
class Graph{
    using container = vertContainer<adjContainer<T>>;
    using iterator_type = decltype(std::declval<adjContainer<T>>().begin()); // Obtiene el tipo de dato que regresa .begin, que debe ser un apuntador. Pero quizá no todas las TAD tengan el nombre ::iterator, dentro de sus funcionalidades.

    private:
        bool directed;
        // container adjacencyList;
    public:
        container adjacencyList;

        Graph();
        Graph(bool _directed = true);
        Graph(int v, bool _directed = true);
        Graph(const container& adjList, bool _directed = true);
        Graph(const Graph& otherGraph, bool _directed = true);
        
        const Graph& operator=(const Graph& otherGraph);

        void loadGraph(int vertices, int connections);
        void loadGraph(const container& adjList);

        void addEdge(int vertex, int connection);
        void addVertex();
        void addVertex(const adjContainer<T>& adjacency);

        int hasEdge(int vertex, int connection, iterator_type& it);
        void removeEdge(int vertex0, int vertex1);

        void DFS(int index);
        void BFS(int index);
        void print();

        bool empty();
        void clear();
};

/*
PARAMETROS: void.
MÉTODO: Constructor por defecto. Inicializa la lista de adyacencia.
ORDER: O(1)
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(){
    adjacencyList = *new container(); // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos. Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

/*
PARAMETROS: const container& adjList, es una lista de adyacencia que se utilizará para inicializar la lista de adyacencia del grafo.
            bool _directed, indica si el grafo es dirigido o no.
MÉTODO: Se inicializa la lista de adyacencia con la lista de adyacencia adjList.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const container& adjList, bool _directed):directed(_directed){
    adjacencyList = *new container(adjList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

/*
PARAMETROS: const Graph& otherGraph, otro grafo que se utilizará para inicializar la lista de adyacencia del grafo.
            bool _directed, indica si el grafo es dirigido o no.
MÉTODO: Se inicializa una nueva lista de adyacencia con la lista de adyacencia de otherGraph.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en otherGraph.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const Graph& otherGraph, bool _directed):directed(_directed){
    delete adjacencyList; 
    adjacencyList = *new container(otherGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

/*
PARAMETROS: const Graph& otherGraph, otro grafo que se utilizará para inicializar la lista de adyacencia del grafo.
MÉTODO: Si existe una lista de adyacencia, la elimina, y la asigna a la lista de adyacencia de otherGraph a la del grafo.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en otherGraph.
RETORNA: const Graph<vertContainer, adjContainer, T>&, una referencia al grafo actual.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
const Graph<vertContainer, adjContainer, T>& Graph<vertContainer, adjContainer, T>::operator=(const Graph& otherGraph){
    delete adjacencyList; 
    adjacencyList = *new container(otherGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

/*
PARAMETROS: int v, el número de vértices del grafo.
            bool _directed, indica si el grafo es dirigido o no.
MÉTODO: Crear un grafo con v vértices y sin aristas.
ORDER: O(V), donde V es el número de vértices del grafo.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(int v, bool _directed): directed(_directed){

    adjacencyList = *new container();
    for(int vx = 0; vx < v; vx++){
        adjacencyList.push_back(adjContainer<T>());
    }
}

/*
PARAMETROS: int vertex, índice del vértice al que se le quiere agregar una arista.
            int connection, índice del vértice al que se le quiere conectar el vértice.
MÉTODO: Verifica si existe una arista entre vertex y connection. Si existe, se agrega una arista entre vertex.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addEdge(int vertex, int connection){
    iterator_type it;
    if (!hasEdge(vertex, connection, it)){
        adjacencyList[vertex].push_back(connection); // Esto asume que la estructura de datos utilizada tiene método push_back y tiene sobrecarga de []
    }
    if(directed){
        if (!hasEdge(connection, vertex, it)){
            adjacencyList[connection].push_back(vertex); 
        }
    }
}

/*
PARAMETROS: int vertex, vertice al que se le quiere verificar si tiene una arista con connection.
            int connection, vertice al que se le quiere verificar si tiene una arista con vertex.
            iterator_type& it, vertice al que se le quiere verificar si tiene una arista con vertex.
MÉTODO: find() verifica que existe connection en la lista de adyacencia de vertex.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: bool, true si existe una arista entre vertex y connection, false en otro caso.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
int Graph<vertContainer, adjContainer, T>::hasEdge(int vertex, int connection, iterator_type& it){
    it = std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection);
    return it != adjacencyList[vertex].end();
}

/*
PARAMETROS: void.
MÉTODO: Agraga un vértice al final de la lista de adyacencia.
ORDER: O(1)
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(){
    adjacencyList.push_back(adjContainer<T>());
}

/*
PARAMETROS: const adjContainer<T>& adjacency, vertice con su lista de adyacencia que se quiere agregar al grafo.
MÉTODO: Agrega un vértice al final de la lista de adyacencia con sus aristas. Si es un grafo no dirigido, se agregan las aristas correspondientes.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(const adjContainer<T>& adjacency){
    adjacencyList.push_back(std::move(adjacency));
    if(!directed){
        for(const auto& element:adjacency){
            addEdge(element, adjacencyList.size()-1);
        }
    }
}

/*
PARAMETROS: int vertex0, vertice de origen de la arista.
            int vertex1, vertice de destino de la arista.
MÉTODO: Verifica si existe una arista entre vertex0 y vertex1. Si existe, se elimina la arista.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex0.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::removeEdge(int vertex0, int vertex1){
    iterator_type it;
    if(!hasEdge(vertex0, vertex1, it)){
        throw(std::out_of_range("The graph does not have that edge"));
    }
    adjacencyList[vertex0].erase(it);
}

/*
PARAMETROS: const container& adjList, lista de adyacencia que se utilizará para inicializar la lista de adyacencia del grafo.
MÉTODO: Verifica si la lista de adyacencia es la misma que la lista de adyacencia del grafo.
        Si no lo es, se elimina la lista de adyacencia y se asigna la lista de adyacencia adjList a la lista de adyacencia del grafo.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(const container& adjList){
    if(*(this->adjacencyList) == &adjList){
        return;
    }
    delete adjacencyList;

    this -> adjacencyList = *new container(adjList);
}

/*
PARAMETROS: int vertices, 
            int connections, 
MÉTODO: Se elimina la lista de adyacencia y se crea una nueva lista de adyacencia con vertices vértices y connections aristas.
ORDER: 
RETORNA: 
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(int vertices, int connections){
    delete adjacencyList;
    adjacencyList = *new container(); // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int v = 0; v < vertices; v++){
        adjacencyList.push_back(adjContainer<T>(connections)); 
    }
}

/*
PARAMETROS: void.
MÉTODO: Por cada vértice en la lista de adyacencia, se imprimen sus aristas. Si esta vacía, se imprime un corchete vacío.
ORDER: O(V+E), donde V es el número de vértices del grafo y E es el número de aristas.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::print(){
    std::cout<<"Impresión de la lista de adyacencia: \n";
    int i = 0;
    for(const auto& vertVec:adjacencyList){
        std::cout <<i<<": ";
        if (vertVec.empty()){
            std::cout<<"[]\n";
        } else{
            for(const auto& adj:vertVec){
                std::cout<<adj<<" ";
            }
            std::cout<<"\n";
        }
        i++;
    }
    std::cout<<"\n";
}

/*
PARAMETROS: 
MÉTODO: 
ORDER: 
RETORNA: 
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::BFS(int index){
    if(index < 0 || index >= adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }

    std::vector<bool> visited(adjacencyList.size(), false);
    std::queue<int> queue;
    std::cout<<"BFS: ";
    visited[index] = true;
    queue.push(index);
    while(!queue.empty()){
        index = queue.front();
        std::cout<<index<<" ";
        queue.pop();
        for(const auto& element:adjacencyList[index]){
            if(!visited[element]){
                queue.push(element);
                visited[element] = true;
            }
        }
    }
    std::cout<<"\n";
}

/*
PARAMETROS: 
MÉTODO: 
ORDER: 
RETORNA: 
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::DFS(int index){
    if(index < 0 || index > adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }
    std::cout<<"DFS: ";
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<int> stack;

    stack.push(index);
    visited[index] = true;

    while(!stack.empty()){
        index = stack.top();
        std::cout << index << " ";
        stack.pop();
        for(const auto& element:adjacencyList[index]){
            if(!visited[element]){
                visited[element] = true;
                stack.push(element);
            }
        }
    }
    std::cout<<"\n";
}

/*
PARAMETROS: 
MÉTODO: 
ORDER: 
RETORNA: 
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool Graph<vertContainer, adjContainer, T>::empty(){
    return adjacencyList.size() == 0;
}