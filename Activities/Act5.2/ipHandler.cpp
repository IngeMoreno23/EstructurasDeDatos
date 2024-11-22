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