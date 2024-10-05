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
        Tree(const Tree<T>& treeCopy);
        const Tree<T> operator=(const Tree<T>& treeCopy);
        bool memberST(T data, Node<T>* & actNode);
        void addNode(Node<T>* & currentNode, T _data);
        void preOrder(Node<T>& currentNode);
        void inOrder(Node<T>& currentNode);
};

template <class T>
Tree<T>::Tree(){
    this->root= new Node<T> (T());

}

template <class T>
Tree<T>::Tree(const Tree<T>& treeCopy){

}

template <class T>
const Tree<T> Tree<T>::operator=(const Tree<T> &treeCopy){
    
}

template <class T>
void Tree<T>::addNode(Node<T>* &currentNode, T _data){
    if(currentNode->left != nullptr){
        if (currentNode -> left -> data < _data){
            
        }
    }
}

template <class T>
void Tree<T>::inOrder(Node<T>& currentNode){

    if (currentNode.left != nullptr){
        preOrder(currentNode.left);
    }
    std::cout<<currentNode.data<<" ";

    if (currentNode.right != nullptr){
        preOrder(currentNode.right);
    }
    // 

}

/*
       $
   %         #
A     &








Recorrido en Preorden
$, %, A, &, #


*/