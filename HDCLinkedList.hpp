#pragma once

#include "NodeC.cpp"
#include "LinkedList.cpp"

template <class T>
class HDCLinkedList: public LinkedList<T>{

    public: 
        // Constructors
        HDCLinkedList();
        HDCLinkedList(const HDCLinkedList<T>& listToCopy);
        HDCLinkedList(std::initializer_list<T> elements);
        ~HDCLinkedList();

        // Operators 
        const HDCLinkedList<T>& operator=(const HDCLinkedList<T>& listToCopy);

        // Addition
        void insert(const NodeC<T>& nodeToInsert, int position);
        void append(const NodeC<T>& nodeToAppend);
        void append(const HDCLinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(HDCLinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void pop();
        void erase(int position);
};