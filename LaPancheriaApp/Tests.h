#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
#include "Persona.h"
#include "Cliente.h"
#include <iostream>
using namespace std;

///PRUEBAS
void cargarYMostrarProducto(){
    int idProducto;
    int idCategoria;
    string nombreProducto;
    float precioUnitario;
    float costoProducto;
    bool estado;

    Producto p;
    cout << "Ingrese id producto: ";
    cin >> idProducto;

    cout << "Ingrese id categoria: ";
    cin >> idCategoria;

    cout << "Ingrese nombre producto: ";
    cin >> nombreProducto;

    cout << "Ingrese precio unitario: ";
    cin >> precioUnitario;

    cout << "Ingrese costo producto: ";
    cin >> costoProducto;

    cout << "Ingrese estado: ";
    cin >> estado;


    p= Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoProducto, estado);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

    Venta v;
    v.getFechaVenta().mostrarFecha();

}

void cargarYMostrarPersona(){
    string nombre;
    string apellido;
    string dni;

    Persona p;
    cout << "Ingrese nombre: ";
    cin >> nombre;

    cout << "Ingrese apellido: ";
    cin >> apellido;

    cout << "Ingrese dni: ";
    cin >> dni;

    p= Persona(nombre, apellido, dni);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

}

void cargarYMostrarCliente(){
    string nombre;
    string apellido;
    string dni;

    Cliente p;
    cout << "Ingrese nombre: ";
    cin >> nombre;

    cout << "Ingrese apellido: ";
    cin >> apellido;

    cout << "Ingrese dni: ";
    cin >> dni;

    p= Cliente(nombre, apellido, dni);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

}


#endif // TESTS_H_INCLUDED
