#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

//Cambiamos el nombre de las variables al inglés xd
//No es porque nos creamos gringos, pero porque después se hará mas legible
//De todas formas, trataremos de no condensar mucho las lineas

/*
El struct del producto con los parametros definidos por la tarea.
*/
struct product {
    int  code;
    char name[31];
    int  price;
};

/*
Un struct de colas que anotará las acciones realizadas sobre la tabla.
Esto es, con el motivo de poder generar boletas en base a la busqueda
de datos dentro de una tabla.
*/

struct Q_price {
    int slot;
    Q_price *next;
};

class hashP {
    private:
        product *HT; //Tabla de Hashing
        int size, filled, curr, queueSize;
        //size = tamaño total, curr = posicion en la tabla
        //queueSize = tamaño de la cola por operaciones
        Q_price *actions;
        //Cola de acciones realizadas

    public:
        hashP (int n) { // n = Total de datos a insertar
            size = (int)(n*1.42); //Tamaño total de la tabla
            HT = new product[ size ]; //La tabla en sí
            
            filled = 0; //Ranuras utilizadas de la tabla
            curr = 0; //Lo usaremos para insertar
            queueSize = 0; //Numero de busquedas
            actions = NULL;

            for (int i = 0; i<size; i++) {
                HT[i].code = -1;
                //Lo rellenamos con -1
            }
            cout << "Se creó un Hash de tamaño " << size << endl;
        }
        
        ~hashP (){
            delete actions;
            delete[] HT;
        }

        /***** 
        Nombre: int enQueue
        Resumen: Añade a la cola una nueva operacion, lo usaremos para
                guardar las compras por cliente y se guardará el código
                del producto comprado por cada nodo.
        Input: Recibe la ranura del item comprado
        Output: 1 si la insercion es exitosa, -1 de no ser así
        *****/

        int enQueue (int newSlot) {
            if (actions == NULL) {
                actions = new Q_price;
                actions->slot = newSlot;
                actions->next = NULL;
                queueSize++;
                return 1;
            }
            if (actions != NULL)
            {
                Q_price *curr;
                Q_price *insert;
                insert = new Q_price;
                insert->next = NULL;
                insert->slot = newSlot;
                curr = actions;

                for (int k = 0; k < queueSize; k++) {
                    if (curr->next == NULL) {
                        curr->next = insert;
                        queueSize++;
                        return 1;
                    }
                    curr = curr->next;
                }
                
            }
            cout << "No hubo insercion" << endl;
            return -1;
        }
        /***** 
        Nombre: void delete_Q
        Resumen: Se usa para vaciar las operaciones. Esto
                pasará luego de imprimir una boleta por cliente
        Input: Recibe el nodo a borrar
        Output: Como es void no retorna nada
        *****/

        void delete_Q (Q_price *current) {
            if (current->next != NULL) {
                delete_Q (current->next);
            }
            cout << "Se borró un nodo" << endl;
            queueSize--;
            delete current;
        }


        /****************************************************/
        /* Aui comienzan las operaciones dentro de la tabla */
        /****************************************************/


        /***** 
        Nombre: int insert
        Resumen: Funcion que maneja la inserción y colisiones de 
                la tabla de Hashing
        Input: Producto a insertar
        Output: La ranura si la insercion es exitosa, -1 de no ser así
        *****/
        int insert (product P) {
            int flag = 0;
            curr = 0;
            if (filled == size) {
                return -1;
            }
            if (filled < size) {
                //Guardaremos el codigo como clue
                int clue = P.code;
                curr = H1(clue, size);
                int i = 0;
                //Solo están estas condiciones asumiendo
                //Que no habrán repetidos
                while (flag == 0) {
                    //Si la ranura está ocupada
                    if (HT[curr].code != -1) {
                        curr = ( H1(clue, size) + H2(clue,size,i) ) % size;
                        i++; //Ésto deplazara el H2()
                    }
                    //Si la ranura está vacía
                    if (HT[curr].code == -1) {
                        HT[curr] = P;
                        filled++;
                        return curr;
                    }    
                }
            }
            return -1;
        }
        /***** 
        Nombre: int search
        Resumen: Funcion que maneja la búsqueda y colisiones de 
                la tabla de Hashing
        Input: Codigo del producto en cuestión
        Output: La ranura si la insercion es exitosa, -1 de no ser así
        *****/
        int search (int clue) {
            int flag = 0;
            curr = 0;
            if (filled == 0) {
                return -1;
            }
            if (filled > 0) {
                curr = H1(clue,size);
                int i = 0;
                while (flag == 0) {
                    //Si no es la ranura que buscamos
                    if (HT[curr].code != clue) {
                        curr = ( H1(clue,size) + H2(clue,size,i) ) % size;
                        i++; //Ésto deplazara el H2()
                    }
                    //Si la ranura tiene el item que buscamos
                    if (HT[curr].code == clue) {
                        enQueue(curr);
                        return curr;
                    }    
                }
            }
            return -1;
        }
        /***** 
        Nombre: int finalPrice
        Resumen: Funcion que calcula el precio total a traves de la cola 
                de operaciones que creamos (NO CALCULA LOS DESCUENTOS)
        Input: NO recibe ningun tipo de input
        Output: Precio total de la compra de productos.
        *****/
        int finalPrice () {
            if (actions == NULL) {
                return 0;
            }
            Q_price *current;    
            current = actions;
            int result = 0;
            for (int j = 0; j<queueSize; j++) {
                result += HT[current->slot].price;
                cout << "Resultado hasta ahora " << result << endl;
                if (current->next != NULL) {
                    current = current->next;
                }
            }
            delete_Q(actions);
            actions = NULL;
            queueSize = 0;
            cout << "El precio sin descuentos es: " << result << endl;
            return result;
        }
};