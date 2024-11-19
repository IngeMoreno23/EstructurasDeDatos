#include <iostream>
#include <stdexcept>
#include "..\Queue\Queue.hpp"

int isPrime(int n)
{
    if(n < 0){
        throw(std::invalid_argument("No se aceptan valores negativos"));
    }

    if(n == 0 || n == 1 || n % 2 == 0){ // Esta parte del código busca quitar el 0 y el 1 de las opciones, así como todos los números pares. Porque la siguiente comprobación, no los toma en cuenta, puesto que no es necesario.
        return false;
    }

    for(int i = 2; i * i < n; i += 2){
        if(n % i == 0){
            return false;
        }
    }

    return true;
}

template <class U>
struct mapElement{
    public: 
        int index;
        int state
        U value;
    
        mapElement
};

template <class T = mapElement<class U>, class U> 
class HashMap{
    private: 
        T *map;
        int capacity;
    public:
        HashMap();
        HashMap(int _capacity);
        void hash(int _index);
        insert(U);
};

template <class T, class U>
HashMap<T, U>::HashMap():capacity(11){
    map = new T[capacity];
}

template <class T, class U>
HashMap<T,U>::HashMap(int _capacity){
    if(isPrime(_capacity)){
        capacity = _capacity;
    } else if (_capacity % 2 == 0){
        _capacity ++;
    }
    while (!isPrime(_capacity)){
        _capacity += 2;
    }
    capacity = _capacity;
}

template <class T, class U>
void HashMap<T,U>::hash(int _index){

}