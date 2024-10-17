#include <iostream>
#include "..\Queue\Queue.hpp"

template <class T>
class PriorityQueue: public Queue<T>{
    public: 
        PriorityQueue();
        PriorityQueue(std::initializer_list<T> list);

        void pop();
        void push(const T& data);
        void rearrangeUp(T data);
        void rearrangeDown(int index);

        void relocateUp(int index);

        T& top();
        bool empty();
        int size();

};

