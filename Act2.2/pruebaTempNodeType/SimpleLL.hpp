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
        virtual ~SimpleLL();

        void append(const SimpleNode<T>& nodeToAppend) override;
        template <class NodeType>
        void append(const BaseLL<T,NodeType>* listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        template <class NodeType>
        void merge(BaseLL<T,NodeType>* listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 
        void erase(int index) override;
};