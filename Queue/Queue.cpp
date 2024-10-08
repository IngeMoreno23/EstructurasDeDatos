#include <iostream>
#include "Queue.hpp"
#include "exceptions.cpp"

template <class T>
Queue<T>::Queue():capacity(10), bottom(-1), top(-1), content(new T[10]){}

template <class T>
Queue<T>::Queue(int _capacity): bottom(-1), top(-1), content(new T[_capacity]){
    capacity=_capacity;
}

template <class T>
Queue<T>::Queue(std::initializer_list<T> list):capacity(list.size()), bottom(list.size()-1), top(0){
    auto iterator=list.begin();
    content= new T[capacity];
    for(int i=0; iterator != list.end(); ++iterator, i++){
        content[i]=*iterator;
    }
}

template<class T>
Queue<T>::Queue(const Queue<T> & queueCopy){
    *this=queueCopy;
}

template <class T>
const Queue<T> Queue<T>::operator=(const Queue<T> & queueCopy){
    delete[] content;

    this->capacity=queueCopy.capacity;
    this->bottom=queueCopy.bottom;
    this->top=queueCopy.top;

    content= new T[this->capacity];
}

template <class T>
Queue<T>::~Queue(){
    delete[] content;
}

template<class T>
bool Queue<T>::isFull(){
    return ((bottom+1) % capacity == top % capacity) ? true : false;
}

template <class T>
bool Queue<T>::isEmpty(){
    return (top == -1) ? true : false;
}

template <class T>
T Queue<T>::deQueue(){
    if(isEmpty()){
        throw(out_of_range("The queue is empty"));
    }
    
    T topValue=content[top];
    content[top]=T();

    if(top == bottom){
        top = bottom = -1;
        return topValue;
    } else {
        top++;
    }
    return topValue;
}

template <class T>
void Queue<T>::enQueue(T data){
    if(isFull()){
        throw(out_of_range("The queue is full"));
    }
    if (top == -1){
        top++;
    }
    content[++bottom % capacity] = data;
}

template<class T>
T Queue<T>::getFront(){
    return content[top];
}

template<class T>
T Queue<T>::getBottom(){
    return content[bottom];
}

template <class T>
void Queue<T>::print(){
    for(int i=0; i<capacity; i++){
        std::cout<<content[i]<<" ";
    }
    std::cout<<std::endl;
}

template <class T>
Queue<T>::Queue(const Stack<T>& stack){
    bottom=-1;
    top=-1;
    capacity=stack.capacity;
    content=new T[stack.capacity];

    for(int i=0; i <= stack.top; i++){
        enQueue(stack.elements[i]);
    }
};
