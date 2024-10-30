#pragma once
#include <iostream>

template <class T>
class Node{
    private:
        T data;
        Node<T> *left, *right;
    public:
        Node(T data =T(), Node<T> *left=nullptr, Node<T> *right=nullptr);
        Node(const Node<T> &otherNode);
        ~Node();
        void destroyNodes(Node<T>* current);

        Node<T> &operator=(T data);
        Node<T> &operator=(Node<T> &otherNode);

        T getData();
        Node<T>* getLeft();
        Node<T>* getRight();

        const T getData() const;
        const Node<T>* getLeft() const;
        const Node<T>* getRight() const;

        void setData(T data);
        void setLeft(Node<T> *left);
        void setRight(Node<T> *right);
};

/*
PARÁMETROS: data, un dato tipo T; left, apuntador a nodo izquiedo; right, apuntador a nodo derecho.
MÉTODO: Iguala los atributos de este nodo con los argumentos, y se genera un nodo con altura 1.
ORDEN: O(1).
RETURN: Ninguno, es el constructor
*/
template <class T>
Node<T>::Node(T data, Node *left, Node *right){
    this->data = data;
    this->left = left;
    this->right = right;
}

/*
PARÁMETROS: El nodo que se busca replicar en el nodo actual.
MÉTODO: Manda a llamar la sobrecarga del operador de asignación al igualar el nodo actual al otro nodo.
ORDEN: O(1). Contando la sobrecarga, O(n)
RETURN: Ninguno, es el constructor.
*/
template <class T>
Node<T>::Node(const Node<T> &otherNode){
    *this= otherNode;
}

/*
PARÁMETROS: Ninguno
MÉTODO: El destructor del nodo. No elimina los nodos hijos, solo se desasigna la localización de la memoria.
ORDEN: O(1).
RETURN: Ninguno, es el destructor.
*/
template <class T>
Node<T>::~Node(){}

/*
PARÁMETROS: El nodo que se busca destruir por completo.
MÉTODO: Recorre el árbol partiendo del nodo inicial nodoI (el que se pasa por parámetro en la primera llamada de la función) hasta los nodos hoja, y los borra hasta que borre el nodoI.
ORDEN: O(1).
RETURN: Ninguno, es el destructor.
*/
template <class T>
void Node<T>::destroyNodes(Node<T>* current){
    if (current != nullptr){
        destroyNodes(getLeft());
        destroyNodes(getRight());
        delete this;
    }
}

/*
PARÁMETROS: Un valor de tipo T.
MÉTODO: Sobrecarga del operador de asignación. Se asigna el valor data pasado como parámetro al atributo data del nodo actual
ORDEN: O(1).
RETURN: Regresa el nodo actual (por referencia).
*/
template <class T>
Node<T> &Node<T>::operator=(T data){
    this->data = data;
    return *this;
}

/*
PARÁMETROS: Un valor de tipo T.
MÉTODO: Sobrecarga del operador de asignación. Se asigna el valor data pasado como parámetro al atributo data del nodo actual
ORDEN: O(n).
RETURN: Regresa el nodo actual (por referencia).
*/
template <class T>
Node<T> &Node<T>::operator=(Node<T> &otherNode){ 
    if(this==&otherNode){
        return *this;
    }
    this->data = otherNode.data;
    if(otherNode.getLeft() != nullptr){
        Node<T>* leftChild = new Node<T>;
        *leftChild = *otherNode.getLeft();
        destroyNodes(getLeft());
        setLeft(leftChild);
    } else{
        destroyNodes(getLeft());
        this->left = nullptr;
    }
    if(otherNode.getRight() != nullptr){
        Node<T>* rightChild = new Node<T>;
        *rightChild = *otherNode.getRight();
        destroyNodes(getRight());
        setRight(rightChild);
    } else{
        destroyNodes(getRight());
        this->right= nullptr;
    }
    return *this;
}

/*
PARÁMETROS: Ninguno
MÉTODO: Accede al dato que almacena el nodo. 
ORDEN: O(1).
RETURN: Una copia del dato tipo T almacenado en el nodo.
*/
template <class T>
T Node<T>::getData(){
    return this->data;
}

/*
PARÁMETROS: Ninguno
MÉTODO: Accede al nodo izquierdo del nodo actual. 
ORDEN: O(1).
RETURN: El apuntador tipo nodo del nodo a la izquierda del nodo actual.
*/
template <class T>
Node<T> *Node<T>::getLeft(){
    return this->left;
}

template <class T>
Node<T> *Node<T>::getRight(){
    return this->right;
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
