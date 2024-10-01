#include <iostream>
#include "Node.cpp"

/*
Se definen constructor de copia y operador de asignación porque se está manejando memoria dinámica. En los árboles binarios de búsqueda no se puede tener el mismo valor. 
*/

template <class T>
class Tree{
    protected:
        Node<T>* root;

    public:
        Tree();
        Tree(const Tree<T>&);
        operator=(const Tree<T>&);
        memberST(T data, Node<T>* actNode);
        addNode(Node<T> nodeAdd)
};

template <class T>
Tree<T>::Tree(){
    this->root= new Node<T>;

}

template <class T>
Tree<T>::Tree(const Tree<T>& treeCopy){

}
