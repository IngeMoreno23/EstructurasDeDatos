#include <string>
#include <sstream>
#include "../../DataStructures/List/DoubleLL.hpp"
#include "HashMap.hpp"

/*
PARAMETROS: String str. Una entrada de la bitácora.
METODO: Separa cada espacio de la entrada de la bitácora y solamente deja la ip.
ORDEN: O(1).
RETURN: String ip, regresa la ip.
*/
std::pair<std::string, std::string> obtainIp(const std::string& str){
    std::stringstream ssStr(str);
    if(! ssStr){
        throw(std::invalid_argument("Entrada no válida"));
    }
    std::string ipOr, ipDest;
    for(int i=0; i < 4; i++){
        ssStr>>ipOr;
    }
    ipOr = ipOr.substr(0, ipOr.find(":"));
    ssStr>>ipDest;
    ipDest = ipDest.substr(0, ipDest.find(":"));
    return std::pair<std::string, std::string>(ipOr,ipDest);
}

/*
PARAMETROS: 2 string a comparar.
METODO: Regresa un entero 1 o 0 que refresenta si es mayor o no.
ORDEN: O(1).
RETURN: Int 1 si es verdad que es menor, int 0 de lo contrario.
*/
int operator>( std::string& a,  std::string& b){
    int numAct1=0, numAct2=0;

    std::stringstream ssStr1(a), ssStr2(b);
    while(ssStr1 >> numAct1 && ssStr2 >> numAct2)
    {    
        if (numAct1 > numAct2){
            return 1;
        } else if (numAct2 > numAct1) {
            return 0;
        }
        ssStr1.ignore();
        ssStr2.ignore();
    }
    return 0;
}


template <class _key, class _value>
void ordenaMerge(const HashMap<_key, _value>& hash){
    ordenaMerge(hash.map, hash.tableSize - 1);
}


// PARAMETROS: Vector de enteros v y el tamaño del vector n
// METODO: Esta función es recursiva donde se divide el vector en 2 partes iguales, formando un arbol binario hasta llegar a un vector de 1.
// Posteriormente se compara cada elemento de las 2 partes inferiores del arbol binario y se ordenan de menor a mayor en un vector auxiliar.
// ORDEN: O(nlog(n)). 
// RETURN: Regresa el vector v con los valores ordenados de menor a mayor.
template <typename T>
void ordenaMerge(T *arr, int inicio, int final){
    if (final - inicio <= 1) return;
    int mitad = inicio + (final-inicio) / 2;
   
    int sizeIzq = mitad - inicio, sizeDer = final - mitad; 
    T *arr1 = new T[sizeIzq], *arr2= new T[sizeDer];

    for (int i = 0; i < sizeIzq; i++) arr1[i] = arr[i + inicio];
    for (int i = 0; i < sizeDer; i++) arr2[i] = arr[i + mitad];

    ordenaMerge(arr1, inicio, mitad);
    ordenaMerge(arr2, mitad, final); 

    int i = 0, j = 0, k = inicio;
    while (i < sizeIzq && j < sizeDer) {
        if (arr1[i] < arr2[j]) {
            arr[k++] = arr1[i++];
        } else {
            arr[k++] = arr2[j++];
        }
    }

    while (i < sizeIzq) arr[k++] = arr1[i++];
    while (j < sizeDer) arr[k++] = arr2[j++];

    delete[] arr1;
    delete[] arr2;
}

struct IpFreq{
    enum class compareBy{FANIN, FANOUT};
    public:
        int fanIn, fanOut;
        bool isFanIn;

        DoubleLL<std::string> adjacencyList;
        std::string ip; 

        IpFreq(int frequency, DoubleLL<std::string> ips):fanIn(frequency),adjacencyList(ips),fanOut(0){}
        IpFreq():fanIn(0), ip(""),fanOut(0){}
        IpFreq(std::string _ip):fanIn(0),ip(_ip),fanOut(0){
            adjacencyList = DoubleLL<std::string>();
        }
        bool operator>(const IpFreq& other){
            if (isFanIn)
                return (fanIn != other.fanIn) ? fanIn > other.fanIn : ip > other.ip;
            else
                return (fanOut != other.fanOut) ? fanOut > other.fanOut : ip > other.ip;
        }
        bool operator == (const std::string& _ip){
            return ip == _ip;
        }
        bool operator<(const IpFreq& other){
            if (isFanIn)
                return (fanIn != other.fanIn) ? fanIn > other.fanIn : ip > other.ip;
            else
                return (fanOut != other.fanOut) ? fanOut > other.fanOut : ip > other.ip;    
        }
        bool operator==(const IpFreq& other){ // Este se utiliza en std::find(). Me gustaría también sobrecargar para que compare los fanIn, pero no puedo porque los std::find no funcionarían.
            return ip == other.ip;
        }
        bool operator!=(const IpFreq& other){
            return ip != other.ip;
        }
        void operator+(int addition){
            fanIn+=addition;
        }
        void visualize(){
            std::cout<<"Ip: "<< ip<< " || || FanIn: "<< fanIn<<" || || FanOut: "<<fanOut<<"\n";
            adjacencyList.print();
        }
        // Por alguna razón, si getData no regresa T por referencia, y como parámetros de la sobrecarga de << es const, (que creo que lleva a recibir un valor temporal), no se imprime nada.
        friend std::ostream& operator<<(std::ostream& os, const IpFreq& ipFreq){ // Se tuvo que agregar const para que aceptara tanto objetos temporales como persistentes. Para la impresión, se usa getData, que regresa un valor temporal. Al intentar ingresarlo a la función, que acepta por referencia, arroja un error de compilación. Por ende, se cambia a const que acepta ambos valores, y no copia ipFreq.
            os <<"IP: " << ipFreq.ip << " fanIn: " << ipFreq.fanIn << " fanOut: " << ipFreq.fanOut;
            return os;
        }
};