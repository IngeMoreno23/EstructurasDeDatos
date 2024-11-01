#pragma once
#include "exceptions.cpp"

template <class T>
class Queue{
    public:
        Queue();
        Queue(std::initializer_list<T> list);
        Queue(int _capacity);

        ~Queue();

        Queue(const Queue<T>& queueCopy);
        const Queue<T>& operator=(const Queue<T>& queueCopy);
        /*
        Esto es para declarar un constructor solo sí se ha definido INCLUDE_PILA_CONSTRUCTOR
        */
        #ifdef STACK_TO_QUEUE
            #include "..\Stack\Stack.hpp"
            friend class Stack<T>;
            Queue(const Stack<T>& stack);
        #endif
        
        void enQueue(T data);
        T deQueue();

        bool isFull();
        bool isEmpty();

        T& getFront();
        T& getBottom();
        virtual void print();

    protected:
        T* content; 
        int top, bottom, capacity; 

};


template <class T>
Queue<T>::Queue():capacity(10), bottom(-1), top(-1), content(new T[10]){
    for(int i=0; i<capacity; i++){
        content[i]= T();
    }
}

template <class T>
Queue<T>::Queue(int _capacity): bottom(-1), top(-1), content(new T[_capacity]){
    capacity=_capacity;
    for(int i=0; i<capacity; i++){
        content[i]= T();
    }
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
const Queue<T>& Queue<T>::operator=(const Queue<T> & queueCopy){
    delete[] content;

    this->capacity=queueCopy.capacity;
    this->bottom=queueCopy.bottom;
    this->top=queueCopy.top;

    content= new T[this->capacity];

    for(int i=top; i <= bottom; i++){
        enQueue(queueCopy.content[i]);
    }
    
    return *this;
}

template <class T>
Queue<T>::~Queue(){
    delete[] content;
}

template<class T>
bool Queue<T>::isFull(){
    return ((bottom + 1) % capacity == top) ? true : false;
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
    } else {
        top = (top + 1) % capacity;
    }
    return topValue;
}

template <class T>
void Queue<T>::enQueue(T data){
    if(isFull()){
        throw(out_of_range("The queue is full"));
    }
    if (top == -1){
        bottom = top = 0;
    } else{
        bottom = (bottom + 1) % capacity;
    }
    content[bottom] = data;
}

template<class T>
T& Queue<T>::getFront(){
    if(isEmpty()){
        throw(out_of_range("The list is empty"));
    }
    return content[top];
}

template<class T>
T& Queue<T>::getBottom(){
    return content[bottom];
}

template <class T>
void Queue<T>::print(){
    for(int i=0; i<capacity; i++){
        std::cout<<content[i]<<" ";
    }
    std::cout<<std::endl;
}


