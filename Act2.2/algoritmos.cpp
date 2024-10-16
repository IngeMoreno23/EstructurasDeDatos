#include "DoubleLL.hpp"
#include <string>
#include <sstream>

std::string obtainIp(const std::string& str){
    std::stringstream ssStr(str);
    std::string ip;
    for(int i=0; i < 4; i++){
        ssStr>>ip;
    }
    return ip;
}

std::string obtainPort(const std::string& str){
    std::stringstream ssStr(str);
    std::string port;
    for(int i=0; i < 4; i++){
        ssStr>>port;
    }
    return port.substr(port.find(':')+1,port.find(' '));
}

int operator>( std::string& a,  std::string& b){
    int numAct1=0, numAct2=0;

    std::stringstream ssStr1(a), ssStr2(b);
    while(ssStr1>>numAct1 && ssStr2 >> numAct2)
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


template <class T>
int busquedaBinaria(DoubleLL<T>& l, std::string clave){
    int inicio=0, final=l.length()-1;
    int mitad = inicio+(final-inicio)/2;
    class DoubleLL<T>::Iterator it=l.begin() + mitad;
    while (inicio <= final){
        std::string ip = obtainIp(*it);
        int comparacion = ip > clave;

        if (comparacion){
            final = mitad-1;
            mitad = inicio + (final-inicio)/2;
            it= it - 1 - ((final-inicio)/2 +(((final-inicio) % 2) == 1)*(1) );
        } else if (ip == clave){
            return mitad;
        } else{
            inicio = mitad+1;
            mitad = inicio + (final-inicio)/2;
            it= it + 1 + (final-inicio)/2;
        }
    }
    
    return mitad;
}

template <class T>
void ordMerge(DoubleLL<T> &l, typename DoubleLL<T>::Iterator itHalf, int n) { // el segundo iterador está localizado a la mitad. Se planea incluirlo como parámetro para que no se tenga que desplazar a la mitad desde la izquierda
    if (n == 1) return;
    int mitad = n / 2;

    DoubleLL<T> l1, l2;
    class DoubleLL<T>::Iterator it1= l.begin(), it2= itHalf, itHalfCopy=itHalf;

    for (int i = 0; i < mitad; i++, ++it1) {
        l1.append(*it1); // esta función consume mucho menos con una lista doblemente enlazada.
    }
    for (int i = mitad; i < n; i++, ++it2) {
        l2.append(*it2);
    }

    ordMerge(l1, itHalf - (mitad - mitad/ 2), mitad); // Resulta que el valor de ithalf cambiaba, así que tuve que hacer una copia.
    ordMerge(l2, itHalfCopy + (n - mitad)/2, n - mitad);

    int i = 0, j = 0, k = 0;
    it1=l1.begin();
    it2=l2.begin();
    class DoubleLL<T>::Iterator it= l.begin();

    while (i < mitad && j < n - mitad) {
        std::string a = obtainIp(*it1), b=obtainIp(*it2);
        if (a>b) {
            *it=*it2;
            ++it2;
            j++;
        } else {
            *it=*it1;
            ++it1;
            i++;
        }
        ++it;
        k++;
    }

    while (i < mitad) {
        *it = *it1;
        ++it;
        ++it1;
        i++;
        k++;
    }

    while (j < n - mitad) {
        *it = *it2;
        ++it;
        ++it2;
        j++;
        k++;
    }
}