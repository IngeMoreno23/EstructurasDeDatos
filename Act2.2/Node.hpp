#pragma once

template <class T>
class Node{
    public:
        Node(T data);
        Node(const Node<T>& nodeToCopy);
        virtual ~Node();

        Node<T>* getNext();
        T getData() const;
        T& getData();

        void setNext(Node<T>* next);
        void setData(T data);

        void operator= (const Node<T>& nodeToCopy);
        void operator= (const T newData);

        int operator>(const Node<T>& nodeB);
        void print();
/*
        virtual void setNext(Node<T>* next) = 0;
        virtual Node<T>* getNext() const = 0;
        virtual void setPrevious(Node<T>* previous) = 0;
        virtual Node<T>* getPrevious() const = 0;
*/
    protected:
        Node<T> *next;
        T data;

};