#pragma once
#include "BaseLL.hpp"
#include "DoubleNode.hpp"
#include <stdexcept>

template<class T>
class DoubleLL:public BaseLL<T, DoubleNode<T>>{
    public:
        DoubleLL();
        DoubleLL(const DoubleLL<T>& listToCopy);
        DoubleLL(std::initializer_list<T> elements);
        ~DoubleLL() override;

        const DoubleLL<T>& operator=(DoubleLL<T> & listToCopy);

        void append(const DoubleNode<T>& nodeToAppend);
        virtual void append(T data) override;

        void append(const DoubleLL<T>& listToAppend); // Agrega los elementos de la segunda lista sin borrarla
        void merge(DoubleLL<T>& listToAppend); // Conecta el último elemento de la primera al primero de la segunda. 

        virtual void erase(int index) ;

        virtual void insert(T data, int index) override;
        virtual void insert(DoubleNode<T>& nodeToInsert, int index);

        void empty() override;
        void print();

        class Iterator{
            private:
                DoubleNode<T> *current;
            public:
                Iterator(DoubleNode<T> *currentNode);

                T& operator*();
                Iterator& operator++();
                Iterator& operator--();
                Iterator& operator+(unsigned int transIndex);
                Iterator& operator-(unsigned int transIndex);
                bool operator!=(const Iterator& otro) const;
        };
        Iterator begin();
        Iterator end();
};

template <class T>
DoubleLL<T>::DoubleLL(){ 
    this->head =new DoubleNode<T> (T());        
    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
}

template <class T> 
DoubleLL<T>::~DoubleLL(){
    empty();
    delete this->head;
}

template <class T>
void DoubleLL<T>::empty(){
    if(this->size == 0){
        return;
    }

    DoubleNode<T>* current = this->head;

    do{
        DoubleNode<T> *temp = current; 
        current = current->getNext();
        delete temp; 
    }while ( current != this->head);

    this->head=new DoubleNode<T> (T());
    this->size=0;
}

template <class T>
DoubleLL<T>::DoubleLL(std::initializer_list<T> elements){
    
    this->size=0;
    
    if(elements.size() == 0){
        this->head = nullptr;
    } else{
        auto iterador = elements.begin(); 

        this->head = new DoubleNode<T> (*iterador); 
        DoubleNode<T>* currentNode = this->head;
        currentNode->setPrevious(this->head);
        iterador++;
        this->size = 1;

        for (; iterador != elements.end(); ++iterador){
            DoubleNode<T>* nextNode = new DoubleNode<T> (*iterador); 
            currentNode->setNext(nextNode);
            nextNode->setPrevious(currentNode);
            currentNode = nextNode;
            this->size++;
        }
        
        currentNode->setNext(this->head);
        this->head->setPrevious(currentNode);
    }
}

template <class T>
DoubleLL<T>:: DoubleLL(const DoubleLL<T>& listToCopy){
    this->head = new DoubleNode<T> (T());

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    *this = listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}

template <class T>
void DoubleLL<T>::append(const DoubleNode<T>& nodeToAppend){
    DoubleNode<T>* newNode = (this->size == 0) ? this->head : new DoubleNode<T> (nodeToAppend.getData());
    if(this->size == 0){
        this->head->setData(nodeToAppend.getData());
    } else {
        this->head->getPrevious()->setNext(newNode);
        newNode->setPrevious(this->head->getPrevious());
    }

    newNode->setNext(this->head);
    this->head->setPrevious(newNode);
    this->size++;
}

template <class T>
void DoubleLL<T>::append(const DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    DoubleNode<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;

    if(this->size == 0){
        this -> head -> setData(listToAppend.head->getData());
        currentNode=this->head;
        this->head->setNext(currentNode);
        this->head->setPrevious(currentNode);
    } else{
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
    }

    currentNodeCopy= currentNodeCopy->getNext();

    while(currentNodeCopy != listToAppend.head){
        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNode = nextNode;
        
        currentNodeCopy = currentNodeCopy->getNext();
    }
    
    currentNode->setNext(this->head);
    currentNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(currentNode);
    this->size += listToAppend.size;
}

template <class T>
void DoubleLL<T>::merge(DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    if(this->size==0){
        this->head=listToAppend.head;
        listToAppend.head=nullptr;
        return;
    }

    DoubleNode<T>* listToAppendHeadCopy = new DoubleNode<T> (listToAppend.head->getData());    
    DoubleNode<T>* temp = this->head->getPrevious();

    temp->setNext(listToAppendHeadCopy);
    listToAppend.head->getPrevious()->setNext(this->head);
    
    listToAppendHeadCopy->setPrevious(temp);
    this->head->setPrevious(listToAppend.head->getPrevious()); // cambié aquí
    listToAppendHeadCopy->setNext(listToAppend.head->getNext());
    this->size+=listToAppend.size;

    listToAppend.head->setNext(nullptr);
    listToAppend.head->setPrevious(nullptr);
    listToAppend.size=0;
}

