#pragma once 

#include <iostream>
#include <algorithm>
#include "exceptionsStack.cpp"


template <class T>
class Stack{
    public:
        Stack();
        Stack(std::initializer_list<T> list);
        Stack(int _capacity);

        ~Stack();
    
        Stack(const Stack<T>& copyStack);

        #ifdef QUEUE_TO_STACK
            #include "..\Queue\Queue.hpp"
            friend class Queue<T>;
            Stack(const Queue<T>& queue); // es importante utilizar una letra distinta a T, para que no haya conflictos con la class T de la clase
        #endif

        const Stack<T>& operator =(const Stack<T>& copyStack);

        void push(T data);

        bool isFull();
        bool isEmpty();
        T& pop();
        T peek();
        int getTop();
        void print();
    private:
        int capacity, top; 
        T* elements;

};

/*
> Parámetros: Ninguno.
> Método: El constructor por defecto. Inicializa una pila de tamaño 10, y la llena del constructor por defecto del tipo de dato T. Tope equivale a -1.
> Orden: O(10) por el std::fill. por la capacidad de la pila, 
*/
template <class T>
Stack<T>::Stack():capacity(10), top(-1), elements(new T[10]){
    std::fill(elements, elements+capacity,T());
}

/*
> Parámetros: La capacidad de la pila.
> Método: Constructor. Inicializa la pila acorde al tamaño especificado, y la llena del constructor por defecto del tipo de dato T. Tope equivale a -1
> Orden: O(n) por el std::fill. n siendo la capacidad de la pila.
*/
template <class T>
Stack<T>::Stack(int _capacity):capacity(_capacity), top(-1), elements(new T[_capacity]){
    std::fill(elements, elements+_capacity,T());
}

/*
> Parámetros: Una lista inicializadora, que permite guardar datos en formato {int1, int2, int3}, y permite acceder al tamaño
> Método: El constructor. Inicializa una pila del tamaño de la lista inicializadora.
> Orden: O(n) n siendo el tamaño de la lista.
*/
template <class T>
Stack<T>::Stack(std::initializer_list<T> list): capacity(list.size()), top(list.size()-1){
    elements= new T[list.size()];
    int i=0;

    for(const T& item:list){
        elements[i]=item;
        i++;
    }

}

/*
> Parámetros: Un stack constante, paso por referencia. 
> Método: Manda llamar a la sobrecarga del operador de asignación.
> Orden: O(1), pero manda a llamar una función de O(n) 
> Retorno: Ninguno.
*/
template <class T>
Stack<T>::Stack(const Stack<T>& copyStack){
    *this = copyStack;
}

/*
> Parámetros: Un stack constante, paso por referencia. 
> Método: Borra la memoria asignada en el constructor, y asigna a un nuevo bloque de memoria del tamaño de la capacidad de la pila 
  pasada como parámetro. Uno a uno copia los elementos.
> Orden: O(n).
> Retorno: Regresa una lista constante para permitir la asignación múltiple a=b=c
*/
template <class T>
const Stack<T>& Stack<T>::operator=(const Stack<T>& copyStack){
    if(this = &copyStack){
        return *this; 
    }
    
    delete[] elements;

    capacity=copyStack.capacity;
    top=copyStack.top;
    elements=new T[capacity];

    for (int i=0; i < capacity; i++){
        elements[i]=copyStack.elements[i];
    }
}

/*
> Parámetros: Un valor de tipo de dato T. 
> Método: Si está lleno, arroja una excepción. Si no, añade 1 al valor del tope y asigna el dato mandado por referencia. 
> Orden: O(1)
> Retorno: Regresa una lista constante para permitir la asignación múltiple a=b=c
*/
template <class T>
void Stack<T>::push(T data){
    if(isFull()){
        throw(stack_overflow("Capacidad excedida\n"));
    }
    elements[++top]=data;
}


/*
> Parámetros: Ninguno.
> Método: Si está vacía la pila arroja una excepción. Guarda el valor en la posición del tope, asigna a esa posición el valor por defecto
  del tipo de dato T, y regresa el valor guardado. Al tope se le resta uno. 
> Orden: O(1)
> Retorno: Un valor del tipo de dato T. 
*/
template <class T>
T& Stack<T>::pop(){
    if (isEmpty()){
        throw(out_of_rangeStack("La pila está vacía\n"));
    }

    return elements[top--];
}
/*
> Parámetros: Ninguno.
> Retorno: El elemento que está en el tope.
> Orden: O(1)
*/
template <class T>
T Stack<T>::peek(){
    return elements[top];
}

/*
> Parámetros: Ninguno.
> Método: Destructor. Elimina los datos en la memoria asignada manualmente.
> Orden: O(1)
*/
template <class T>
Stack<T>::~Stack(){
    delete[] elements;
}

/*
> Parámetros: Ninguno.
> Retorno: Un valor booleano. TRUE si el tope equivale a -1, FALSE si el tope es cero o mayor. La pila contiene elementos siempre, pero en caso de
  que el tope equivalga a cero significa que no se consideran parte de la pila.
> Orden: O(1)
*/
template <class T>
bool Stack<T>::isEmpty(){
    if(top==-1){
        return true;
    }
    return false;
}

/*
> Parámetros: Ninguno.
> Retorno: Un valor booleano. TRUE si el tope es mayor o igual a la capacidad menos uno, falso si no.
> Orden: O(1)
*/
template <class T>
bool Stack<T>::isFull(){
    if(top >= capacity-1){
        return true;
    }
    return false;
}

/*
> Parámetros: Ninguno.
> Método: Imprime todos los valores de la pila
> Orden: O(n). n siendo la cantidad de elementos hasta el tope
*/
template <class T>
void Stack<T>::print(){

    for(int i=0; i<top; i++){
        std::cout<<elements[i]<<" ";
    }
    std::cout<<std::endl;
}

/*
> Parámetros: Ninguno.
> Orden: O(1)
> Retorno: Regresa el valor del tope de la pila
*/
template <class T>
int Stack<T>::getTop(){
    return top;
}
