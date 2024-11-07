EdgeListGraph

Construction of a EdgeListGraph

by constructor:
pasing matrix in format:
{ {vertex, vertexDestination},
  {vertex_n, vertexDestination_n} }
EdgeListGraph(std::initializer_list<std::initializer_list<T>> matrix){

    for(auto& edge : matrix){
        if{edge[0] not in this->vertexlist}
            appendVertex(edge[0])       // appendVertex(T data)
        EdgeListEdge(edge[0], edge[1])        // EdgeListEdge(T vertexOrigin, T data)

        // doing a sort append
    }
}




que necesito

EdgeListEdge
Set - Crear edges solo con T& vertexOrigin, T& vertexDestination, por referencia desde el dato de vertex
Update - Modificar el peso con U newWeight

EdgeListVertex
Set - Crear vertex




que quiero hacer
- crear un grafo completo, deberá tener opcion para hacer 
- agregar vertices junto con arcos con formato {T, init_list<T>}

- añadir vertices
- modificar vertices (incluirá modificar los arcos)
- quitar vertices

- añadir arcos
- NO EXISTIRÁ MODIFICAR arco
- eliminar arco

EdgeListGraph
Constructor (std::initializer_list<std::initializer_list<T>>)- Crear una grafo completo con el formato:
        { {vertex, vertexDestination},
        {vertex_n, vertexDestination_n} }

Set - appendVertex(T vertexData) - Añadir un vector solo con el dato-key.
    **Estarán ordenados por T vertex de menor a mayor.**

    Verifica si ya existe.
    La inserción debe verificar
        que no este vacio
        que **SI ES MENOR INSERTAMOS WAZAAAAA** 
        


    **A CADA CONDICION, DEBEMOS DE VERIFICAR SI YA HAY UN VERTICE IGUAL**
    **SI ES IGUAL, std::cerr << "Vertice ya existente.\n" RETURN**
    condicion base -> **SI vertexData < this->head **
        el primero es mayor al argumento
        volver el argumento cabeza y que apunte al antes primer head.
    
    **while -> current.getNextVertex() != nullptr && vertex > current.getNextVertex()->getVertex().
    condicion loop -> **SI vertexData < current.nextVertex->getVertex() || current.nextVertex == nullptr -> APPEND**
        si el siguiente es mayor
        añadirlo despues del actual

Update - updateVertex(T vertexToUpdate, T newVertexKey) - Cambiar el dato-key de T vertex.
    Recorrera la lista de vertices.
    Verifica si existe, 
    **RECORRER PRIMERA VEZ PARA VERIFICAR QUE newVertexKey NO ESTE CREADO**
    **SI NO SE ENCUENTRA vertexToUpdate, REGRESA UN CERR**

    SI SE ENCUENTRA:

    misma logica para reacomodar que el anterior,

    verificar que el newVertexKey sea menor que el current.getVertex()
    condicion base_0 -> **newVertexKey < vertexToUpdate**
        current = head  **// ESTO SE HACE PORQUE PROBABLEMENTE NO ESTE ACOMODADO**

    condition base ->