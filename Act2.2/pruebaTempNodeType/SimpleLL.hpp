#pragma once

#include <iostream>
#include "BaseLL.hpp"
#include "SimpleNode.hpp"

template <class T>
class SimpleLL:public BaseLL<T, SimpleNode<T>>{
    public: 
        SimpleLL();
        SimpleLL(const SimpleLL<T>& listToCopy);
        SimpleLL(std::initializer_list<T> elements);

        ~SimpleLL();

        const SimpleLL<T>& operator =(const SimpleLL<T>& listToCopy);

        void append(const SimpleNode<T>& nodeToAppend) override;
        void append(const SimpleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(SimpleLL<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void erase(int index);
        void insert(SimpleNode<T>& nodeToInsert, int index) override;
                
        virtual void insert(T data, int index) override;
        virtual void append(T data) override;


};