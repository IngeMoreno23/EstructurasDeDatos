#include "DoubleNode.hpp"

template<class T>
DoubleNode<T>::DoubleNode(){
    prev=nullptr;
    next=nullptr;
    data=T();
};

template<class T>
DoubleNode<T>::DoubleNode(T _data):data(_data){
    prev=nullptr;
    next=nullptr;
};

template <class T>
DoubleNode<T>::~DoubleNode(){}

template <class T>
DoubleNode<T>* DoubleNode<T>::getPrevious(){
    return prev;
}

template <class T>
void DoubleNode<T>::setPrevious(DoubleNode<T>* previous){
    prev=previous;
}

template <class T>
DoubleNode<T>* DoubleNode<T>::getNext(){
    return next;
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode<T>* next){
    this->next=next;
}