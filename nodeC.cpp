#pragma once

#include <iostream>

#include "NodeC.hpp"

#include "Node.cpp"

template <class T>
NodeC<T>::NodeC(T data): Node<T>(data){
    previous=nullptr;
}

template <class T>
NodeC<T>::~NodeC(){
    delete previous;
    // delete this;
}

template<class T>
NodeC<T>* NodeC<T>::getPrevious(){
    return previous;
}

template<class T>
void NodeC<T>::setPrevious(NodeC<T>* previous){
    this-> previous=previous;
}
