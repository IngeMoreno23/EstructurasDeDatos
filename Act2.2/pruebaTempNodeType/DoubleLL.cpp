#include "DoubleLL.hpp"
#include "BaseLL.hpp"
#include "ops.cpp"
template <class T>
DoubleLL<T>::DoubleLL(){ 
    this->head = nullptr;
    this->head->setNext(nullptr);
    this->head->setPrevious(nullptr);
        
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

    while ( current != this->head){
        DoubleNode<T> *temp = current; 
        current = current->getNext();
        delete temp; 
    }
    this->head->setNext(nullptr);
    this->head->setPrevious(nullptr);   
    this->head =nullptr;
 
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
    this->head = new DoubleNode<T>;

    this->head->setNext(this->head);
    this->head->setPrevious(this->head);
        
    *this = listToCopy; // Usar *this para referirse al objeto y poder mandar llamar a la sobrecarga de asignación. 
}


template <class T>
void DoubleLL<T>::append(const DoubleNode<T>& nodeToAppend){
    if(this->head == nullptr){
        DoubleNode<T>* newNode=new DoubleNode<T> (nodeToAppend.getData());
        this->head=newNode;
        newNode->setPrevious(this->head);
        newNode->setNext(this->head);
        this->size++;
        return;
    }

    DoubleNode<T>* newNode=new DoubleNode<T> (nodeToAppend.getData());
    this->head->getPrevious()->setNext(newNode);
    newNode->setNext(this->head);
    newNode->setPrevious(this->head->getPrevious());
    this->head->setPrevious(newNode);
    this->size++;
}

template <class T>
void DoubleLL<T>::append(const DoubleLL<T>& listToAppend){
    if (listToAppend.size == 0){
        return;
    }
    
    DoubleNode<T>* currentNode=this->head->getPrevious(), *currentNodeCopy=listToAppend.head;

    if(this->head == nullptr){
        this -> head = new DoubleNode<T> (listToAppend.head->getData());
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
    DoubleNode<T>* temp = new DoubleNode<T> (data);
    this->append(*temp);
    delete temp;
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
DoubleLL<T>::Iterator::Iterator(DoubleNode<T>* currentNode, DoubleNode<T>* headNode) 
    : current(currentNode), head(headNode) {}

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
    current = current->getPrevious();
    return *this;
}

template <class T>
bool DoubleLL<T>::Iterator::operator!=(const Iterator& otro) const {
    return current != otro.current;
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::begin() {
    return Iterator(this->head, this->head);
}

template <class T>
class DoubleLL<T>::Iterator DoubleLL<T>::end() {
    return Iterator(this->head, this->head);
}
