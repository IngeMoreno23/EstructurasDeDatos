#pragma once
#include "..\Queue\Queue.hpp"
#include <iostream>
#include <algorithm>

template <class T>
class PriorityQueue: public Queue<T>{
    public: 
        PriorityQueue();
        PriorityQueue(int _capacity);
        PriorityQueue(std::initializer_list<T> list);
        ~PriorityQueue();

        void pop();
        void push(const T& data);

        void rearrangeUp();
        void rearrangeDown();

        T& Top();
        bool empty();
        int size();
        virtual void print();

};

template <class T>
PriorityQueue<T>::PriorityQueue():Queue<T>(){}

template <class T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<T> list):Queue<T>(list){}

template <class T>
PriorityQueue<T>::PriorityQueue(int _capacity):Queue<T>(_capacity){};

template <class T>
PriorityQueue<T>::~PriorityQueue(){};

/*
> Parámetros: Ninguno
> Método: 
> Retorno: Valor booleano que indica si la lista está vacía o no.
> Orden: O(1).
*/
template <class T>
bool PriorityQueue<T>::empty(){
    return (this -> top == -1) ? true : false;
}

template <class T>
T& PriorityQueue<T>::Top(){
    if(empty()){
        throw(out_of_range("The list is empty"));
    }
    return this -> content[0];
}

template <class T>
void PriorityQueue<T>::rearrangeUp() {
    int position = this->bottom;  
    int parent = (position - 1 + this->capacity) % this->capacity;

    while (position != this->top && this->content[parent] < this->content[position]) {
        std::swap(this->content[parent], this->content[position]);
        position = parent;
        parent = (position - 1 + this->capacity) % this->capacity;
    }
}

template <class T>
void PriorityQueue<T>::rearrangeDown() {
    int position = this->top + 1; 
    int leftChild, rightChild, maxChild;

    while ((2 * position + 1) % this->capacity != this->bottom) {  
        leftChild = (2 * position) % this->capacity;
        rightChild = (2 * position + 1) % this->capacity;

        if (this->content[rightChild] > this->content[leftChild]) {
            maxChild = rightChild;
        } else {
            maxChild = leftChild;
        }

        if (this->content[position] >= this->content[maxChild]) {
            return;
        }
        std::swap(this->content[position], this->content[maxChild]);
        position = maxChild;
    }
}


template <class T>
void PriorityQueue<T>::pop(){
    if(this -> isEmpty()){
        throw(out_of_range("The queue is empty"));
    }

    std::swap(this -> content[ this -> top], this -> content[ this -> bottom]);
    if(this -> top == this -> bottom){
        this -> content[this -> bottom]= T();
        this -> top = this -> bottom = -1;
    } else{
        this -> content[this -> bottom]= T();
        if (size() == 1){
            this -> top = this -> bottom = -1;
            return; 
        }
        this -> bottom --;
    }
    rearrangeDown();
    
}

template <class T>
void PriorityQueue<T>::push(const T& data){
    if(this -> isFull()){
        throw(out_of_range("The queue is full"));
    }
    try{
        this->enQueue(data);
        rearrangeUp();
    } catch(out_of_range& ex){
        std::cerr<<"Exception: "<<ex.what();
        return;
    }
}

template <class T>
int PriorityQueue<T>::size(){
    if(this-> isEmpty()){
        return 0; 
    }

    return (this -> bottom >= this -> top) ? 
                this -> bottom - this -> top + 1:
                (this -> bottom + this -> capacity) - this->top + 1; 
}

template <class T>
void PriorityQueue<T>::print(){
    std::cout<<"La cola es de tamaño "<<size()<<": ";
    Queue<T>::print();
}