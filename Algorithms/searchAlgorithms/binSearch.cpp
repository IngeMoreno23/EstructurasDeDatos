#include <vector>

// PARAMETROS: Vector de enteros ordenados v, el tamaño del vector n y entero a buscar x
// METODO: Esta función donde encuentra la mitad del vector y compara el valor de los elementos v[mitad] con el valor x,
// si no es igual, se compara si v[mitad] es menor o mayor que x, y se actualiza el inicio o fin hasta llegar a un vector de 1 elemento.
// ORDEN: O(log(n)). 
// RETURN: Regresa la posición del número x en el vector v. Si no se encuentra, regresa -1.
template <typename T>
int busqBinaria(std::vector<T> &v, int n, int x){
    int inicio = 0, fin = n-1, mitad;
    while(inicio <= fin){
        mitad = (inicio + fin) / 2;
        if(v[mitad] == x){
            return mitad;
        } else if(v[mitad] > x){
            fin = mitad - 1;
        } else {
            inicio = mitad + 1;
        }
    }
    return -1;
}