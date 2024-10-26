/*

Este código maneja un archivo txt que contiene registros de errores de acceso. En cada registro se tiene el mes, el día, y la hora en la sucedió el error.
A partir de este documento, el código los almacena en un vector y los acomoda en orden descendiente. Además, muestra las fechas ordenadas que se encuentran en un rango especificado por el usuario. Se crean nuevos txt, de los cuales uno tiene la bitácora ordenada ascendentemente, otro la filtrada en orden ascendente, y uno último la filtrada en orden descendente. 

Cristian Ricardo Luque Arámbula A01741850

Última modificación: 23/09/2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <map>

static std::map <int, std::string> itom{ 
    {1, "Jan"}, {2, "Feb"}, {3, "Mar"}, {4, "Apr"}, {5, "May"}, {6, "Jun"}, {7, "Jul"}, 
    {8, "Aug"}, {9, "Sep"}, {10, "Oct"}, {11, "Nov"}, {12, "Dec"} 
};

static std::map <std::string, int> mtoi{
    {"Jan",1}, {"Feb",2}, {"Mar",3}, {"Apr",4}, {"May",5}, {"Jun",6}, {"Jul",7}, {"Aug",8}, 
    {"Sep",9}, {"Oct",10}, {"Nov",11}, {"Dec",12}
};

/*
> PARAMETROS: Dos strings de formato "Oct 9 10:32:24 423.2.230.77:6166 Failed password for illegal user guest" o formato "Oct 9 00:00:00" (para la fecha de inicio del filtro) y "Oct 9 99:99:99" (para la fecha de fin del filtro) 
> METODO: Esta sobrecarga del operador > traduce el mes de los strings a sus equivalentes numéricos. Luego compara numéricamente (a>b) los meses, días, horas, minutos y segundos. 
> ORDEN: O(n).
> RETURN: Regresa un entero. 0 si (a < b) y 1 si (a > b). Si (a > b) y el mes y el dia coinciden en ambos strings a y b, en vez de regresar 1, regresa 2.
*/

int operator > (std::string a, std::string b){
    
    int mesA= mtoi[a.substr(0,3)], mesB=mtoi[b.substr(0,3)];
    if (mesA != mesB){
        return mesA > mesB;
    }

    int hourPositionA =a.find_first_of(" ",5), hourPositionB=b.find_first_of(" ", 5);

    int diaA = std::stoi(a.substr(4,hourPositionA)), diaB = std::stoi(b.substr(4,hourPositionB));

    if(diaA != diaB){
        return diaA > diaB;
    };

    if (strcmp(a.substr(hourPositionA).c_str(),b.substr(hourPositionB).c_str()) > 0){
        return 2;
    }

    return 0;
}

