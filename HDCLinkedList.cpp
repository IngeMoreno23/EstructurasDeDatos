#pragma once

#include <string>
#include <iostream>

#include "HDCLinkedList.hpp"

#include "LinkedList.cpp"
#include "NodeC.cpp"

template <class T>
HDCLinkedList<T>::HDCLinkedList():LinkedList<T>(){ 
    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    LinkedList<T>::syncHead(); // se emplea para que apunten los dos heads apunten al mismo lugar, solo que el apuntador en LinkedList solo tendrá acceso a los atributos privados, protegidos y públicos (y por ende maneja node, y no node c), y lo que está en HDCLink maneja el apuntador con nodeC

}

template <class T>
HDCLinkedList<T>::HDCLinkedList(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        this->head = new NodeC<T> (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        NodeC<T>* currentNode= this->head;
        currentNode->setPrevious(head);
        iterador++;
        this->size=1;

        for (; iterador != elements.end(); ++iterador){ // se puede no inicializar nada en for

            NodeC<T>* nextNode = new NodeC<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode=nextNode;
            this->size++;
        }
        
        currentNode->setNext(this->head);
        this->head->setPrevious(currentNode);
    }
}

template <class T>
HDCLinkedList<T>:: HDCLinkedList(const HDCLinkedList<T>& listToCopy){
    this->head=new NodeC<T>;

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    LinkedList<T>::syncHead(); // se emplea para que apunten los dos heads apunten al mismo lugar, solo que el apuntador en LinkedList solo tendrá acceso a los atributos privados, protegidos y públicos (y por ende maneja node, y no node c), y lo que está en HDCLink maneja el apuntador con nodeC

    *this=listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T> 
HDCLinkedList<T>::~HDCLinkedList() {
    if(this->size==0){
        return;
    }

    NodeC<T>* current=this->head;

    do{
        Node<T> *temp=current; 
        current=static_cast<NodeC<T>*>(current->getNext());
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    while (current != this->head);

    this->size=0; // Por propósitos de consistencia, checar si una lista ha sido borrada o actualizaciones futuras al código. 
}

// se pone const HDCLinkedList <T>& para realizar múltiples asignaciones
// O(n^2)
template <class T>
const HDCLinkedList<T>& HDCLinkedList<T>::operator=(const HDCLinkedList<T> & listToCopy){
    if (this == &listToCopy){ // Aquí se comparan los apuntadores. si el apuntador al objeto es el mismo al apuntador de la lista que se mandó, se regresa, pues es el mismo objeto.
        return *this;
    }
    
    this->empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    // Resulta que no se declara el nodeC<T> * para todos, el asterisco debe ir antes de cada variable
    NodeC<T>* currentNodeCopy=listToCopy.head, *currentNode = new NodeC<T> (currentNodeCopy->getData());
    this->head=currentNode;

    currentNodeCopy= static_cast<NodeC<T>*>(currentNodeCopy->getNext());

    while(currentNodeCopy != listToCopy.head){

        NodeC<T>* nextNode= new NodeC<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=static_cast<NodeC<T>*> (currentNodeCopy->getNext());
        currentNode=nextNode;
    }
    currentNode->setNext(this->head);
    this->head->setPrevious(currentNode);

    this->size=listToCopy.size;

    LinkedList<T>::syncHead();
    return *this;
}


template<class T>
void HDCLinkedList<T>::append(const NodeC<T>& nodeToAppend){
    if(static_cast<NodeC<T>*>(this->head->getNext()) == this->head){
        NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
        this->head=newNode;
        newNode->setPrevious(this->head);
        newNode->setNext(this->head);
        this->size++;
        return;
    }

    NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
    this->head->getPrevious()->setNext(newNode);
    newNode->setNext(this->head);
    newNode->setPrevious(head->getPrevious());
    this->head->setPrevious(newNode);

    this->size++;
    // A menos que justo se asigne un valor en la memoria manualmente antes de mandar llamar esta función, ahí sí tiene sentido solo hacer que el último nodo apunte a esa función. 
}

// SI SE AÑADE UN NODO HASTA EL FINAL, SE PUEDE ACCEDER A PARTIR DEL PRIMER ELEMENTO (PREVIOUS)
template <class T>
void HDCLinkedList<T>::append(const HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    NodeC<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;
    do{
        NodeC<T>* nextNode= new NodeC<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode=nextNode;
        
        currentNodeCopy= static_cast<NodeC<T>*>(currentNodeCopy->getNext());
    } while(currentNodeCopy != listToAppend.head);
    
    currentNode->setNext(this->head);
    currentNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(currentNode);
    this->size+=listToAppend.size;

}

template <class T>
void HDCLinkedList<T>::merge(HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    NodeC<T>* listToAppendHeadCopy= new NodeC<T> (listToAppend.head->getData());    
    NodeC<T>* temp=this->head->getPrevious();

    temp->setNext(listToAppendHeadCopy);
    listToAppend.head->getPrevious()->setNext(this->head);
    
    listToAppendHeadCopy->setPrevious(temp);
    this->head->setPrevious(listToAppend.head->getPrevious());
    listToAppendHeadCopy->setNext(listToAppend.head->getNext());
    this->size+=listToAppend.size;

    listToAppend.head->setNext(nullptr);
    listToAppend.head->setPrevious(nullptr);
    listToAppend.size=0;

    // Considero que no es necesario borrar manualmente la lista segunda. Puesto que esta solo contiene variables, size, head;
    // El peligro de esta función es que si la segunda se sale de su ámbito será borrada la otra sección de la lista. La creación de este método fue mera experimentación. ENTONCES SI HAGO QUE EL DESTRUCTOR SE LLAME AQUI, DESPUÉS DE HACER QEU HEAD APUNTE A NULL, ESTARÉ EVADIENDO ESTE CASO.
    // estaba equivocado, sí se manda llamar al destructor cuando el objeto sale de ámbito, pero como yo hice que el apuntador de head fuera nullptr, el destructor no borrará los otros nodos. 
    // Aparte, si creo un nuevo objeto, también consume en la memoria (pero no dinámica). solo lo llamaría para llamar al destructor, pero la segunda lista ya no tiene memoria dinámica asignada.
}

template <class T>
void HDCLinkedList<T>::insert(const NodeC<T>& nodeToInsert, int index){
    if(index >= this->size || index < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    NodeC<T>* currentNode=this->head;
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

template <class T>
void HDCLinkedList<T>::pop(){
    
    NodeC<T>* temp= this->head-> getPrevious();
    temp->getPrevious()->setNext(this->head);
    delete temp;

}

template <class T>
void HDCLinkedList<T>::erase(int position){
    if(position >= this->size || position < 0 || this->head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size==1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }


    NodeC<T>* currentNode=static_cast<NodeC<T>*>(this->head); // una variable que guarda un apuntador. NO es memoria dinámica.

    if (position == 1){
        this->head=static_cast<NodeC<T>*>(currentNode->getNext());
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i=0;i<=position; i++){
            currentNode=static_cast<NodeC<T>*>(currentNode->getNext());
        }
        NodeC<T>*temp =static_cast<NodeC<T>*>(currentNode->getNext());
        static_cast<NodeC<T>*>(temp->getNext())->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    this->size--;
    
}

template <class T>
void HDCLinkedList<T>::print(){
    if (this->size==0){
        std::cout<<"size= "<<this->size<<" elements: ";
        return;
    }
    NodeC<T>* currentNode= this->head;

    std::cout<<"size= "<<this->size<<" elements: ";

    do{
        std::cout<<currentNode->getData()<<" ";
        currentNode=static_cast<NodeC<T>*>(currentNode->getNext());
    }while(currentNode!=this->head);
    std::cout<<"\n";
}


/*
Tuve que hacer un método getHead porque la cabeza (atributo privado tanto en la clase base como en la derivada), sí puede ser accedida como atributo privado a partir de la clase base, si se está en un método de la clase base. */

template <class T>
void HDCLinkedList<T>::append(T data) {
    NodeC<T>* temp = new NodeC<T> (data);
    append(*temp);
    delete temp;
}

template <class T>
void HDCLinkedList<T>::empty(){
    if(this->size==0){
        return;
    }

    NodeC<T>* current=this->head;

    do{
        Node<T> *temp=current; 
        current=static_cast<NodeC<T>*>(current->getNext());
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    while (current != this->head);

    this->size=0;
}

template <class T>
NodeC<T>* HDCLinkedList<T>::getHead() { return this->head; };
