/*



*/

#pragma once

#include <iostream>
#include "node.cpp" 

template <class T>
class LinkedList{

    Node<T> *head; // automaticamente privado

    private:
        int size;
    public: 
        // Constructors
        LinkedList();
        LinkedList(const LinkedList<T>& listToCopy);
        LinkedList(std::initializer_list<T> elements);
        ~LinkedList();

        // Operators 
        void operator=(const LinkedList<T>& listToCopy);
        T& operator[](unsigned int position); 

        // Addition
        void insert(const Node<T>& nodeToInsert, int position);
        void append(const Node<T>& nodeToAppend);
        void append(const LinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(LinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void erase(int position);

        void update(T data, int position);

        //information
        int length();
        bool isEmpty();
        int search(T data);

        void exchangeElements(int position1, int position2);
        void invertList();
        void empty();

        void ordMerge(LinkedList<T> &l);

        // Node access
};

template <class T>
LinkedList<T>::LinkedList():head(nullptr),size(0){}

// iteración por rango en una estructura de datos. Permite recibir estructuras sin tamaño fijo como parámetro
template <class T>
LinkedList<T>::LinkedList(std::initializer_list<T> elements){

    size=0;
    
    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new Node<T> (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        Node<T>* currentNode= head;

        for (; iterador !=elements.end(); ++iterador){ // se puede no inicializar nada en for

            Node<T>* nextNode = new Node<T> (*iterador); 

            // xupdateNodeAccess()
            currentNode->setNext(nextNode);
            currentNode=nextNode;
            size++;
        }
    }
    currentNode->setNext(nullptr);
}

template <class T>
LinkedList<T>:: LinkedList(const LinkedList<T>& listToCopy){
    *this=listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T> 
LinkedList<T>::~LinkedList(){
    while(head!=nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        Node<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0; // Por propósitos de consistencia, checar si una lista ha sido borrada o actualizaciones futuras al código. 
}

template <class T>
void LinkedList<T>::operator=(const LinkedList<T> & listToCopy){
    if (this == &listToCopy){ // Aquí se comparan los apuntadores. si el apuntador al objeto es el mismo al apuntador de la lista que se mandó, se regresa, pues es el mismo objeto.
        return;
    }
    
    while(head!=nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        Node<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    
    size=0;

    if (listToCopy.head==nullptr){
        return;
    }

    // Resulta que no se declara el node<T> * para todos, el asterisco debe ir antes de cada variable
    Node<T>* currentNodeCopy=listToCopy.head, *currentNode = new Node<T> (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){

        Node<T>* nextNode= new Node<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }
    size=listToCopy.size;
}

// Paso por referencia para no realizar copias y para poder modificar el valor directamente.
template <class T>
T& LinkedList<T>::operator[](unsigned int position){
    if(position==0){
        return *head;
    }
    if (position >= size){
        std::cerr<<"Out of range";
    }

    Node<T>* currentNode=head;
    for(int i=0; i < position; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

template<class T>
void LinkedList<T>::append(const Node<T>& nodeToAppend){
    if(head==nullptr){
        head=new Node<T> (nodeToAppend->getData());
        return;
    }

    Node<T>* currentNode=head;
    while(currentNode->getNext()!= nullptr){
        currentNode= currentNode->getNext();
    }

    // Es super necesario crear un nuevo nodo aquí, puesto que el que se manda por referencia puede salir de ámbito y borrarse. 
    currentNode->setNext(new Node<T> (nodeToAppend->getData()));
    size++;
    // A menos que justo se asigne un valor en la memoria manualmente antes de mandar llamar esta función, ahí sí tiene sentido solo hacer que el último nodo apunte a esa función. 
}

template <class T>
void LinkedList<T>::append(const LinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    Node<T>* currentNode=head, currentNodeCopy=listToAppend.head;
    while(currentNode->getNext() != nullptr){
        currentNode= currentNode->getNext();
    }
    
    while(currentNodeCopy->getNext()!=nullptr)
    {
        Node<T>* nextNode= new Node<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        currentNode=nextNode;
        
        currentNodeCopy= currentNodeCopy->getNext();
    }
    
    size+=listToAppend.size;

}

template <class T>
void LinkedList<T>::empty(){

    while(head!=nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        Node<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}
template <class T>
void LinkedList<T>::merge(LinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    Node<T>* currentNode=head;
    while(currentNode->getNext() != nullptr){
        currentNode= currentNode->getNext();
    }

    currentNode->setNext(listToAppend.head);
    size+=listToAppend.size;

    listToAppend.head=nullptr; // Considero que no es necesario borrar manualmente la lista segunda. Puesto que esta solo contiene variables, size, head;
    listToAppend.size=0; // El peligro de esta función es que si la segunda se sale de su ámbito será borrada la otra sección de la lista. La creación de este método fue mera experimentación. 

}

template <class T>
void LinkedList<T>::insert(const Node<T>& nodeToInsert, int position){
    if(position >= size || position < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    Node<T>* currentNode=head;
    for(int i = 0; i < position - 1; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    Node<T>* newNode = new Node<T> (nodeToInsert->getData());
    newNode->setNext(currentNode->getNext());
    currentNode->setNext(newNode);
    size++;

}

template <class T>
void LinkedList<T>::erase(int position){
    if(position >= size || position < 0 || head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (size==1){
        delete head; 
        head=nullptr;
        size=0;
        return;
    }


    Node<T>* currentNode=head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (position == 0){
        head=currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i=0;i<position; i++){
            currentNode=currentNode->getNext();
        }
        Node<T>*temp =currentNode->getNext();
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    size--;
    
}

template <class T>
void LinkedList<T>::update(T data, int position){
    if(position <0 || position >=size){
        return; 
    }

    Node<T>* currentNode=head;
    
    for (int i=0; i<position; i++){
        currentNode=currentNode->getNext();
    }
    currentNode->setData(data);
}

template <class T>
void LinkedList<T>::ordMerge(LinkedList<T> &l){
    int n=l.length();

    if (n == 1) return;
    int mitad = n / 2;
    linkedList<T> l1, l2;
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);
    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (l1[i] > l2[j]) {
            l[k] = l2[j];
            j++;
        } else {
            l[k] = l1[i];
            i++;
        }
        k++;
    }
    while (i < mitad) {
        l[k] = l1[i];
        i++;
        k++;
    }
    while (j < n - mitad) {
        l[k] = l2[j];
        j++;
        k++;
    }
}

template <class T>
int LinkedList<T>::length(){
    return size;

}

template <class T>
bool LinkedList<T>::isEmpty(){
    
    if (head==nullptr){
        return true;
    }
    return false;
}

template <class T>
int LinkedList<T>::search(T data){
    Node<T>* currentNode=head;
    int i=0;
    while(currentNode->getNext()!=nullptr){
        if (currentNode->getData() == data){
            return i;
        }
        i++;
    }
}

template <class T>
void LinkedList<T>::exchangeElements(int positionA, int positionB){
    T buffer= *this[positionA];
    (*this)[positionA]=(*this)[positionB];
    (*this)[positionB]=buffer;
    // Esto es posible porque paso por referencia desde la sobrecarga de operador y desde el nodo. 
    // Supongo que también se puede hacer yendo uno por uno. o con el operador []
}

template <class T>
void LinkedList<T>::invertList(){
    int positionA, half= (size % 2 ==0) ? size/2: 1 + size/2;
    while(positionA < half){
        exchangeElements(positionA,size-positionA-1);
        positionA++;
    }
}
