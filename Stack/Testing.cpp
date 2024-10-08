#include "Stack.cpp"
#include "..\Queue\Queue.cpp"

#include <iostream>
#include <sstream>
#include <string>

/*
> Parámetros: Un string constante, paso por referencia. Este string es una ecuación en formato polaco inverso. 
> Método: Guarda el string en un stringstream, que va almacenando cada cadena de caracteres en un string. Este 
  evalua si se puede convertir a un dato de tipo flotante. En caso de poder, se añade uno a la capacidad 
  máxima que requeriría un stack para resolver la ecuación. En caso de no serlo, el caracter se trata de un 
  operador + - / *, por lo que se resta uno a la capacidad máxima. 
> Orden: O(n). n siendo la cantidad de cadenas separadas por un " " en el string.
> Retorno: Un entero. La capacidad máxima de un stack que resolvería la ecuación. 
*/
int maxStackCapacity(const std::string& ecuacion){
    std::stringstream ss(ecuacion); 
    std::string element;
    int capacity=0, maxCapacity=0; 
    while (ss>>element){
        std::stringstream ssElement(element);
        float actNum;
        if(ssElement>>actNum){
            capacity++;
            maxCapacity = (capacity > maxCapacity) ? capacity: maxCapacity;
        } else{
            ssElement.clear();
            capacity--;
        }
    }
    return maxCapacity; 
}

/*
> Parámetros: Un string constante, paso por referencia. Este string es una ecuación en formato polaco inverso, llamado también posfijo. 
> Método: Guarda el string en un stringstream, que va almacenando cada cadena de caracteres en un string. Este 
  evalua si se puede convertir a un dato de tipo flotante. En caso de poderlo, se añade a la pila. En caso de no serlo, el caracter se 
  trata de un operador + - / *, por lo que se extraen los últimos dos valores de la pila y se les aplica la operación correspondiente. 
  El resultado se agrega a la pila. 
> Orden: O(n). n siendo la cantidad de cadenas separadas por un " " en el string.
> Retorno: Un entero. La capacidad máxima de un stack que resolvería la ecuación. 
*/
float polacaInversa(const std::string& ecuacion){

    std::stringstream ss(ecuacion); // Inicializo el stringstream con la ecuación
    Stack<float> pila(maxStackCapacity(ecuacion));
    std::string token;

    while (ss>>token){ // Cada cadena ('+'. "4.567", '*') es ingresada a un string token
        std::stringstream tokenStream(token);
        float actNum;
        if(tokenStream>>actNum){ // Se intenta guardar el valor de cada stream individual en un dato float.
            try{
                pila.push(actNum);
            } catch(stack_overflow ex){
                std::cout<<ex.what();
            }
        } else{
            tokenStream.clear();
            tokenStream.str(token);
            char operation = (tokenStream.str()[0]);
            float a, b; // Se declaran fuera del bloque try catch, para que el siguiente los detecte
            
            try{
                b=pila.pop();
                a=pila.pop();
            } catch(out_of_rangeStack ex){
                std::cout<<ex.what();
            }

            try{
                if (operation == '+'){
                    pila.push(a+b);
                } else if (operation == '-'){
                    pila.push(a-b);
                } else if (operation == '*'){
                    pila.push(a*b);
                } else if (operation == '/'){
                    pila.push(a/b);
                }
            } catch(stack_overflow ex){
                std::cout<<ex.what();
            }
        }
    }
    if(pila.getTop() != 0){
        throw(bad_argument("Insuficiente cantidad de operadores"));
    }
    return pila.peek();
}

int main() {
    // casos de prueba
    std::string caso1= "3 4 + 5 6 + *"; // Ecuación básica, sin paréntesis ni operadores complejos
    std::string caso2= "10 7 3 2 / 5 * 7 2 + -"; // La pila acaba con más de un valor, arroja error. 
    std::string caso3= "10 2 3 4 + * 2 3 + / +"; // Prueba la capacidad de procesar entradas con múltiples niveles (paréntesis).
    std::string caso4= "5 1 2 + 4 * + 3 - 6 * 2 /"; // Ecuación larga con operadores consecutivos del mismo tipo.
    std::string caso5= "3 4 + +"; // Causa error, porque intenta aplicar un operador a un solo número. 
    std::string caso6= "2.6 3.3 * 4.9 5 + * 6 / 7 -"; // Maneja números flotantes.

    try{
        float result=polacaInversa(caso1);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";
    }

    try{
        float result=polacaInversa(caso2);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";
    }

    try{
        float result=polacaInversa(caso3);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";
    }

    try{
        float result=polacaInversa(caso4);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";
    }

    try{
        float result=polacaInversa(caso5);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";        
    }
    
    try{
        float result=polacaInversa(caso6);
        std::cout<<"El resultado es: "<<result<<"\n";
    } catch(bad_argument ex){
        std::cout<<ex.what()<<"\n";
    }

    return 0;
}