#pragma once
#include "Stack.cpp"

template <class T>
class Queue{
    public:
        Queue();
        Queue(std::initializer_list<T> list);
        Queue(int _capacity);
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

        const Stack<T> & toStack();
        const Queue<T> operator=(const Stack<T>& stackCopy);

    private:
        int top, bottom, capacity;
        T* content; 
};