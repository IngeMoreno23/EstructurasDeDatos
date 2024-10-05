#pragma once 

#include <iostream>
#include "exceptions.cpp"
#include "Queue\Queue.cpp"

template <class T>
class Stack{
    public:
        Stack();
        Stack(std::initializer_list<T> list);
        Stack(int _capacity);
        ~Stack();

        Stack(const Stack<T>& copyStack);
        const Stack<T>& operator =(const Stack<T>& copyStack);
        const Stack<T>& queueToStack(const Queue<T>& queue);
        void push(T data);

        bool isFull();
        bool isEmpty();
        T pop();
        T peek();

        void print();
    private:
        int capacity, top; 
        T* elements;

};
