#pragma once
#include "..\Queue\Queue.hpp"
#include <iostream>
#include <algorithm>

template <class T>
class PriorityQueue: public Queue<T>{
    public: 
        PriorityQueue();
        PriorityQueue(int _capacity);
        PriorityQueue(std::initializer_list<T> list);
        virtual ~PriorityQueue();

        void pop();
        void push(const T& data);

        void rearrangeUp();
        void rearrangeDown();

        T& Top();
        bool empty();
        int size();
        virtual void print();

};

/*
> Parámetros: Ninguno
> Método: Constructor por defecto, manda llamar el constructor de la clase base
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue():Queue<T>(){}

/*
> Parámetros: Una lista inicializadora
> Método: Constructor con una lista, manda llamar el constructor de la clase base que tiene este mismo parámetro.
> Retorno: Nada
> Orden: O(n).
*/

template <class T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<T> list):Queue<T>(list){}

/*
> Parámetros: Un entero con la capacidad de la lista a construir.
> Método: Constructor que especifica el tamaño de la lista, manda llamar el constructor de la clase base con el mismo parámetro.
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(int _capacity):Queue<T>(_capacity){};

/*
> Parámetros: Nada.
> Método: Destructor de la clase
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::~PriorityQueue(){
    delete[] this -> content;
};

/*
> Parámetros: Ninguno
> Método: Si el valor del tope es equivalente a -1, la lista está vacía.
> Retorno: Valor booleano que indica si la lista está vacía o no.
> Orden: O(1).
*/
template <class T>
bool PriorityQueue<T>::empty(){
    return (this -> top == -1) ? true : false;
}

/*
> Parámetros: Ninguno
> Método: Accede al primer dato en el bloque de memoria de la cola.
> Retorno: Regresa el dato en el índice cero en el bloque de memoria de la cola, o bien, el dato con mayor prioridad.
> Orden: O(1).
*/
template <class T>
T& PriorityQueue<T>::Top(){
    if(empty()){
        throw(out_of_range("The list is empty"));
    }
    return this -> content[0];
}

/*
> Parámetros: Ninguno.
> Método: Cambia de lugar el elemento con mayor prioridad por el de menos prioridad. Posteriormente, elimina el último elemento de la cola, dejando fuera el elemento con mayor prioridad. Compara el nodo en la posición del nodo raíz con los nodos hijos, y los intercambia por el nodo hijo mayor para seguir comparando con sus nuevos nodos hijos. Deja de comparar hasta que no tiene nodos hijos, o hasta encontrar nodos hijos menores a él.
> Retorno: Ninguno.
> Orden: O(log(n)) (incluyendo la función de rearrangeDown)
*/

template <class T>
void PriorityQueue<T>::pop(){
    if(empty()){
        throw(out_of_range("The queue is empty"));
    }

    std::swap(this -> content[ this -> top], this -> content[ this -> bottom]);
    if(this -> top == this -> bottom){
        this -> content[this -> bottom]= T();
        this -> top = this -> bottom = -1;
    } else{
        this -> content[this -> bottom]= T();
        if (size() == 1){
            this -> top = this -> bottom = -1;
            return; 
        }
        this -> bottom --;
    }
    rearrangeDown();
    
}

/*
> Parámetros: Ninguno.
> Método: Compara el nodo en una posición del arreglo con su nodo padre para intercambiar sus lugares en caso de ser mayor. Para hasta llegar al nodo raíz o hasta encontrar un nodo padre mayor a él. 
> Retorno: Ninguno.
> Orden: O(log(n))
*/
template <class T>
void PriorityQueue<T>::rearrangeDown() {
    int position = this->top + 1; 
    int leftChild, rightChild, maxChild;

    while ((2 * position + 1) % this->capacity != this->bottom) {  
        leftChild = (2 * position) % this->capacity;
        rightChild = (2 * position + 1) % this->capacity;

        if (this->content[rightChild] > this->content[leftChild]) {
            maxChild = rightChild;
        } else {
            maxChild = leftChild;
        }

        if (this->content[position] >= this->content[maxChild]) {
            return;
        }
        std::swap(this->content[position], this->content[maxChild]);
        position = maxChild;
    }
}

/*
> Parámetros: Ninguno.
> Método: Agrega un elemento a la cola. Este lo compara con su nodo padre para intercambiar sus lugares en caso de ser mayor. Para hasta llegar al nodo raíz o hasta encontrar un nodo padre mayor a él. 
> Retorno: Ninguno.
> Orden: O(log(n)) (incluyendo la función de rearrangeUp)
*/
template <class T>
void PriorityQueue<T>::push(const T& data){
    if(this -> isFull()){
        throw(out_of_range("Out of bounds"));
    }
    try{
        this->enQueue(data);
        rearrangeUp();
    } catch(out_of_range& ex){
        std::cerr<<"Exception: "<<ex.what();
        return;
    }
}

/*
> Parámetros: Ninguno.
> Método: Compara el nodo en una posición del arreglo con su nodo padre para intercambiar sus lugares en caso de ser mayor. Para hasta llegar al nodo raíz o hasta encontrar un nodo padre mayor a él. 
> Retorno: Ninguno.
> Orden: O(log(n))
*/
template <class T>
void PriorityQueue<T>::rearrangeUp() {
    int position = this->bottom;  
    int parent = (position - 1 + this->capacity) % this->capacity;

    while (position != this->top && this->content[parent] < this->content[position]) {
        std::swap(this->content[parent], this->content[position]);
        position = parent;
        parent = (position - 1 + this->capacity) % this->capacity;
    }
}


/*
> Parámetros: Ninguno.
> Método: Checa si el elemento bottom ha envuelto la cola. Si no, resta top a bottom. Si sí, agrega a bottom la capacidad + 1 y restarle el valor del tope.  
> Retorno: Un entero con el tamaño de la cola, el resultado del cálculo del método. 
> Orden: O(1)
*/
template <class T>
int PriorityQueue<T>::size(){
    if(empty()){
        return 0; 
    }

    return (this -> bottom >= this -> top) ? 
                this -> bottom - this -> top + 1:
                (this -> bottom + this -> capacity) - this->top + 1; 
}

/*
> Parámetros: Ninguno.
> Método: Imprime el tamaño de la cola y manda a llamar el método print base, que itera por los elementos para imprimirlos uno a uno.
> Retorno: Nada.
> Orden: O(n)
*/
template <class T>
void PriorityQueue<T>::print(){
    std::cout<<"La cola es de tamaño "<<size()<<": ";
    Queue<T>::print();
}