/*
> PARAMETROS: Vector de strings v y el tamaño del vector n
> METODO: Esta función es recursiva donde se divide el vector en 2 partes iguales, formando un arbol binario hasta llegar a un vector de tamaño 1. Posteriormente se compara cada elemento de las 2 partes inferiores del arbol binario y se ordenan de menor a mayor en un vector auxiliar.
> ORDEN: O(nlog(n)). n es el tamaño del vector.
> RETURN: No regresa nada. El vector se pasa por referencia y es ordenado desde las respectivas ubicaciones en la memoria de los elementos.
*/
#include "..\Algorithms\sortingAlgorithms\mergeSort.cpp"
void ordenaMerge(std::vector<std::string> &v, int n){
    if (n == 1) return;
    int mitad = n / 2;
    std::vector<std::string> v1, v2;
    for (int i = 0; i < mitad; i++) v1.push_back(v[i]);
    for (int i = mitad; i < n; i++) v2.push_back(v[i]);
    ordenaMerge(v1, mitad);
    ordenaMerge(v2, n - mitad); 
    int i = 0, j = 0, k = 0;
    while (i < mitad && j < n - mitad) {
        if (v1[i] > v2[j]) {
            v[k] = v2[j];
            j++;
        } else {
            v[k] = v1[i];
            i++;
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

/*
> PARAMETROS: Recibe un string que contiene el nombre de un archivo txt.
> METODO: Cada línea de un archivo txt es guardado como un string en un vector por medio de un cíclo.
> ORDEN: O(n). 
> RETURN: Regresa un vector de strings con las líneas del archivo como elementos.
*/

std::vector<std::string> creaVector(std::string fileName){
    std::fstream file;
    file.open(fileName);
    if (!file){
        std::cout<<"The file could not be opened";
    }

    std::vector<std::string> vec;
    std::string temp;

    while(std::getline(file,temp)){
        vec.push_back(temp);
    }
    return vec;
}


/*
> PARAMETROS: Vector de strings ordenados vec, el tamaño del vector n y el string que se busca.
> METODO: Esta función contiene un ciclo for donde se compara el valor de los elementos v[i] con la clave.
> ORDEN: O(log(n)).
> RETURN: Regresa la posición del string (en el vector vec) cuyo mes y día son equivalentes al de la clave. 
*/

int busquedaBinaria(const std::vector<std::string>& vec, std::string clave){
    int inicio=0, final=vec.size(), ultimaInstancia=0;
    
    while (inicio <= final){
        int mitad = inicio+(final-inicio)/2;
        int comparacion = vec[mitad]>clave;

        if (comparacion == 2){
            ultimaInstancia=mitad;
        }
        if (comparacion){
            final = mitad-1;
        } else{
            inicio = mitad+1;
        }
    }
    return ultimaInstancia;
}

/*
> PARAMETROS: Dos strings. Uno que solicita un entero y otro que se imprime especificando el rango del entero requerido si no se recibe un entero.
> METODO: Un cíclo que imprime el mensaje de solicitud del entero y, en caso de no recibir un entero, imprime el mensaje de error, se repite hasta que se en la entrada tenga un entero.
> ORDEN: Depende de la cantidad de interacciones del usuario. 
> RETURN: Regresa un entero ingresado por el usuario. 
*/

int recibeUnEntero(std::string textoSolicitud, std::string textoError){
    int entero=0;
    while(std::cout<<textoSolicitud && !(std::cin >>entero)){
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout<<textoError<<std::endl;
    }

    std::cin.ignore(1000,'\n');
    return entero;
}

int main()
{
    std::vector<std::string> vec=creaVector("bitacora.txt"); 

    ordenaMerge(vec,vec.size());

    // Inicializa el rango de fechas de las entradas que se mostrarán en el documento filtrado.
    int mesInicio=1, diaInicio=0, mesFinal=12, diaFinal=31;

    do{
        std::cout<<"Ingresa las fechas que desea filtrar (fecha de inicio)\n";
        mesInicio=recibeUnEntero("-Mes (entre 1 y 12): ","Ingrese un numero entero entre 1 y 12");
        diaInicio=recibeUnEntero("-Dia: (entre 1 y 31): ","Ingrese un numero entero entre 0 y 31");
   
    } while ((mesInicio < 1 || mesInicio > 12 || diaInicio < 1 || diaInicio > 31) && std::cout<<"Ingrese una fecha valida\n\n");

    do{
        std::cout<<"Ingresa las fechas que desea filtrar (fecha de fin)\n";
        mesFinal=recibeUnEntero("-Mes (entre 1 y 12): ","Ingrese un numero entero entre 1 y 12");
        diaFinal=recibeUnEntero("-Dia: (entre 1 y 31): ","Ingrese un numero entero entre 0 y 31");
        
    } while ((mesFinal < 1 || mesFinal > 12 || diaFinal < 1 || diaFinal > 31) && std::cout<<"Ingrese una fecha valida\n\n");

    // Crea un string para la fecha de inicio y la fecha de fin con el mismo formato que las entradas en la bitacora, pero asegurando que siempre será mayor al último día y menor o igual al primero
    std::string clave=itom[mesInicio]+ " " + std::to_string(diaInicio)+ " " + "00:00:00";
    std::string fechaFinal=itom[mesFinal]+ " " + std::to_string(diaFinal)+ " " + "99:99:99";    

    // Inicializa la posición en la que se encuentra la primera entrada en el vector cuyos mes y día coinciden con la fecha inicial establecida
    int posicionInicial=busquedaBinaria(vec,clave);
    
    std::string stringFiltrado, stringFiltradoDescend, stringOrdenado, temp;

    // Crea un string con las entradas en las fechas entre las fechas específicadas. Hace un string igual pero en orden descendentes.
    for(int i = 0; i < posicionInicial;i++){    
        stringOrdenado+=vec[i]+"\n";
    }

    for(int i = posicionInicial; fechaFinal > vec[i] && i < vec.size();i++){    
        stringOrdenado+=vec[i]+"\n";
        stringFiltrado+=vec[i]+"\n";
        temp=vec[i]+"\n";
        stringFiltradoDescend=temp+stringFiltradoDescend;
    }

    std::cout<<stringFiltradoDescend;

    std::ofstream bitacoraFiltrada("bitacoraF.txt"), bitacoraFiltradaDescend("bitacoraFDescend.txt"),bitacoraOrdenada("bitacoraO.txt");

    bitacoraOrdenada<<stringOrdenado;
    bitacoraOrdenada.close();

    bitacoraFiltrada<<stringFiltrado;
    bitacoraFiltrada.close();

    bitacoraFiltradaDescend<<stringFiltradoDescend;
    bitacoraFiltradaDescend.close();
}
