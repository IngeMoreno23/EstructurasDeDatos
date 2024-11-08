#pragma once
#include <iostream>
#include <queue>
#include "Node.hpp"

template <class T>
class BST {
private:
    Node<T>* root;
    int size;

    void destroyTree(Node<T>* current);
    Node<T>* findMin(Node<T>* current);

    int balanceFactor(Node<T>* node);
    Node<T>* rightRotate(Node<T>* y);
    Node<T>* leftRotate(Node<T>* y);

    void recursiveCopyTree(const Node<T>* current);
    Node<T>* recursiveInsert(T data, Node<T>* current);
    Node<T>* recursiveDelete(T data, Node<T>* current, bool &isDeleted);
    bool recursiveSearch(T data, Node<T>* current) const;

    void recursivePreorder(const Node<T>* current) const;
    void recursiveInorder(const Node<T>* current) const;
    void recursivePostorder(const Node<T>* current) const;
    void levelOrder() const;

    int recursiveHeight(Node<T>* current) const;
    bool recursiveAncestors(T target, const Node<T>* current) const;
    int recursiveWhatLevelAmI(T target, const Node<T>* current, int level) const;

public:
    BST();
    BST(T data);
    BST(const Node<T>& otherNode);
    BST(const BST<T>& otherBST);
    virtual ~BST();

    BST<T>& operator=(T data);
    BST<T>& operator=(const BST<T>& otherBST);

    void insertNode(T data);
    void deleteNode(T data);
    bool search(T data) const;

    void visit(int order) const;
    int height() const;
    void ancestors(T target) const;
    int whatLevelAmI(T target) const;

    int getSize() const;
};

/*
PARÁMETROS: Node<T> *current, algún nodo para borrarlo junto con todos sus hijos.
MÉTODO: Comienza por un nodo, mientras no sea una hoja, llama recursivamente este método con sus hijos eliminandolos, y elimina a este nodo.
ORDEN: O(n). n = Tamaño del arbol.
RETURN: void. Elimina el árbol.
*/
template <class T>
void BST<T>::destroyTree(Node<T>* current) {
    if (current == nullptr) {
        return;
    }
    destroyTree(current->getLeft());
    destroyTree(current->getRight());
    delete current;
}

/*
PARÁMETROS: Node<T> *current, algún nodo para recorrer a sus hijos.
MÉTODO: Busca la subrama izquierda de este nodo porque el minimo de este subarbol está siempre a la máxima izquierda.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: Node<T>. El nodo menor de toda la subrama.
*/
template <class T>
Node<T>* BST<T>::findMin(Node<T>* current) {
    while (current && current->getLeft() != nullptr) {
        current = current->getLeft();
    }
    return current;
}

/*
PARÁMETROS: Node<T> *node, algún nodo para saber si sus subramas estan desequilibradas.
MÉTODO: Resta la altura de sus nodos hijos, si esta más allá del rango -1, 1, quiere decir que esta desbalanceado.
ORDEN: O(1).
RETURN: int. x > 1, desbalanceo a la izquierda; x < -1, desbalanceo a la izquierda.
*/
template <class T>
int BST<T>::balanceFactor(Node<T>* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = (node->getLeft() != nullptr) ? node->getLeft()->getHeight() : 0;
    int rightHeight = (node->getRight() != nullptr) ? node->getRight()->getHeight() : 0;
    return leftHeight - rightHeight;
}

/*
PARÁMETROS: Node<T> *y, El nodo padre de sus subramas desbalanceadas.
MÉTODO: Intercambia la posición del padre con su hijo izquierdo, y reemplazan sus raices, luego se vuelven a calcular sus nuevas alturas.
ORDEN: O(1).
RETURN: Node<T>. Regresa a su hijo izquierdo, que ahora es el nuevo padre de la subrama.
*/
template <class T>
Node<T>* BST<T>::rightRotate(Node<T>* y) {
    Node<T>* x = y->getLeft();
    Node<T>* T2 = x->getRight();

    // Rotar nodos.
    x->setRight(y);
    y->setLeft(T2);

    // Actualizar alturas.
    int yLeftHeight = (y->getLeft() != nullptr) ? y->getLeft()->getHeight() : 0;
    int yRightHeight = (y->getRight() != nullptr) ? y->getRight()->getHeight() : 0;
    y->setHeight(1 + std::max(yLeftHeight, yRightHeight));

    int xLeftHeight = (x->getLeft() != nullptr) ? x->getLeft()->getHeight() : 0;
    int xRightHeight = (x->getRight() != nullptr) ? x->getRight()->getHeight() : 0;
    x->setHeight(1 + std::max(xLeftHeight, xRightHeight));

    return x;
}

