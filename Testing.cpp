#include <iostream>
#include <string>

#include "linkedList.cpp"
#include "HDCLinkedList.cpp"
#include "NodeC.cpp"
#include "Node.cpp"

int main(){
    {
        LinkedList<int> lista={2,3,5};
        LinkedList<int> lista2=lista;
        LinkedList<std::string> listaVacia;

        std::cout<<"list 1: ";
        lista.print();
        std::cout<<"list 2: ";
        lista2.print();
        std::cout<<"empty list : ";
        listaVacia.print();

        std::cout<<"\nAppending new data to empty list (Hello world)\n";
        listaVacia.append("Hello world");
        listaVacia.print();

        std::cout<<"\nAppending new node to list 1 (4)\n";
        Node<int> newNode= Node<int> (4);
        lista.append(newNode);
        lista.print();

        std::cout<<"\nAppending new data to list 1 (7)\n";
        lista.append(7);
        lista.print();

        std::cout<<"\nIndividual testing. Accesing list 1 through indexes 0 to 5\n";

        std::cout<<lista[0]<<" ";
        std::cout<<lista[1]<<" ";
        std::cout<<lista[2]<<" ";
        std::cout<<lista[3]<<" ";
        std::cout<<lista[4]<<"\n";

        try{
            
        std::cout<<lista[5]<<"\n";
        }catch(std::invalid_argument){
            std::cout<<"\nerror in access\n";
        }


        lista.append(lista2);
        std::cout<<"\nAppending list 2 to list 1. New size: "<<lista.length()<<std::endl;

        std::cout<<"list 1: ";
        lista.print();
        std::cout<<"list 2: ";
        lista2.print();

        std::cout<<"\nOrdering list 1\n";
        try{
            lista.ordMerge(lista, lista.length());
        } catch(std::invalid_argument)
        {
            std::cout<<"error";
        }

        lista.print();

        std::cout<<"\nErasing value at index 2\n";
        lista.erase(2);
        lista.print();

        std::cout<<"\nUpdating value to 10 at index 3\n";
        lista.update(10,3);
        lista.print();

        std::cout<<"\nExchanging first and last element\n";
        lista.exchange(0,lista.length()-1);
        lista.print();

        std::cout<<"\nInverting list\n";
        lista.invert();
        lista.print();

        std::cout<<"\nNumber 10 is at index "<<lista.search(10)<<std::endl;

        LinkedList<int> lista3={6,4,7,1};
        std::cout<<"\nMerging new list ";
        lista3.print();    
        lista.merge(lista3);
        lista.print();
        
        std::cout<<"\nLinks in list 3 should not exist anymore\n";
        lista3.print();

        std::cout<<"\nOrdering\n";
        lista.ordMerge(lista,lista.length());
        lista.print();
        
        std::cout<<"\nIs list 1 empty? "<<lista.isEmpty();

        std::cout<<"\nInserting number 3 at index 5\n";
        lista.insert(3,5);
        lista.print();

        std::cout<<"\nEmptying list 1\n";
        lista.empty();
        lista.print();

        lista2.empty();
        listaVacia.empty();
    }
    
    
    std::cout<<"\nCHECKING PERFORMANCE OF CIRCULAR DOUBLY LINKED LIST WITH HEAD NODE:\n";

    HDCLinkedList<int> lista={2,3,5};
    HDCLinkedList<int> lista2=lista;
    HDCLinkedList<std::string> listaVacia;
    
    std::cout<<"list 1: ";
    lista.print();
    std::cout<<"list 2: ";
    lista2.print();
    std::cout<<"empty list : ";
    listaVacia.print();

    std::cout<<"\nAppending new data to empty list (Hello world)\n";
    // listaVacia.append("Hello world"); // No tengo idea por qué este en particular no se puede, y el de int de abajo sí
    // Creo que es porque lo agrega como Node a un NodeC. Eso es un problema. SI SE MANDÓ A LLAMAR AL APPEND DE LINKEDLIST, Y LO INICIALIZA COMO NODE normal
    listaVacia.print();

    std::cout<<"\nAppending new node to list 1 (4)\n";
    NodeC<int> newNode= NodeC<int> (4);
    lista.append(newNode);
    lista.print();

    std::cout<<"\nAppending new data to list 1 (7)\n";
    lista.append(7);
    lista.print();

    std::cout<<"\nIndividual testing. Accesing list 1 through indexes 0 to 5\n"; // Aquí al sobrecargarlo, como va al operator[] de linkedList normal, como que empieza a buscar a partir de la cabeza que no sé por qué, si es privada, se tiene acceso a ella. Supongo que es porque no puse this->head

    std::cout<<lista[0]<<" ";
    std::cout<<lista[1]<<" ";
    std::cout<<lista[2]<<" ";
    std::cout<<lista[3]<<" ";
    std::cout<<lista[4]<<"\n";

    try{
        
    std::cout<<lista[5]<<"\n";
    }catch(std::invalid_argument){
        std::cout<<"\nerror in access\n";
    }


    lista.append(lista2);
    std::cout<<"\nAppending list 2 to list 1. New size: "<<lista.length()<<std::endl;

    std::cout<<"list 1: ";
    lista.print();
    std::cout<<"list 2: ";
    lista2.print();

    std::cout<<"\nOrdering list 1\n";
    try{
        lista.ordMerge(lista, lista.length());
    } catch(std::invalid_argument)
    {
        std::cout<<"error";
    }

    lista.print();

    std::cout<<"\nErasing value at index 2\n";
    lista.erase(2);
    lista.print();

    std::cout<<"\nUpdating value to 10 at index 3\n";
    lista.update(10,3);
    lista.print();

    std::cout<<"\nExchanging first and last element\n";
    lista.exchange(0,lista.length()-1);
    lista.print();

    std::cout<<"\nInverting list\n";
    lista.invert();
    lista.print();

    std::cout<<"\nNumber 10 is at index "<<lista.search(10)<<std::endl;

    HDCLinkedList<int> lista3={6,4,7,1};
    std::cout<<"\nMerging new list ";
    lista3.print();    
    lista.merge(lista3);
    lista.print();
    
    std::cout<<"\nLinks in list 3 should not exist anymore\n";
    lista3.print();

    std::cout<<"\nOrdering\n";
    lista.ordMerge(lista,lista.length());
    lista.print();
    
    std::cout<<"\nIs list 1 empty? "<<lista.isEmpty();

    std::cout<<"\nInserting number 3 at index 5\n";
    lista.insert(3,5);
    lista.print();

    std::cout<<"\nEmptying list 1\n";
    lista.empty();
    lista.print();

    lista2.empty();
    listaVacia.empty();
}