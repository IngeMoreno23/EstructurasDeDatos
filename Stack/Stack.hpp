#include <iostream>

template <class T>
class Stack{
    public:
        Stack();
        Stack(std::initializer_list<T> list);
        Stack(int capacity);
        
        
    private:
        int capacity, top; 
        T* elements;

};

template <class T>
Stack<T>::Stack():capacity(10), top(-1), elements(new T[10]){
}