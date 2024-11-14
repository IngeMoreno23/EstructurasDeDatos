#include <iostream> 
#include <sstream>
#include "Graph.hpp"

/*
PARAMETROS: int& val.
MÉTODO: Verifica que la entrada del usuario sea de tipo int y la regresa en el argumento val.
ORDER: O(1).
RETORNA: bool.
*/
bool aceptaEnteros(int& val){
    std::stringstream buffer(""); 
    std::string tempInput;
    std::getline(std::cin, tempInput);
    buffer<<tempInput; 
    std::cin.clear();
    if(!(buffer >> val)){
        return false; 
    }
    return true;
}

/*
PARAMETROS: int n, cantidad de vértices.
            int m, Graph<vertContainer, cantidad de aristas.
            adjContainer, T>& graph, grafo a cargar por referencia.
MÉTODO: Inicializa una vector de n vectores (listas de adyacencia) y se pregunta al usuario por las aristas.
        Se verifica que los vértices sean válidos (entre los índices del vector) y se añaden al grafo.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void loadGraph(int n, int m, Graph<vertContainer, adjContainer, T>& graph){
    if( n <= 0){
        throw(std::invalid_argument("Valor de vértice inválido"));
    } else if ( m < 0){
        throw(std::invalid_argument("Número de arcos inválido"));
    }

    int origen = 0, destino = 0; // NO poner unsigned int porque reintrepreta los negativos como positivos
    std::stringstream buffer(""); 
    std::string tempInput;
    graph.adjacencyList = vertContainer<adjContainer<T>>(n); 
    for(int i = 0; i < m; i++){
// Código para aceptar sólo enteros 
        std::cout<<"Ingrese el vértice de origen (vertice origen, vertice destino):\n(";
        std::getline(std::cin, tempInput);
        buffer<<tempInput;
        while(!(buffer >> origen)){
            std::cin.clear();
            std::cout<<"\n"<<buffer.str()<<" es una entrada inválida. Ingrese enteros (vertice origen, vertice destino):\n (";
            buffer.str("");
            buffer.clear(); // ES necesario poner clear.
            std::getline(std::cin, tempInput); 
            buffer<<tempInput;
        }
        std::cin.clear();
        buffer.str("");
        buffer.clear();

        std::cout<<"Ingrese el vértice de destino (vertice origen, vertice destino): \n("<<origen<<", ";
        std::getline(std::cin, tempInput);
        buffer<<tempInput;
        while(!(buffer >> destino) || destino < 0){
            std::cin.clear();
            std::cout<<")\n"<<buffer.str()<<" es una entrada inválida. Ingrese enteros (vertice origen, vertice destino):\n("<<origen<<", ";
            buffer.str("");
            buffer.clear(); // ES necesario poner clear.
            std::getline(std::cin, tempInput); // Poner ignore después de getline hace que se trabe porque getline pasa todo el stream de bits a tempInput, y cuando se quiere ignorar, está vacío el stream
            buffer<<tempInput;
        }

        try{
            if(graph.hasEdge(origen, destino)){
                std::cout<<"El grafo ya contiene ese arco\n\n"; // En nuestra implementación de grafo, no arroja error al intentar añadir un arco que ya existe, así que para cumplir con los requisitos de la actividad, se ha implementado fuera de la función.
                i--;
            } else{
                graph.addEdge(origen, destino);
                std::cout<<"\nEl arco ("<<origen<<", "<<destino<<") se ingresó correctamente !\n";
            }
        }catch(std::exception& ex){
            std::cout<<"\nUna de las entradas fue inválida. Que los vértices sean un valor entre el primer y el último vértice (0, # vertices - 1)\n";
            i--;
        }
        std::cin.clear();
        buffer.str("");
        buffer.clear();
    }
}

/*
> PARÁMETROS: adjacencyList (lista de adyacencia con los vértices y sus respectivas conexiones), V (el vértice a partir del cual se desea realizar el dfs), visited (vector con los vértices ya visitados), vertexOrdered (stack que guarda los datos en orden topológico), m (entero que indica cuantos arcos se quieren mostrar).
> MÉTODO: Realiza un recorrido DFS recursivo por cada vértice no visitado. Hasta que llega al último vértice al que puede a partir del vértice inicial especificado, lo agrega a la pila y se regresa al vértice pasado para explorar los vértices vecinos aún no visitados.
> ORDEN: O(V + E)
> RETORNO: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void topologicalSortRec(vertContainer<adjContainer<T>>& adjacencyList, int v, std::vector<bool>& visited, std::stack<T>& vertexOrdered, int& m){
    visited[v] = true;
    for(const auto& neighbor:adjacencyList[v]){
        if(!visited[neighbor]){ 
            topologicalSortRec(adjacencyList, neighbor, visited, vertexOrdered, m);
            if(vertexOrdered.size() > m){
                break;
            }
        }
    }
    vertexOrdered.push(v);
}

/*
> PARÁMETROS: adjacencyList (lista de adyacencia con los vértices y sus respectivas conexiones), n (entero que indica a partir de qué vértice se quiere empezar), m (entero que indica cuantos arcos se quieren mostrar).
> MÉTODO: Realiza un recorrido DFS recursivo por cada vértice no visitado. Imprime la pila con los vértices en orden topológico.
> ORDEN: O(V + E)
> RETORNO: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void topologicalSort(vertContainer<adjContainer<T>>& adjacencyList, int n, int m){
    if(n >= adjacencyList.size()){
        throw(std::invalid_argument("Parámetro inválido"));
    }
    if (n < 0 || m < 0){
        throw(std::out_of_range("Parámetros fuera de rango"));
    }
    std::vector<bool> visited(adjacencyList.size(), false);
    std::stack<T> vertexOrdered;

    for(int v = n; v < adjacencyList.size() && m > 0; v++){
        if(!visited[v]){
            topologicalSortRec(adjacencyList, v, visited, vertexOrdered, m);
        }
    }
    if(m > vertexOrdered.size()){
        std::cout<<"Cantidad de arcos excede los vértices a mostrar. Se mostrará el orden topológico del grafo: ";
    }
    for(int i = 0; i < m && !vertexOrdered.empty(); i++){
        std::cout<<vertexOrdered.top()<<" ";
        vertexOrdered.pop();
    }
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
    if(n >= graph.size()){
        throw(std::invalid_argument("Parámetro inválido"));
    }
    if (n < 0 || m < 0){
        throw(std::out_of_range("Parámetros fuera de rango"));
    }
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

// Es una alternativa un poco costosa pero muy efectiva para los grafos dirigidos que tienen varias conexiones a ciclos existentes, pues con este no se tienen problemas al colorear o al guardar en conjuntos.
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
struct JohnsonCycleDetector{
    private:
        std::vector<std::vector<int>> B; // Guarda la trayectoria de los grafos para bloquearlos o desbloquearlos.
        std::vector<bool> blocked; // vectores bloqueados (no son parte de ciclos)
        std::vector<int> stack;  // Guarda el recorrido, potencialmente un ciclo.
        int V; // Tamaño de la lista de adyacencia

    public:
        bool oddCycle;
        // std::set<std::vector<int>> cycles; // Aquí se guardan los ciclos encontrados, pero para este proceso no se requiere la estructura de datos.
        JohnsonCycleDetector(vertContainer<adjContainer<T>>& adjacencyList){
            oddCycle = false; 
            this -> V = adjacencyList.size();
            B.resize(V); // Se cambia el tamaño a la cantidad de vértices que tiene el grafo.
            blocked.resize(V, false); 

            for (int i = 0; i < V; ++i) {
                std::fill(blocked.begin(), blocked.end(), false); // Reset a los vértices bloqueados, tanto en blocked como en B.
                for (auto& list : B) {
                    list.clear();
                }
                findCyclesFrom(i, i, adjacencyList);
            }
        }
        // Encuentra los ciclos a partir de start. Parámetros: 
        bool findCyclesFrom(int v, int start, vertContainer<adjContainer<T>>& adjacencyList){ // v es el vértice actual 
            bool hasCycle = false; 
            stack.push_back(v); // Agrega el vértice al stack que almacena ciclos.
            blocked[v] = true;  // Bloquea el vértice en caso de que no se contenga un ciclo.

            for(int w: adjacencyList[v]){
                if(w == start){ 
                    /*  // Si ha regresado al vértice inicial, originalmente se agrega el ciclo al set de ciclos, pero en esta modificación, solo se revisa si el ciclo tiene longitud impar. Se comentaron las líneas del algoritmo que no se requieren en esta implementación, pues no se necesitan visualizar los ciclos, solo requiero la cantidad de vértices en ellos
                    stack.push_back(start); 
                    cycles.insert(stack);
                    stack.pop_back();
                    */
                    if (stack.size() % 2 == 1){
                        oddCycle = true;
                    }
                    hasCycle = true; 
                } else if(!blocked[w]){
                    if (findCyclesFrom(w, start, adjacencyList)){
                        hasCycle = true;
                    }
                }
            }
            if(hasCycle){ // Se desbloquea el vértice si sí se encontró un ciclo. En caso de no encontrarlo, se bloquean todos los vértice en la trayectoria recorrida que no tienen ciclo. 
                unblock(v);
            } else{
                for(int w: adjacencyList[v]){
                    if (find(B[w].begin(), B[w].end(), v) == B[w].end()) {
                        B[w].push_back(v);
                    }
                }
            }

            stack.pop_back();
            return hasCycle;

        }

        void unblock(int u) {
            blocked[u] = false;
            for (int w : B[u]) {
                if (blocked[w]) {
                    unblock(w);
                }
            }
            B[u].clear();
        }


};

