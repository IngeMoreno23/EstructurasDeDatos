#pragma once

#include <iostream>
#include "Node.cpp" 
#include "NodeC.cpp"
#include "LinkedList.hpp"
#include "HDCLinkedList.hpp"

template <class T>
LinkedList<T>::LinkedList():head(nullptr),size(0){}

template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> elements){
    
    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new Node<T> (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        Node<T>* currentNode = head;
        iterador++;
        size=1;

        for (; iterador != elements.end(); ++iterador){ // se puede no inicializar nada en for
            Node<T>* nextNode = new Node<T> (*iterador); 

            currentNode->setNext(nextNode);
            currentNode=nextNode;
            size++;
        }
        currentNode->setNext(nullptr);

    }
}

template <class T> 
LinkedList<T>:: LinkedList(const LinkedList<T>& listToCopy):head(nullptr), size(0){
    operator=(listToCopy);
}

template <class T> 
LinkedList<T>::~LinkedList(){
    if (size != 0){

        while(head != nullptr){ 
            Node<T> *temp=head; 
            head=head->getNext();
            delete temp; 
        }
        size=0;
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T> & listToCopy){
    if (this == &listToCopy){ 
        return *this;
    }
    
    while(head != nullptr){ 
        Node<T> *temp = head; 
        head = head->getNext();
        delete temp;
    }
    
    size=0;

    if (listToCopy.head == nullptr){
        return *this;
    }

    Node<T>* currentNodeCopy = listToCopy.head, *currentNode = new Node<T> (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){

        Node<T>* nextNode = new Node<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    size = listToCopy.length();
    
    return *this;
}

/*
PARAMETROS: Recibe una posición del nodo en la lista.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
ORDEN: O(n).
RETURN: Regresa como referencia del dato del nodo para que pueda ser modificado.
*/
template <class T>
T& LinkedList<T>::operator[](unsigned int index){

    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    Node<T>* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

template <class T>
void LinkedList<T>::insert(T data, int index){
    insert(* new Node<T> (data), index);
}

/*
PARAMETROS: Recibe un dato del tipo de dato de la lista enlazada.
METODO: Crea un nodo y llama a la función append con ese nuevo nodo como argumento.
ORDEN: O(1).
RETURN: Se añade un nodo a la lista enlazada.
*/
template <class T>
void LinkedList<T>::append(T data){
    Node<T>* temp = new Node<T> (data);
    append(*temp);
    delete temp;
}

/*
PARAMETROS: Recibe un nodo del tipo de dato de la lista enlazada.
METODO: Busca el último elemento de la lista que apunta a un nullptr y hace que este elemento apunte al nodo que recibió como argumento.
ORDEN: O(n).
RETURN: Se añade un nodo a la lista enlazada.
*/
template<class T>
void LinkedList<T>::append(const Node<T>& nodeToAppend){
    if(head == nullptr){
        head = new Node<T> (nodeToAppend.getData());
        size++;
        return;
    }

    Node<T>* currentNode = head;
    while(currentNode->getNext() != nullptr){
        currentNode = currentNode->getNext();
    }

    // Es super necesario crear un nuevo nodo aquí, puesto que el que se manda por referencia puede salir de ámbito y borrarse. 
    currentNode->setNext(new Node<T> (nodeToAppend.getData()));
    size++;
    // A menos que justo se asigne un valor en la memoria manualmente antes de mandar llamar esta función, ahí sí tiene sentido solo hacer que el último nodo apunte a esa función. 
}

/*
PARAMETROS: Recibe una lista enlazada (listToAppend) del tipo de dato de la lista enlazada actual.
METODO: Copia los elementos de listToAppend al final de la lista enlazada actual.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con copias de los nodos de listToAppend al final.
*/
template <class T>
void LinkedList<T>::append(const LinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    Node<T>* currentNode=head, * currentNodeCopy = listToAppend.head;
    while(currentNode->getNext() != nullptr){
        currentNode= currentNode->getNext();
    }
    
    while(currentNodeCopy != nullptr)
    {
        Node<T>* nextNode = new Node<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        currentNode = nextNode;
        
        currentNodeCopy = currentNodeCopy->getNext();
    }
    
    size+=listToAppend.size;

}

/*
PARAMETROS: Ninguno.
METODO: Elimina los nodos de la lista enlazada actual desde el primer elemento al último.
ORDEN: O(n).
RETURN: Lista enlazada actual sin apuntar a ningún nodo.
*/
template <class T>
void LinkedList<T>::empty(){
    while(head != nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        Node<T> *temp=this->head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}

/*
PARAMETROS: Recibe una lista enlazada (listToAppend) del tipo de dato de la lista enlazada actual.
METODO: El último elementos de la lista enlazada actual apunta al primero de la listToAppend. listToAppend ahora no apunta a ningun nodo.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con los nodos de listToAppend al final.
*/
template <class T>
void LinkedList<T>::merge(LinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    Node<T>* currentNode=head;
    while(currentNode->getNext() != nullptr){
        currentNode= currentNode->getNext();
    }

    currentNode->setNext(listToAppend.head);
    size+=listToAppend.size;

    listToAppend.head=nullptr; // Considero que no es necesario borrar manualmente la lista segunda. Puesto que esta solo contiene variables, size, head;
    listToAppend.size=0; // El peligro de esta función es que si la segunda se sale de su ámbito será borrada la otra sección de la lista. La creación de este método fue mera experimentación. 

}

/*
PARAMETROS: Recibe un nodo y una posición en donde insertar el nodo.
METODO: Verifica que la posición se encuentre entre el primer elemento y el tamaño de la lista, si es así, busca el elemento anterior a esa posición
a hace que ese nodo apunte al nuevo nodo, y el nuevo nodo apunte a la posición del siguiente nodo. Si no cumple la condición añade al final.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con un nodo extra en la posición indicada.
*/
template <class T>
void LinkedList<T>::insert(const Node<T>& nodeToInsert, int position){
    if(position >= size || position < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    Node<T>* currentNode = head;
    for(int i = 0; i < position - 1; i++){
        currentNode = currentNode->getNext();
    }

    Node<T>* newNode = new Node<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    currentNode->setNext(newNode);
    size++;

}

/*
PARAMETROS: Recibe la posición de un nodo a eliminar.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size. Busca el nodo en esa posición y lo elimina,
el nodo anterior ahora apunta al nodo al que apuntaba el nodo que se elimino.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con el nodo de esa posición eliminado.
*/
template <class T>
void LinkedList<T>::erase(int index){
    if(index >= size || index < 0 || head == nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (size == 1){
        delete head; 
        head=nullptr;
        size=0;
        return;
    }


    Node<T>* currentNode=head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (index == 0){
        head=currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i=0;i < index-1; i++){
            currentNode=currentNode->getNext();
        }
        Node<T>*temp = currentNode->getNext();
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    size--;
    
}

/*
PARAMETROS: Recibe un dato del tipo de dato del nodo y una posición del nodo en la lista.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
Remplaza el dato del nodo en la posición del argumento con el dato recibido en el argumento
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con un nodo extra en la posición indicada.
*/
template <class T>
void LinkedList<T>::update(T data, int index){

    if(index < 0 || index >= size){
        return; 
    }

    operator[](index)=data;
}

/*
PARAMETROS: Rebibe la lista a ordenar y su número de nodos.
METODO: Utiliza el algoritmo divide y venceras, que separa la lista a la mitad varias veces hasta tener listas de 1 nodo, compara los datos de estos nodos
y acomoda los nodos de menor a mayor de forma recursiva hasta ordenarlos en la lista original.
ORDEN: O(nlog(n)).
RETURN: Regresa la lista enlazada con sus nodos ordenados de menor a mayor según sus datos.
*/
template <class T>
void LinkedList<T>::ordMerge(LinkedList<T> &l, int n){
    if (n == 1) return;
    int mitad = n / 2;
    LinkedList<T> l1, l2;
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);
    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (l1[i] > l2[j]) {
            l[k] = l2[j];
            j++;
        } else {
            l[k] = l1[i];
            i++;
        }
        k++;
    }
    while (i < mitad) {
        l[k] = l1[i];
        i++;
        k++;
    }
    while (j < n - mitad) {
        l[k] = l2[j];
        j++;
        k++;
    }
}

template <class T>
int LinkedList<T>::length() const {
    return size;

}

template <class T>
bool LinkedList<T>::isEmpty(){
    if (head == nullptr){
        return true;
    }
    return false;
}

/*
PARAMETROS: Rebibe un dato a buscar en la lista enlazada actual.
METODO: Compara el dato de cada nodo en la lista hasta encontrar uno que coincida.
ORDEN: O(n).
RETURN: Regresa la posición del primer nodo que coincida con el dato, si no se encuentra, regresa -1.
*/
template <class T>
int LinkedList<T>::search(T data){
    Node<T>* currentNode=this->head;

    int i=0;
    while(currentNode->getNext() != nullptr && currentNode->getNext() != head ){
        if (currentNode->getData() == data){
            return i;
        }
        i++;
        currentNode=currentNode->getNext();
    }
    return -1;
}

/*
PARAMETROS: Rebibe 2 posiciones de nodos de la lista enlazada actual que intercambiaran de valor.
METODO: Busca la el dato de los 2 nodos que se quieren cambiar, y remplaza solo los datos que contienen.
ORDEN: O(n).
RETURN: Regresa la lista actual con 2 nodos que intercambiaron su valor.
*/
template <class T>
void LinkedList<T>::exchange(int indexA, int indexB){
    T buffer = operator[](indexA);
    operator[](indexA) = operator[](indexB);
    operator[](indexB) = buffer;
}

/*
PARAMETROS: Nada.
METODO: Remplaza los datos de la posición actual y la posición size-posición actual, remplazando el primer elemento y el último hasta llegar a la mitad de la lista.
ORDEN: O(n).
RETURN: Regresa la lista actual con los datos de los nodos remplazados de inicio a fin.
*/
template <class T>
void LinkedList<T>::invert(){
    int positionA = 0, half = (size % 2 ==0) ? size/2: 1 + size/2;
    while(positionA < half){
        exchange(positionA,size-positionA-1);
        positionA++;
    }
}

/*
PARAMETROS: Nada.
METODO: Recorre cada nodo e imprime los datos de cada uno en la consola.
ORDEN: O(n).
RETURN: Imprime los datos de los nodos de la lista en la consola.
*/
template <class T>
void LinkedList<T>::print(){
    Node<T>* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    while(currentNode != nullptr){
        std::cout<<currentNode->getData()<<" ";
        currentNode=currentNode->getNext();
    }
    std::cout<<"\n";
}

/*
PARAMETROS: Recibe una posición del nodo en la lista.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
ORDEN: O(n).
RETURN: Regresa como referencia del dato del nodo para que pueda ser modificado.
*/
template <class T>
T& LinkedList<T>::at(int position){
    return operator[](position-1);
}