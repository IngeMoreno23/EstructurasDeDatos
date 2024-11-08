#include "..\..\DataStructures\Graph\Graph.hpp"
#include "..\..\DataStructures\Graph\ArchPondGraph.hpp"

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void loadGraph(int n, int m, vertContainer<adjContainer<T>>& container){
    if( n < 0 || m < 0 || m > n){
        throw(std::invalid_argument("Valor de vértice inválido"));
    }
    
    container = vertContainer<adjContainer<T>>(); // Aquí hay que estandarizar el código para que funcione con otros que no sean vectores. Y no funcionará si no tiene un constructor con el tamaño como parámetros.
    for(int i = 0; i < n; i++){
        adjContainer<T> temp = adjContainer<T>();
        for(int j = 0; j < m; j++){
            temp.push_back(j);
        }
        container.push_back(temp); 
    }
}

template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void DFS(vertContainer<adjContainer<T>>& container, int n){
    if( n < 0 || n >= container.size()){
        throw(std::invalid_argument("Valor de vértice inválido"));
    }

    std::cout<<"DFS ("<<n<<"): ";
    std::vector<bool> visited(container.size(), false);
    std::stack<int> stack;

    stack.push(n);
    visited[n] = true;

    while(!stack.empty()){
        n = stack.top();
        std::cout << n << " ";
        stack.pop();
        for(const auto& element:container[n]){
            if(!visited[element]){
                visited[element] = true;
                stack.push(element);
            }
        }
    }
    std::cout<<"\n";
}


template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void BFS(vertContainer<adjContainer<T>>& container, int n){
    std::cout<<"\ndep: "<<n<<" "<<container.size();
    if(n < 0 || n >= container.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }

    std::vector<bool> visited(container.size(), false);
    std::queue<int> queue;
    std::cout<<"BFS ("<<n<<"): ";
    visited[n] = true;
    queue.push(n);
    while(!queue.empty()){
        n = queue.front();
        std::cout<<n<<" ";
        queue.pop();
        for(const auto& element:container[n]){
            if(!visited[element]){
                queue.push(element);
                visited[element] = true;
            }
        }
    }
    std::cout<<"\n";
}

template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main(){
    vecGraph<int> testConstInt(3), testAddEdgeInt;
    vecGraph<std::string> testConstStr(6), testAddEdgeStr;
    testConstStr.print();

    // CASOS DE PRUEBA GENERALES DE LA IMPLEMENTACIÓN DE LA LISTA DE ADYACENCIA:
    std::cout<<"> Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existen ninguno de los vértices): \n";
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::cout<<"\n> Impresión de la lista de adyacencia (añadiendo un arco de 1 a 2 cuando no existe vértice 2): \n";
    testAddEdgeInt.addVertex(2);     // Añadir dos vértices, 0 y 1. 
    try{
        testAddEdgeInt.addEdge(1, 2);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar añadir arco: " <<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::cout<<"\n> Impresión de la lista de adyacencia (añadiendo un arco de 2 a 2): \n";
    testAddEdgeInt.addVertex(); // Añadir vértice 2
    testAddEdgeInt.addEdge(1,2);
    testAddEdgeInt.addEdge(2,2);
    testAddEdgeInt.print();

    std::cout<<"\n> Impresión de la lista de adyacencia (quitando el arco inexistente de 1 a 1): \n";
    try{
        testAddEdgeInt.removeEdge(1,1);
    } catch(std::out_of_range& ex){
        std::cout<<"Error al intentar quitar el arco: "<<ex.what()<<"\n";
        testAddEdgeInt.print();
    }

    std::vector<std::vector<int>> container = {{1,2},{0,2,3},{0,1,4},{1,4},{2,3}};
    Graph<> testGraphContainer(container), testLoadGraph;
    std::cout<<"\n> Impresión de la lista de adyacencia creada con un contenedor como parámetro: \n";
    testGraphContainer.print();
    
    std::cout<<"\n> Recorridos DFS: \n";
    DFS(testGraphContainer.adjacencyList, 0);
    DFS(testGraphContainer.adjacencyList, 1);
    
    std::cout<<"\n> Recorridos BFS: \n";
    BFS(testGraphContainer.adjacencyList, 0);
    BFS(testGraphContainer.adjacencyList, 1);
    
    std::cout<<"\n> Recorridos DFS y BFS en grafos vacíos: \n";
    try{
        DFS(testLoadGraph.adjacencyList, 0);
    } catch(std::exception& ex){
        std::cout<<"Error: "<<ex.what()<<"\n";
    }

    try{
        BFS(testLoadGraph.adjacencyList, 0);
    } catch(std::exception& ex){
        std::cout<<"Error: "<<ex.what()<<"\n";
    }

    std::cout<<"\n> Implementación del método loadGraph con una lista de adyacencias como parámetro: \n";
    testLoadGraph.loadGraph(container);
    testLoadGraph.print();

    std::cout<<"\n> Implementación del método loadGraph con valores inválidos: \n";
    try{
        testLoadGraph.loadGraph(-2,3);
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }
    std::cout<<"\n> LoadGraph con más conexiones que vértices (imposible): \n";
    try{
        testLoadGraph.loadGraph(4,5);
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }
    std::cout<<"\n> LoadGraph con más vértices que conexiones (correcto): \n";
    loadGraph(5,4, testLoadGraph.adjacencyList);
    testLoadGraph.print();
}

