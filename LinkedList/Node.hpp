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

    protected:
        Node<T> *next;
        T data;

};