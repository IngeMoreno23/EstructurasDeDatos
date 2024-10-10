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
