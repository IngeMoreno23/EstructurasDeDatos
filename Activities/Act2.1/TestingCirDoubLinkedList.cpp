#include <iostream>
#include <string>

#include "..\..\DataStructures\List\DoubleLL.hpp"
#include "testConf.cpp" 

/*
PARAMETROS: Lista que se desea invertir.
METODO: Remplaza los datos de la posición actual y la posición size-posición actual, remplazando el primer elemento y el último hasta llegar a la mitad de la lista.
ORDEN: O(n).
RETURN: Regresa la lista actual con los datos de los nodos remplazados de inicio a fin.
*/
template <class T>
DoubleLL<T> invertir(DoubleLL<T> lista){
    lista.invert();
    return lista;
}

/*
PARAMETROS: Rebibe una lista enlazada y un dato a buscar dentro de los nodos de esa lista.
METODO: Compara el dato de cada nodo en la lista hasta encontrar uno que coincida.
ORDEN: O(n).
RETURN: Regresa la posición del primer nodo que coincida con el dato, si no se encuentra, regresa 0.
*/
template <class T>
int buscar(DoubleLL<T>& lista, T data){
    return (lista.search(data)+1);
}

/*
PARAMETROS: Recibe una lista enlazada, un dato del tipo de dato del nodo y una posición del nodo en la lista.
METODO: Verifica que la lista no este vacia, y que index este en el rango del primer elemento y size.
Remplaza el dato del nodo en la posición del argumento con el dato recibido en el argumento
ORDEN: O(n).
RETURN: Regresa la lista enlazada actual con un nodo extra en la posición indicada.
*/
template <class T>
void update(DoubleLL<T>& lista, int position, T data){
    lista.update(data, position-1);
}


/*
PARAMETROS: Rebibe la lista a ordenar y su número de nodos.
METODO: Utiliza el algoritmo divide y venceras, que separa la lista a la mitad varias veces hasta tener listas de 1 nodo, compara los datos de estos nodos
y acomoda los nodos de menor a mayor de forma recursiva hasta ordenarlos en la lista original.
ORDEN: O(nlog(n)).
RETURN: Regresa la lista enlazada con sus nodos ordenados de menor a mayor según sus datos.
*/
template <class T>
void ordenaMerge(DoubleLL<T> &l, int n){
    if (n == 1) return;
    int mitad = n / 2;
    DoubleLL<T> l1, l2;
    for (int i = 0; i < mitad; i++) l1.append(l[i]);
    for (int i = mitad; i < n; i++) l2.append(l[i]);
    ordenaMerge(l1, mitad);
    ordenaMerge(l2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (l1[i] > l2[j]) {
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

/*
PARAMETROS: Rebibe la lista a ordenar.
METODO: Utiliza el algoritmo divide y venceras, que separa la lista a la mitad varias veces hasta tener listas de 1 nodo, compara los datos de estos nodos
y acomoda los nodos de menor a mayor de forma recursiva hasta ordenarlos en la lista original.
ORDEN: O(nlog(n)).
RETURN: Regresa la lista enlazada con sus nodos ordenados de menor a mayor según sus datos.
*/
template <class T>
DoubleLL<T> ordenar(DoubleLL<T> lista){
    ordenaMerge(lista,lista.length());
    //DoubleLL<T> &l, typename DoubleLL<T>::Iterator itHalf, int n
    return lista;
}

template <class T>
void testLista(DoubleLL<T>& lista){
    std::cout<<"Lista original: ";
    lista.print();
    try{
        update(lista,POSITION_CHANGE,VALUE_CHANGE);
        std::cout<<"Cambio a "<<VALUE_CHANGE<< " en la posición "<<POSITION_CHANGE<<"\n";
        lista.print();
    } catch (std::invalid_argument){
        std::cout<<"Hubo un error intentado actualizar el valor\n";
    }

    try{
        int posicion = buscar(lista,VALUE_SEARCH);
        std::cout<<"El valor "<<VALUE_SEARCH<<" se encuentra en la posición "<<posicion<<"\n ";
    } catch (std::invalid_argument){
        
        std::cout<<"\nHubo un error buscando el valor\n"<<std::endl;
    }

    DoubleLL<std::string> nuevaLista = invertir(lista), nuevaLista2 = ordenar(lista);

    std::cout<<"\nLista original invertida: ";
    nuevaLista.print();
    std::cout<<"Lista original ordenada: ";
    nuevaLista2.print(); 
}

int main(){
    DoubleLL<std::string> lista = LIST_TEST;  
    testLista(lista);

}