#pragma once
#include "SimpleNode.hpp"

template <class T>
class DoubleNode: public SimpleNode<T>{
    public:
        DoubleNode(T _data);
        DoubleNode();
        ~DoubleNode();

        DoubleNode<T>* getPrevious();
        void setPrevious(DoubleNode<T>* prev);

        DoubleNode<T>* getNext();
        virtual void setNext(DoubleNode<T>* next);

    private:
        DoubleNode<T> *prev;

};


template<class T>
DoubleNode<T>::DoubleNode(){
    prev=nullptr;
    this->next=nullptr;
    this->data=T();
};

template<class T>
DoubleNode<T>::DoubleNode(T _data){
    this->data=_data;
    prev=nullptr;
    this->next=nullptr;
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
    return static_cast<DoubleNode<T>*>(this->next);
}

template <class T>
void DoubleNode<T>::setNext(DoubleNode<T>* next){
    this->next=next;
}

