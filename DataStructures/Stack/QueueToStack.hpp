#define QUEUE_TO_STACK
#include "..\Queue\Queue.hpp"
#include "Stack.hpp"

/*
> Parámetros: Una cola circular. 
> Método: Borra la memoria asignada en el constructor, y asigna a un nuevo bloque de memoria del tamaño de la capacidad de la cola, que después 
  asigna a la pila. Determina los elementos que hay entre el primer y último valor de la cola, y los copia en la pila. Es un constructor.
> Orden: O(n). n siendo los elementos en la cola circular.
*/
template <class T>
Stack<T>::Stack(const Queue<T>& queue){
    
    elements= new T[queue.capacity];
    capacity=queue.capacity;
    top=-1;
    int diff=(queue.bottom % queue.capacity) - (queue.top % queue.capacity);
    for(int i = 0; i <= diff; i++){
        push(queue.content[i]);
    }
}


