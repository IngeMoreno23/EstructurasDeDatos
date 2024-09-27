#pragma once

#include <iostream>

#include "NodeC.hpp"

#include "Node.cpp"

template<class T>
NodeC<T>::NodeC():Node<T>(T()){
// Valor primitivo. Si son numéricos es cero, si es un string es uno vacío. 
}

template <class T>
NodeC<T>::NodeC(T data): Node<T>(data){
    previous=nullptr;
}

template <class T>
NodeC<T>::~NodeC(){ // CAMBIAR ESTO 
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
