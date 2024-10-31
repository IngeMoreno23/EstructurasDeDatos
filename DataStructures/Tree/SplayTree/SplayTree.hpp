#include <iostream>
#include "Node.hpp"
#include <functional>

template <class T>
class SplayTree{
    public: 
        SplayTree();
        SplayTree(std::initializer_list<T> list);
        SplayTree(const SplayTree<T> &otherTree);
        const SplayTree<T>& operator=(const SplayTree<T> &otherTree);

        ~SplayTree();
        void destroyTree(Node<T> *current);

        void splay(T data);
        void endSplay();
        T top(); // en este caso el valor T no puede haber sido pasado por referencia porque lo que hace es obtener T por getData(), que no espasado por referencia

        void zig(bool toRight);

        int insert(T data);
        int search(T data);
        void deleteN(T data);

        void preOrder();
        void inOrder();
        void postOrder();
        void inReverseOrder();

        void preOrder(Node<T> *current);
        void inOrder(Node<T> *current);
        void postOrder(Node<T> *current);
        void inReverseOrder(Node<T> *current);

        void inReverseOrder(Node<T>* current, std::function<void(T&)> callback);
        void inReverseOrder(std::function<void(T&)> callback);
    private: 
        Node<T>* root; 
};

/*
PARAMETROS: void.
MÉTODO: Constructor por defecto de la clase SplayTree.
ORDEN: O(1).
RETURN: void. Crea un árbol vacío.
*/
template <class T>
SplayTree<T>::SplayTree():root(nullptr){}

/*
PARAMETROS: initializer_list<T> list, lista de elementos a insertar en el árbol.
MÉTODO: inserta los elementos de la lista en el árbol.
ORDEN: O(n).
RETURN: void, el árbol con los elementos de la lista.
*/
template <class T>
SplayTree<T>::SplayTree(std::initializer_list<T> list):root(nullptr){ // si no se inicializ la raíz como null, el método inserción no insertará el nodo raíz
    for(const auto &element:list){
        insert(element);
    }
}

/*
PARAMETROS: SplayTree<T> &otherTree, árbol a copiar.
MÉTODO: copia el árbol otherTree en el árbol actual, mandando llamar la sobrecarga de operador de asignación del nodo nodo1=nodo2.
ORDEN: O(n).
RETURN: void, el árbol actual con los elementos de otherTree.
*/
template <class T>
SplayTree<T>::SplayTree(const SplayTree<T> & otherTree){
    root = new Node<T>;
    *root = *otherTree.root;
}

/*
PARAMETROS: SplayTree<T> &otherTree, árbol a copiar.
MÉTODO: copia el árbol otherTree en el árbol actual.
ORDEN: O(n).
RETURN: SplayTree<T>&, el árbol actual con los elementos de otherTree.
*/
template <class T> 
const SplayTree<T>& SplayTree<T>::operator=(const SplayTree<T> &otherTree){
    if(this = &otherTree){
        return *this;
    }

    *root = *otherTree.root;
}

/*
PARAMETROS: void.
MÉTODO: Destructor de la clase SplayTree.
ORDEN: O(n).
RETURN: void. Destruye el árbol.
*/
template <class T>
SplayTree<T>::~SplayTree(){
    if (root != nullptr){
        destroyTree(root);
        root = nullptr;
    }
}

/*
PARAMETROS: Node<T>* current, nodo raíz del árbol a destruir.
MÉTODO: Llama recurivamente este método con los hijos del nodo actual, y elimina el nodo actual.
ORDEN: O(n).
RETURN: void. Vacia el árbol.
*/
template <class T>
void SplayTree<T>::destroyTree(Node<T>* current){
    if(current != nullptr){
        destroyTree(current->getLeft());
        destroyTree(current->getRight());
        delete current;
    }
}

template<class T>
void SplayTree<T>::zig(bool toRight){
    Node<T> *temp = root;

    if(!toRight){
        root = root->getLeft();
        temp->setLeft(root->getRight());
        root->setRight(temp);
    } else{
        root = root -> getRight();
        temp -> setRight(root -> getLeft());
        root -> setLeft(temp);
    }
}

template <class T>
T SplayTree<T>::top(){
    return root->getData();
}
/*
PARAMETROS: T data, dato a buscar para hacer un desplegado.
MÉTODO: Realiza una rotación para subir el nodo con el dato data y subirlo ligeramente de nivel.
ORDEN: O(log(n)).
RETURN: void. El nodo con el dato data sube 1-2 niveles.
*/
template <class T>
void SplayTree<T>::splay(T data){
    if(root == nullptr){
        throw(std::runtime_error("El árbol está vacío"));
    } else if (root->getData() == data){
        return;
    }
    Node<T> *temp = root;
    bool cond = (data < root->getData()) ? (root->getLeft() != nullptr) : (root->getRight() != nullptr);
    while (cond){
        temp = root;
        if(data < root -> getData()){ // No necesito checar si es null porque en el cond ya garanticé que no. 
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
        cond = (data < root->getData()) ? (root -> getLeft() != nullptr) : (root -> getRight() != nullptr && root-> getData() != data);
    }
}

template <class T>
void SplayTree<T>::endSplay(){
    if(root == nullptr){
        throw(std::runtime_error("El árbol está vacío"));
    }
    Node<T> *temp = root;
    while(root->getRight() != nullptr){
        temp = root; 
        root = root -> getRight();
        temp -> setRight(root -> getLeft());
        root -> setLeft(temp);
    }
}

/*
PARAMETROS: T data, dato a insertar en el árbol.
MÉTODO: Realiza una rotación con splay() y el dato data como argumento, y luego inserta el dato en el árbol.
ORDEN: O(log(n)).
RETURN: void. El dato data es insertado en el árbol.
*/
template <class T>
int SplayTree<T>::insert(T data){
    if(root == nullptr){
        root = new Node<T>(data);
        return 1;
    }

    splay(data);
    if(root -> getData() == data){
        return 0;
    }
    Node<T> *newNode = new Node<T>(data);
    if(data < root -> getData()){
        newNode -> setRight(root);
        newNode -> setLeft(root->getLeft());
        root -> setLeft(nullptr);
    } else{
        newNode -> setLeft(root);
        newNode -> setRight(root->getRight());
        root-> setRight(nullptr);
    }
    root = newNode;
    return 1;
}

/*
PARAMETROS: T data, dato a buscar en el árbol.
MÉTODO: Se realiza una rotación con splay() y el dato data como argumento, y se verifica si el dato está en el árbol.
ORDEN: O(log(n)).
RETURN: int, 1 si el dato está en el árbol, 0 si no.
*/
template <class T>
int SplayTree<T>::search(T data){
    splay(data);

    return (root->getData() == data) ? 1 : 0;
}

/*
PARAMETROS: T data, dato a eliminar del árbol.
MÉTODO: Si el dato está en el árbol, se realiza una rotación con splay() y el dato data como argumento, y se elimina el nodo con el dato data.
ORDEN: O(log(n)).
RETURN: void. El dato data es eliminado del árbol.
*/
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
        if (pastRoot->getRight() == nullptr && pastRoot->getLeft() == nullptr){
            root = nullptr;
        }
        delete pastRoot;
    } else{
        return;
    }

}

