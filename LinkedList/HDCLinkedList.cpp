#pragma once

#include <string>
#include <iostream>

#include "HDCLinkedList.hpp"

#include "LinkedList.cpp"
#include "NodeC.cpp"

template <class T>
HDCLinkedList<T>::HDCLinkedList():LinkedList<T>(){ 
    this->head = new NodeC<T>;

    this->head->setNext(nullptr);
    this->head->setPrevious(nullptr);
        
}

template <class T>
HDCLinkedList<T>::HDCLinkedList(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head = nullptr;
    } else{
        auto iterador = elements.begin(); 

        this->head = new NodeC<T> (*iterador); 
        NodeC<T>* currentNode = static_cast<NodeC<T>*>(this->head);
        currentNode->setPrevious(static_cast<NodeC<T>*>(this->head));
        iterador++;
        this->size = 1;

        for (; iterador != elements.end(); ++iterador){

            NodeC<T>* nextNode = new NodeC<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode = nextNode;
            this->size++;
        }
        
        currentNode->setNext(this->head);
        static_cast<NodeC<T>*>(this->head)->setPrevious(currentNode);
    }
}

template <class T>
HDCLinkedList<T>:: HDCLinkedList(const HDCLinkedList<T>& listToCopy){
    this->head = new NodeC<T>;

    this->head->setNext(this->head);
    static_cast<NodeC<T>*>(this->head)->setPrevious(static_cast<NodeC<T>*>(this->head));
        
    *this = listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T> 
HDCLinkedList<T>::~HDCLinkedList() {
    if(this->size == 0){
        delete this->head;
        return;
    }

    empty();
    
    delete this->head;

    this->size=0; 
}

/*
PARAMETROS: Rebibe una lista doble circular (listToCopy) por referencia.
METODO: Vacia la lista actual y crea nuevos nodos copiando el dato de los nodos del listToCopy.
ORDEN: O(n).
RETURN: Regresa como referencia la lista doble circular actual.
*/
template <class T>
const HDCLinkedList<T>& HDCLinkedList<T>::operator=(const HDCLinkedList<T> & listToCopy){
    if (this == &listToCopy){ 
        return *this;
    }
    
    empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    NodeC<T>* currentNodeCopy = static_cast<NodeC<T>*>(listToCopy.head), *currentNode = new NodeC<T> (currentNodeCopy->getData());
    this->head = currentNode;

    currentNodeCopy = static_cast<NodeC<T>*>(currentNodeCopy->getNext());

    while(currentNodeCopy != listToCopy.head){

        NodeC<T>* nextNode = new NodeC<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=static_cast<NodeC<T>*> (currentNodeCopy->getNext());
        currentNode=nextNode;
    }
    currentNode->setNext(this->head);
    static_cast<NodeC<T>*>(this->head)->setPrevious(currentNode);

    this->size = listToCopy.size;

    return *this;
}

/*
PARAMETROS: Recibe un nodo del tipo de dato de la lista enlazada.
METODO: Busca el último elemento de la lista que apunta a un nullptr y hace que este elemento apunte al nodo que recibió como argumento.
ORDEN: O(n).
RETURN: Se añade un nodo a la lista enlazada.
*/
template<class T>
void HDCLinkedList<T>::append(const NodeC<T>& nodeToAppend){
    if(this->head->getNext() == nullptr){
        NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
        this->head=newNode;
        newNode->setPrevious(static_cast<NodeC<T>*>(this->head));
        newNode->setNext(this->head);
        this->size++;
        return;
    }

    NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
    static_cast<NodeC<T>*>(this->head)->getPrevious()->setNext(newNode);
    newNode->setNext(this->head);
    newNode->setPrevious(static_cast<NodeC<T>*>(this->head)->getPrevious());
    static_cast<NodeC<T>*> (static_cast<NodeC<T>*>(this->head))->setPrevious(newNode);
    this->size++;
}

/*
> PARAMETROS: Recibe una lista enlazada circular doble (listToAppend) del tipo de dato de la lista enlazada actual.
> METODO: Copia los elementos de listToAppend al final de la lista enlazada actual.
> ORDEN: O(n).
> RETURN: Regresa la lista enlazada actual con copias de los nodos de listToAppend al final.
*/
template <class T>
void HDCLinkedList<T>::append(const HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    NodeC<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;
    if(currentNode == nullptr){
        currentNode = this->head;
    }
    
    do{
        NodeC<T>* nextNode = new NodeC<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
        
        currentNodeCopy = static_cast<NodeC<T>*>(currentNodeCopy->getNext());
    } while(currentNodeCopy != listToAppend.head);
    
    currentNode->setNext(this->head);
    currentNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(currentNode);
    this->size += listToAppend.size;

}

/*
PARAMETROS: Recibe una lista enlazada circular doble (listToAppend) del tipo de dato de la lista enlazada actual.
METODO: El último elementos de la lista enlazada actual apunta al primero de la listToAppend. listToAppend ahora no apunta a ningun nodo.
ORDEN: O(1).
RETURN: Regresa la lista enlazada actual con los nodos de listToAppend al final.
*/
template <class T>
void HDCLinkedList<T>::merge(HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    NodeC<T>* listToAppendHeadCopy = new NodeC<T> (listToAppend.head->getData());    
    NodeC<T>* temp = static_cast<NodeC<T>*>(this->head)->getPrevious();

    temp->setNext(listToAppendHeadCopy);
    listToAppend.head->getPrevious()->setNext(this->head);
    
    listToAppendHeadCopy->setPrevious(temp);
    this->head->setPrevious(static_cast<NodeC<T>*>(listToAppend.head)->getPrevious()); // cambié aquí
    listToAppendHeadCopy->setNext(listToAppend.head->getNext());
    this->size+=listToAppend.size;

    listToAppend.head->setNext(nullptr);
    listToAppend.head->setPrevious(nullptr);
    listToAppend.size=0;
}

/*
PARAMETROS: Recibe un nodo y una posición en donde insertar el nodo.
METODO: Verifica que la posición se encuentre entre el primer elemento y el tamaño de la lista, si es así, busca el elemento anterior a esa posición
a hace que ese nodo apunte al nuevo nodo, y el nuevo nodo apunte a la posición del siguiente nodo. Si no cumple la condición añade al final.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con un nodo extra en la posición indicada.
*/
template <class T>
void HDCLinkedList<T>::insert(const NodeC<T>& nodeToInsert, int index){
    if(index >= this->size || index < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    NodeC<T>* currentNode = this->head;
    for(int i = 1; i < index; i++){
        currentNode= static_cast<NodeC<T>*>(currentNode->getNext());
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    NodeC<T>* newNode = new NodeC<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    newNode->setPrevious(currentNode);
    
    static_cast <NodeC<T>*> (newNode->getNext()) -> setPrevious(newNode);

    currentNode->setNext(newNode);
    this->size++;

}

/*
PARAMETROS: Nada.
METODO: Obtiene el ultimo nodo (nodo anterior a cabeza) y el anterior a este, el nodo anterior ahora apunta a la cabeza y eliminamos el último nodo.
ORDEN: O(1).
RETURN: Regresa la lista enlazada actual sin el último nodo.
*/
template <class T>
void HDCLinkedList<T>::pop(){
    
    NodeC<T>* temp= this->head-> getPrevious();
    temp->getPrevious()->setNext(this->head);
    delete temp;

}

/*
PARAMETROS: Recibe la posición de un nodo a eliminar.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size. Busca el nodo en esa posición y lo elimina,
el nodo anterior ahora apunta al nodo al que apuntaba el nodo que se elimino y el siguiente también apunta a él.
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con el nodo de esa posición eliminado.
*/
template <class T>
void HDCLinkedList<T>::erase(int index){
    if(index >= this->size || index < 0 || this->head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }


    NodeC<T>* currentNode = static_cast<NodeC<T>*>(this->head); // una variable que guarda un apuntador. NO es memoria dinámica.

    if (index == 1){
        this->head = static_cast<NodeC<T>*>(currentNode->getNext());
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i = 0;i <= index; i++){
            currentNode = static_cast<NodeC<T>*>(currentNode->getNext());
        }
        NodeC<T>*temp = static_cast<NodeC<T>*>(currentNode->getNext());
        static_cast<NodeC<T>*>(temp->getNext())->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    this->size--;
    
}

/*
PARAMETROS: Nada.
METODO: Recorre cada nodo desde head hasta llegar a el mismo e imprime los datos de cada nodo en la consola.
ORDEN: O(n).
RETURN: Imprime los datos de los nodos de la lista en la consola.
*/
template <class T>
void HDCLinkedList<T>::print(){
    if (this->size == 0){
        std::cout<<"size= "<<this->size<<" elements: ";
        return;
    }
    NodeC<T>* currentNode = static_cast<NodeC<T>*>(this->head);

    std::cout<<"size= "<<this->size<<" elements: ";

    do{
        std::cout<<currentNode->getData()<<" ";
        currentNode = static_cast<NodeC<T>*>(currentNode->getNext());
    }while(currentNode != this->head);
    std::cout<<"\n";
}

/*
PARAMETROS: Recibe un dato del tipo de dato de la lista enlazada doble circular.
METODO: Crea un nodo y llama a la función append con ese nuevo nodo como argumento.
ORDEN: O(1).
RETURN: Se añade un nodo a la lista enlazada.
*/
template <class T>
void HDCLinkedList<T>::append(T data) {
    NodeC<T>* temp = new NodeC<T> (data);
    append(*temp);
    delete temp;
}

/*
PARAMETROS: Ninguno.
METODO: Elimina los nodos de la lista enlazada actual desde el primer elemento al último.
ORDEN: O(n).
RETURN: Lista enlazada actual sin apuntar a ningún nodo.
*/
template <class T>
void HDCLinkedList<T>::empty(){
    if(this->size == 0){
        return;
    }

    NodeC<T>* current = static_cast<NodeC<T>*>(this->head);

    while ( current != this->head){
        Node<T> *temp = current; 
        current = static_cast<NodeC<T>*>(current->getNext());
        delete temp; 
    }

    this->head->setNext(nullptr);
    static_cast<NodeC<T>*>(this->head)->setPrevious(nullptr);    

    this->size=0;
}
