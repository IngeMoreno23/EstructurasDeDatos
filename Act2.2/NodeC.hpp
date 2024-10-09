#pragma once

#include "Node.cpp"

template <class T>
class NodeC: public Node<T>{
    public:
        NodeC(T data);
        NodeC();
        ~NodeC() override;

        NodeC<T>* getPrevious();
        
        void setPrevious(NodeC<T>* previous);
        NodeC<T>* getNext();

    private:
        NodeC<T> *previous;

};