/*
PARÁMETROS: Node<T> *x, El nodo padre de sus subramas desbalanceadas.
MÉTODO: Intercambia la posición del padre con su hijo derecho, y reemplazan sus raices, luego se vuelven a calcular sus nuevas alturas.
ORDEN: O(1).
RETURN: Node<T>. Regresa a su hijo derecho, que ahora es el nuevo padre de la subrama.
*/
template <class T>
Node<T>* BST<T>::leftRotate(Node<T>* x) {
    Node<T>* y = x->getRight();
    Node<T>* T2 = y->getLeft();

    // Rotar nodos.
    y->setLeft(x);
    x->setRight(T2);

    // Actualizar alturas.
    int xLeftHeight = (x->getLeft() != nullptr) ? x->getLeft()->getHeight() : 0;
    int xRightHeight = (x->getRight() != nullptr) ? x->getRight()->getHeight() : 0;
    x->setHeight(1 + std::max(xLeftHeight, xRightHeight));

    int yLeftHeight = (y->getLeft() != nullptr) ? y->getLeft()->getHeight() : 0;
    int yRightHeight = (y->getRight() != nullptr) ? y->getRight()->getHeight() : 0;
    y->setHeight(1 + std::max(yLeftHeight, yRightHeight));
    
    return y;
}

/*
PARÁMETROS: Node<T> *current, Un nodo de un árbol EXTERNO a copiar.
MÉTODO: Mientras no se encuentre una hoja, toma solo el dato en el nodo del otro árbol, y vuelve a llamar este método recursivamente
con los hijos del nodo del otro árbol.
ORDEN: O(n). n = Tamaño del arbol a copiar.
RETURN: void. Regresa el árbol copiado por valor.
*/
template <class T>
void BST<T>::recursiveCopyTree(const Node<T>* current) {
    if (current == nullptr) {
        return;
    }
    insertNode(current->getData());
    recursiveCopyTree(current->getLeft());
    recursiveCopyTree(current->getRight());
}

/*
PARÁMETROS: T data, un dato de tipo T; Node<T> *current, un nodo de este árbol.
MÉTODO: Se recorre el árbol hasta llegar al nivel inferior de la subrama, si se encuentra un nodo sin hijos, se crea un
nuevo nodo hoja con el valor data del argumento. Si data es igual al dato de un nodo, no se inserta.
Luego se hace un balanceo con los padres del nodo incertado.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: Node<T>. Regresa de manera recursiva el nodo actual que puede ser modificado por el balanceo.
*/
template <class T>
Node<T>* BST<T>::recursiveInsert(T data, Node<T>* current) {
    if (current == nullptr) {
        return new Node<T>(data);
    }

    if (data < current->getData()) {
        current->setLeft(recursiveInsert(data, current->getLeft()));
    } else if (data > current->getData()) {
        current->setRight(recursiveInsert(data, current->getRight()));
    } else {
        return current; // El dato ya existe, no insertar.
    }

    // Actualizar alturas.
    int leftHeight = (current->getLeft() != nullptr) ? current->getLeft()->getHeight() : 0;
    int rightHeight = (current->getRight() != nullptr) ? current->getRight()->getHeight() : 0;
    current->setHeight(1 + std::max(leftHeight, rightHeight));

    int balance = balanceFactor(current);

    // Rotar si hay desbalance.
    if (balance > 1 && data < current->getLeft()->getData()) {
        return rightRotate(current);
    }
    if (balance < -1 && data > current->getRight()->getData()) {
        return leftRotate(current);
    }
    if (balance > 1 && data > current->getLeft()->getData()) {
        current->setLeft(leftRotate(current->getLeft()));
        return rightRotate(current);
    }
    if (balance < -1 && data < current->getRight()->getData()) {
        current->setRight(rightRotate(current->getRight()));
        return leftRotate(current);
    }

    return current;
}

