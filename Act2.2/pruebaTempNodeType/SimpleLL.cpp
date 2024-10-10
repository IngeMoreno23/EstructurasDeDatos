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
const SimpleLL<T>& SimpleLL<T>::operator=(const SimpleLL<T>& listToCopy){

    if (this == &listToCopy){ 
        return *this;
    }
    this->empty();
    
    if (listToCopy.head == nullptr){
        return *this;
    }

    SimpleNode<T>* currentNodeCopy = listToCopy.head, *currentNode = new SimpleNode<T> (currentNodeCopy->getData());
    this->head=currentNode;

    currentNodeCopy = currentNodeCopy->getNext();

    while(currentNodeCopy != nullptr){
        SimpleNode<T>* nextNode = new SimpleNode<T> (currentNodeCopy->getData()); //usar los getters.
        currentNode->setNext(nextNode);
        currentNodeCopy = currentNodeCopy->getNext();
        currentNode = nextNode;
    }

    currentNode->setNext(nullptr);
    this->size = listToCopy.length();
    
    return *this;
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

template <class T>
void SimpleLL<T>::merge(SimpleLL<T>& listToAppend){
    getNode(this->size-1)->setNext(listToAppend.head);
    listToAppend.head=nullptr;
}

template <class T>
void SimpleLL<T>::append(const SimpleLL<T>& listToAppend){
    SimpleNode<T>* currentNode=getNode(this->size-1), *currentCopyNode=listToAppend.head;
    while(currentCopyNode != nullptr){
        SimpleNode<T> *newNode = new SimpleNode<T> (currentCopyNode.data);
        currentNode -> setNext(currentCopyNode);
        currentNode = currentNode -> getNext();
        currentCopyNode = currentCopyNode -> getNext();
    }
    listToAppend.head=nullptr;
}

template <class T>
void SimpleLL<T>::insert(SimpleNode<T>& nodeToInsert, int index){
    SimpleNode<T>* currentNode= this->getNode(index);
    SimpleNode<T>* nextCurrentNode=currentNode->getNext();

    currentNode->setNext(new SimpleNode<T> (nodeToInsert.data));
    currentNode->getNext()->setNext(nextCurrentNode);
}


template <class T>
void SimpleLL<T>::insert(T data, int index){
    this->insert(* new SimpleNode<T> (data), index);
}

template <class T>
void SimpleLL<T>::append(T data){
    SimpleNode<T>* temp = new SimpleNode<T> (data);
    this->append(*temp);
    delete temp;
}