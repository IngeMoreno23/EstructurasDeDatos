#pragma once

template <class T>
class SimpleNode{
    protected:
        T data;
        SimpleNode<T>* next;
    public:
        SimpleNode();
        SimpleNode(T data);
        SimpleNode(const SimpleNode<T>& nodeToCopy);
        ~SimpleNode();

        SimpleNode<T>* getNext();
        T getData() const;
        T& getData(); 

        void setData(T data);

        void setNext(SimpleNode<T>* nextNode);
        void operator= (const SimpleNode<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const SimpleNode<T>& nodeB);
        void print();
};

template <class T>
SimpleNode<T>::SimpleNode(){
    this ->data=T();
    next=nullptr;
}

template <class T>
SimpleNode<T>::SimpleNode(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void SimpleNode<T>::operator=(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

// Jun 3 13:11:26 543.89.843.57:5249 Failed password for illegal user guest
template <class T>
int SimpleNode<T>::operator>(const SimpleNode<T>& nodeB){
    return (this->data >nodeB.data);
}

template <class T>
SimpleNode<T>::SimpleNode(const SimpleNode<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
SimpleNode<T>::~SimpleNode(){
}

template <class T>
SimpleNode<T>* SimpleNode<T>::getNext(){
    return next;
}

template <class T> 
T SimpleNode<T>::getData() const {
    return data;
}

template <class T>
T& SimpleNode<T>::getData(){
    return data;
}

template <class T>
void SimpleNode<T>::setNext(SimpleNode<T>* next)
{
    this->next=next;
}

template <class T>
void SimpleNode<T>::setData(T data){
    this->data=data;
}

template <class T>
void SimpleNode<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void SimpleNode<T>::print(){
    std::cout<<data;
}
