#pragma once 

#include <iostream>
#include "exceptions.cpp"

template <class T>
class Stack{
    public:
        Stack();
        Stack(std::initializer_list<T> list);
        Stack(int _capacity);
        ~Stack();

        Stack(const Stack<T>& copyStack);
        const Stack<T>& operator =(const Stack<T>& copyStack);

        void push(T data);

        bool isFull();
        bool isEmpty();
        T pop();
        T top();
    private:
        int capacity, stackTop; 
        T* elements;

};
