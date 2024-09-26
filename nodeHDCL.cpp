#include <iostream>

#include "node.cpp"
/*
Aprendizajes de esta tarea. Una clase al utilizar plantillas se debe poner en formato node<T>
*/

template <class T>
class NodeC{
    public:
        NodeC(T data);
        NodeC(const NodeC<T>& nodeToCopy);
        ~NodeC();

        NodeC<T>* getPrevious();
        NodeC<T>* getNext();
        T& getData();
        
        void setNext(NodeC<T>* next);
        void setPrevious(NodeC<T>* previous);
        void setData(T data);

        void operator= (const NodeC<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const NodeC<T>& nodeB);

        void print();
    private:
        NodeC<T> *next;
        NodeC<T> *previous;
        T data;

};

template <class T>
NodeC<T>::NodeC(T data){
    this ->data=data;
    next=nullptr;
    previous=nullptr;
}

template <class T>
void NodeC<T>::operator=(const NodeC<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

template <class T>
int NodeC<T>::operator>(const NodeC<T>& nodeB){
    if(data>nodeB.data){
        return 1;
    } else{
        return 0;
    }
}
template <class T>
NodeC<T>::NodeC(const NodeC<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
NodeC<T>::~NodeC(){
    delete previous;
    delete next;

    // delete this;
}

template <class T>
Node<T>* Node<T>::getNext(){
    return next;
}

template <class T> // TENGO DUDA AQUÍ. Por referencia. 
T& NodeC<T>::getData(){
    return data;
}

template<class T>
NodeC<T>* NodeC<T>::getPrevious(){
    return previous;
}

template <class T>
void NodeC<T>::setNext(NodeC<T>* next)
{
    this->next=next;
}

template<class T>
void NodeC<T>::setPrevious(NodeC<T>* previous){
    this-> previous=previous;
}

template <class T>
void NodeC<T>::setData(T data){
    this->data=data;
}

template <class T>
void NodeC<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void NodeC<T>::print(){
    std::cout<<data;
}