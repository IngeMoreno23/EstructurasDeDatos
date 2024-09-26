#pragma once

#include "Node.cpp"

template <class T>
class LinkedList{
    
    protected:
        int size;
        Node<T> *head; // automaticamente privado

    public: 
        // Constructors
        LinkedList();
        LinkedList(const LinkedList<T>& listToCopy);
        LinkedList(std::initializer_list<T> elements);
        ~LinkedList();

        // Operators 
        LinkedList<T>& operator=(const LinkedList<T>& listToCopy);
        T& operator[](unsigned int index); 

        // Addition with list terminology (nodes, other lists)
        void insert(const Node<T>& nodeToInsert, int position);

        void append(const Node<T>& nodeToAppend);
        void append(const LinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla

        void merge(LinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        // Data addition 
        void append(T data);
        void insert(T data, int index);


        void erase(int position);
        void update(T data, int position);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);

        void print();
        void exchange(int position1, int position2);
        void invert();
        void empty();
        void ordMerge(LinkedList<T> &l, int n);
};