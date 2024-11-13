#include <iostream> 
#include "..\..\DataStructures\Graph\Graph.hpp"



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



template <typename T>
using vecGraph = Graph<std::vector, std::vector, T>; // Alias template 

int main()
{
    vecGraph<int> testGraphContainer({{1,2},{0,2,3},{0,1,4},{1,4},{2,3}}), testGraphContainer2({{1},{2},{3},{4},{0}}), testGraphContainer3({{1},{2},{1},{0},{0}});

    // PRUEBA DE FUNCIONALIDADES DE LOS MÉTODOS IMPLEMENTADOS.
    Graph<> functionTestGraph;

    testGraphContainer.topologicalSort();
    std::cout<<"\nEs bipartito: ";
    std::cout<<bipartiteGraph(testGraphContainer2.adjacencyList);
    std::cout<<"\nEs bipartito: ";
    std::cout<<bipartiteGraph(testGraphContainer3.adjacencyList);
}