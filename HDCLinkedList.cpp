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
        
    LinkedList<T>::syncHead(); 
}

template <class T>
HDCLinkedList<T>::HDCLinkedList(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head = nullptr;
    } else{
        auto iterador = elements.begin(); 

        this->head = new NodeC<T> (*iterador); 
        NodeC<T>* currentNode = this->head;
        currentNode->setPrevious(head);
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
        this->head->setPrevious(currentNode);
    }
}

template <class T>
HDCLinkedList<T>:: HDCLinkedList(const HDCLinkedList<T>& listToCopy){
    this->head = new NodeC<T>;

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    LinkedList<T>::syncHead(); 

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

template <class T>
const HDCLinkedList<T>& HDCLinkedList<T>::operator=(const HDCLinkedList<T> & listToCopy){
    if (this == &listToCopy){ 
        return *this;
    }
    
    empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    NodeC<T>* currentNodeCopy = listToCopy.head, *currentNode = new NodeC<T> (currentNodeCopy->getData());
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
    this->head->setPrevious(currentNode);

    this->size = listToCopy.size;

    LinkedList<T>::syncHead();
    return *this;
}


template<class T>
void HDCLinkedList<T>::append(const NodeC<T>& nodeToAppend){
    if(this->head->getNext() == nullptr){
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
}

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

template <class T>
void HDCLinkedList<T>::merge(HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    NodeC<T>* listToAppendHeadCopy = new NodeC<T> (listToAppend.head->getData());    
    NodeC<T>* temp = this->head->getPrevious();

    temp->setNext(listToAppendHeadCopy);
    listToAppend.head->getPrevious()->setNext(this->head);
    
    listToAppendHeadCopy->setPrevious(temp);
    this->head->setPrevious(listToAppend.head->getPrevious());
    listToAppendHeadCopy->setNext(listToAppend.head->getNext());
    this->size+=listToAppend.size;

    listToAppend.head->setNext(nullptr);
    listToAppend.head->setPrevious(nullptr);
    listToAppend.size=0;
}

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

template <class T>
void HDCLinkedList<T>::pop(){
    
    NodeC<T>* temp= this->head-> getPrevious();
    temp->getPrevious()->setNext(this->head);
    delete temp;

}

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

template <class T>
void HDCLinkedList<T>::print(){
    if (this->size == 0){
        std::cout<<"size= "<<this->size<<" elements: ";
        return;
    }
    NodeC<T>* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";

    do{
        std::cout<<currentNode->getData()<<" ";
        currentNode = static_cast<NodeC<T>*>(currentNode->getNext());
    }while(currentNode != this->head);
    std::cout<<"\n";
}

template <class T>
void HDCLinkedList<T>::append(T data) {
    NodeC<T>* temp = new NodeC<T> (data);
    append(*temp);
    delete temp;
}

template <class T>
void HDCLinkedList<T>::empty(){
    if(this->size == 0){
        return;
    }

    NodeC<T>* current = this->head;

    while ( current != this->head){
        Node<T> *temp = current; 
        current = static_cast<NodeC<T>*>(current->getNext());
        delete temp; 
    }

    head->setNext(nullptr);
    head->setPrevious(nullptr);    

    this->size=0;
}


// La cabeza (atributo privado tanto en la clase base como en la derivada), sí puede ser accedida como atributo privado a partir de la clase base, si se está en un método de la clase base. */
template <class T>
NodeC<T>* HDCLinkedList<T>::getHead() { return this->head; };
