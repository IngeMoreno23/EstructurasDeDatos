#include <vector>

//  heapify un subarbol cuya raiz es el nodo i
// un elemento del arreglo  arr[]. n es el tamaño del heap
void heapify(std::vector<int> &arr, int n, int i)
{
    int largest = i;   // Inicializar largest como raiz. Se utiliza indice 0 para el primer elemento.
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // Si el nodo hijo izquierdo tiene mayor valor que el raiz
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // Si el nodo hijo derecho tiene mayor valor que el raiz
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // SI largest es la raiz
    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        // Recursivamente se aplica lo mismo al subarbol afectado. (heapify)
        heapify(arr, n, largest);
    }
}

// funcion principal del  heap sort
void heapSort(std::vector<int> &arr, int n)
{
    // Construir el heap a partir del vector inicial.
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Se extrae la raiz del heap intercambiando los elementos del arreglo.
    for (int i = n - 1; i >= 0; i--)
    {
        // La raiz va al final del arreglo.
        std::swap(arr[0], arr[i]);

        // nuevamente se llama a heapify para el arbol incluido en el vector [0]..[i]
        heapify(arr, i, 0);
    }
}
