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
        Node<T>& addNode(Node<T>* & currentNode, T _data);
        void preOrder(Node<T> *currentNode);
        void inOrder(Node<T> *currentNode);
        void posOrder(Node<T> *currentNode);
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

/*
template <class T>
void Tree<T>::addNode(Node<T>* &currentNode, T _data){
    if(currentNode != nullptr){
        if(currentNode->data == _data){
            currentNode= new Node<T> (_data); //el apuntador que equivale a null es el hijo del pasado nodo, que ahora tiene el valor. 
            // PERO NO TIENE SENTIDO PORQUE ESTOY INTENTANDO ASIGNAR UN DATO A NULL, Y NULL NO ES UNA POSICIÓN EN LA MEMORIA
            return;
        } else if (currentNode-> data > _data){
            addNode(currentNode->left);
        } else{
            addNode(currentNode->right);
        }
    }
}
*/

template <class T>
Node<T>& Tree<T>::addNode(Node<T>* &currentNode, T _data){
    if(currentNode != nullptr){
        if(currentNode->data == _data){
            return new Node<T> (_data);
        } else if (currentNode-> data > _data){
            currentNode->left = addNode(currentNode->left);
        } else{
            currentNode->right = addNode(currentNode->right);
        }
    }
}
template <class T>
void Tree<T>::inOrder(Node<T> * currentNode){

    if (currentNode != nullptr){
        inOrder(currentNode.left);
        std::cout<<currentNode.data<<" ";
        inOrder(currentNode.right);
    }

}

template <class T>
void Tree<T>::preOrder(Node<T> * currentNode){
    if (currentNode != nullptr){
        std::cout<<currentNode.data<<" ";
        preOrder(currentNode.left);
        preOrder(currentNode.right);
    }

}

template <class T>
void Tree<T>::posOrder(Node<T> * currentNode){
    if (currentNode != nullptr){
        posOrder(currentNode.left);
        posOrder(currentNode.right);
        std::cout<<currentNode.data<<" ";
    }
}


/*
       $
   %         #
A     &


template <class T>
void Tree<T>::inOrder(Node<T> * currentNode){

    if (currentNode.left != nullptr){
        preOrder(currentNode.left);
    }
    std::cout<<currentNode.data<<" ";

    if (currentNode.right != nullptr){
        preOrder(currentNode.right);
    }
    // 

}






Recorrido en Preorden
$, %, A, &, #


*/