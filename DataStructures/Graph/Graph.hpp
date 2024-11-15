#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <stdexcept>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <iterator>

template <template <typename...> class vertContainer = std::vector, template <typename...> class adjContainer = std::vector, typename T = int>
bool canDFS(int vertex, int parent, vertContainer<adjContainer<T>>& graph, std::vector<bool>& isVisited);

template <template <typename...> class vertContainer = std::vector, template <typename...> class adjContainer = std::vector, typename T = int>
bool isTree(vertContainer<adjContainer<T>>& graph, int n, int m);

template<typename weight_type>
struct arch{
    weight_type weight;
    int destination;
};

template <template <typename...> class vertContainer = std::vector, template <typename...> class adjContainer = std::vector, typename T = int>
using container = vertContainer<adjContainer<T>>;

// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. Coloco el último T porque es posible que se implemente con structs, para guardar el índice al que apunta
template <
    template <typename...> class vertContainer = std::vector, 
    template <typename...> class adjContainer = std::vector, 
    typename T = int>
// Valores por defecto
class Graph{
    private:
        bool directed;
    public:
        using container = vertContainer<adjContainer<T>>;
        using iterator_type = decltype(std::declval<adjContainer<T>>().begin()); // Obtiene el tipo de dato que regresa .begin, que debe ser un apuntador. Pero quizá no todas las TAD tengan el nombre ::iterator, dentro de sus funcionalidades.

        container adjacencyList;

        Graph(bool _directed = true);
        Graph(int v, bool _directed = true);
        Graph(const container& adjList, bool _directed = true);
        Graph(const Graph& otherGraph, bool _directed = true);

        ~Graph();
        
        // const Graph& operator=(const Graph& otherGraph); // NO es necesario

        void loadGraph(int vertices, int connections);
        void loadGraph(const container& adjList);

        void addEdge(int vertex, int connection);
        void addVertex(int n = 1);
        void addVertex(const adjContainer<T>& adjacency);

        int hasEdge(int vertex, int connection, iterator_type& it); // Existe solo para cuando, de existir el arco, se realice una operación con este. 
        int hasEdge(int vertex, int connection);
        void removeEdge(int vertex0, int vertex1);

        void DFS(int index);
        void BFS(int index);
        void print();

        bool empty();
        void clear();

        void topologicalSort();
        void topologicalSortRec(int v, std::vector<bool>& visited, std::stack<T>& stack);
};

