// Autoria
// Cristian Luque A01741850
// Oliver Moreno A01742930
// Rodolfo Blas A01741665

// Este programa recibe y filtra la entrada del usuario en un ciclo hasta obtener un entero positivo n. 
// Ofrece la suma de todos los elementos enteros de 1 a n por medio de tres metodos
// Recursivo, iterativo y suma directa (por el metodo de Gauss)
// Finalmente imprime los resultados de los 3 metodos

#include <iostream>
#include <string>

// Esta funcion acepta la entrada del usuario y vuelve a pedirla hasta que se ingrese un entero positivo. 
// Regresa el valor entero obtenido, puede ser un valor entre 1 y 2,147,483,647, por el tipo de dato entero y el filtro de los datos negativos.
int filtraInput(){

    int n=-1;

    // Se utiliza cin >> n para la condicion, puesto que si espera un entero y no lo recibe, regresa NULL. 
    // Una alternativa a este bloque es aceptar la entrada del usuario como string y tratar de convertir a entero con un bloque try catch
    while((std::cout << "Ingresa un entero positivo n>=1." << std::endl << "n=") && (! (std::cin >> n) || n < 1)){ 
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout<<"La entrada no es valida \n";
    }
    
  return n;
}

// PARAMETROS: Recibe un entero positivo que refiere al numero maximo que se acumula en la suma de los enteros de 1 a n
// METODO: Esta funcion contiene un ciclo for que, en una variable llamada suma, va sumando los valores de i
// del ciclo for a los cuales se le aumenta 1 en cada ciclo hasta llegar a n. 
// ORDEN: O(n). Es de orden n. 
// RETURN: Regresa la sumatoria de 1 a n en un unsigned long long int (de 0 a 2^63 -1)
unsigned long long int sumaIterativa(int n){

    unsigned long long int suma=0;

    for(int i = 1 ; i <= n ; i++){
        suma+=i;
    }

    return suma;
}

// PARAMETROS: Recibe un entero positivo que sera el limite para la suma (de 1 a n). Recibe el parametro suma que refiere 
// a la suma que lleva acumulada de las pasadas recursiones 
// METODO: Revisa si el valor de n es equivalente a cero para regresar la suma acumulada. De no ser el caso, vuelve a llamar a
// la funcion, ahora como parametros n-1 y la suma (acumulada) + n. 
// ORDEN: O(n). Es de orden n
// RETURN: Regresa la sumatoria de 1 a n en un unsigned long long int (de 0 a 2^63 -1)
// COMENTARIOS ADICIONALES: Es mas sencillo obtener segmentation fault con numeros altos al utilizar el metodo recursivo
unsigned long long int sumaRecursiva(int n, long long int suma) 
{
    if (n==0){  
        return suma; 
    }
    else{
        return sumaRecursiva(--n,suma+n);
    }
}

// PARAMETROS: Recibe un entero positivo que sera el limite para la suma (de 1 a n)
// METODO: Aplica la formula de la sumatoria Gaussiana para calcular la sumatoria. n * (n + 1) / 2
// RETURN: Regresa la sumatoria de 1 a n en un unsigned long long int (de 0 a 2^63 -1)
// ORDEN: O(1). Es de orden constante
unsigned long long int sumaDirecta(int n){
    return n * (n + 1) / 2;
}

int main() 
{
    int n=filtraInput();

    // Imprime resultados del metodo iterativo
    std::cout<<"La suma iterativa de 1 a n es de " + std::to_string(sumaIterativa(n)) + "\n";

    // Imprime resultados del metodo recursivo
    std::cout<<"La suma recursiva de 1 a n es de " + std::to_string(sumaRecursiva(n , 0)) + "\n";
    
    // Imprime resultados del metodo matematico directo
    std::cout<<"La suma directa de 1 a n es de " + std::to_string(sumaDirecta(n)) + "\n";

}
