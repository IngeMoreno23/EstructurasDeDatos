#include "PriorityQueue.hpp"
#include <iostream>
/*

template <class T>
class PriorityQueue{
    private:
        T *elements;
        int bottom;
        int capacity;
    public:
        PriorityQueue();
        ~PriorityQueue();

        void heapify();
        void push();
        void pop();
        T top();
        bool isEmpty();
        int size();
};

*/
template <class T >
PriorityQueue<T>::PriorityQueue(): capacity(10), bottom(-1){
    this->elements= new T[capacity];
}

template <class T >
PriorityQueue<T>::PriorityQueue(int _capacity): capacity(_capacity), bottom(-1){
    this->elements= new T[_capacity];
}




template <class T>
void heapify(){
    for(int i=0; i < this->bottom; i++){
        
    }
}

template <class T>
void push(){
    
}

template <class T>
void pop(){
    if(this->bottom == -1)
        return;
    T temp = this->elements[0];
    this->elements[0] = this->elements[this->bottom];
    this->elements[this->bottom] = temp;

    ordenaHaciaArriba(this->bottom + 1);

    this->bottom--;
}
template <class T>
T top(){
    return this->elements[0];
}
template <class T>
bool isEmpty(){
    if(this->bottom == -1)
        return true;
}
template <class T>
int size(){
    return this->bottom+1;
}