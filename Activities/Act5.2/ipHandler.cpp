#include <string>
#include <sstream>
#include <vector>
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

struct IpFreq{
    public:
        int fanIn, fanOut;
        bool isFanIn;

        std::vector<std::string> destIps;
        std::string ip; 

        IpFreq(int frequency, std::vector<std::string> ips):fanIn(frequency),destIps(ips),fanOut(0){}
        IpFreq():fanIn(0), ip(""),fanOut(0){}
        IpFreq(std::string _ip):fanIn(0),ip(_ip),fanOut(0),destIps(std::vector<std::string>()){}
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

        void visualize(){
            std::cout<<"Ip: "<< ip<< " || || FanIn: "<< fanIn<<" || || FanOut: "<<fanOut<<"\n";
            for(const auto& ip:destIps){
                std::cout<<ip<<" ";
            }
            std::cout<<"\n";
        }

        friend std::ostream& operator<<(std::ostream& os, const IpFreq& ipFreq){ 
            os <<"IP: " << ipFreq.ip << " fanIn: " << ipFreq.fanIn << " fanOut: " << ipFreq.fanOut;
            return os;
        }
};