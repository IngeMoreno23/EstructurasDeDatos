#pragma once

#include <iostream>
#include "Node.hpp"
#include <sstream>
#include <cstring>

template <class T>
Node<T>::Node(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void Node<T>::operator=(const Node<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

// Jun 3 13:11:26 543.89.843.57:5249 Failed password for illegal user guest
template <class T>
int Node<T>::operator>(const Node<T>& nodeB){

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

