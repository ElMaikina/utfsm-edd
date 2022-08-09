#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

struct monomio
{
    unsigned int exponente;
    float constante;
    monomio *next;
};
struct polinomio {
    unsigned int lengthM;
    monomio *head;
    monomio *tail;
};
class arrayOfPoly {
    private:
        int lengthN;
        polinomio *array;

    public:
        arrayOfPoly(){
            lengthN = 0;
            array = NULL;
        }
        ~arrayOfPoly() {
            for(unsigned int k = 0; k < lengthN; k++) {
                remove(array[k].head);
            }
            cout << "Se borraron todos los polinomios" << endl;
        }
        /***** 
Nombre: void setLengthN
Resumen: Define el largo a utilizar en el arreglo.
Input: recibe un imput de largo desconocido
*****/
        void setLengthN(unsigned int N){
            lengthN = N;
            array = new polinomio[lengthN];
        }

        //Define el largo del i-esimo polinomio
        void setLengthM(int i, unsigned int M){
            array[i].lengthM = M;
        }
/*****
Retorno: Es void no retorna nada.
*****/

        /***** 
Nombre: void remove
Resumen: Funcion utilizada dentro del destructor de la clase
Input: recibe un imput de tipo struct monomio apuntando a del
*****/
        //Funcion que se usara dentro de el destructor de la clase
        void remove(monomio *del) {
            if (del->next != NULL) {
                remove(del->next);
            }
            cout << "Se borró el monomio " << del->constante;
            cout << "X^" << del->exponente << endl;
            delete del;
        }
/*****
Retorno: Es void no retorna nada.
*****/


        /***** 
Nombre: add_monomio
Resumen: Funcion utilizada para añadir elemento a un polinomio de indice i en orden decendente
Input: recibe un entero i, un numero de largo x entero exp y un numero entero A
*****/
        //Operacion para añadir elementos a 
        //un polinomio de indice i en orden 
        //descendiente
        int add_monomio(int i,unsigned int exp, int A) {
            monomio *tmp = new monomio;
            monomio *current = array[i].head;

            tmp->exponente = exp;
            tmp->constante = A;
            //Si el elemento es el primero en insertarse
            if ( array[i].head == NULL ) {
                array[i].head = array[i].tail = tmp;
                cout << "   Se inserto un elemento al inicio!" << endl;
                return 1;
            }
            //Si el elemento nuevo va despues de la cola
            if (tmp->exponente <= array[i].tail->exponente) {
                array[i].tail->next = tmp;
                array[i].tail = array[i].tail->next;
                cout << "   Se inserto un elemento al final!" << endl;
                return 1;
            }
            //Si el nuevo elemento va antes de la cabeza
            if (tmp->exponente >= array[i].head->exponente) {
                tmp->next = array[i].head;
                array[i].head = tmp;
                cout << "   Se inserto un elemento anterior!" << endl;
                return 1;
            }
            //Si nuestro elemento va antes de la cola y despues de la cabeza
            current = array[i].head;
            while (current != array[i].tail) {
                if (tmp->exponente <= current->exponente
                && tmp->exponente >= current->next->exponente) {
                    tmp->next = current->next;
                    current->next = tmp;
                    cout << "   Se inserto un elemento!" << endl;
                    return 1;
                }
                current = current->next;
            }
            cout << "   No se pudo insertar!" << endl;
            return 0;    
        }
        /*****
Retorno: Un arreglo ordenado de manera que los polinomios dentro de este, sus exponentes poseen orden decendente
*****/



            /***** 
Nombre: void read
Resumen: Funcion utilizada para mostrar por pantalla el polinomio expresado
Input: recibe un entero i
*****/
        //Imprime por pantalla el polinomio expresado
        void read(int i) {
            cout << endl << "Leeremos el polinomio " << i << endl;
            monomio *current = array[i].head;
            for(int k = 0; k<array[i].lengthM; k++) {
                cout << current->constante << "X^"; 
                cout << current->exponente << " + ";
                current = current->next;
            }
            cout << "0" << endl <<endl;
        }
                /*****
Retorno: Es void no retorna nada.
*****/


     /***** 
Nombre: calculate
Resumen: Funcion utilizada para calcular el valor del polinomio en base al algoritmo de Horner
Input: recibe un entero i y un float x
*****/
        //Calcula el valor del polinomio atraves del algoritmo de Horner
        float calculate(int i, float x) {
            float result = 0;
            if (i > lengthN) {
                cout << "Fuera de rango" << endl;
                return 0;
            }            
            monomio *current = array[i].head;

            for (int k = array[i].head->exponente; k >= 0; k--) {
                if (current != NULL && k == current->exponente) {
                    result = result * x; result += current->constante;
                    current = current->next;
                }
                else {
                    result = result * x;
                }
            }
            return result;
        }
/*****
Retorno: Valor a la variable result, mostrando el resultado hasta ahora
*****/  

         /***** 
Nombre: coeficiente
Resumen: Funcion utilizada para buscar el coeficiente del monomio con expontente e del i-esimo polinomio.
Input: recibe un entero i y un float x
*****/
        //busca el coeficiente del monomio con exponente e
        //del i-ésimo polinomio
        int coeficient (int i, unsigned int e) {
            if (i > lengthN) {
                cout << "Fuera de rango" << endl;
                return 0;
            }
            monomio *current;
            for(current = array[i].head; current!=array[i].tail; current = current->next){
                if (current->exponente == e) {return current->constante;}
            }
            return 0;
        }
};

/*****
Retorno: Valor del coeficiente en la posicion actual
*****/  



int main() {

    fstream file;
    file.open("ejemplo.txt", ios::in);
    if( !file.is_open() ){
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }

    arrayOfPoly arrayFinal;
    string operacion;
    int nroPoly;
    float aux; 

    int N;
    unsigned int M, expAux;
    float baseAux;

    file >> N;
    cout << "N es " << N << endl;
    arrayFinal.setLengthN(N);

    for (int i = 0; i < N; i++) {
        file >> M;
        cout << "la M numero " << i << " es " << M << endl;
        arrayFinal.setLengthM(i, M);
        
        for (int k = 0; k < M; k++) {
            file >> expAux >> baseAux;
            cout << "Creamos el nodo " << baseAux << "X^";
            cout << expAux << endl;

            arrayFinal.add_monomio(i, expAux, baseAux);
        }
    }
    cout << "Leimos todos los polinomios!" << endl;

    fstream output;
    output.open("output.txt", ios::out);
    if( !output.is_open() ){
        cout<<"Error al crear el archivo"<<endl;
        exit(1);
    }
    while(!file.eof()) {
        file >> operacion >> nroPoly >> aux;
        if (operacion == "EVALUAR") {
            cout << arrayFinal.calculate(nroPoly, aux) << endl;
            output << arrayFinal.calculate(nroPoly, aux) << endl;
        }
        if (operacion == "COEFICIENTE") {
            cout << arrayFinal.coeficient(nroPoly, (int)aux) << endl;    
            output << arrayFinal.coeficient(nroPoly, (int)aux) << endl;
        }
    }
    cout << endl;
    file.close();
    output.close();
    return 0;
}