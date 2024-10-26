/*
Este código es la implementación de una cola circular con algunas modificaciones para simular un árbol heap. Tiene métodos como
pop() y push() para agregar y eliminar elementos, empty(), size() y top() para conocer datos de la cola como si está vacía, el tamaño y el dato con mayor prioridad.
También cuenta con un método print con el propósito de comprobar el correcto funcionamiento de la cola. 

Cristian Ricardo Luque Arámbula A01741850
Oliver Moreno Ibarra A01742930
Rodolfo Romero Blas Valdez A01741665

Última modificación: 18/10/2024
*/

#include "..\DataStructures\Queue\PriorityQueue.hpp"
#include <iostream>
#include <string>

int main(){

    PriorityQueue<std::string> initQueue1(2), initQueue2 ={"Alberto", "Berenice", "Fernando"};
    PriorityQueue<int> initQueue3;
    std::cout<<"Primer caso de prueba, probar con datos distintos a enteros para verificar que la plantilla se haya realizado correctamente, testear los constructores\n";
    initQueue1.print();
    initQueue2.print();
    initQueue3.print();
    PriorityQueue<int> pQueue(4);
    std::cout<<"\nSegundo caso de prueba. Acceder a un valor cuando la lista está vacía.\n";
    try{
        std::cout<<"La lista está vacía? "<<pQueue.empty()<<"\n";
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.top()<<"\n";
    } catch(out_of_range& ex){
        std::cout<<"Error. "<<ex.what()<<"\n";
    }
    
    std::cout<<"\nTercer caso de prueba. Utiliza push hasta llenar la lista.\n";
    try{
        pQueue.push(5);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.top()<<"\n";

        pQueue.push(6);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.top()<<"\n";

        pQueue.push(10);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.top()<<"\n";

        pQueue.push(8);
        pQueue.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue.top()<<"\n";

        pQueue.push(15);
        pQueue.print();
    } catch(out_of_range& ex2){
        std::cout<<"Error: "<<ex2.what()<<"\n";
    }

    std::cout<<"\nCuarto caso de prueba. Sacar valores hasta vaciar la lista. \n";
    PriorityQueue<int> pQueue2(4);
    try{
        pQueue2.print();
        pQueue2.push(5);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.push(6);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.push(10);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.push(8);
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.pop();
        pQueue2.print();
        std::cout<<"El valor con mayor prioridad es: "<<pQueue2.top()<<"\n";
        pQueue2.pop();
    } catch(out_of_range& ex3){
        std::cout<<"Error: "<<ex3.what()<<"\n";
    }
}