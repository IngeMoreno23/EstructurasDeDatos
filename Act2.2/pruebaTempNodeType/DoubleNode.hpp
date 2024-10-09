#pragma once

#include "SimpleNode.cpp"

template <class T>
class DoubleNode: public SimpleNode<T>{
    public:
        DoubleNode(T _data);
        DoubleNode();
        ~DoubleNode() override;

        DoubleNode<T>* getPrevious();
        void setPrevious(DoubleNode<T>* prev);

        DoubleNode<T>* getNext();
        void setNext(DoubleNode<T>* next);

    private:
        DoubleNode<T> *prev, *next;

};
