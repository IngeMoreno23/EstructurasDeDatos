#include <vector>

// PARAMETROS: Vector de enteros v y el tamaño del vector n
// METODO: Esta función contiene un ciclo 2 ciclos for anidados donde se compara el valor de los elementos i con los valores subsecuentes j,
// intercambiando i y j si i > j, colocando el valor mayor al final del vector.
// ORDEN: O(n^2). 
// RETURN: Regresa el vector v con los valores ordenados de menor a mayor.
void ordenaBurbuja(std::vector<int> &v, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n-1; j++){
            if(v[j] > v[j+1]){
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
        }
    }
}