#include "SimpleNode.hpp"
#include <iostream>


template <class T>
SimpleNode<T>::SimpleNode(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void SimpleNode<T>::operator=(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

// Jun 3 13:11:26 543.89.843.57:5249 Failed password for illegal user guest
template <class T>
int SimpleNode<T>::operator>(const SimpleNode<T>& nodeB){
    return (this->data >nodeB.data);
}

template <class T>
SimpleNode<T>::SimpleNode(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
SimpleNode<T>::~SimpleNode(){
}

template <class T>
SimpleNode<T>* SimpleNode<T>::getNext(){
    return next;
}

template <class T> 
T SimpleNode<T>::getData() const {
    return data;
}

template <class T>
T& SimpleNode<T>::getData(){
    return data;
}

template <class T>
void SimpleNode<T>::setNext(SimpleNode<T>* next)
{
    this->next=next;
}

template <class T>
void SimpleNode<T>::setData(T data){
    this->data=data;
}

template <class T>
void SimpleNode<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void SimpleNode<T>::print(){
    std::cout<<data;
}

