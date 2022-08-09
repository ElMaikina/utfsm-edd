#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>

using namespace std;

struct FlujoNeto {
    int hora;
    int minuto;
    int personas;
}; //Usaremos este para el publico

struct FlujoEmpleados {
    char evento;
    string RUT;
    string hora;
    int flag; //Indicara si el ingreso es repetido
}; //Usaremos este para los empleados

/*
Nombre: horaEsMenor

Resumen: Evalua a traves de los valores ASCII de los caracteres de la hora
para determinar si la horaA es menor a la horaB

Input: horaA y horaB, ambos strings con formato XX:XX si no son de ese formayo
se evaluara incorrectamente pero no habra error

Retorno: Entero que representa un Verdadero u Falso
*/
int horaEsMenor(string horaA, string horaB) {
    //Lee un string de formato 00:00
    if(horaA[0] < horaB[0]){ //Si la decima/ventiava hora es mayor
        return 1;
    }
    if(horaA[0] == horaB[0]){ //Si la decima/ventiava hora es igual
        if(horaA[1] < horaB[1]) {
            return 1;
        }
        if(horaA[1] == horaB[1]) {
            if(horaA[3] < horaB[3]) {
                return 1;
            }
            if(horaA[3] == horaB[3]) {
                if(horaA[4] <= horaB[4]) {
                    return 1;
                }
            }
        }
    }
    return 0;
}//Retorna 1 si la hora A es menor a la B

/*
Nombre: empleadosAux

Resumen: Calcula el numero de empleados a cierta hora dada, pondra en "lista negra"
a traves de un flag a cualquier entrada repetida de un mismo empleado

Input: string hora, string que nos dirá hasta que punto hay que contar los empleados.
struct FlujoEmpleados *E, el arreglo previamente leido de los empleados.
int len, largo del arreglo de empleados

Retorno: Entero que indica cuantos empleados habrá en total
*/
int empleadosAux(string hora, struct FlujoEmpleados *E, int len) {
    int total = 0; //Total de entradas o salidas 
    
    //Flag que nos indica si esta repetido el RUT, algo asi como una lista negra
    for(int k = 0; k<len; k++) {
        for(int j = k+1; j<len; j++) {
            if(E[k].RUT == E[j].RUT && E[k].evento == E[j].evento) {
                E[j].flag = 1;
            }
        }
        if(E[k].flag == 0 && horaEsMenor(E[k].hora, hora) ) {
            if(E[k].evento == 'E') {
                total += 1;
                cout<<"Una E encontrada"<<endl;
            }
            if(E[k].evento == 'S') {
                total -= 1;
                cout<<"Una S encontrada"<<endl;
            }
        }
    }
    cout << endl;
    cout << "Hay un total de " << total << " ingresos validos de empleados!" << endl;
    return total;
}

/*
Nombre: evaluarHora

Resumen: Compara dos horas, una en formato entero hora y entero minuto. y la otra en
formato string de la forma XX:XX, devolvera True si la hora en entero es menor al string
y False en caso de lo contrario

Input: int hora: entero que representa la cantidad de horas. int minuto: entero que
representa la cantidad de minutos. string horaStr: hora en formato string XX:XX

Retorno: Verdadero si la hora entero es menor o igual al string y Falso si no es asi
*/
int evaluarHora(int hora, int minuto, string horaStr){
    int horaAux;
    int minutoAux;
    horaAux = ( (int)horaStr[0] - 48) * 10 + ( (int)horaStr[1] - 48); 
    minutoAux = ( (int)horaStr[3] - 48) * 10 + ( (int)horaStr[4] - 48);
    if(hora < horaAux){
        return 1;
    }
    if(hora == horaAux){
        if(minuto <= minutoAux){
            return 1;
        }
    }
    return 0;
} //Evalua si la hora es menor a la hora string

