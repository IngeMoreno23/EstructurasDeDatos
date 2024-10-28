#include <iostream>
#include "Node.hpp"

template <class T>
class SplayTree{
    public: 
        SplayTree();
        SplayTree(std::initializer_list<T> list);
        SplayTree(const SplayTree<T> &otherTree);
        const SplayTree<T> operator=(const SplayTree<T> &otherTree);
        ~SplayTree();

        void splay(T data);

        void insert(T data);
        int search(T data);
        void deleteN(T data);

        void preOrder();
        void inOrder();
        void postOrder();

    private: 
        Node<T>* root; 
        // Node<T>* lastAccess; // Posible optimización
};

template <class T>
SplayTree<T>::SplayTree(){
    root = nullptr;
}

template <class T>
SplayTree<T>::SplayTree(std::initializer_list<T> list){
    for(const auto &element:list){
        insert(element);
    }
}

template <class T>
SplayTree<T>::~SplayTree(){
    while (root != nullptr){
        deleteN(root -> getData());
    }
}
template <class T>
void SplayTree<T>::splay(T data){
    if(root == nullptr){
        throw(std::runtime_error("El árbol está vacío"));
    } else if (root->getData() == data){
        return;
    }
    Node<T> *temp = root;
    bool cond = (data > root->getData()) ? (root->getLeft() != nullptr) : (root->getRight() != nullptr);
    while (cond){
        if(data < root -> getData()){
            temp = root;
            if(data < root->getLeft()->getData() && root->getLeft()->getLeft() != nullptr){
                // rotación zig zig
                root = root->getLeft()->getLeft();
                temp->getLeft()->setLeft(root->getRight());
                root->setRight(temp);
            } else if(data > root->getLeft()->getData() && root->getLeft()->getRight() != nullptr){
                // realiza el movimiento zig zag
                root = root->getLeft()->getRight();
                temp->getLeft()->setRight(root -> getLeft());
                root->setLeft(temp->getLeft());
                temp->setLeft(root->getRight());
                root->setRight(temp);
            } else{
                // zig y break
                root = root->getLeft();
                temp->setLeft(root->getRight());
                root->setRight(temp);
                break;
            }
        } else if (data > root->getData()){ // No necesito checar si es null porque en el cond ya garanticé que no.
            if(data > root->getRight()->getData() && root->getRight()->getRight() != nullptr){
                // zig zig 
                root= root->getRight()->getRight();
                temp->getRight()->setRight(root->getLeft());
                root->setLeft(temp);
            } else if(data < root->getRight()->getData() && root->getRight()->getLeft() != nullptr){
                // zig zag 
                root = root->getRight()->getLeft();
                temp -> getRight() -> setLeft(root -> getRight());
                root -> setRight(temp->getRight());
                temp -> setRight(root->getLeft());
                root -> setLeft(temp);
            } else{
                // zig y break
                root = root -> getRight();
                temp -> setRight(root -> getLeft());
                root -> setLeft(temp);
                break;
            }
        } else{
            break; // No debería ser necesario este break por la formulación del cond
        }
        cond = (data > root->getData()) ? (root -> getLeft() != nullptr) : (root -> getRight() != nullptr && root-> getData() != data);
    }
}

// insert tiene una fuga de memoria ??
template <class T>
void SplayTree<T>::insert(T data){
    if(root == nullptr){
        root = new Node<T>(data);
        return;
    }

    splay(data);
    if(root -> getData() == data){
        return;
    }
    Node<T> *temp= root;
    root = new Node<T>(data);
    if(data < temp -> getData()){
        root -> setRight(temp);
        root -> setLeft(temp->getLeft());
    } else{
        root -> setLeft(temp);
        root -> setRight(temp->getRight());
    }
}

template <class T>
int SplayTree<T>::search(T data){
    splay(data);

    return (root->getData() == data) ? 1 : 0;
}

template <class T>
void SplayTree<T>::deleteN(T data){
    if(root == nullptr){
        throw(std::runtime_error("El árbol está vacío"));
    }

    if (search(data)){
        Node<T> *pastRoot = root;
        if (root -> getLeft() != nullptr){
            root = root -> getLeft();
            splay(data);
            root -> setRight(pastRoot->getRight());
        } else if (root -> getRight() != nullptr){
            root = root -> getRight();
        }

        delete pastRoot;
    } else{
        return;
    }

}