/*
PARAMETROS: void.
MÉTODO: Llama a preOrder(Node<T>* current) con la raíz del árbol.
ORDEN: O(n).
RETURN: void. Despliega los elementos del árbol en preOrder.
*/
template <class T>
void SplayTree<T>::preOrder(){
    if(root != nullptr){
        preOrder(root);
    }
}

/*
PARAMETROS: void.
MÉTODO: Llama a inOrder(Node<T>* current) con la raíz del árbol.
ORDEN: O(n).
RETURN: void. Despliega los elementos del árbol en inOrder.
*/
template <class T>
void SplayTree<T>::inOrder(){
    if(root != nullptr){
        inOrder(root);
    }
}

/*
PARAMETROS: void.
MÉTODO: Llama a inReverseOrder(Node<T>* current) con la raíz del árbol.
ORDEN: O(n).
RETURN: void. Despliega los elementos del árbol en inReverseOrder.
*/
template <class T>
void SplayTree<T>::inReverseOrder(){
    if(root != nullptr){
        inReverseOrder(root);
    }
}

/*
PARAMETROS: void.
MÉTODO: Llama a postOrder(Node<T>* current) con la raíz del árbol.
ORDEN: O(n).
RETURN: void. Despliega los elementos del árbol en postOrder.
*/
template <class T>
void SplayTree<T>::postOrder(){
    if(root != nullptr){
        postOrder(root);
    }
}

/*
PARAMETROS: Node<T>* current, nodo raíz del subárbol a desplegar.
MÉTODO: Imprime el nodo actual, y llama recursivamente a preOrder con los hijos del nodo actual de izquierda a derecha.
ORDEN: O(n).
RETURN: void. Despliega los elementos del subárbol en preOrder.
*/
template <class T>
void SplayTree<T>::preOrder(Node<T>* current){
    if(current != nullptr){
        std::cout << current->getData() << "\n";
        preOrder(current->getLeft());
        preOrder(current->getRight());
    }
}

/*
PARAMETROS: Node<T>* current, nodo raíz del subárbol a desplegar.
MÉTODO: Llama recursivamente a inOrder con los hijos izquierdo del nodo actual, imprime el nodo actual y llama a inOrder con el hijo derecho del noco actual.
ORDEN: O(n).
RETURN: void. Despliega los elementos del subárbol en inOrder.
*/
template <class T>
void SplayTree<T>::inOrder(Node<T>* current){
    if(current != nullptr){
        inOrder(current->getLeft());
        std::cout << current->getData() << "\n";
        inOrder(current->getRight());
    }
}

/*
PARAMETROS: Node<T>* current, nodo raíz del subárbol a desplegar.
MÉTODO: Llama recursivamente a inReverseOrder con los hijos derecho del nodo actual, imprime el nodo actual y llama a inReverseOrder con el hijo izquierdo del noco actual.
ORDEN: O(n).
RETURN: void. Despliega los elementos del subárbol en inReverseOrder.
*/
template <class T>
void SplayTree<T>::inReverseOrder(Node<T>* current){
    if(current != nullptr){
        inReverseOrder(current->getRight());
        std::cout << current->getData() << "\n";
        inReverseOrder(current->getLeft());
    }
}


template <class T>
void SplayTree<T>::inReverseOrder(Node<T>* current, std::function<void(T&)> callback){
    if(current != nullptr){
        inReverseOrder(current->getRight(), callback);
        callback(current->getData());  // En lugar de cout
        inReverseOrder(current->getLeft(), callback);
    }
}

template <class T>
void SplayTree<T>::inReverseOrder(std::function<void(T&)> callback){
    inReverseOrder(root, callback);
}

/*
PARAMETROS: Node<T>* current, nodo raíz del subárbol a desplegar.
MÉTODO: Llama recursivamente a postOrder con los hijos del nodo actual de izquierda a derecha, e imprime el nodo actual.
ORDEN: O(n).
RETURN: void. Despliega los elementos del subárbol en postOrder.
*/
template <class T>
void SplayTree<T>::postOrder(Node<T>* current){
    if(current != nullptr){
        postOrder(current->getLeft());
        postOrder(current->getRight());
        std::cout << current->getData() << "\n";
    }
}
