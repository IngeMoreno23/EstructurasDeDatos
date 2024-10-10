#include <iostream>
#include <sstream>
#include <cstring>
#include "BaseLL.hpp"
#include "SimpleNode.hpp"
#include "DoubleNode.hpp"

template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL():head(nullptr), size(0){}

template <class T, class NodeType>
BaseLL<T, NodeType>::BaseLL(std::initializer_list<T> elements){

    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new NodeType (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        NodeType* currentNode = head;
        iterador++;
        size=1;

        for (; iterador != elements.end(); ++iterador){ // se puede no inicializar nada en for
            NodeType* nextNode = new NodeType (*iterador); 

            currentNode->setNext(nextNode);
            currentNode=nextNode;
            size++;
        }
        currentNode->setNext(nullptr);

    }
}

template <class T, class NodeType> 
BaseLL<T, NodeType>:: BaseLL(const BaseLL<T, NodeType>& listToCopy):head(nullptr), size(0){
    operator=(listToCopy);
}

template <class T, class NodeType>
BaseLL<T, NodeType>:: ~BaseLL(){
    if (size != 0){

        while(head != nullptr){ 
            NodeType *temp=head; 
            head=head->getNext();
            delete temp; 
        }
        size=0;
    }
}

template <class T, class NodeType>
auto & BaseLL<T, NodeType>::operator=(const BaseLL<T, NodeType>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }

    empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }
    
    NodeType* currentNodeCopy = listToCopy.head, *currentNode = new NodeType (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){

        NodeType* nextNode = new NodeType (currentNodeCopy.data); //usar los getters.
        currentNode->setNext(nextNode);

        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    size = listToCopy.length();
    
    return *this;
}

template <class T, class NodeType>
T& BaseLL<T, NodeType>::operator[](unsigned int index){
    
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

template <class T, class NodeType>
void BaseLL <T, NodeType>::empty(){
    while(head != nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        NodeType *temp=this->head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}

template <class T, class NodeType>
void BaseLL<T, NodeType>::update(T data, int index){
    
    if(index < 0 || index >= size){
        return; 
    }

    operator[](index)=data;
}

template <class T, class NodeType>
NodeType* BaseLL<T, NodeType>::getNode(int index){
        
    if (index >= size || index < 0){
        std::cout<<"Index "<<index<<" is out of range";
        throw(std::invalid_argument("Out of range"));
    }
    NodeType* currentNode = this->head;

    for(int i = 0; i < index; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode; 
}

template <class T, class NodeType>
int BaseLL<T,NodeType>::length() const {
    return size;
}

template <class T,class NodeType>
bool BaseLL<T,NodeType>::isEmpty(){
    if (head == nullptr){
        return true;
    }
    return false;
}


template <class T, class NodeType>
int BaseLL<T,NodeType>::search(T data){
    NodeType* currentNode=this->head;

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

template <class T, class NodeType>
void BaseLL<T,NodeType>::exchange(int indexA, int indexB){
    T buffer = operator[](indexA);
    operator[](indexA) = operator[](indexB);
    operator[](indexB) = buffer;
}

template <class T, class NodeType>
void BaseLL<T,NodeType>::invert(){
    int positionA = 0, half = (size % 2 ==0) ? size/2: 1 + size/2;
    while(positionA < half){
        exchange(positionA,size-positionA-1);
        positionA++;
    }
}

template <class T, class NodeType>
void BaseLL<T,NodeType>::print(){
    NodeType* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    while(currentNode != nullptr){
        std::cout<<currentNode->getData()<<" ";
        currentNode=currentNode->getNext();
    }
    std::cout<<std::endl;
}