/*
PARÁMETROS: T data, un dato a buscar de tipo T; Node<T> *current, un nodo de este árbol; isDeleted, un condicional si se encuentra el dato.
MÉTODO: Se recorre el árbol hasta llegar a un nodo que se iguale con el dato buscado del argumento, si no,
busca el subarbol izquiero si es menor y el subarbol derecho si es mayor. Si se encuentra el nodo se elimina
solo si tiene un solo nodo hijo o este es nodo hoja, sino se recorre hacia abajo buscando findMin(). Y balancea a los padres.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: Node<T>. Regresa de manera recursiva el nodo actual que puede ser modificado por el balanceo.
*/
template <class T>
Node<T>* BST<T>::recursiveDelete(T data, Node<T>* current, bool &isDeleted) {
    if (current == nullptr) {
        return current;
    }

    if (data < current->getData()) {
        current->setLeft(recursiveDelete(data, current->getLeft(), isDeleted));
    } else if (data > current->getData()) {
        current->setRight(recursiveDelete(data, current->getRight(), isDeleted));
    } else {
        // Nodo encontrado.
        isDeleted = true;
        if (current->getLeft() == nullptr || current->getRight() == nullptr) {
            Node<T>* temp = current->getLeft() ? current->getLeft() : current->getRight();
            if (temp == nullptr) {
                temp = current;
                current = nullptr;
            } else {
                *current = *temp;
            }
            delete temp;
        } else {
            Node<T>* temp = findMin(current->getRight());
            current->setData(temp->getData());
            current->setRight(recursiveDelete(temp->getData(), current->getRight(), isDeleted));
        }
    }

    if (current == nullptr) {
        return current;
    }

    // Actualizar alturas.
    int leftHeight = (current->getLeft() != nullptr) ? current->getLeft()->getHeight() : 0;
    int rightHeight = (current->getRight() != nullptr) ? current->getRight()->getHeight() : 0;
    current->setHeight(1 + std::max(leftHeight, rightHeight));

    int balance = balanceFactor(current);

    // Rotar si hay desbalance.
    if (balance > 1 && balanceFactor(current->getLeft()) >= 0) {
        return rightRotate(current);
    }
    if (balance > 1 && balanceFactor(current->getLeft()) < 0) {
        current->setLeft(leftRotate(current->getLeft()));
        return rightRotate(current);
    }
    if (balance < -1 && balanceFactor(current->getRight()) <= 0) {
        return leftRotate(current);
    }
    if (balance < -1 && balanceFactor(current->getRight()) > 0) {
        current->setRight(rightRotate(current->getRight()));
        return leftRotate(current);
    }

    return current;
}

/*
PARÁMETROS: T data, un dato a buscar de tipo T; Node<T> *current, un nodo de este árbol.
MÉTODO: Se recorre el árbol hasta llegar a un nodo que se iguale con el dato buscado del argumento, si no,
busca el subarbol izquiero si es menor y el subarbol derecho si es mayor. Si se llega a un nodo hoja y no es igual a data,
el nodo no esta dentro de este árbol.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: bool. true, si se encuentra; false, si no se encuentra.
*/
template <class T>
bool BST<T>::recursiveSearch(T data, Node<T>* current) const {
    if (current == nullptr) {
        return false;
    }
    if (current->getData() == data) {
        return true;
    } else if (data < current->getData()) {
        return recursiveSearch(data, current->getLeft()); // Buscar en el subárbol izquierdo
    } else {
        return recursiveSearch(data, current->getRight()); // Buscar en el subárbol derecho
    }
}

/*
PARÁMETROS: TNode<T> *current, un nodo de este árbol.
MÉTODO: Imprime el nodo actual, luego el izquierdo y al final el derecho, de manera recursiva hasta llegar a un nodo hoja.
ORDEN: O(n). n = Tamaño del arbol.
RETURN: void. Imprime en consola.
*/
template <class T>
void BST<T>::recursivePreorder(const Node<T>* current) const {
    if (current == nullptr) {
        return;
    }
    std::cout << current->getData() << " ";
    recursivePreorder(current->getLeft());
    recursivePreorder(current->getRight());
}

/*
PARÁMETROS: TNode<T> *current, un nodo de este árbol.
MÉTODO: Imprime el nodo izquierdo, luego el actual y al final el derecho, de manera recursiva hasta llegar a un nodo hoja.
ORDEN: O(n). n = Tamaño del arbol.
RETURN: void. Imprime en consola. Imprime ordenado menor a mayor.
*/
template <class T>
void BST<T>::recursiveInorder(const Node<T>* current) const {
    if (current == nullptr) {
        return;
    }
    recursiveInorder(current->getLeft());
    std::cout << current->getData() << " ";
    recursiveInorder(current->getRight());
}

/*
PARÁMETROS: TNode<T> *current, un nodo de este árbol.
MÉTODO: Imprime el nodo izquierdo, luego el derecho y al final el actual, de manera recursiva hasta llegar a un nodo hoja.
ORDEN: O(n). n = Tamaño del arbol.
RETURN: void. Imprime en consola. Imprime ordenado menor a mayor.
*/
template <class T>
void BST<T>::recursivePostorder(const Node<T>* current) const {
    if (current == nullptr) {
        return;
    }
    recursivePostorder(current->getLeft());
    recursivePostorder(current->getRight());
    std::cout << current->getData() << " ";
}

