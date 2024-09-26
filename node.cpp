#pragma once

#include <iostream>
#include "Node.hpp"

template <class T>
Node<T>::Node(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void Node<T>::operator=(const Node<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

template <class T>
int Node<T>::operator>(const Node<T>& nodeB){
    if(data>nodeB.data){
        return 1;
    } else{
        return 0;
    }
}
template <class T>
Node<T>::Node(const Node<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
Node<T>::~Node(){
}

template <class T>
Node<T>* Node<T>::getNext(){
    return next;
}

// TENGO DUDA AQUÍ. Por referencia? Supongo que sí, para poder modificarlo. Pero se puede modificar con el setter. 
/*
Pero esto da problemas cuando una instancia del objeto const es utilizada como parametro como en el caso del paso const & de lista enlazada en la que se tiene esta lista constante y uno de los nodos regresa un dato por referencia.

Entonces creo que es un poco innecesario pasar este dato por referencia, porque igual si tengo el objeto y necesito cambiar data, puedo hacerlo con los setters.

Igual se tiene que declarar como const para que la instancia del objeto tome este método como alternativa
*/

template <class T> 
T Node<T>::getData() const {
    return data;
}

template <class T>
T& Node<T>::getData(){
    return data;
}

template <class T>
void Node<T>::setNext(Node<T>* next)
{
    this->next=next;
}

template <class T>
void Node<T>::setData(T data){
    this->data=data;
}

template <class T>
void Node<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void Node<T>::print(){
    std::cout<<data;
}



/*
Aprendizajes 
node<T>

*/