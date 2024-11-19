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

    for(int i = 3; i * i <= n; i += 2){
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
    
};

template <class T> 
class HashMap{
    private: 
        mapElement<T> *map;
        int tableSize;
    public:
        HashMap();
        HashMap(int _tableSize);
        int hash(int _index);
        int insert(T& element);
        void show();
};

template <class T>
HashMap<T>::HashMap():tableSize(101){ // Número impar 
    map = new T[tableSize];
}

template <class T>
HashMap<T>::HashMap(int _tableSize){
    if(isPrime(_tableSize)){
        tableSize = _tableSize;
    } else if (_tableSize % 2 == 0){
        _tableSize ++;
    }
    while (!isPrime(_tableSize)){
        _tableSize += 2;
    }
    tableSize = _tableSize;
}

template <class T>
int HashMap<T>::hash(int _index){

}

template <class T>
int HashMap<T>::insert(T& element){
    while(hash)
}