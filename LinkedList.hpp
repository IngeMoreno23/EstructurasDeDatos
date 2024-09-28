#pragma once

#include "Node.cpp"

template <class T>
class LinkedList{
    private:
        Node<T> *head;
    protected:
        int size;
    public: 
        // Constructors
        LinkedList();
        LinkedList(const LinkedList<T>& listToCopy);
        LinkedList(std::initializer_list<T> elements);
        virtual ~LinkedList();

        // Operators 
        LinkedList<T>& operator=(const LinkedList<T>& listToCopy);
        T& operator[](unsigned int index); 

        // Addition with list terminology (nodes, other lists)
        void insert(const Node<T>& nodeToInsert, int position);
        void append(const Node<T>& nodeToAppend);
        void append(const LinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(LinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        // Data addition 
        virtual void append(T data);
        virtual void insert(T data, int index);

        virtual void erase(int index);
        virtual void update(T data, int index);

        //information
        int length() const; // Declarada constante puesto que se accede a esta en la sobrecarga del operador de asignación. Y regresar un valor no constante en una instancia constante causa errores. 
        bool isEmpty();
        int search(T data);
        T& at(int position);

        void print();
        void exchange(int index1, int index2);
        void invert();
        virtual void empty();
        void ordMerge(LinkedList<T> &l, int n);

        virtual Node<T>* getHead();
        void syncHead();
};
