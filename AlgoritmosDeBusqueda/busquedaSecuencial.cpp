#include <vector>
// PARAMETROS: Vector de enteros ordenados v, el tamaño del vector n y entero a buscar x
// METODO: Esta función contiene un ciclo for donde se compara el valor de los elementos v[i] con el valor x,
// ORDEN: O(n). 
// RETURN: Regresa la posición del número x en el vector v. Si no se encuentra, regresa -1.
int busqSecuencial(std::vector<int> &v, int n, int x){
    for(int i = 0; i < n; i++){
        if(v[i] == x){
            return i;
        }
    }
    return -1;
}