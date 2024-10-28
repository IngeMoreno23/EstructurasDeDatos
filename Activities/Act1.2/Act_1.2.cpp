#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "..\..\Algorithms\searchAlgorithms\algoritmosDeBusqueda.cpp"
#include "..\..\Algorithms\sortingAlgorithms\algoritmosDeOrdenamiento.cpp"

void llenarRandVector(std::vector<int> &v, int n){
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        v.push_back(rand() % 100);
    }
}

void copiarVector(std::vector<int> &v0, std::vector<int> &v1, int n){
    for(int i = 0; i < n; i++){
        v1.push_back(v0[i]);
    }
}

int main() {
    std::vector<int> v, v1, v2, v3, v4, v5; 
    int n;
    std::cout << "Ingrese el tamano del vector: ";
    while(std::cin >> n && n <= 0){
        std::cout << "Ingrese un tamano mayor a 0: ";
    }
    llenarRandVector(v, n);
    std::cout << "Vector: \n";
    for(int i = 0; i < n; i++){
        std::cout << v[i] << " ";
    }
    std::cout << std::endl << std::endl;

    //Métodos de ordenamiento
    copiarVector(v, v1, n);
    ordenaIntercambio(v1, n);
    std::cout << "Vector ordenado por intercambio: \n";
    for(int i = 0; i < n; i++){
        std::cout << v1[i] << " ";
    }
    std::cout << std::endl;

    copiarVector(v, v2, n);
    ordenaBurbuja(v2, n);
    std::cout << "Vector ordenado por burbuja: \n";
    for(int i = 0; i < n; i++){
        std::cout << v2[i] << " ";
    }
    std::cout << std::endl;

    copiarVector(v, v3, n);
    ordenaMerge(v3, n);
    std::cout << "Vector ordenado por merge: \n";
    for(int i = 0; i < n; i++){
        std::cout << v3[i] << " ";
    }
    std::cout << std::endl << std::endl;

    //Métodos de búsqueda
    int x;
    std::cout << "Ingrese el numero a buscar: ";
    std::cin >> x;
    std::cout << std::endl;

    std::cout << "Busqueda secuencial: \n";
    std::cout << "El numero " << x << " se encuentra en la posicion " << std::to_string(busqSecuencial(v3, n, x)) << std::endl;
    
    std::cout << "Busqueda binaria: \n";
    std::cout << "El numero " << x << " se encuentra en la posicion " << std::to_string(busqBinaria(v3, n, x)) << std::endl;

    return 0;
}

