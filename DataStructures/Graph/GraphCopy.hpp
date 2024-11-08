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
    public:
        container adjacencyList;

        Graph(bool _directed = true);
        Graph(int v, bool _directed = true);
        Graph(const container& adjList, bool _directed = true);
        Graph(const Graph& otherGraph, bool _directed = true);

        ~Graph();
        
        const Graph& operator=(const Graph& otherGraph);

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

        bool isTree();
        bool bipartiteGraph();
        void topologicalSort();
};

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(bool _directed):directed(_directed){
    adjacencyList = container(); // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos. Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const container& adjList, bool _directed):directed(_directed){
    adjacencyList = container(adjList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(const Graph& otherGraph, bool _directed):directed(_directed){
    
    adjacencyList = container(otherGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
const Graph<vertContainer, adjContainer, T>& Graph<vertContainer, adjContainer, T>::operator=(const Graph& otherGraph){
    adjacencyList = container(otherGraph.adjacencyList);  // ESTO CONFÍA EN QUE LA ESTRUCTURA DE DATOS UTILIZADA TIENE SOBRECARGADO EL OPERADOR DE ASIGNACIÓN.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(int v, bool _directed): directed(_directed){

    adjacencyList = container();
    for(int vx = 0; vx < v; vx++){
        adjacencyList.push_back(adjContainer<T>());
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::~Graph(){} // los contenedores se borran cuando el objeto sale de ámbito. Como tal, los contenedores deberían tener su administración de la memoria.

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

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
int Graph<vertContainer, adjContainer, T>::hasEdge(int vertex, int connection, iterator_type& it){
    if(vertex < 0 || vertex >= adjacencyList.size() || connection < 0 || connection >= adjacencyList.size()){
        throw(std::out_of_range("No existe tal vértice"));
    }

    it = std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection);
    return it != adjacencyList[vertex].end();
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
int Graph<vertContainer, adjContainer, T>::hasEdge(int vertex, int connection){
    if(vertex < 0 || vertex >= adjacencyList.size() || connection < 0 || connection >= adjacencyList.size()){
        throw(std::out_of_range("No existe tal vértice"));
    }
    return std::find(adjacencyList[vertex].begin(), adjacencyList[vertex].end(), connection) != adjacencyList[vertex].end();
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(int n){
    if(n < 0){
        throw(std::invalid_argument("Función de adición de vértices solo acepta valores positivos"));
    }
    for(int i = 0; i < n; i++){
        adjacencyList.push_back(adjContainer<T>()); // Necesario poner el <T> después de adjContainer.
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::addVertex(const adjContainer<T>& adjacency){
    adjacencyList.push_back(std::move(adjacency));
    if(!directed){
        for(const auto& element:adjacency){
            addEdge(adjacencyList.size(), element);
        }
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::removeEdge(int vertex0, int vertex1){
    iterator_type it;
    if(!hasEdge(vertex0, vertex1, it)){
        throw(std::out_of_range("El grafo no contiene tal arco"));
    }
    adjacencyList[vertex0].erase(it);
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(const container& adjList){
    if(&adjacencyList == &adjList){
        return;
    }
    adjacencyList = container(adjList);
}

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

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::DFS(int index){
    if(index < 0 || index >= adjacencyList.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }
    std::cout<<"DFS ("<<index<<"): ";
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

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool Graph<vertContainer, adjContainer, T>::empty(){
    return adjacencyList.size() == 0;
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::clear(){
    if(adjacencyList.size() == 0){
        return;
    }

    adjacencyList = container(); // Esto es posible porque el contenedor, en su sobrecarga de asignación, ya tiene un proceso que elimina los datos actuales y cambia a los datos nuevos. No necesito eliminar el contenedor, dentro de su implementación se hace todo esto.
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool Graph<vertContainer, adjContainer, T>::isTree(){

}