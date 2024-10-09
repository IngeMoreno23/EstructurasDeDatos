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
        ~HDCLinkedList() override;

        // Operators 
        const HDCLinkedList<T>& operator=(const HDCLinkedList<T>& listToCopy);

        // Addition
        void insert(const NodeC<T>& nodeToInsert, int index);
        void append(const NodeC<T>& nodeToAppend);
        void append(T data) override;
        void append(const HDCLinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(HDCLinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 
        void pop();
        void erase(int index);
        void print();
        void empty() override;

        
        class Iterator{
            private:
                NodeC<T> *current;
                NodeC<T> *head;
            public:
                Iterator(NodeC<T> *currentNode, NodeC<T> *headNode);

                T& operator*();
                Iterator& operator++();
                Iterator& operator--();
                bool operator!=(const Iterator& otro) const;
        };
        Iterator begin();
        Iterator end();
};