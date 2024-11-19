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
        
        mapElement():index(-1), state(-1), value(U()){};
};

template <class T = int> 
class HashMap{
    private: 
        mapElement<T> *map;
        int tableSize;
    public:
        HashMap();
        HashMap(int _tableSize);

        const HashMap& operator=();
        bool operator == (HashMap& otherHashMap);
        int hash(T& element);
        void insert(T& element);
        void show();
};

template <class T>
HashMap<T>::HashMap():tableSize(101){ // Número primo 
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

// Se supone que este método es implementado por el objeto en particular que se almacena en el mapa.  
template <class T>
int HashMap<T>::hash(T& element){
/*
ESTE MÉTODO SE IMPLEMENTA CUANDO SE GUARDAN OBJETOS NO PRIMITIVOS.
*/
}

template <>
int HashMap<int>::hash(int& element){
    return element % tableSize;
}

template <class T>
void HashMap<T>::insert(T& element){
    int index = hash(element); // se obtiene el índice a partir de la función hash
    for(int i = 0; hash(map + index) -> state == -1 && i <= tableSize; i++){ // NO sé cual de las dos condiciones sea más costosa en assembly. !(hash(index) + 1) o hash(index) == -1
        index = (index + 1) % tableSize; 
    }
    
    if((map + index) -> state != 1){
        map -> state = 1;
    }

}