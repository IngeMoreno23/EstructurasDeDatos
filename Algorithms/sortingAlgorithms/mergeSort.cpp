#include <vector>

// PARAMETROS: Vector de enteros v y el tamaño del vector n
// METODO: Esta función es recursiva donde se divide el vector en 2 partes iguales, formando un arbol binario hasta llegar a un vector de 1.
// Posteriormente se compara cada elemento de las 2 partes inferiores del arbol binario y se ordenan de menor a mayor en un vector auxiliar.
// ORDEN: O(nlog(n)). 
// RETURN: Regresa el vector v con los valores ordenados de menor a mayor.
template <typename T>
void ordenaMerge(std::vector<T> &v, int n){
    if (n == 1) return;
    int mitad = n / 2;
    std::vector<int> v1, v2;
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
