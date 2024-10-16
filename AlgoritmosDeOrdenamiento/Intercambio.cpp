#include <vector>

// PARAMETROS: Vector de enteros v y el tamaño del vector n
// METODO: Esta función contiene un ciclo for donde se compara el valor de los elementos i con los valores subsecuentes j de otro ciclo 
// for anidado iniciando de i+1 hasta n, intercambiando i y j si i > j, colocando el valor mayor al final del vector. 
// ORDEN: O(n^2). 
// RETURN: Regresa el vector v con los valores ordenados de menor a mayor.
void ordenaIntercambio(std::vector<int> &v, int n){
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(v[i] > v[j]){
                int aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}