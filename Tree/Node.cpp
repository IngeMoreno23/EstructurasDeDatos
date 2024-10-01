#include <iostream>

template <class T>
class Node{
    public:
        Node();
        Node(const T& data, Node<T>* left=nullptr, Node<T>* right=nullptr);

        Node<T> *left, *right;
        T data;

};

template <class T>
Node<T>::Node(){
    left=nullptr; 
    right=nullptr;
    data=T();
}

template <class T>
Node<T>::Node(const T& data, Node<T>* left, Node<T>* right):data(data), left(left), right(right){}


