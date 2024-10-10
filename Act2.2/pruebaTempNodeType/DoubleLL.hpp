#pragma once
#include "BaseLL.hpp"
#include "DoubleNode.hpp"

template<class T>
class DoubleLL:public BaseLL<T, DoubleNode<T>>{
    public:
        DoubleLL();
        DoubleLL(const DoubleLL<T>& listToCopy);
        DoubleLL(std::initializer_list<T> elements);
        ~DoubleLL() override;

        const DoubleLL<T>& operator=(DoubleLL<T> & listToCopy);

        void append(const DoubleNode<T>& nodeToAppend);
        virtual void append(T data) override;

        void append(const DoubleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(DoubleLL<T>& listToAppend); // Conecta el último elemento de la primera al primero de la segunda. 

        virtual void erase(int index) ;

        virtual void insert(T data, int index) override;
        virtual void insert(DoubleNode<T>& nodeToInsert, int index);

        void empty() override;

        class Iterator{
            private:
                DoubleNode<T> *current;
                DoubleNode<T> *head;
            public:
                Iterator(DoubleNode<T> *currentNode, DoubleNode<T> *headNode);

                T& operator*();
                Iterator& operator++();
                Iterator& operator--();
                bool operator!=(const Iterator& otro) const;
        };
        Iterator begin();
        Iterator end();
};