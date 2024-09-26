/*
EXPLICACIÓN DEL CÓDIGO 
Cristian Ricardo Luque Arámbula A01741850
*/

#pragma once

#include <iostream>
#include "nodeHDCL.cpp" 
#include <string>
#include "linkedList.cpp"

template <class T>
class HDCLinkedList: public LinkedList<T>{

    private:
        int size;
    public: 
        // Constructors
        HDCLinkedList();
        HDCLinkedList(const HDCLinkedList<T>& listToCopy);
        HDCLinkedList(std::initializer_list<T> elements);
        ~HDCLinkedList();

        // Operators 
        const HDCLinkedList<T>& operator=(const HDCLinkedList<T>& listToCopy);
        T& operator[]( int position); 

        // Addition
        void insert(const Node<T>& nodeToInsert, int position);
        void append(const Node<T>& nodeToAppend);
        void append(const HDCLinkedList<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(HDCLinkedList<T>& listToMerge); // Conecta el último elemento de la primera al primero de la segunda. 

        void erase(int position);
        void pop();
        void empty();

        void update(T data, int position);

        //information
        int length();
        bool isEmpty();
        int search(T data);
        void print();

        void exchangeElements(int position1, int position2);
        void invertList();

        void ordMerge(HDCLinkedList<T> &l);
};

template <class T>
HDCLinkedList<T>::HDCLinkedList():head(nullptr),size(0){}

// iteración por rango en una estructura de datos. Permite recibir estructuras sin tamaño fijo como parámetro
template <class T>
HDCLinkedList<T>::HDCLinkedList(std::initializer_list<T> elements){

    size=0;
    
    if(elements.size() == 0){
        head=nullptr;
    } else{
        auto iterador=elements.begin(); // crea un iterador que detecta automáticamente el tipo. 

        head = new Node<T> (*iterador); // new (parametros). Manda a llamar al constructor que toma const T& como parámetro
        Node<T>* currentNode= head;
        for (; iterador !=elements.end(); ++iterador){ // se puede no inicializar nada en for

            Node<T>* nextNode = new Node<T> (*iterador); 
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
        Node<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0; // Por propósitos de consistencia, checar si una lista ha sido borrada o actualizaciones futuras al código. 
}

template <class T>
void HDCLinkedList<T>::empty(){
    while(head!=nullptr){ // Se utiliza la variable head en vez de crear otra para ir accediendo los elementos. 
        Node<T> *temp=head; 
        head=head->getNext();
        delete temp; // No se borra el apuntador, se borra lo almacenado en la dirección.
    }
    size=0;
}

// se pone const HDCLinkedList <T>& para realizar múltiples asignaciones
// O(n^2)
template <class T>
const HDCLinkedList<T>& HDCLinkedList<T>::operator=(const HDCLinkedList<T> & listToCopy){
    if (this == &listToCopy){ // Aquí se comparan los apuntadores. si el apuntador al objeto es el mismo al apuntador de la lista que se mandó, se regresa, pues es el mismo objeto.
        return this;
    }
    
    empty();    

    if (listToCopy.head==nullptr){
        return this;
    }

    // Resulta que no se declara el node<T> * para todos, el asterisco debe ir antes de cada variable
    Node<T>* currentNodeCopy=listToCopy.head, *currentNode = new node<T> (currentNodeCopy->getData());
    head=currentNode;

    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy ->getNext()!= listToCopy.head){

        Node<T>* nextNode= new node<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }
    currentNode->setNext(head);
    head->setPrevious(currentNode);

    size=listToCopy.size;
}

// Paso por referencia para no realizar copias y para poder modificar el valor directamente.
template <class T>
T& HDCLinkedList<T>::operator[](int position){

    if(position==1){
        return *head;
    }
    if (position > size){
        throw std::invalid_argument("Out of range");
    }

    Node<T>* currentNode=head;
    for(int i=1; i < position; i++){
        currentNode=currentNode->getNext();
    }

    return currentNode->getData();
}

template<class T>
void HDCLinkedList<T>::append(const Node<T>& nodeToAppend){
    if(head==nullptr){
        Node<T>* newNode=new Node<T> (nodeToAppend->getData());
        head=newNode;
        newNode->setPrevious(newNode);
        newNode->setNext(newNode);
        return;
    }

    Node<T>* newNode=new Node<T> (nodeToAppend->getData());
    head->getPrevious()->setNext(newNode);
    newNode->setNext(head);
    newNode->setPrevious(head->getPrevious());

    size++;
    // Es super necesario crear un nuevo nodo aquí, puesto que el que se manda por referencia puede salir de ámbito y borrarse. 
    Node<T> *newNode= new Node<T> (nodeToAppend->getData());
    currentNode->setNext(newNode);
    newNode->setPrevious(currentNode);
    newNode->setNext(head);
    size++;
    // A menos que justo se asigne un valor en la memoria manualmente antes de mandar llamar esta función, ahí sí tiene sentido solo hacer que el último nodo apunte a esa función. 
}

// SI SE AÑADE UN NODO HASTA EL FINAL, SE PUEDE ACCEDER A PARTIR DEL PRIMER ELEMENTO (PREVIOUS)
template <class T>
void HDCLinkedList<T>::append(const HDCLinkedList<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    Node<T>* currentNode=head, currentNodeCopy=listToAppend.head;
    while(currentNode->getNext() != head){
        currentNode= currentNode->getNext();
    }
    
    while(currentNodeCopy->getNext()!=listToAppend.head)
    {
        Node<T>* nextNode= new Node<T> (currentNodeCopy->getData());
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
    
    Node<T>* temp=head->getPrevious();
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
void HDCLinkedList<T>::insert(const Node<T>& nodeToInsert, int position){
    if(position >= size || position < 1){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    Node<T>* currentNode=head;
    for(int i = 1; i <= position; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    Node<T>* newNode = new Node<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    currentNode->setNext(newNode);
    size++;

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


    Node<T>* currentNode=head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (position == 1){
        head=currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i=0;i<=position; i++){
            currentNode=currentNode->getNext();
        }
        Node<T>*temp =currentNode->getNext();
        temp->getNext()->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    size--;
    
}

template <class T>
void HDCLinkedList<T>::pop(){
    
    Node<T>* temp= head-> getPrevious();
    temp->getPrevious()->setNext(head);
    delete temp;

}

template <class T>
void HDCLinkedList<T>::update(T data, int position){

    if(position < 1 || position > size){
        return; 
    }

    Node<T>* currentNode=head;
    
    for (int i=1; i<position; i++){
        currentNode=currentNode->getNext();
    }
    currentNode->setData(data);
}

template <class T>
void HDCLinkedList<T>::ordMerge(HDCLinkedList<T> &l){
    int n=l.length();

    if (n == 1) return;
    int mitad = n / 2;
    HDCLinkedList<T> l1, l2;
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
int HDCLinkedList<T>::length(){
    return size;

}

template <class T>
bool HDCLinkedList<T>::isEmpty(){
    
    if (head==nullptr){
        return true;
    }
    return false;
}

template <class T>
int HDCLinkedList<T>::search(T data){
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
void HDCLinkedList<T>::exchangeElements(int positionA, int positionB){

    // Para manejar las posiciones como índices
    if (positionA < 1 || positionB < 1){
        std::cerr<<"Out of range";
        return;
    }

    T buffer= *this[positionA];
    (*this)[positionA]=(*this)[positionB];
    (*this)[positionB]=buffer;
    // Esto es posible porque paso por referencia desde la sobrecarga de operador y desde el nodo. 
    // Supongo que también se puede hacer yendo uno por uno. o con el operador []
}

template <class T>
void HDCLinkedList<T>::invertList(){
    int positionA, half= (size % 2 == 0) ? size/2 : 1 + size/2;
    while(positionA < half){
        exchangeElements(positionA,size-positionA-1);
        positionA++;
    }
}

template <class T>
void HDCLinkedList<T>::print(){
    std::string text;
    Node<T>*currentNode=head->getNext();
    while(head!=currentNode->getNext())
    {
        std::cout<<currentNode->getData();
    }
}