/*
> PARÁMETROS: adjacencyList(estructura de datos con estructuras de dato dentro, en este caso un vector de vectores de enteros)
> MÉTODO: Aplica el algoritmo de Johnson para detectar ciclos. Si detecta un ciclo de longitud impar, no es bipartito (porque no se pueden dividir en dos sets sin elementos repetidos)
> ORDEN: O((V + E)(C + 1)). V = número de vértices. E = número de aristas/arcos. C = número de ciclos elementales.
> RETORNO: valor booleano, que determina si es bipartito o no. 
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
bool bipartiteGraph(vertContainer<adjContainer<T>>& adjacencyList){
    for(const auto& list:adjacencyList){ // Checa si algún vértice en un grafo (no cargado con loadGraph) apunta a uno que no esté contenido.
        for(const auto& vertex:list){
            if(vertex >= adjacencyList.size()){
                throw(std::out_of_range("Uno o más vértices contienen arcos a vértices inexistentes"));
            }
        }
    }
    JohnsonCycleDetector detectCycles(adjacencyList);
    return detectCycles.oddCycle;
}

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main()    // PRUEBA DE FUNCIONALIDADES DE LOS MÉTODOS IMPLEMENTADOS.
{
    vecGraph<int> testGraphContainer({{1,2},{0,2,3},{0,1,4},{1,4},{2,3}}), errorGraph({{2},{4},{5}}), testGraphContainer2({{1},{2},{0}}), testGraphContainer3({{1},{2},{3},{0},{0}});
    vecGraph<int> loadedGraph;

    std::cout<<"Carga tu grafo.\n";
    try{
        int vertices = 0, conexiones = 0;
        std::cout<<"Ingresa la cantidad de vértices: ";
        while(!aceptaEnteros(vertices)){
            std::cout<<"\nEntrada inválida. Ingrese un entero: ";
        }
        std::cout<<"Ingresa la cantidad de arcos: ";
        while(!aceptaEnteros(conexiones)){
            std::cout<<"\nEntrada inválida. Ingrese un entero: ";
        }
        std::cout<<"\n";
        loadGraph(vertices,conexiones,loadedGraph);
        loadedGraph.print();
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }
    std::cout<<"\n";

    try{
        int n = 0, m = 0;
        while(std::cout<<"Mostrar a partir del vértice: " && !aceptaEnteros(n)){
            std::cout<<"\nSolo enteros. ";
        }
        while(std::cout<<"Cantidad de arcos: " && !aceptaEnteros(m)){
            std::cout<<"\nSolo enteros. ";
        }
        std::cout<<"Ordenamiento topológico: ";
        topologicalSort(testGraphContainer.adjacencyList, n, m);
    }catch(std::exception& ex){
        std::cout<<"Error. "<<ex.what();
    }
    std::cout<<"\n";

    try{ // Intentando con un grafo con vértices fuera de rango
        std::cout<<"\nEs bipartito: "<<bipartiteGraph(errorGraph.adjacencyList);
    } catch(std::exception& ex){
        std::cout<<"Error. "<< ex.what();
    }
    std::cout<<"\n";
    // PROBAR CON EL GRAFO CARGADO
    try{
        std::cout<<"\nEl grafo cargado es bipartito: "<<bipartiteGraph(loadedGraph.adjacencyList);
    } catch(std::exception& ex){
        std::cout<<"Error. "<< ex.what();
    }
    std::cout<<"\n";

    try{
        int w = 0, x = 0;
        while(std::cout<<"A partir del vértice: " && !aceptaEnteros(w)){
            std::cout<<"\nSolo enteros positivos. ";
        }
        while(std::cout<<"Arcos: " && !aceptaEnteros(x)){
            std::cout<<"\nSolo enteros positivos. ";
        }
        std::cout<<"El grafo cargado es arbol: "<<isTree(loadedGraph.adjacencyList, w, x);
    } catch(std::exception& ex){
        std::cout<<"Error. "<<ex.what();
    }
}