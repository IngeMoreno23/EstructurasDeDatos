#include "Stack.cpp"

#include <iostream>
#include <sstream>
#include <cctype>
#include <string>

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

// Función para evaluar una expresión postfija o polaca inversa
float polacaInversa(const std::string& ecuacion){

    std::stringstream ss(ecuacion); // Inicializo el stringstream con la ecuación
    Stack<float> pila(maxStackCapacity(ecuacion));
    std::string token;

    while (ss>>token){ // Cada cadena ('+'. "4.567", '*') es ingresada a un string token
        std::stringstream tokenStream(token);
        float actNum;
        if(tokenStream>>actNum){ // Se intenta guardar el valor de cada stream individual en un dato float.
            pila.push(actNum);
        } else{
            tokenStream.clear();
            tokenStream.str(token);
            char operation = (tokenStream.str()[0]);
            float b=pila.pop(), a=pila.pop();
            if (operation == '+'){
                pila.push(a+b);
            } else if (operation == '-'){
                pila.push(a-b);
            } else if (operation == '*'){
                pila.push(a*b);
            } else if (operation == '/'){
                pila.push(a/b);
            }
        }
    }
    return pila.peek();
}

int main() {
    std::string ec= "10 5 + 6 3 2 + - * 8 4 / 2 9 5 - * + 7 2 3 * + - +";
    float result=polacaInversa(ec);
    std::cout<<result;

    return 0;
}