#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>

using namespace std;

class arr_extensible{
    private:
        unsigned long nA; //Numero de datos
        unsigned long nB; //Numero de datos
        int *A; //Arreglo A en cuestion
        int *B; //Arreglo B en cuestion
    public:
        arr_extensible(){
            nA = 1; //Largo inicial de A 
            nB = 1; //Largo inicial de B
            A = new int[nA]; //Creacion del arreglo A de tamaño nA
            B = new int[nB]; //Creacion del arreglo B de tamaño nB
        }
        ~arr_extensible() { //Destructor de arr_extensible
            A = NULL;
            B = NULL;
            delete A;
            delete B;
        }
        void init(unsigned long i);
        bool setValue(unsigned long i, int v);
        int getValue(unsigned long i);
        void append(int v);
        void remove();
        void grow(int* A, int* B);
        void shrink();
        unsigned long size();
};
    /***** 
Nombre: void setValue
Resumen: Permite añadir o cambiar el valor v a una posicion del arreglo extensible
Input: recibe la posicion i del arreglo y un numero entero v.
*****/
bool arr_extensible::setValue(unsigned long i, int v){
    if ( i > nA ){
        return false;
    }
    A[i] = v;
    cout<<"Se añadio el valor "<<v<<endl;
    return true;
}

int arr_extensible::getValue(unsigned long i){
    if ( i > nA ){
        return 0;
    }
    cout<<"El valor pedido es "<<A[i]<<endl;
    return A[i];
}
/*****
Retorno: El arreglo con el nuevo valor v en su posicion i.
*****/
    /***** 
Nombre: void grow.
Resumen: Hace crecer el arreglo B y A correspondientemente.
Input: recibe el arreglo A y B.
*****/
void arr_extensible::grow(int* A, int* B){
    while(nA > nB){
        nB = nB*2;
    }
    B = NULL;
    delete B;
    B = new int[nB];
    cout<<"El nuevo largo de B es "<<nB<<endl;
    
    for (long unsigned k = 0; k<nA; k++){
        B[k] = A[k];
    }
    A = NULL;
    delete A;
    A = new int[nA];
    cout<<"El nuevo largo de A es "<<nA<<endl;

    for (unsigned long k = 0; k<nA; k++){
        A[k] = B[k];
    }/*****
Retorno: Es void asi que solo cambia el valor de los punteros/arreglos.
*****/
}
   /***** 
Nombre: void shrink
Resumen: Disminuye el tamaño de los arreglos, evaluando el tamaño de A con B, para asi disminuir el tamaño de B para luego crear un nuevo arreglo A con el tamaño del nuevo arreglo B.
Input: recibe el arreglo A y B.
*****/
void arr_extensible::shrink(){
    if(nA % 2 == 0 && nB % nA == 0){
        nB = nA;
        cout<<"El nuevo largo de B es "<<nB<<endl;
        B = new int[nB];
        for (long unsigned k = 0; k<=nA; k++){
            B[k] = A[k];
        }
    }
    A = new int[nA];
    for (long unsigned k = 0; k<=nA; k++){
        A[k] = B[k];
    }
}/*****
Retorno: Los nuevos arreglos A y B de nuevo tamaño.
*****/
    /***** 
Nombre: void init.
Resumen: Permite inicializar el arreglo A con un valor de i > 1, para luego utilizar la funcion grow.
Input: recibe un unsinged long valor, el cual se pide en el main. 
*****/
void arr_extensible::init(unsigned long i){
    if(i==1){
        exit(1);
    }
    if(i<=0){
        cerr<<"no se puede inicializar un arreglo de ese tamaño"<< endl;
        exit(1);
    }
    if(i>1){
        nA = i;
    }
    grow(A,B);
    for (long unsigned k = 0; k<nA; k++){
        A[k] = 0;
    }
}/*****
Retorno: El arreglo A con tamaño valor y el arreglo B con tamaño valor*2
*****/
/***** 
Nombre: void append.
Resumen: Añade un valor alfinal del arreglo A y luego comparar el nuevo tamaño del arreglo A con el arreglo B a partir de la funcion grow.
Input: Un valor entero v
*****/
void arr_extensible::append(int v){
    nA++;
    cout<<"El valor nuevo de nA es "<<nA<<endl;
    grow(A,B);
    A[nA] = v;
    cout<<"Se añadio el valor "<<v<<endl;
}/*****
Retorno: El nuevo arreglo A, el nuevo arreglo B (En el caso de que el nuevo A sea mayor a B) y el nuevo tamaño del arreglo A con su valor añadido por pantalla.
*****/
/*****
Retorno: El arreglo A con tamaño valor y el arreglo B con tamaño valor*2
*****/

/***** 
Nombre: void remove.
Resumen: Le quita el ultimo valor al arreglo A, para luego ajustar su tamaño mediante la funcion shrink().
Input: Recibe el arreglo A
*****/
void arr_extensible::remove(){
    nA--;
    shrink();
}/*****
Retorno: El arreglo A sin la ultima posicion anterior, y el nuevo valor de B(en caso de que el nuevo valor del tamaño de A sea la mitad del arreglo B)
*****/


/***** 
Nombre: void size.
Resumen: Muestra por pantalla el largo del arreglo A.
Input: Recibe el arreglo A
*****/
unsigned long arr_extensible::size(){
    cout<<"El largo es "<<nA<<endl;
    return nA;
}/*****
Retorno: El tamaño del arreglo A por pantalla y el arreglo A
*****/



int main(){
    unsigned long valor = 5;
    arr_extensible arreglo;
    arreglo.init(valor);
    arreglo.size();

    arreglo.append(4);
    arreglo.append(5);
    arreglo.append(7);
    arreglo.append(13);
    arreglo.append(99);
    arreglo.append(0);
    arreglo.size();

    arreglo.getValue(0);
    arreglo.getValue(1);
    arreglo.getValue(2);
    arreglo.getValue(3);
    arreglo.getValue(4);
    arreglo.getValue(5);
    arreglo.getValue(6);
    arreglo.getValue(7);
    arreglo.size();
  
    return 0;
