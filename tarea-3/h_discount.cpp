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
El struct del ofertas con los parametros definidos por la tarea.
*/
struct offer {
    int code;
    int off;
    int discount;
    int same[10];
};

/*
Un struct de colas que anotará las acciones realizadas sobre la tabla.
Esto es, con el motivo de poder generar boletas en base a la busqueda
de datos dentro de una tabla.
*/

struct clientOff {
    clientOff *next;
    int slotOg;
    int Qty;
};


class hashO {
    private:
        offer *HT; //Tabla de Hashing
        int size, filled, curr;
        //size = tamaño total, curr = posicion en la tabla
        int *PwD;
        int PwDFilled;
        clientOff *items;
        int ItemVariety;
    public:
        hashO (int n) { // n = Total de datos a insertar
            size = (int)(n*1.42); //Tamaño total de la tabla
            HT = new offer[ size ]; //La tabla en sí
            
            filled = 0; //Ranuras utilizadas de la tabla
            curr = 0; //Lo usaremos para insertar

            initPwD(n);
            PwDFilled = 0;  
            //Arreglo con los codigos de productos con descuentos
            //para insertar elementos en el arreglo
            items = NULL;
            //Lista enlazada que guarda las compras
            ItemVariety = 0;
            //Variedad de items comprados

            for (int i = 0; i<size; i++) {
                HT[i].code = -1;
                //Lo rellenamos con -1
            }
            cout << "Se creó un Hash de tamaño " << size << endl;
        }


        ~hashO (){
            delete [] PwD;
            delete items;
            delete[] HT;
        }

        /***** 
        Nombre: void initPwD
        Resumen: Crea un arreglo donde se almacenan los productos con 
                descuento, así sabremos que productos no buscar en el Hash
        Input: Tamaño del arreglo, osea cuantos productos tienen descuento
        Output: Como es void no devuelve nada
        *****/
        void initPwD (int size) {
            PwD = new int[size];
        }

        /***** 
        Nombre: void insertPwD
        Resumen: Inserta un producto con descuentas
        Input: Codigo del producto en cuestion
        Output: Como es void no devuelve nada
        *****/
        void insertPwD (int code) {
            PwD[PwDFilled] = code;
            PwDFilled++;
        }

        /***** 
        Nombre: void searchPwD
        Resumen: Busca por su codigo, si el producto tiene descuento
        Input: Codigo del producto en cuestion
        Output: Devuelve 1 si existe, 0 si no
        *****/
        int searchPwD (int code) {
            for (int i = 0; i<PwDFilled; i++) {
                if ( PwD[i] == code ) {
                    cout << "El elemento tiene descuento!" << endl;
                    return 1;
                }
            }
            cout << "El elemento no tiene descuento!" << endl;
            return 0;
        }

        /***** 
        Nombre: void buyItem
        Resumen: Añade un elemento a la cola de compras
        Input: Slot del producto en cuestion, de esta manera
                la busqueda es instantanea
        Output: Devuelve 1 si la insercion es exitosa, 0 si no
        *****/
        int buyItem (int NewSlot) {
            if (items == NULL) {
                clientOff *curr;
                curr = new clientOff;
                curr->next = NULL;
                curr->Qty = 1;
                curr->slotOg = NewSlot;

                items = curr;
                ItemVariety = 1;
                cout << "   Se compró un item!" << endl;
                return 1;
            }
            if (items != NULL) {
                clientOff *curr;
                curr = items;
                for (int i = 0; i < ItemVariety; i++) {
                    if ( curr->slotOg == NewSlot ) {
                        curr->Qty++;
                        cout << "   Se compró un item!" << endl;
                        return 1;
                    }
                    if (curr->next == NULL) {
                        curr->next = new clientOff;
                        curr->next->next = NULL;
                        curr->next->Qty = 1;
                        curr->next->slotOg = NewSlot;
                        ItemVariety++;
                        cout << "   Se compró un item!" << endl;
                        return 1;
                    }
                    curr = curr->next;
                }
            }
            return 0;
        }

/*
        void free_shop_list (clientOff *current) {
            if (current->next != NULL) {
                free_shop_list (current->next);
            }
            delete current;
        }
*/



        /****************************************************/
        /* Aqui comienzan las operaciones dentro de la tabla */
        /****************************************************/


        /***** 
        Nombre: int insert
        Resumen: Funcion que maneja la inserción y colisiones de 
                la tabla de Hashing
        Input: Producto a insertar
        Output: La ranura si la insercion es exitosa, -1 de no ser así
        *****/
        int insert (offer P) {
            int flag = 0;
            curr = 0;
            if (filled == size) {
                cout << "Hash lleno, insercion fallida" << endl;
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
                        cout << "Colisión en "<<curr<<", desplazando..." << endl;
                    }
                    //Si la ranura está vacía
                    if (HT[curr].code == -1) {
                        HT[curr] = P;
                        filled++;
                        insertPwD(clue);
                        cout << "Descuento añadido!" << endl;
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
                cout << "Hash vacío, búsqueda fallida" << endl;
                return -1;
            }
            if (filled > 0 && searchPwD(clue) == 1) {
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
                        buyItem(curr);
                        return curr;
                    }    
                }
            }
            return -1;
        }
        /***** 
        Nombre: int finalPrice
        Resumen: Funcion que calcula los descuentos totales por
                la compra de productos de un cliente
        Input: NO recibe ningun tipo de input
        Output: Precio total a descontar de los productos.
        *****/
        int discount () 
        {
            int TotalDiscount = 0;
            if (items != NULL) {
                clientOff *curr;
                curr = items;
                for (int i = 0; i < ItemVariety; i++)
                {
                    clientOff *aux;

                    if (curr->next != NULL) {
                        aux = curr->next;
                        for (int k = 0; k < 10 && HT[curr->slotOg].same[k] != -1; k++)
                        {
                            //Esta parte calcula los descuentos si es que hay productos
                            //equivalentes, los agrega para aplicar al descuento y luego
                            //los resta del otro producto, asi no hay doble descuento
                            if ( HT[curr->slotOg].same[k] == HT[aux->slotOg].code
                                && aux->slotOg != curr->slotOg) 
                            {
                                curr->Qty += aux->Qty;
                                aux->Qty = 0;
                            }
                            if (aux->next != NULL) {aux = aux->next;}
                        }
                    }

                    if ( curr->Qty >= HT[curr->slotOg].off ) 
                    {
                        //Suma al descuento si es que se alcanza la cuota necesaria
                        TotalDiscount += curr->Qty / HT[curr->slotOg].off * HT[curr->slotOg].discount;
                    }
                    curr = curr->next;
                }
            }
            cout << "El descuento total: " << TotalDiscount << endl;
            items = NULL;
            return TotalDiscount;
        }
};
