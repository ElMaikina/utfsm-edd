#include <iostream>
#include <stdlib.h>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <cmath>

#include "codes.cpp"
#include "h_discount.cpp"
#include "h_product.cpp"

using namespace std;

int main() {
    fstream productos;
    fstream ofertas;
    fstream compras;


    //Abrimos el archivo de ofertas y generamos un Hash para las ofertas
    ofertas.open("ofertas.dat", ios::in | ios::binary);

    if( !ofertas.is_open() ){
        cout << "Error al abrir ofertas.dat" << endl;
        exit(1);
    }
    int nO; //Entero que guarda el numero de pofertas
    ofertas.read( (char *)&nO, sizeof(int) );
    hashO tablaOfertas(nO); //Creamos nuestra tabla de Hashing para ofertas
    offer auxO; //Una oferta auxiliar para insertar en la tabla

    cout << endl;

    while(nO > 0) {
        ofertas.read( (char*)&auxO, sizeof(offer));
        cout << "Code: " << auxO.code << endl; 
        cout << "Off: " << auxO.off << endl;
        cout << "Discount: " << auxO.discount << endl;
        tablaOfertas.insert(auxO);
        nO--;
        cout << endl;
    }
    ofertas.close();
    cout << endl << endl;





    productos.open("productos.dat", ios::in | ios::binary);

    //Abrimos el archivo de productos y generamos un Hash para los productos
    if( !productos.is_open() ){
        cout << "Error al abrir productos.dat" << endl;
        exit(1);
    }



    ofstream boletas;

    boletas.open("boletas.txt", ios::out);

    //Creamos la boleta para poder meter cuestiones uwu
    if( !boletas.is_open() ){
        cout << "Error al abrir boletas.txt" << endl;
        exit(1);
    }





    int nP; //Entero que guarda el numero de productos
    productos.read( (char *)&nP, sizeof(int) );
    hashP tablaProductos(nP); //Creamos nuestra tabla de Hashing para productos
    product auxP; //Un producto auxiliar para insertar en la tabla

    cout << endl;
    while(nP > 0) {
        productos.read( (char*)&auxP, sizeof(product));
        cout << "Codigo: " << auxP.code << endl; 
        cout << "Nombre: " << auxP.name << endl;
        cout << "Precio: " << auxP.price << endl;
        tablaProductos.insert(auxP);
        nP--;
        cout << endl;
    }

    productos.close();
    cout << endl << endl;



    //Finalmente, abrimos el archivo de Compras
    compras.open("compras.txt", ios::in);
    if( !compras.is_open() ){
        cout << "Error al abrir compras.txt" << endl;
        exit(1);
    }




    int n_clientes, n_compras, codigo_actual, clienteBoleta;
    clienteBoleta = 0;
    compras >> n_clientes;
    cout << "Numero de clientes: " << n_clientes << endl;

    boletas << n_clientes << endl;


    for (int c = 0; c < n_clientes; c++) {
        compras >> n_compras;
        cout << "Numero de compras: " << n_compras << endl;
        for (int Nc = 0; Nc < n_compras; Nc++) {
            compras >> codigo_actual;
            cout << codigo_actual << endl;
            
            tablaProductos.search(codigo_actual);
            tablaOfertas.search(codigo_actual);       
        }
        cout << endl;

        clienteBoleta = tablaProductos.finalPrice() - tablaOfertas.discount();
        cout << clienteBoleta << endl;

        boletas << clienteBoleta << endl;



        clienteBoleta = 0;
        cout << endl;
        
    }

    compras.close();
    boletas.close();
    return 0;
}