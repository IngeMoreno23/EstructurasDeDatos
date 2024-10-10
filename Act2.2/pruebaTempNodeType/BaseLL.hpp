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
        auto& operator=(const BaseLL<T,NodeType>& listToCopy);
        T& operator[](unsigned int index); 

        // Data addition 
        virtual void append(T data) = 0;
        virtual void insert(T data, int index) = 0;

        virtual void update(T data, int index);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);
        NodeType* getNode(int index);

        void print();
        void exchange(int index1, int index2);
        void invert();
        virtual void empty();
};
