#pragma once

#include <string>
#include <iostream>
#include "linkedList.cpp"
#include "nodeC.cpp" 

template <class T>
class HDCLinkedList: public LinkedList<T>{

    public: 
        // Constructors
        HDCLinkedList();
        HDCLinkedList(const HDCLinkedList<T>& listToCopy);
        HDCLinkedList(std::initializer_list<T> elements);
        ~HDCLinkedList();

        // Operators 
        const HDCLinkedList<T>& operator=(const HDCLinkedList<T>& listToCopy);

        // Addition
        void insert(const NodeC<T>& nodeToInsert, int position);
        void append(const NodeC<T>& nodeToAppend);
        void append(const HDCLinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(HDCLinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void pop();
        void erase(int position);
};

template <class T>
HDCLinkedList<T>::HDCLinkedList():LinkedList<T>(){
}

// iteración por rango en una estructura de datos. Permite recibir estructuras sin tamaño fijo como parámetro
template <class T>
HDCLinkedList<T>::HDCLinkedList(std::initializer_list<T> elements){

    size=0;
    
    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new NodeC<T> (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        NodeC<T>* currentNode= head;
        for (; iterador !=elements.end(); ++iterador){ // se puede no inicializar nada en for

            NodeC<T>* nextNode = new NodeC<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode=nextNode;
            size++;
        }
        
        currentNode->setNext(head);
        head->setPrevious(currentNode);
    }
}

template <class T>
HDCLinkedList<T>:: HDCLinkedList(const HDCLinkedList<T>& listToCopy){
    *this=listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T> 
HDCLinkedList<T>::~HDCLinkedList(){
    while(head!=nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        NodeC<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0; // Por propósitos de consistencia, checar si una lista ha sido borrada o actualizaciones futuras al código. 
}

// se pone const HDCLinkedList <T>& para realizar múltiples asignaciones
// O(n^2)
template <class T>
const HDCLinkedList<T>& HDCLinkedList<T>::operator=(const HDCLinkedList<T> & listToCopy){
    if (this == &listToCopy){ // Aquí se comparan los apuntadores. si el apuntador al objeto es el mismo al apuntador de la lista que se mandó, se regresa, pues es el mismo objeto.
        return *this;
    }
    
    empty();    

    if (listToCopy.head==nullptr){
        return *this;
    }

    // Resulta que no se declara el nodeC<T> * para todos, el asterisco debe ir antes de cada variable
    NodeC<T>* currentNodeCopy=listToCopy.head, *currentNode = new NodeC<T> (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy ->getNext()!= listToCopy.head){

        NodeC<T>* nextNode= new NodeC<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }
    currentNode->setNext(head);
    head->setPrevious(currentNode);

    size=listToCopy.size;
    return *this;
}


template<class T>
void HDCLinkedList<T>::append(const NodeC<T>& nodeToAppend){
    if(head==nullptr){
        NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
        head=newNode;
        newNode->setPrevious(newNode);
        newNode->setNext(newNode);
        return;
    }

    NodeC<T>* newNode=new NodeC<T> (nodeToAppend.getData());
    head->getPrevious()->setNext(newNode);
    newNode->setNext(head);
    newNode->setPrevious(head->getPrevious());

    size++;
    // A menos que justo se asigne un valor en la memoria manualmente antes de mandar llamar esta función, ahí sí tiene sentido solo hacer que el último nodo apunte a esa función. 
}

// SI SE AÑADE UN NODO HASTA EL FINAL, SE PUEDE ACCEDER A PARTIR DEL PRIMER ELEMENTO (PREVIOUS)
template <class T>
void HDCLinkedList<T>::append(const HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    NodeC<T>* currentNode=head, currentNodeCopy=listToAppend.head;
    while(currentNode->getNext() != head){
        currentNode= currentNode->getNext();
    }
    
    while(currentNodeCopy->getNext()!=listToAppend.head)
    {
        NodeC<T>* nextNode= new NodeC<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode=nextNode;
        
        currentNodeCopy= currentNodeCopy->getNext();
    }
    
    currentNode->setNext(head);
    head->setPrevious(currentNode);

    size+=listToAppend.size;

}

template <class T>
void HDCLinkedList<T>::merge(HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    NodeC<T>* temp=head->getPrevious();
    temp->setNext(listToAppend.head);
    listToAppend.head->setPrevious(temp);

    size+=listToAppend.size;

    listToAppend.head=nullptr;
    listToAppend.size=0;

    // Considero que no es necesario borrar manualmente la lista segunda. Puesto que esta solo contiene variables, size, head;
    // El peligro de esta función es que si la segunda se sale de su ámbito será borrada la otra sección de la lista. La creación de este método fue mera experimentación. ENTONCES SI HAGO QUE EL DESTRUCTOR SE LLAME AQUI, DESPUÉS DE HACER QEU HEAD APUNTE A NULL, ESTARÉ EVADIENDO ESTE CASO.
    // estaba equivocado, sí se manda llamar al destructor cuando el objeto sale de ámbito, pero como yo hice que el apuntador de head fuera nullptr, el destructor no borrará los otros nodos. 
    // Aparte, si creo un nuevo objeto, también consume en la memoria (pero no dinámica). solo lo llamaría para llamar al destructor, pero la segunda lista ya no tiene memoria dinámica asignada.
}

template <class T>
void HDCLinkedList<T>::insert(const NodeC<T>& nodeToInsert, int position){
    if(position >= size || position < 1){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    NodeC<T>* currentNode=head;
    for(int i = 1; i <= position; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    NodeC<T>* newNode = new NodeC<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    currentNode->setNext(newNode);
    size++;

}

template <class T>
void HDCLinkedList<T>::pop(){
    
    NodeC<T>* temp= head-> getPrevious();
    temp->getPrevious()->setNext(head);
    delete temp;

}

template <class T>
void HDCLinkedList<T>::erase(int position){
    if(position >= size || position < 1 || head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (size==1){
        delete head; 
        head=nullptr;
        size=0;
        return;
    }


    NodeC<T>* currentNode=head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (position == 1){
        head=currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i=0;i<=position; i++){
            currentNode=currentNode->getNext();
        }
        NodeC<T>*temp =currentNode->getNext();
        temp->getNext()->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    size--;
    
}