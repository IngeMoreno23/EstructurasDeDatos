/*
Cristian Ricardo Luque Arámbula - A01741850
Oliver Moreno Ibarra - A01742930
Rodolfo Blas Romero Valdez - A01741665
Última modificación: 07/11/2024

*/

#include "..\..\DataStructures\Graph\Graph.hpp"

#include <sstream>
#include <string>
#include <iostream>

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
PARAMETROS: vertContainer<adjContainer<T>>& container, contenedor de vértices.
            int n, índice de inicio de recorrido.
MÉTODO: Realiza un recorrido en profundidad en el grafo a partir del índice n.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void DFS(vertContainer<adjContainer<T>>& container, int n){
    if(n < 0 || n >= container.size()){
        throw(std::out_of_range("El índice se encuentra fuera de rango"));
    }
    std::cout<<"DFS ("<<n<<"): ";
    std::vector<bool> visited(container.size(), false);
    std::stack<int> stack;

    stack.push(n);

    while(!stack.empty()){
        n = stack.top();
        stack.pop();
        
        if(!visited[n]){
            visited[n] = true;
            std::cout << n << " ";
            for(const auto& element:container[n]){
                if(!visited[element]){
                    stack.push(element);
                }
            }
        }
    }
    std::cout<<"\n";

}

/*
PARAMETROS: vertContainer<adjContainer<T>>& container, contenedor de vértices.
            int n, índice de inicio de recorrido.
MÉTODO: Realiza un recorrido en amplitud en el grafo a partir del índice n.
ORDER: O(V+E), donde V es el número de vértices y E es el número de aristas en adjList.
RETORNA: void.
*/
template <template <typename...> class vertContainer, template <typename...> class adjContainer, typename T>
void BFS(vertContainer<adjContainer<T>>& container, int n){
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
    vecGraph<int> vertexInit(3), defaultInit; // Inicializaciones. 
    vecGraph<std::string> vertexInitStr(6), defaultInitStr;
    Graph<> testGraphContainer({{1,2},{0,2,3},{0,1,4},{1,4},{2,3}});

    // PRUEBA DE FUNCIONALIDADES DE LOS MÉTODOS IMPLEMENTADOS.
    Graph<> functionTestGraph;

    std::cout<<"\n> Impresión de la lista de adyacencia creada con un contenedor como parámetro: \n";
    testGraphContainer.print();
    
    std::cout<<"\n> Implementación del método loadGraph con valores potencialmente inválidos: \n";
    try{
        int vertices = 0, conexiones = 0;
        std::cout<<"Ingresa la cantidad de vértices: ";
        while(!aceptaEnteros(vertices)){
            std::cout<<"\n"<<"Entrada inválida. Ingrese un entero: ";
        }
        std::cout<<"\nIngresa la cantidad de arcos: ";
        while(!aceptaEnteros(conexiones)){
            std::cout<<"\n"<<"Entrada inválida. Ingrese un entero: ";
        }
        std::cout<<"\n";
        loadGraph(vertices,conexiones,functionTestGraph);
        functionTestGraph.print();
    } catch(std::invalid_argument& ex){
        std::cout<<"Error al intentar cargar grafo: "<<ex.what()<<"\n";
    }

    int startingn = 0;
    std::cout<<"\n> Recorridos DFS y BFS en el grafo construido a partir del índice: ";
    while(!aceptaEnteros(startingn)){
        std::cout<<"\nEntrada inválida. Ingrese un entero: ";
    }
    try{
        DFS(functionTestGraph.adjacencyList, startingn);
    } catch(std::exception& ex){
        std::cout<<"Error: "<<ex.what()<<"\n";
    }

    try{
        BFS(functionTestGraph.adjacencyList, startingn);
    } catch(std::exception& ex){
        std::cout<<"Error: "<<ex.what()<<"\n";
    }
}