template<class T>
const DoubleLL<T> & DoubleLL<T>::operator=(DoubleLL<T> & listToCopy) {
    if (this == &listToCopy){ 
        return *this;
    }
    
    empty();    

    if (listToCopy.head == nullptr){
        return *this;
    }

    DoubleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new DoubleNode<T> (currentNodeCopy->getData());
    this->head = currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != listToCopy.head){

        DoubleNode<T>* nextNode = new DoubleNode<T> (currentNodeCopy->getData());
        currentNode->setNext(nextNode);
        nextNode->setPrevious(currentNode);
        currentNodeCopy=currentNodeCopy->getNext();
        currentNode=nextNode;
    }

    currentNode->setNext(this->head);
    this->head->setPrevious(currentNode);

    this->size = listToCopy.size;

    return *this;
}

template <class T>
void DoubleLL<T>::erase(int index){


    if(index >= this->size || index < 0 || this->head==nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }


    DoubleNode<T>* currentNode = this->head; // una variable que guarda un apuntador. NO es memoria dinámica.

    if (index == 1){
        this->head = currentNode->getNext();
        delete currentNode; // se puede borrar con delete el contenido de una variable que almacena un apuntador, aún cuando esta variable en particular no fue la que asignó memoria con new.
    } else{
        for(int i = 0;i <= index; i++){
            currentNode = currentNode->getNext();
        }
        DoubleNode<T>*temp = currentNode->getNext();
        temp->getNext()->setPrevious(currentNode);
        currentNode->setNext(temp->getNext());
        delete temp;
    }
    this->size--;
}

template <class T>
void DoubleLL<T>::insert(T data, int index){
    this->insert(* new DoubleNode<T> (data), index);
}

template <class T>
void DoubleLL<T>::append(T data){
    DoubleNode<T> temp(data);
    this->append(temp);
}

template <class T>
void DoubleLL<T>::print(){
    DoubleNode<T>* currentNode = this->head;

    std::cout<<"size= "<<this->size<<" elements: ";
    do{
        std::cout<<currentNode->getData()<<"\n";
        currentNode=currentNode->getNext();
    } while(currentNode -> getNext() != this->head);
    std::cout<<std::endl;
}

template <class T>
void DoubleLL<T>::insert(DoubleNode<T>& nodeToInsert, int index){
    if(index >= this->size || index < 0){
        std::cerr<<"Out of range, appending instead";
        append(nodeToInsert);
        return;
    }

    DoubleNode<T>* currentNode = this->head;
    for(int i = 1; i < index; i++){
        currentNode= currentNode->getNext();
    }

    // nodeToInsert.setNext(currentNode -> getNext()); Antes usaba este código, pero me di cuenta que es mejor asignar la memoria nuevamente. Aunque esto también se puede hacer antes de llamar a la función, siento que hacerlo desde la función es más sólido. 
    DoubleNode<T>* newNode = new DoubleNode<T> (nodeToInsert.getData());
    newNode->setNext(currentNode->getNext());
    newNode->setPrevious(currentNode);
    
    newNode->getNext() -> setPrevious(newNode);

    currentNode->setNext(newNode);
    this->size++;
}

template <class T>
DoubleLL<T>::Iterator::Iterator(DoubleNode<T>* currentNode) 
    : current(currentNode){}

template <class T>
T& DoubleLL<T>::Iterator::operator*() {
    return current->getData();
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator++() {
    current = current->getNext();
    return *this;
}

template <class T>
class DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator--() {
    if(current)
    current = current->getPrevious();
    return *this;
}

template <class T>
typename DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator+(unsigned int transIndex)
{
    if(this == nullptr){
        throw(std::invalid_argument("La lista está vacía. "));
    }
    for(int i=0; i<transIndex; i++){
        current=current->getNext();
    }
    return *this;
}

template <class T>
typename DoubleLL<T>::Iterator& DoubleLL<T>::Iterator::operator-(unsigned int transIndex)
{
    if(this == nullptr){
        throw(std::invalid_argument("La lista está vacía. "));
    }
    for(int i=0; i<transIndex; i++){
        current=current->getPrevious();
    }
    return *this;
}

template <class T>
bool DoubleLL<T>::Iterator::operator!=(const Iterator& otro) const {
    return current != otro.current;
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::begin() {
    return Iterator(this->head);
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::end() {
    return Iterator(this->head->getPrevious());
}
