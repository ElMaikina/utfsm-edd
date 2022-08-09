#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

//Dejaremos las funciones de hashing como funciones
//Globales, así podremos usarlo en tablas de Hashing 
//distintas

/***** 
Nombre: int H1
Resumen: Toma un valor, lo separa por sus digitos y los
        eleva a cada uno al orden de su decima potencia:
        Ej: 135 -> 1^3 + 3^2 + 5^1 = 1 + 9 + 5 = 15
Input: El entero a transformar y el tamaño del arreglo
    (Hahing) donde se irá a insertar el valor
Output: Un entero que representa la ranura de inserción
*****/
int H1(int code, int size) {
    int mono, result = 0;
    int power = 1;
    int len = 0;
    for (int i = code; i > 0; i = i/10) {
        power *= 10;
        len++;
    }
    while(power > 1) {
        mono = code/(power/10) - code/(power)*10;

        for (int k = 0; k < len; k++) {
            mono = mono * mono;    
        }
        result += mono;
        power /= 10;
        len--;
    }
    return result%size;
}

/***** 
Nombre: int H2
Resumen: Funcion usada para calcular la siguiente ranura
        al haber una colisión. Elegimos usar i, porque
        es la mejor función para rreglos pequeños
Input: El entero a transformar,el tamaño del arreglo
    (Hahing) donde se irá a insertar el valor y la
    i-ésima colisión / iteración
Output: Un entero que representa cuanto se deplaza la ranura
*****/
int H2(int code, int size, int i) {
    return i;
}