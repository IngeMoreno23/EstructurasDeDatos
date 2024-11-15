#include "parameterConfiguration.cpp"
#include <string>
#include <sstream>
#include <vector>

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

// PARAMETROS: Vector de enteros v y el tamaño del vector n
// METODO: Esta función es recursiva donde se divide el vector en 2 partes iguales, formando un arbol binario hasta llegar a un vector de 1.
// Posteriormente se compara cada elemento de las 2 partes inferiores del arbol binario y se ordenan de menor a mayor en un vector auxiliar.
// ORDEN: O(nlog(n)). 
// RETURN: Regresa el vector v con los valores ordenados de menor a mayor.
template <typename T>
void ordenaMerge(std::vector<T> &v, int n){
    if (n == 1) return;
    int mitad = n / 2;
    std::vector<T> v1, v2;
    for (int i = 0; i < mitad; i++) v1.push_back(v[i]);
    for (int i = mitad; i < n; i++) v2.push_back(v[i]);
    ordenaMerge(v1, mitad);
    ordenaMerge(v2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (v1[i] < v2[j]) {
            v[k] = v1[i];
            i++;
        } else {
            v[k] = v2[j];
            j++;
        }
        k++;
    }
    while (i < mitad) {
        v[k] = v1[i];
        i++;
        k++;
    }
    while (j < n - mitad) {
        v[k] = v2[j];
        j++;
        k++;
    }
}

struct IpFreq{
    public:
        int fanOut;
        std::vector<std::string> adjacencyList;
        std::string ip; 

        IpFreq(int frequency, std::vector<std::string> ips):fanOut(frequency),adjacencyList(ips){}
        IpFreq():fanOut(0), ip(""){}
        IpFreq(std::string _ip):fanOut(0),ip(_ip){
            adjacencyList= std::vector<std::string>();
        }
        void addConnection(std::string _ip){
            adjacencyList.push_back(_ip);
        }
        bool operator>(const IpFreq& other){
            return (fanOut != other.fanOut) ? fanOut > other.fanOut : ip > other.ip;
        }
        bool operator == (const std::string& _ip){
            return ip == _ip;
        }
        bool operator<(const IpFreq& other){
            return (fanOut != other.fanOut) ? fanOut < other.fanOut : ip > other.ip;        
        }
        bool operator==(const IpFreq& other){ // Este se utiliza en std::find(). Me gustaría también sobrecargar para que compare los fanOut, pero no puedo porque los std::find no funcionarían.
            return ip == other.ip;
        }
        bool operator!=(const IpFreq& other){
            return ip != other.ip;
        }
        void operator+(int addition){
            fanOut+=addition;
        }
        
        // Por alguna razón, si getData no regresa T por referencia, y como parámetros de la sobrecarga de << es const, (que creo que lleva a recibir un valor temporal), no se imprime nada.
        friend std::ostream& operator<<(std::ostream& os, const IpFreq& ipFreq){ // Se tuvo que agregar const para que aceptara tanto objetos temporales como persistentes. Para la impresión, se usa getData, que regresa un valor temporal. Al intentar ingresarlo a la función, que acepta por referencia, arroja un error de compilación. Por ende, se cambia a const que acepta ambos valores, y no copia ipFreq.
            os <<"IP: " << ipFreq.ip << " FanOut: " << ipFreq.fanOut;
            return os;
        }
};