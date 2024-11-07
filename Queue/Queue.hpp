#pragma once
#include "..\Stack\Stack.hpp"

template <class T>
class Stack;

template <class T>
class Queue{
    public:
        Queue();
        Queue(std::initializer_list<T> list);
        Queue(int _capacity);
        Queue(const Stack<T>& stack);

        ~Queue();

        Queue(const Queue<T>& queueCopy);
        const Queue<T> operator=(const Queue<T>& queueCopy);

        void enQueue(T data);
        T deQueue();

        bool isFull();
        bool isEmpty();

        T getFront();
        T getBottom();
        void print();

        // const Queue<T> operator=(const Stack<T>& stackCopy);
    private:
        T* content; 
        int top, bottom, capacity; 
        friend class Stack<T>;
};