#include <iostream>
#include <stdexcept>

bool isPrime(int n)
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

template <class _key, class _value>
struct mapElement{
    public: 
        _key key;
        int state;
        _value value;
        
        mapElement():key(_key()), state(-1), value(_value()){};

        friend std::ostream& operator<<(std::ostream& os, const mapElement<_key,_value>& mapElement){ // Se tuvo que agregar const para que aceptara tanto objetos temporales como persistentes. Para la impresión, se usa getData, que regresa un valor temporal. Al intentar ingresarlo a la función, que acepta por referencia, arroja un error de compilación. Por ende, se cambia a const que acepta ambos valores, y no copia ipFreq.
            os <<"["<< mapElement.key<<"] = "<<mapElement.value<<"  State: "<<mapElement.state;
            return os;
        }
};

template <class _key = int, class _value = int> 
class HashMap{
    private: 
        mapElement<_key, _value> *map;
        int tableSize;
    public:
        HashMap();
        HashMap(int _tableSize);

        const HashMap& operator=(HashMap& otherHashMap);
        _value& operator [](const _key& key);
        virtual int hash(const _key& key);
        void insert(_key& key, _value& value);
        void show();
        void eliminate(const _key& key);

        int capacity();
};

template <class _key, class _value> 
HashMap<_key, _value>::HashMap():tableSize(101){ // Número primo 
    map = new mapElement[tableSize];
}

template <class _key, class _value> 
HashMap<_key, _value>::HashMap(int _tableSize){
    if(isPrime(_tableSize)){
        tableSize = _tableSize;
    } else if (_tableSize % 2 == 0){
        _tableSize ++;
    }
    while (!isPrime(_tableSize)){
        _tableSize += 2;
    }
    tableSize = _tableSize;
    map = new mapElement<_key,_value>[tableSize];

}

// Se supone que este método es implementado por el objeto en particular que se almacena en el mapa.  
template <class _key, class _value> 
int HashMap<_key, _value>::hash(const _key& key){
    return key % tableSize;
/*
ESTE MÉTODO SE IMPLEMENTA CUANDO SE GUARDAN OBJETOS NO PRIMITIVOS. En este caso 
*/
}

template <class _key, class _value> 
void HashMap<_key, _value>::insert(_key& key, _value& value){
    int index = hash(key); // se obtiene el índice a partir de la función hash

    for(int i = 0; map[index].state == 1 && i <= tableSize; index = (index + 1) % tableSize, i++){}
    
    if(map[index].state != 1){
        map[index].value = value;
        map[index].state = 1;
        map[index].key = key;
    }

}

template <class _key, class _value> 
void HashMap<_key, _value>::eliminate(const _key& key){
    int index = hash(key); // se obtiene el índice a partir de la función hash

    for(int i = 0; (map[index].key != key || map[index].state == -1) && i <= tableSize; index = (index + 1) % tableSize, i++){} // NO sé cual de las dos condiciones sea más costosa en assembly. !(hash(index) + 1) o hash(index) == -1
    
    if(map[index].key == key && map[index].state == 1){
        map[index].key = _key();
        map[index].state = 0;
        map[index].value = _value();
    } else {
        throw(std::exception("No such value exists"));
    }
}

/*
PARÁMETROS: void.
MÉTODO: Imprime cada indice del array "map" que contiene los elementos insertados o vacios de la tabla hasg
ORDEN: O(n), donde n es el la capacidad de la tabla hash (tableSize).
RETURN: void.
*/
template <class _key, class _value> 
void HashMap<_key, _value>::show(){
    mapElement<_key,_value> *current = map;
    for(int i = 0; i < tableSize; i++) {
        std::cout<< *(current + i) << "\n";
    }
    std::cout<<"\n";
}


/*
PARÁMETROS: void.
MÉTODO: Retorna la el atributo "tableSize" de la tabla hash. 
ORDEN: O(1).
RETURN: int, el tamaño de la tabla hash.
*/
template <class _key, class _value> 
int HashMap<_key, _value>::capacity(){
    return tableSize;
}

template <class _key, class _value> 
_value& HashMap<_key, _value>::operator[](const _key& key){
    int index = hash(key);

    for(int i = 0; (map[index].key != key || map[index].state != 1) && i <= tableSize && map[index].state; index = (index + 1) % tableSize, i++){}
    
    
    if(map[index].key != key && map[index].state != 1){ // Si no lo encuentra, marca como encontrado, porque muy posiblemente, al valor que se regresa se asigne otro. Y si no se le asigna otro, no debería usarse esta función sino find.
        map[index].key=key;
        map[index].state = 1;
    }

    return map[index].value;
}