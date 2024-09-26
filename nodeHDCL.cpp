#pragma once

#include <iostream>

#include "node.cpp"

/*
Aprendizajes de esta tarea. Una clase al utilizar plantillas se debe poner en formato node<T>
*/

template <class T>
class NodeC: public Node<T>{
    public:
        NodeC(T data);
        ~NodeC();

        NodeC<T>* getPrevious();
        
        void setPrevious(NodeC<T>* previous);

    private:
        NodeC<T> *previous;

};

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
