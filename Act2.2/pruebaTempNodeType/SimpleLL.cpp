#include "SimpleLL.hpp"
#include "BaseLL.hpp"

template <class T>
SimpleLL<T>::SimpleLL():BaseLL<T, SimpleNode<T>>(){}

template <class T>
SimpleLL<T>::SimpleLL(std::initializer_list<T> elements):BaseLL<T, SimpleNode<T>>(elements){};

template <class T>
SimpleLL<T>::SimpleLL(const SimpleLL<T>& listToCopy){}

template <class T>
SimpleLL<T>::~SimpleLL(){
    this->empty();
}

template<class T>
void SimpleLL<T>::append(const SimpleNode<T>& nodeToAppend){
    if(this->head == nullptr){
        this->head = new SimpleNode<T> (nodeToAppend.getData());
        this->size++;
        return;
    }

    SimpleNode<T>* currentNode = this->head;
    while(currentNode->getNext() != nullptr){
        currentNode = currentNode->getNext();
    }

    currentNode->setNext(new SimpleNode<T> (nodeToAppend.getData()));
    this->size++;
}


template <class T>
void SimpleLL<T>::erase(int index){

    if(index >= this->size || index < 0 || this->head == nullptr){
        std::cerr<<"Out of range";
        return;
    } else if (this->size == 1){
        delete this->head; 
        this->head=nullptr;
        this->size=0;
        return;
    }

    SimpleNode<T> * prevNode = (index != 0) ? this->getNode(index-1): this->head;
    SimpleNode<T> * nodeToErase = prevNode->getNext();
    prevNode->setNext(nodeToErase->getNext());

    delete nodeToErase;

}