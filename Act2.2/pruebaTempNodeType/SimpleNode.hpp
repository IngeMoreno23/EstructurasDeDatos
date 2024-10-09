#pragma once

template <class T>
class SimpleNode{
    protected:
        T data;
        SimpleNode<T>* next;
    public:
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