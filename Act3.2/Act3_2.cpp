#include "PriorityQueue.hpp"
#include <iostream>

int main(){
    PriorityQueue<int> pQueue(4);
    std::cout<<"Primer caso de prueba. Acceder a un valor cuando la lista está vacía\n";
    try{
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.Top()<<"\n";
    } catch(out_of_range& ex){
        std::cout<<"Error. "<<ex.what()<<"\n";
    }
    
    std::cout<<"\nSegundo caso de prueba. Utiliza push hasta llenar la lista.\n";
    try{
        pQueue.push(5);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.Top()<<"\n";

        pQueue.push(6);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.Top()<<"\n";

        pQueue.push(10);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.Top()<<"\n";

        pQueue.push(8);
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.Top()<<"\n";
        pQueue.print();
        pQueue.push(15);
        pQueue.print();
    } catch(out_of_range& ex){
        std::cerr<<"Error. "<<ex.what()<<"\n";
    }
    std::cout<<"\nCuarto caso de prueba. Sacar valores hasta vaciar la lista. \n";
    PriorityQueue<int> pQueue2(4);
    try{
        pQueue2.print();
        pQueue2.push(5);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.push(6);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.push(10);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.push(8);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.Top()<<"\n";
        pQueue2.pop();
    } catch(out_of_range& ex){
        std::cerr<<"Error. "<<ex.what()<<"\n";
    }
}