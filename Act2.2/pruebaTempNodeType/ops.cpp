#include "DoubleLL.hpp"

template <class T>
int busquedaBinaria(const DoubleLL<T>& l, std::string clave, bool upper){
    int inicio=0, final=l.length(), ultimaInstancia=0;
    
    while (inicio <= final){
        int mitad = inicio+(final-inicio)/2;
        std::string ip = obtainIp(l[mitad]);
        int comparacion = ip > clave;

        if (upper ){
            ultimaInstancia=mitad;
        }
        if (comparacion){
            final = mitad-1;
        } else{
            inicio = mitad+1;
        }
    }
    return ultimaInstancia;
}

int operator>( std::string& a,  std::string& b){
    int numAct1=0, numAct2=0;

    std::stringstream ssStr1(a), ssStr2(b);
    while(ssStr1>>numAct1 && ssStr2 >> numAct2)
    {    
        if (numAct1>numAct2){
            return 1;
        } else if (numAct2>numAct1) {
            return 0;
        }
        ssStr1.ignore();
        ssStr2.ignore();
    }
    return 0;
}

std::string obtainIp(const std::string& str){
    std::stringstream ssStr(str);
    std::string ip;
    for(int i=0; i<4; i++){
        ssStr>>ip;
    }
    return ip;
}


template <class T>
void ordMerge(DoubleLL<T> &l, int n) {
    if (n == 1) return;

    int mitad = n / 2;
    DoubleLL<T> l1, l2;
    
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);

    ordMerge(l1, mitad);
    ordMerge(l2, n - mitad);

    int i = 0, j = 0, k = 0;

    while (i < mitad && j < n - mitad) {
        std::string a = obtainIp(l1[i]), b=obtainIp(l2[j]);
        if (a>b) {
            l[k] = l2[j];
            j++;
        } else {
            l[k] = l1[i];
            i++;
        }
        k++;
    }

    while (i < mitad) {
        l[k] = l1[i];
        i++;
        k++;
    }

    while (j < n - mitad) {
        l[k] = l2[j];
        j++;
        k++;
    }
}

