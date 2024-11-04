#include <vector>
// Se requiere poner template en cada uno y <typename...> para las plantillas anidadas. Por default, se utiliza std::vector. 
template <
    template <typename...> class vertContainer = std::vector, 
    template <typename...> class adjContainer = std::vector, 
    typename T>

class Graph{
    using container = vertContainer<adjContainer<T>>;
    private:
        container nodes;
    public:
        Graph();
        Graph(int v);
        Graph(const container& adjList);
        Graph(const Graph& otherGraph);
        
        const Graph& operator=(const Graph& otherGraph);

        void loadGraph(int vertices, int connections);
        void loadGraph(const container& adjList);
        void DFS();
        void BFS();
};

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(){
    nodes = container();
    // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. 
    // Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos.
    // Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
Graph<vertContainer, adjContainer, T>::Graph(int v){

    nodes = container();
    for(int vx = 0; vx < v; vx++){
        nodes.push_back(adjContainer())
    }
    // Al parecer los contenedores de la STL se inicializan automáticamente, así que no es necesario poner new. 
    // Además, como son atributos de la clase, sobrevivirán al salir de ámbito. A menos que se tengan punteros como atributos.
    // Pero como es sabido, en funciones, los datos inicializados de cualquier tipo no sobrevivirán al salir del ámbito a menos que se utilice el operador new. 
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(const container& adjList){
    if(*(this->nodes) == &adjList){
        return;
    }
    delete nodes;

    // opt 1. Las estructuras de datos utilizadas deben tener el operador de asignación sobrecargado.
    this -> nodes = container(adjList);
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void Graph<vertContainer, adjContainer, T>::loadGraph(int vertices, int connections){
    delete nodes;
    nodes = new container;

    // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int v = 0; v < vertices; v++){
        nodes.push_back(adjContainer(connections)); 
    }
}
