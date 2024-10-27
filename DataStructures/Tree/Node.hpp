#pragma once
#include <iostream>

template <class T>
class Node{
    private:
        T data;
        Node<T> *left, *right;
        int height;
    public:
        Node(T data, Node<T> *left=nullptr, Node<T> *right=nullptr);
        Node(const Node &otherNode);
        ~Node();

        Node<T> &operator=(T data);
        Node<T> &operator=(Node<T> &otherNode);

        T getData();
        Node<T>* getLeft();
        Node<T>* getRight();
        int getHeight();

        const T getData() const;
        const Node<T>* getLeft() const;
        const Node<T>* getRight() const;

        void setData(T data);
        void setLeft(Node<T> *left);
        void setRight(Node<T> *right);
        void setHeight(int height);
};

/*
PARÁMETROS: data, un dato tipo T; left, apuntador a nodo izquiedo; right, apuntador a nodo derecho.
MÉTODO: Iguala los atributos de este nodo con los argumentos, y se genera un nodo con altura 1.
ORDEN: O(1).
RETURN: void. Este nodo.
*/
template <class T>
Node<T>::Node(T data, Node *left, Node *right){
    this->data = data;
    this->left = left;
    this->right = right;
    this->height = 1;
}

/*
PARÁMETROS: Node &otherNode, algún nodo a copiar su atributo data.
MÉTODO: Solo iguala el dato sin ligarlo a los hijos de otherNode, y se genera el nodo con altura 1.
ORDEN: O(1).
RETURN: void. Este nodo.
*/
template <class T>
Node<T>::Node(const Node &otherNode){
    this->data = otherNode.data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
}

template <class T>
Node<T>::~Node(){

}

template <class T>
Node<T> &Node<T>::operator=(T data){
    this->data = data;
    return *this;
}

/*
PARÁMETROS: Node &otherNode, algún nodo a copiar su atributo data.
MÉTODO: Se verifica que no se este pasando el mismo nodo a copiar, copia el atributo data de otherNode y reestablece sus otros atributos.
ORDEN: O(1).
RETURN: Este nodo.
*/
template <class T>
Node<T> &Node<T>::operator=(Node &otherNode){
    if(this==&otherNode){
        return *this;
    }
    this->data = otherNode.data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
    return *this;
}

template <class T>
T Node<T>::getData(){
    return this->data;
}

template <class T>
Node<T> *Node<T>::getLeft(){
    return this->left;
}

template <class T>
Node<T> *Node<T>::getRight(){
    return this->right;
}

template <class T>
int Node<T>::getHeight(){
    return this->height;
}

template <class T>
const T Node<T>::getData() const {
    return this->data; 
}

template <class T>
const Node<T>* Node<T>::getLeft() const {
    return this->left; 
}

template <class T>
const Node<T>* Node<T>::getRight() const {
    return this->right; 
}

template <class T>
void Node<T>::setData(T data){
    this->data = data;
}

template <class T>
void Node<T>::setLeft(Node<T> *left){
    this->left = left;
}

template <class T>
void Node<T>::setRight(Node<T> *right){
    this->right = right;
}

template <class T>
void Node<T>::setHeight(int height){
    this->height = height;
}