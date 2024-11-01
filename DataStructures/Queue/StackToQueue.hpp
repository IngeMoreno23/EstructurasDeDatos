#define STACK_TO_QUEUE
#include "..\Stack\Stack.hpp"
#include "Queue.hpp"

template <class T>
Queue<T>::Queue(const Stack<T>& stack){
    bottom=-1;
    top=-1;
    capacity=stack.capacity;
    content=new T[stack.capacity];

    for(int i=0; i <= stack.top; i++){
        enQueue(stack.elements[i]);
    }
}