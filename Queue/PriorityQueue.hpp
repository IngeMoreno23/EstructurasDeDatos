#pragma once
#include <iostream>
#include <algorithm>
#include "..\Queue\exceptions.cpp"

template <class T>
class PriorityQueue{
    public: 
        PriorityQueue();
        PriorityQueue(int _capacity);
        PriorityQueue(std::initializer_list<T> list);
        virtual ~PriorityQueue();

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
> Método: Constructor por defecto, manda llamar el constructor de la clase base
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(){
    capacity = 10; 
    bottom = -1;
    content = new T[capacity];
    emptyQueue(); // Colocado solo por motivos de depuración y pruebas
}

/*
> Parámetros: Una lista inicializadora
> Método: Constructor con una lista, manda llamar el constructor de la clase base que tiene este mismo parámetro.
> Retorno: Nada
> Orden: O(n).
*/

template <class T>
PriorityQueue<T>::PriorityQueue(std::initializer_list<T> list):capacity(list.size() + 10) {
    content = new T[capacity];
     emptyQueue(); // Colocado solo por motivos de depuración 
    bottom = (list.size() > 0) ? list.size() - 1: -1; 
    int i = 0; 
    for(const auto& element :list){
        content[i++]=element;
    }
}

/*
> Parámetros: Un entero con la capacidad de la lista a construir.
> Método: Constructor que especifica el tamaño de la lista, manda llamar el constructor de la clase base con el mismo parámetro.
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::PriorityQueue(int _capacity){
    capacity= _capacity;
    bottom = -1; 
    content = new T[_capacity];

    emptyQueue(); // Colocada solo por motivos de depuración y pruebas
}

/*
> Parámetros: Nada.
> Método: Destructor de la clase
> Retorno: Nada
> Orden: O(1).
*/
template <class T>
PriorityQueue<T>::~PriorityQueue(){
    delete[] this -> content;
}

template <class T> 
void PriorityQueue<T>::emptyQueue(){
    bottom = -1; 
    for(int i = 0; i < capacity; i++){
        content[i]=T();
    } 
}

/*
> Parámetros: Ninguno
> Método: Si el índice del último valor es equivalente a -1, la lista está vacía.
> Retorno: Valor booleano que indica si la lista está vacía o no.
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

    for(int i = 0; i < capacity; i++){
        std::cout <<content[i]<<" "; 
    }
    std::cout<<std::endl;

}
