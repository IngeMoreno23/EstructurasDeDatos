#include <iostream>
#include <initializer_list>
#include "..\Tree\BST.hpp"

void test(BST<int> &myBST){
    
    std::cout << "Insertando 1..5" << std::endl;
    myBST.insertNode(1);
    myBST.insertNode(2);
    myBST.insertNode(3);
    myBST.insertNode(4);
    myBST.insertNode(5);
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);

    std::cout << "Nivel mas bajo / Height: " << myBST.height() << std::endl << std::endl;

    std::cout << "Tratando de borrar el nodo con dato 6 (NO EXISTE):" << std::endl;
    myBST.deleteNode(6); std::cout << std::endl;

    std::cout << "Buscaremos el nodo 1 de diferentes formas:" << std::endl;
    std::cout << "whatLevelAmI(1): " << myBST.whatLevelAmI(1) << std::endl;
    std::cout << "ancestors(1): "; myBST.ancestors(1); std::cout << std::endl;
    std::cout << "Tratando de borrar el nodo con dato 1 (SI EXISTE):" << std::endl;
    myBST.deleteNode(1);
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);
    std::cout << "Tamaño del arbol tras eliminar 1: " << myBST.getSize() << std::endl << std::endl;

    std::cout << "Buscaremos el nodo 5 de diferentes formas:" << std::endl;
    std::cout << "whatLevelAmI(5): " << myBST.whatLevelAmI(5) << std::endl;
    std::cout << "ancestors(5): "; myBST.ancestors(5); std::cout << std::endl;
    std::cout << "Tratando de borrar el nodo con dato 5 (SI EXISTE):" << std::endl;
    myBST.deleteNode(5);
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);
    std::cout << "Tamaño del arbol tras eliminar 5: " << myBST.getSize() << std::endl << std::endl;

    std::cout << "Nuevo nivel mas bajo / Height: " << myBST.height() << std::endl << std::endl;
}

void test(BST<std::string> &myBST){
    
    std::cout << "Insertando 'a'..'e'" << std::endl;
    myBST.insertNode("a");
    myBST.insertNode("b");
    myBST.insertNode("c");
    myBST.insertNode("d");
    myBST.insertNode("e");
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);

    std::cout << "Nivel mas bajo / Height: " << myBST.height() << std::endl << std::endl;

    std::cout << "Tratando de borrar el nodo con dato 'f' (NO EXISTE):" << std::endl;
    myBST.deleteNode("f"); std::cout << std::endl;

    std::cout << "Buscaremos el nodo 'b' de diferentes formas:" << std::endl;
    std::cout << "whatLevelAmI('b'): " << myBST.whatLevelAmI("b") << std::endl;
    std::cout << "ancestors('b'): "; myBST.ancestors("b"); std::cout << std::endl;
    std::cout << "Tratando de borrar el nodo con dato 'b' (SI EXISTE):" << std::endl;
    myBST.deleteNode("b");
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);
    std::cout << "Tamaño del arbol tras eliminar 'b': " << myBST.getSize() << std::endl << std::endl;

    std::cout << "Buscaremos el nodo 'd' de diferentes formas:" << std::endl;
    std::cout << "whatLevelAmI('d'): " << myBST.whatLevelAmI("d") << std::endl;
    std::cout << "ancestors('d'): "; myBST.ancestors("d"); std::cout << std::endl;
    std::cout << "Tratando de borrar el nodo con dato 'd' (SI EXISTE):" << std::endl;
    myBST.deleteNode("d");
    std::cout << "preorder:\t"; myBST.visit(1);
    std::cout << "inorder:\t"; myBST.visit(2);
    std::cout << "postorder:\t"; myBST.visit(3);
    std::cout << "level order:\t"; myBST.visit(4);
    std::cout << "Tamaño del arbol tras eliminar 'd': " << myBST.getSize() << std::endl << std::endl;

    std::cout << "Nuevo nivel mas bajo / Height: " << myBST.height() << std::endl << std::endl;
}
int main(){
    std::cout << std::endl;
    
    BST<int> myBST1;
    std::cout << "Prueba 1: Constructor default:" << std::endl;
    test(myBST1);

    std::cout << "------------------------------" << std::endl << std::endl;

    std::cout << "Prueba 2: Constructor de copia:" << std::endl;
    std::cout << "Crearemos una lista con 10, 11, 12, 13, 14, 15 y la copiaremos." << std::endl;
    BST<int> myBST2pre;
    myBST2pre.insertNode(10);
    myBST2pre.insertNode(11);
    myBST2pre.insertNode(12);
    myBST2pre.insertNode(13);
    myBST2pre.insertNode(14);
    myBST2pre.insertNode(15);

    std::cout << "Arbol utilizado previo a la copia." << std::endl;
    std::cout << "preorder:\t"; myBST2pre.visit(1);
    std::cout << "inorder:\t"; myBST2pre.visit(2);
    std::cout << "postorder:\t"; myBST2pre.visit(3);
    std::cout << "level order:\t"; myBST2pre.visit(4);

    BST<int> myBST2 = myBST2pre;
    std::cout << "Arbol copiado que se somete a la prueba de igualdad." << std::endl;
    std::cout << "preorder:\t"; myBST2pre.visit(1);
    std::cout << "inorder:\t"; myBST2pre.visit(2);
    std::cout << "postorder:\t"; myBST2pre.visit(3);
    std::cout << "level order:\t"; myBST2pre.visit(4);
    std::cout << std::endl;
    std::cout << "Si agregamos un nuevo dato, no se deverían de enlazar" << std::endl;
    std::cout << "Añadiendo 20 al arbol previo a la copia" << std::endl;
    myBST2pre.insertNode(20);
    std::cout << "Arbol utilizado previo a la copia." << std::endl;
    std::cout << "preorder:\t"; myBST2pre.visit(1);
    std::cout << "inorder:\t"; myBST2pre.visit(2);
    std::cout << "postorder:\t"; myBST2pre.visit(3);
    std::cout << "level order:\t"; myBST2pre.visit(4);

    std::cout << "Arbol copiado que se somete a la prueba de igualdad." << std::endl;
    std::cout << "preorder:\t"; myBST2.visit(1);
    std::cout << "inorder:\t"; myBST2.visit(2);
    std::cout << "postorder:\t"; myBST2.visit(3);
    std::cout << "level order:\t"; myBST2.visit(4);
    std::cout << std::endl;

    std::cout << "------------------------------" << std::endl << std::endl;

    std::cout << "Prueba 3: Lista más larga:" << std::endl;
    test(myBST2);

    std::cout << "------------------------------" << std::endl << std::endl;

    BST<std::string> myBSTstr;
    std::cout << "Prueba 4: Arbol de string, diferente tipo de dato:" << std::endl;
    test(myBSTstr);

    return 0;
}