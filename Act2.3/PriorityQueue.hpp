#pragma once
#include <iostream>

template <class T>
class PriorityQueue{
    private:
        T *elements;
        int bottom;
        int capacity;

        void ordenaHaciaArriba(int posicion);
        void ordenaHaciaAbajo(int posicion);
    public:
        PriorityQueue();
        PriorityQueue(int capacity);

        ~PriorityQueue();

        void heapify();
        void push();
        void pop();
        T top();
        bool isEmpty();
        int size();
};