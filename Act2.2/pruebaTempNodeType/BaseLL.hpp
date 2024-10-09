#pragma once

#include "SimpleNode.cpp"
#include <string>

template <class T, class NodeType>
class BaseLL{
    protected:
        int size;
        NodeType *head;
    public: 
        // Constructors
        BaseLL();
        BaseLL(const BaseLL<T,NodeType>& listToCopy);
        BaseLL(std::initializer_list<T> elements);
        virtual ~BaseLL();

        // Operators 
        BaseLL<T,NodeType>& operator=(const BaseLL<T,NodeType>& listToCopy);
        T& operator[](unsigned int index); 

        // Addition with list terminology (nodes, other lists)
        virtual void insert(const NodeType&, int position)= 0;
        virtual void append(const NodeType& nodeToAppend) = 0;
        virtual void append(const BaseLL<T,NodeType>* listToAppend)=0; // Agrega los elementos de la segunda lista sin borrarla
        virtual void merge(BaseLL<T,NodeType>* listToMerge)=0; // Conecta el último elemento de la primera al primero de la segunda. 

        // Data addition 
        void append(T data);
        void insert(T data, int index);

        virtual void erase(int index) = 0;
        virtual void update(T data, int index);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);
        NodeType* getNode(int position);

        void print();
        void exchange(int index1, int index2);
        void invert();
        virtual void empty();
};
