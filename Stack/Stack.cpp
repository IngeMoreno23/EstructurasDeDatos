#include "Stack.hpp"

template <class T>
Stack<T>::Stack():capacity(10), top(-1), elements(new T[10]){
}

template <class T>
Stack<T>::Stack(int _capacity):capacity(_capacity),top(-1), elements(new T[_capacity]){
}

template <class T>
Stack<T>::Stack(std::initializer_list<T> list): capacity(list.size()), top(list.size()-1){
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
    top=copyStack.top;
    elements=new T[capacity];

    for (int i=0; i < capacity; i++){
        elements[i]=copyStack.elements[i];
    }
}

template <class T>
void Stack<T>::push(T data){
    if(top >= capacity - 1){
        throw(stack_overflow("Capacidad excedida\n"));
    }
    
    elements[++top]=data;
}

// No se puede borrar la memoria asignada a un solo elemento en un bloque de memoria. Simplemente se ignora que está ahí. 
template <class T>
T Stack<T>::pop(){
    return elements[top--];
}

template <class T>
T Stack<T>::peek(){
    return elements[top];
}


template <class T>
Stack<T>::~Stack(){
    delete[] elements;
}


template <class T>
bool Stack<T>::isEmpty(){
    if(top==-1){
        return true;
    }
    return false;
}

template <class T>
bool Stack<T>::isFull(){
    if(top >= capacity-1){
        return true;
    }
    return false;
}