/*
PARAMETROS: bool _directed, indica si el grafo es dirigido o no.
MÉTODO: Inicializa la lista de adyacencia vacia.
ORDER: O(1)
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(bool _directed):directed(_directed){
    adjacencyList = container(); // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos. Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
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
    adjacencyList = container(adjList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
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
    
    adjacencyList = container(otherGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
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

    adjacencyList = container();
    for(int vx = 0; vx < v; vx++){
        adjacencyList.push_back(adjContainer<T>());
    }
}

/*
PARAMETROS: void.
MÉTODO: Destructor de la clase Graph.
ORDER: O(1).
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::~Graph(){} // los contenedores se borran cuando el objeto sale de ámbito. Como tal, los contenedores deberían tener su administración de la memoria.

/*
PARAMETROS: int vertex, índice del vértice al que se le quiere agregar una arista.
            int connection, índice del vértice al que apuntará el vértice.
MÉTODO: Verifica que los vertices esten en el rango de los índices del vector. Agrega una arista a vertex que apunta a connection.
        Si el grafo no es dirigido, agrega una arista de connection a vertex.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addEdge(int vertex, int connection){
    // Esto se podría incluir, pero en la implementación de un grafo, puede que se agreguen conexiones a vertices que aún no forman parte pero eventualmente lo harán. Arrojar una excepcion, consider que sería más pertinente hacerlo en un hasEdge. Tampoco creo factible el hecho de crear un nuevo vertice o n vertices hasta llegar al vertice que se busca conectar.
    // Pero entonces, no le veo mucho sentido a un vector que no tenga los vertices completos hasta el vertice que quiere conectar. Pero el vertice de destino, considero yo, el error de no existir debería ser arrojado en otra función
    
    if(vertex < 0 || vertex >= adjacencyList.size() || connection < 0 || connection >= adjacencyList.size()){
        throw(std::out_of_range("No existe tal vértice"));
    }
    
    iterator_type it;
    if (!hasEdge(vertex, connection, it)){
        adjacencyList[vertex].push_back(connection); // Esto asume que la estructura de datos utilizada tiene método push_back y tiene sobrecarga de []
    }
    if(!directed){
        if (!hasEdge(connection, vertex, it)){
            adjacencyList[connection].push_back(vertex); 
        }
    }
}

/*
PARAMETROS: int vertex, vertice desde donde apunta la arista.
            int connection, vertice hacia donde apunta la arista.
            iterator_type& it, vertice (de tipo lista de adyacencia) donde se encuentra la arista.
MÉTODO: find() verifica que existe connection en la lista de adyacencia de vertex.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: int, 1 si existe la arista, 0 si no existe.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
int Graph<vertContainer, adjContainer, T>::hasEdge(int vertex, int connection, iterator_type& it){
    if(vertex < 0 || vertex >= adjacencyList.size() || connection < 0 || connection >= adjacencyList.size()){
        throw(std::out_of_range("No existe tal vértice"));
    }

    it = std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection);
    return it != adjacencyList[vertex].end();
}

/*
PARAMETROS: int vertex, vertice desde donde apunta la arista.
            int connection, vertice hacia donde apunta la arista.
MÉTODO: Verifica si vertex tiene una arista que apunta a connection.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: int, 1 si existe la arista, 0 si no existe.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
int Graph<vertContainer, adjContainer, T>::hasEdge(int vertex, int connection){
    if(vertex < 0 || vertex >= adjacencyList.size() || connection < 0 || connection >= adjacencyList.size()){
        throw(std::out_of_range("No existe tal vértice"));
    }
    return std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection) != adjacencyList[vertex].end();
}

/*
PARAMETROS: int n, cantidad de vértices a añadir.
MÉTODO: Agraga n vértices sin aristas al final de la lista de adyacencia.
ORDER: O(n), donde n es la cantidad de vértices a añadir.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(int n){
    if(n < 0){
        throw(std::invalid_argument("Función de adición de vértices solo acepta valores positivos"));
    }
    for(int i = 0; i < n; i++){
        adjacencyList.push_back(adjContainer<T>()); // Necesario poner el <T> después de adjContainer.
    }
}

/*
PARAMETROS: const adjContainer<T>& adjacency, vertice (de tipo lista de adyacencia) que se quiere agregar al grafo.
MÉTODO: Agrega un vértice al final de la lista de adyacencia con sus aristas. Si es un grafo no dirigido, se agregan las aristas correspondientes.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(const adjContainer<T>& adjacency){
    adjacencyList.push_back(std::move(adjacency));
    if(!directed){
        for(const auto& element:adjacency){
            addEdge(element, adjacencyList.size() -1);
        }
    }
}

/*
PARAMETROS: int vertex0, vertice origen de la arista.
            int vertex1, vertice destino de la arista.
MÉTODO: Verifica si existe una arista entre vertex0 y vertex1. Si existe, se elimina la arista.
ORDER: O(E), donde E es el número de aristas en la lista de adyacencia de vertex0.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::removeEdge(int vertex0, int vertex1){
    iterator_type it;
    if(!hasEdge(vertex0, vertex1, it)){
        throw(std::out_of_range("El grafo no contiene tal arco"));
    }
    adjacencyList[vertex0].erase(it);
}

/*
PARAMETROS: const container& adjList, lista de adyacencia que se utilizará para inicializar la lista de adyacencia del grafo.
MÉTODO: Verifica si la lista de adyacencia es la misma que la lista de adyacencia del grafo.
        Si no lo es, se reemplaza la lista de adyacencia con adjList a la lista de adyacencia del grafo.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(const container& adjList){
    if(&adjacencyList == &adjList){
        return;
    }
    adjacencyList = container(adjList);
}

/*
PARAMETROS: int vertices, 
            int connections, 
MÉTODO: Se reemplaza el grafo actual con un grafo con vertices vértices y connections aristas.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(int vertices, int connections){
    if( vertices < 0 || connections < 0 || connections > vertices){
        throw(std::invalid_argument("Valor de vértice inválido"));
    }
    adjacencyList = container(); // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int v = 0; v < vertices; v++){
        adjContainer<T> temp = adjContainer<T>();
        for(int i = 0; i < connections; i++){
            temp.push_back(i);
        }
        adjacencyList.push_back(temp); 
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
    std::cout<<"[\n";
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
    std::cout<<"]\n";
}

/*
PARAMETROS: vertContainer<adjContainer<T>>& container, contenedor de vértices.
            int n, índice de inicio de recorrido.
MÉTODO: Realiza un recorrido en amplitud en el grafo a partir del índice n.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::BFS(int index){
    if(index < 0 || index >= adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }

    std::vector<bool> visited(adjacencyList.size(), false);
    std::queue<int> queue;
    std::cout<<"BFS ("<<index<<"): ";
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
PARAMETROS: vertContainer<adjContainer<T>>& container, contenedor de vértices.
            int n, índice de inicio de recorrido.
MÉTODO: Realiza un recorrido en profundidad en el grafo a partir del índice n.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::DFS(int index){
    if(index < 0 || index >= adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }
    std::cout<<"DFS ("<<index<<"): ";
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<int> stack;

    stack.push(index);

    while(!stack.empty()){
        index = stack.top();
        stack.pop();
        
        if(!visited[index]){
            visited[index] = true;
            std::cout << index << " ";
            for(const auto& element:adjacencyList[index]){
                if(!visited[element]){
                    stack.push(element);
                }
            }
        }
    }
    std::cout<<"\n";
}

/*
PARAMETROS: void.
MÉTODO: Verifica que la cantidad de vértices sea 0.
ORDER: O(1).
RETORNA: bool, true si el grafo no tiene vértices, false en otro caso.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool Graph<vertContainer, adjContainer, T>::empty(){
    return adjacencyList.size() == 0;
}

/*
PARAMETROS: void.
MÉTODO: Si la lista de adyacencia está vacía, no hace nada. Si no, la limpia asignando una lista de vértices vacia.
ORDER: O(1).
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::clear(){
    if(adjacencyList.size() == 0){
        return;
    }

    adjacencyList = container(); // Esto es posible porque el contenedor, en su sobrecarga de asignación, ya tiene un proceso que elimina los datos actuales y cambia a los datos nuevos. No necesito eliminar el contenedor, dentro de su implementación se hace todo esto.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::topologicalSort(){
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<T> vertexOrdered;

    for(int v = 0; v < adjacencyList.size(); v++){
        if(!visited[v]){
            topologicalSortRec(v, visited, vertexOrdered);
        }
    }

    while(!vertexOrdered.empty()){
        std::cout<<vertexOrdered.top()<<" ";
        vertexOrdered.pop();
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::topologicalSortRec(int v, std::vector<bool>& visited, std::stack<T>& vertexOrdered){
    visited[v] = true;
    for(int i = 0; i < adjacencyList[v].size(); i++){
        if(!visited[i]){ 
            topologicalSortRec(i, visited, vertexOrdered);
        }
    }
    vertexOrdered.push(v);
}

/*
PARAMETROS: int vertex, vértice actual.
            int parent, vértice de la recursión anterior, padre directo.
            vertContainer<adjContainer<T>>& graph, 
            std::vector<bool>& isVisited, 
MÉTODO: Si la lista de adyacencia está vacía, no hace nada. Si no, la limpia asignando una lista de vértices vacia.
ORDER: O(V+E),  donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: bool. true si no encuentra ciclos, false si encuentra ciclos.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool canDFS(int vertex, int parent, vertContainer<adjContainer<T>>& graph, std::vector<bool>& isVisited){

    isVisited[vertex] = true;

    for(int v : graph[vertex]){
        if(!isVisited[v]){
            if(!canDFS(v, vertex, graph, isVisited))
                return false;
        } else { // Si ya esta visitado y su padre no es el de la llamada recursiva sino otro, es un ciclo.
            if(v != parent)
                return false;
        }
    }
    return true;
}

/*
PARAMETROS: vertContainer<adjContainer<T>>& graph, grafo al que se verificara la existencia de un árbol.
            int n, número de vertices.
            int m, número de aristas.
MÉTODO: Si la lista de adyacencia está vacía, no 1 menos que el número de vértices. Que no haya ciclos en el grafo,
        y que todos sus nodos hayan sido visitados sin ciclos.hace nada. Si no, la limpia asignando una lista de vértices vacia.
ORDER: O(V+E),  donde V es el número de vértic tiene estructura de árbolde aristas no tiene estructura de árbolORNA: bool. true si no encuentra ciclos, false si encuentra ciclos.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool isTree(vertContainer<adjContainer<T>>& graph, int n, int m){
    if(n-1 != m)
        return false;

    std::vector<bool> isVisited(n, false);
    
    if(!canDFS(0, -1, graph, isVisited))
        return false;

    for(bool v : isVisited){
        if(!v)
            return false;
    }

    return true;
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
inline bool bipartiteGraphHelper(vertContainer<adjContainer<T>>& adjacencyList, 
                                std::vector<bool>& visited, 
                                std::unordered_set<int>& setA, 
                                std::unordered_set<int>& setB, 
                                std::unordered_set<int> *currentSet, 
                                bool isSetA, 
                                int current){

    for(const auto& vertex:adjacencyList[current]){
        if(visited[vertex]) {
            if((!isSetA && setA.count(vertex)) || (isSetA && setB.count(vertex))) {
                return false;
            }
            continue;
        }
        visited[vertex] = true;
        if(!(currentSet -> insert(vertex).second))
            return false;
        if(!bipartiteGraphHelper(adjacencyList, visited, setA, setB, (isSetA) ? &setB : &setA, !isSetA, vertex))
            return false;
    }
    return true;
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool bipartiteGraph(vertContainer<adjContainer<T>>& adjacencyList){
    std::vector<bool> visited(adjacencyList.size(), false);
    std::unordered_set<int> setA, setB;

    int i = 0; 
    for(const auto& adjList:adjacencyList){    
        if(visited[i]){
            i++;
            continue;
        }
        visited[i] = true;

        if(!setA.insert(i).second){
            return false;
        }
        if(!bipartiteGraphHelper(adjacencyList, visited, setA, setB, &setB, false, i)){
            return false;
        }
        i++;
    }
    return true;
}