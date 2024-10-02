#include "Stack.hpp"

template <class T>
Stack<T>::Stack():capacity(10), stackTop(-1), elements(new T[10]){
}

template <class T>
Stack<T>::Stack(int _capacity):capacity(_capacity),stackTop(-1), elements(new T[_capacity]){
}

template <class T>
Stack<T>::Stack(std::initializer_list<T> list): capacity(list.size()), stackTop(list.size()-1){
    elements= new T[list.size()];
    int i=0;

    for(const T& item:list){
        elements[i]=item;
        i++;
    }

}

template <class T>
Stack<T>::Stack(const Stack<T>& copyStack){
    *this = copyStack;
}

template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& copyStack){
    delete[] elements;

    capacity=copyStack.capacity;
    stackTop=copyStack.stackTop;
    elements=new T[capacity];

    for (int i=0; i < capacity; i++){
        elements[i]=copyStack.elements[i];
    }
}

template <class T>
void Stack<T>::push(T data){
    if(stackTop >= capacity - 1){
        throw(stack_overflow("Capacidad excedida\n"));
    }
    
    elements[++stackTop]=data;
}

// No se puede borrar la memoria asignada a un solo elemento en un bloque de memoria. Simplemente se ignora que está ahí. 
template <class T>
T Stack<T>::pop(){
    return elements[stackTop--];
}

template <class T>
T Stack<T>::top(){
    return elements[stackTop];
}


template <class T>
Stack<T>::~Stack(){
    delete[] elements;
}


template <class T>
bool Stack<T>::isEmpty(){
    if(stackTop==-1){
        return true;
    }
    return false;
}

template <class T>
bool Stack<T>::isFull(){
    if(stackTop >= capacity-1){
        return true;
    }
    return false;
}