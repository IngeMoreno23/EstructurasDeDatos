#include "BaseLL.cpp"

template<class T>
class DoubleLL:public BaseLL<T, DoubleNode<T>>{
    public:
        void append(NodeC<T>&);
};