/*
PARÁMETROS: void.
MÉTODO: Añade la raíz del arbol en una cola FIFO, imprime el primer elemento y guarda sus hijos en la cola, y repite
el proceso hasta que se llegue a las hojas.
ORDEN: O(n). n = Tamaño del arbol.
RETURN: void. Imprime en consola. Imprime ordenado por niveles.
*/
template <class T>
void BST<T>::levelOrder() const {
    if (this->root == nullptr) {
        return;
    }

    std::queue<Node<T>*> nodeQueue;
    nodeQueue.push(this->root);

    while (!nodeQueue.empty()) {
        Node<T>* current = nodeQueue.front();
        nodeQueue.pop();
        std::cout << current->getData() << " ";

        if (current->getLeft() != nullptr) {
            nodeQueue.push(current->getLeft());
        }
        if (current->getRight() != nullptr) {
            nodeQueue.push(current->getRight());
        }
    }
}

/*
PARÁMETROS: Node<T>* current, un nodo de este árbol.
MÉTODO: Recorre cada nodo hasta llegar a un nodo hoja y suma 1 por cada recursión.
Toma el valor máximo (más profundo) de cada subrama buscada.
ORDEN: O(n).
RETURN: int. Nivel más profundo del árbol.
*/
template <class T>
int BST<T>::recursiveHeight(Node<T>* current) const {
    if (current == nullptr) {
        return -1;
    }

    // Busca la profundidad del siguiente nodo.
    int leftDepth = recursiveHeight(current->getLeft());
    int rightDepth = recursiveHeight(current->getRight());

    return std::max(leftDepth, rightDepth) + 1; // Regresa la mayor profundidad.
}

/*
PARÁMETROS: T target, un dato de tipo T a buscar; Node<T>* current, un nodo del árbol.
MÉTODO: Recorre el árbol hasta encontrar el nodo con dato igual a target, si se encuentra, se imprime cada padre que recorrió el método.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: bool. true, si se encuentra el dato e imprime desde abajo hacia arriba; false si no se encuentra y no imprime nada.
*/
template <class T>
bool BST<T>::recursiveAncestors(T target, const Node<T>* current) const {
    if (current == nullptr) {
        return false;
    }

    if (current->getData() == target) {
        return true;
    } else if (target < current->getData()){
        if (recursiveAncestors(target, current->getLeft())) {
            std::cout << current->getData() << " ";
            return true;
        }
    } else {
        if (recursiveAncestors(target, current->getRight())) {
            std::cout << current->getData() << " ";
            return true;
        }
    }
    return false;
}

/*
PARÁMETROS: T target, un dato de tipo T a buscar; Node<T>* current, un nodo del árbol; int level, el nivel de profundidad de ese nodo.
MÉTODO: Comienza por la raíz en nivel 0 y si no se iguala a target, busca en sus subramas sumandole 1 al nivel de manera recursiva.
ORDEN: O(log(n)). n = Tamaño del arbol.
RETURN: int. Regresa la profundidad del árbol, si no se encuentra target, devuelve -1.
*/
template <class T>
int BST<T>::recursiveWhatLevelAmI(T target, const Node<T>* current, int level) const {
    if (current == nullptr) {
        return -1;
    }

    if (current->getData() == target) {
        return level;
    } else if (target < current->getData()) {
        return recursiveWhatLevelAmI(target, current->getLeft(), level + 1);
    } else {
        return recursiveWhatLevelAmI(target, current->getRight(), level + 1);
    }
}

/*
PARÁMETROS: void. Default.
MÉTODO: Inicializa un árbol vacio.
ORDEN: O(1).
RETURN: void. Este árbol.
*/
template <class T>
BST<T>::BST() : root(nullptr), size(0) {}

/*
PARÁMETROS: T data, un dato de tipo T.
MÉTODO: Inicializa un árbol vacio y luego inserta un nodo con ese data de argumento.
ORDEN: O(1).
RETURN: void. Este árbol.
*/
template <class T>
BST<T>::BST(T data) : root(nullptr), size(0) {
    insertNode(data);
}

