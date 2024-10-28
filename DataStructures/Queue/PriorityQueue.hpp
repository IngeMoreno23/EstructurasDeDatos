#pragma once
#include <iostream>
#include <algorithm>
#include "exceptions.cpp"

template <class T>
class PriorityQueue{
    public: 
        PriorityQueue();
        PriorityQueue(int _capacity);
        PriorityQueue(std::initializer_list<T> list);
        PriorityQueue(const PriorityQueue<T>& otherPQueue);
        ~PriorityQueue();

        const PriorityQueue<T>& operator =(const PriorityQueue<T>& otherPQueue);
        void pop();
        void push(const T& data);
        void emptyQueue();

        void rearrangeUp();
        void rearrangeDown();

        T& top();
        bool empty();
        int size();
        virtual void print();

    private: 
        T* content;
        int capacity, bottom; 

};

/*
> Parámetros: Ninguno
> Método: Constructor por defecto, inicializa una cola prioritaria con capacidad de 10, bottom (índice del último valor) equivalente a 1 y asigna un bloque de memoria de tamaño 10
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(){
    capacity = 10; 
    bottom = -1;
    content = new T[capacity];
}

/*
> Parámetros: Una lista inicializadora
> Método: Constructor con una lista inicializadora. La capacidad de la cola prioritaria es el tamaño de la lista más diez. Se asigna un bloque de memoria del tamaño de la capacidad y el índice al útlimo valor equivale al tamaño de la lista menos uno.
> Retorno: Nada
> Orden: O(n).
*/

template <class T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<T> list):capacity(list.size() + 10) {
    content = new T[capacity];
    bottom = (list.size() > 0) ? list.size() - 1: -1; 
    int i = 0; 
    for(const auto& element :list){
        content[i++]=element;
    }
}

/*
> Parámetros: Un entero con la capacidad de la cola a construir.
> Método: Constructor que especifica el tamaño de la cola. Asigna el valor del parámetro a la capacidad, el índice al último valor equivale a menos uno y asigna un bloque de memoria del tamaño de la capacidad especificada.
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(int _capacity){
    capacity= _capacity;
    bottom = -1; 
    content = new T[_capacity];

}

/*
> Parámetros: Otra cola prioritaria, por referencia
> Método: Constructor de copia. Toma los valores de capacidad y el índice del último valor a partir de los valores de la cola (que se pasó como parámetro). Se asigna un bloque de memoria del tamaño de la otra cola y copia sus valores.
> Retorno: Nada
> Orden: O(n).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& otherPQueue){
    capacity = otherPQueue.capacity; 
    bottom = otherPQueue.bottom;
    content = new T[capacity];

    for(int i=0; i<=bottom; i++){
        content[i] = otherPQueue.content[i];
    }
}

/*
> Parámetros: Otra cola prioritaria, por referencia
> Método: Sobrecarga del operador de asignación. Actualiza los valores de capacidad y el índice del último valor a partir de los valores de la cola (que se pasó como parámetro), se asigna un bloque de memoria del tamaño de la otra cola y copia sus valores.
> Retorno: Nada
> Orden: O(n).
*/
template <class T>
const PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& otherPQueue){
    if (this == &otherPQueue){
        return *this;
    }
    capacity = otherPQueue.capacity; 
    bottom = otherPQueue.bottom;

    delete[] content;
    content= new T[capacity];

    for(int i=0; i<=bottom; i++){
        content[i] = otherPQueue.content[i];
    }

    return *this; 
}

/*
> Parámetros: Nada.
> Método: Destructor de la clase
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::~PriorityQueue(){
    delete[] content;
}

/*
> Parámetros: Nada.
> Método: Pasa por cada valor de la cola y lo iguala al valor por defecto del tipo de dato que se maneja. Si es int, es cero. Si es string, es ""; 
> Retorno: Nada
> Orden: O(n).
*/
template <class T> 
void PriorityQueue<T>::emptyQueue(){
    bottom = -1; 
    for(int i = 0; i < capacity; i++){
        content[i]=T();
    } 
}

/*
> Parámetros: Ninguno
> Método: Si el índice del último valor es equivalente a -1, la cola está vacía.
> Retorno: Valor booleano que indica si la cola está vacía o no.
> Orden: O(1).
*/
template <class T>
bool PriorityQueue<T>::empty(){
    return (bottom == -1) ? true : false;
}

/*
> Parámetros: Ninguno
> Método: Accede al primer dato en el bloque de memoria de la cola.
> Retorno: Regresa el dato en el índice cero en el bloque de memoria de la cola, o bien, el dato con mayor prioridad.
> Orden: O(1).
*/
template <class T>
T& PriorityQueue<T>::top(){
    if(empty()){
        throw(out_of_range("La cola está vacía"));
    }
    return content[0];
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
        throw(out_of_range("La cola está vacía"));
    }

    if(bottom > 0) {
        std::swap(content[0], content[bottom]);
        content[bottom--]= T();
        rearrangeDown();
    } else {
        content[bottom--]= T();
    }

}

/*
> Parámetros: Ninguno.
> Método: Compara el nodo en una posición del arreglo con su nodo padre para intercambiar sus lugares en caso de ser mayor. Para hasta llegar al nodo raíz o hasta encontrar un nodo padre mayor a él. 
> Retorno: Ninguno.
> Orden: O(log(n))
*/
template <class T>
void PriorityQueue<T>::rearrangeDown() {
    int parent = 1; 
    int leftChild, rightChild, maxChild;

    while (2 * parent <= (bottom + 1)) {  
        leftChild = (2 * parent);
        rightChild = (2 * parent + 1);

        maxChild = (content[rightChild - 1] > content[leftChild - 1]) ? rightChild : leftChild;
        
        if (content[parent - 1] >= content[maxChild - 1]) {
            return;
        }
        
        std::swap(content[parent - 1], content[maxChild - 1]);
        parent = maxChild;
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
    if(bottom + 1 >= capacity){
        throw(out_of_range("La cola está llena"));
    }

    content[++bottom] = data;
    rearrangeUp();

}

/*
> Parámetros: Ninguno.
> Método: Compara el nodo en una posición del arreglo con su nodo padre para intercambiar sus lugares en caso de ser mayor. Para hasta llegar al nodo raíz o hasta encontrar un nodo padre mayor a él. 
> Retorno: Ninguno.
> Orden: O(log(n))
*/
template <class T>
void PriorityQueue<T>::rearrangeUp() {

    int child = bottom + 1;  
    int parent = child / 2; 

    while (child > 1 && content[parent - 1] < content[child - 1]) {
        std::swap(content[parent - 1], content[child - 1]);
        child = parent;
        parent = child / 2 ;
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
    return !empty() ? bottom + 1 : 0;
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

    for(int i = 0; i <= bottom; i++){
        std::cout <<content[i]<<" "; 
    }
    std::cout<<std::endl;

}
