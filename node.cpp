#include <iostream>
/*
Aprendizajes de esta tarea. Una clase al utilizar plantillas se debe poner en formato node<T>


*/

/*


        Node<T>* getPrevious();
        Node<T>* getNext();
        T& getData();
        
        void setNext(Node<T>* next);
        void setPrevious(Node<T>* previous);
        void setData(T data);

        void operator= (const Node<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const Node<T>& nodeB);

        void print();
*/
template <class T>
class Node{
    public:
        Node(T data);
        Node(const Node<T>& nodeToCopy);
        ~Node();

        Node<T>* getNext();
        T& getData();

        void setNext(Node<T>* next);
        void setData(T data);

        void operator= (const Node<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const Node<T>& nodeB);
        void print();

    private:
        Node<T> *next;
        T data;

};

template <class T>
Node<T>::Node(T data){
    this ->data=data;
    next=nullptr;
}

template <class T>
void Node<T>::operator=(const Node<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}

template <class T>
int Node<T>::operator>(const Node<T>& nodeB){
    if(data>nodeB.data){
        return 1;
    } else{
        return 0;
    }
}
template <class T>
Node<T>::Node(const Node<T>& nodeToCopy){
    this->data=nodeToCopy.data;
}


template <class T>
Node<T>::~Node(){
    delete this;
}

template <class T>
Node<T>* Node<T>::getNext(){
    return next;
}

template <class T> // TENGO DUDA AQUÍ. Por referencia? Supongo que sí, para poder modificarlo.
T& Node<T>::getData(){
    return data;
}

template <class T>
void Node<T>::setNext(Node<T>* next)
{
    this->next=next;
}

template <class T>
void Node<T>::setData(T data){
    this->data=data;
}

template <class T>
void Node<T>::operator=(const T newData){
    this->data=newData;
}

template <class T>
void Node<T>::print(){
    std::cout<<data;
}