/*
PARÁMETROS: BST<T> otherBST, otro árbol de tipo T.
MÉTODO: Inicializa un árbol vacio y luego inserta cada nodo del árbol por valor, siempre y cuando no sea un árbol vacio.
ORDEN: O(1).
RETURN: void. Este árbol.
*/
template <class T>
BST<T>::BST(const BST<T>& otherBST) : root(nullptr), size(0) {
    if (otherBST.root != nullptr) {
        recursiveCopyTree(otherBST.root);
    }
}

/*
PARÁMETROS: void.
MÉTODO: Llama al método destroyTree que elimina cada nodo del árbol, desde las hojas hasta la raíz.
ORDEN: O(1).
RETURN: void. Este árbol.
*/
template <class T>
BST<T>::~BST() {
    destroyTree(root);
}

/*
PARÁMETROS: T data, un dato a insertar de tipo T.
MÉTODO: Llama al método recursivo para insertar el nodo del argumento. Comienza por la raíz y busca
en el nivel inferior un lugar para insertarlo como nodo hoja. Suma 1 a size del árbol.
ORDEN: O(1).
RETURN: void. Este árbol.
*/
template <class T>
void BST<T>::insertNode(T data) {
    this->root = recursiveInsert(data, this->root);
    this->size++;
}

/*
PARÁMETROS: T data, un dato a buscar y borrar de tipo T.
MÉTODO: Llama al método recursive Delete, que toma data y lo busca para eliminar. Comienza por la raíz
y si se encuentra y borra el dato, isDeleted se vuelve true, que resta 1 a size del árbol.
ORDEN: O(1).
RETURN: void.
*/
template <class T>
void BST<T>::deleteNode(T data) {
    bool isDeleted = false;
    this->root = recursiveDelete(data, this->root, isDeleted);
    if(isDeleted){
        this->size--;
    } else {
        std::cerr << "Node not found" << std::endl;
    }
}

/*
PARÁMETROS: T data, un dato a buscar de tipo T.
MÉTODO: Llama al método recursiveSearch, que busca un nodo con el mismo dato que data de manera recursiva.
ORDEN: O(1).
RETURN: bool. true, si se encuentra; false, si no se encuentra.
*/
template <class T>
bool BST<T>::search(T data) const {
    return recursiveSearch(data, this->root);
}

/*
PARÁMETROS: int order, método por el cuál imprimir.
MÉTODO: Llama a cualquiera de estas funciones según el argumento dado:
1.- Preorder
2.- Inorder
3.- Postorder
4.- Level by level
ORDEN: O(1).
RETURN: void. Imprime el árbol en consola.
*/
template <class T>
void BST<T>::visit(int order) const {
    if(order == 1){
        recursivePreorder(this->root);
        std::cout << std::endl;
    } else if (order == 2){
        recursiveInorder(this->root);
        std::cout << std::endl;
    } else if (order == 3){
        recursivePostorder(this->root);
        std::cout << std::endl;
    } else if (order == 4){
        levelOrder();
        std::cout << std::endl;
    } else {
        std::cerr << "Ingrese un argumento entre 1 y 4.\n"
        "1.- Preorder\n"
        "2.- Inorder\n"
        "3.- Postorder\n"
        "4.- Level by level" << std::endl;
        return;
    }
}

/*
PARÁMETROS: void.
MÉTODO: Llama al método recursiveHeight, que busca la profundidad del árbol desde la raíz.
ORDEN: O(1).
RETURN: int. Nivel más profundo del árbol.
*/
template <class T>
int BST<T>::height() const {
    return recursiveHeight(this->root);
}

/*
PARÁMETROS: T target, un dato de tipo T a buscar sus ancestros.
MÉTODO: Llama al método recursiveAncestors que comienza a buscar a target desde el nodo raíz de forma recursiva.
ORDEN: O(1).
RETURN: void. Imprime en consola un error si no se encuentra target.
*/
template <class T>
void BST<T>::ancestors(T target) const {
    if (!recursiveAncestors(target, this->root)) {
        std::cerr << "No ancestors found" << std::endl;
    }
}

/*
PARÁMETROS: T target, un dato de tipo T a buscar su profundidad.
MÉTODO: Llama al método recursiveWhatLevelAmI que comienza a buscar a target desde el nodo raíz de forma recursiva.
ORDEN: O(1).
RETURN: void. Imprime en consola un error si no se encuentra target.
*/
template <class T>
int BST<T>::whatLevelAmI(T target) const {
    int level = recursiveWhatLevelAmI(target, this->root, 0);
    if (level == -1) {
        std::cerr << "Node not found" << std::endl;
    }
    return level;
}

template <class T>
int BST<T>::getSize() const {
    return this->size;
}