#include <iostream>
#include "..\Queue\Queue.hpp"

int main(){
    Queue<std::string> cola({"Pedro","Ernesto","Julián","Pancho"});
    std::cout<<cola.getFront()<<std::endl;

    try{
        cola.deQueue();
        cola.print();
        cola.deQueue();
        cola.print();
        cola.deQueue();
        cola.print();
        cola.deQueue();
        cola.print();
        cola.deQueue();

    } catch(out_of_range &ex){
        std::cout<<ex.what()<<std::endl;
    }

    try{
        cola.enQueue("Bernie1");
        cola.print();
        cola.enQueue("Bernie2");
        cola.print();
        cola.enQueue("Bernie3");
        cola.print();
        cola.enQueue("Bernie4");
        cola.print();
        cola.deQueue();
        cola.print();
        cola.enQueue("Bernie5");
        cola.print();
        cola.enQueue("Bernie6");
    } catch(out_of_range &ex){
        std::cout<<ex.what()<<std::endl;
    }
}