/*
Nombre: clientesAux

Resumen: Calcula la cantidad de clientes hasta la hora pedida

Input: string hora: string que representa la hora pedida. struct FlujoNeto *N: arreglo
de los ingresos de clientes. int len: largo del arreglo de clientes

Retorno: Devuelve la cantidad de clientes a tal hora
*/
int clientesAux(string hora, struct FlujoNeto *N, int len) {
    int total = 0;
    for(int k = 0; k<len; k++) {
        if(evaluarHora(N[k].hora, N[k].minuto, hora)){
            total += N[k].personas;
        }
    }
    cout << endl;
    cout << "Hay un total de " << total << " ingresos validos de clientes!" << endl;
    return total;
}

/*
Nombre: cantidadPersonas

Resumen: Lee los ingresos de clientes y empleados desde dos archivos distintos, luego
buscará cuantas personas habrá en total hasta la hora pedida

Input: string hora: hora en formato string XX:XX

Retorno: Devolverá un entero con la cantidad de personas en total
*/
int cantidadPersonas(string hora) {
    fstream fileOne;
    fstream fileTwo;

    fileOne.open("asistencia.txt", ios::in);
    if( !fileOne.is_open() ){
        cout << "Error al abrir el archivo asistencia.txt" << endl;
        exit(1);
    }
    
    fileTwo.open("flujo-publico.dat", ios::binary | ios::in);
    if( !fileTwo.is_open() ){
        cout << "Error al abrir el archivo flujo-publico.txt" << endl;
        exit(1);
    }

    int total = 0; //Total de ingresos / salidas
    string horaIn; //Hora que nos entregaran para evaluar

    //Desde aqui nos ocuparemos de manipular el archivo que corresponde a los empleados

    int line = 0;
    char InOut;
    string RUT;
    string time;

    FlujoEmpleados *empleados;
    empleados = new FlujoEmpleados[ (24*60*100) ];
    //El tamaño del arreglo es igual a la cantidad de tiempo en minutos x la cantidad de empleados
    //Suponiendo que puede haber mas de un ingreso o salida por tiempo

    while(fileOne >> InOut >> RUT >> time){
       empleados[line].evento = InOut;
       empleados[line].RUT = RUT;
       empleados[line].hora = time;
       line++;
    }

    cout << "Hay un total de " << line << " ingresos/salidas de empleados" << endl;
    cout << endl;

    for(int i = 0; i<line; i++){
        cout << "Input: " << empleados[i].evento; 
        cout << " Rut: " << empleados[i].RUT; 
        cout << " Hora: " << empleados[i].hora << endl;
    }

    total += empleadosAux(hora, empleados, line);
    cout << endl;
    line = 0;

    //Desde aqui nos ocuparemos de manipular el archivo que corresponde a los clientes

    FlujoNeto *clientes; 
    clientes = new FlujoNeto[ (24*60) ];
    //El tamaño del arreglo es igual a la cantidad de tiempo en minutos

    while( !fileTwo.eof() ) {
        fileTwo.read( (char*)&clientes[line], sizeof(FlujoNeto));
        line++;
    }
    fileTwo.close();

    cout << "Hay un total de " << line << " ingresos de clientes" << endl;
    cout << endl;

    for(int i = 0; i<line; i++){
        cout << "Hora: " << clientes[i].hora; 
        cout << " Minuto: " << clientes[i].minuto; 
        cout << " Personas: " << clientes[i].personas << endl;
    }
    total += clientesAux(hora, clientes, line);
    cout << endl;
    line = 0;

    empleados = NULL;
    clientes = NULL;
    delete[] empleados;
    delete[] clientes;
    fileOne.close();
    fileTwo.close();

    return total;
}
//Retorna un entero con la cantidad de personas en la hora entregada

int main(){
    cout << "Ejecutando el main..."<<endl;
    int retorno;
    string time;
    cout << "Ingrese la hora que desea buscar: "<<endl;
    cin >> time;
    retorno = cantidadPersonas(time);
    cout << "Hay un total de " << retorno << " personas a la hora " << time << endl;
    return 0;
}
