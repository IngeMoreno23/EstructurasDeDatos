#pragma once 

#include <iostream>
#include "exceptionsStack.cpp"
#include "..\Queue\Queue.hpp"

template <class T> // Importante para no tener un círculo en las declaraciones, porque estoy usando la clase queue en stack y stack en queue
class Queue;

template <class T>
class Stack{
    public:
        Stack();
        Stack(std::initializer_list<T> list);
        Stack(int _capacity);
        Stack(const Queue<T>& queue); // es importante utilizar una letra distinta a T, para que no haya conflictos con la class T de la clase

        ~Stack();
    
        Stack(const Stack<T>& copyStack);
        const Stack<T>& operator =(const Stack<T>& copyStack);

        
        void push(T data);

        bool isFull();
        bool isEmpty();
        T pop();
        T peek();
        int getTop();
        void print();
    private:
        int capacity, top; 
        T* elements;
        friend class Queue<T>;

};
