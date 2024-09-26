#pragma once

#include "Node.hpp"

template <class T>
class NodeC: public Node<T>{
    public:
        NodeC(T data);
        virtual ~NodeC();

        NodeC<T>* getPrevious();
        
        void setPrevious(NodeC<T>* previous);

    private:
        NodeC<T> *previous;

};