#include "PersonaManager.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoCliente.h"
#include "ArchivoEmpleado.h"
#include <iostream>
using namespace std;

int PersonaManager::cantidadRegistros(){
    ArchivoEmpleado a;

    return a.getCantidadRegistros();
}

void PersonaManager::cargarEmpleado(){
    ArchivoEmpleado a;

    int idEmpleado, permiso, dia, mes, anio;
    string nombre, apellido, dni, contrasenia, puesto, email, nCelular;
    float sueldo;
    Fecha fechaIngreso, fechaNacimiento;
    bool estado;
    idEmpleado= a.getCantidadRegistros();
    estado=true;

    Empleado e;

    cout << "\n Ingrese el nombre del empleado a registrar: ";
    cin.ignore();
    getline(cin,nombre);

    cout << "\n Ingrese apellido del empleado: ";
    getline(cin,apellido);

    cout << "\n Ingrese dni del empleado: ";
    getline(cin,dni);

    cout << "\n Ingrese contraseña del empleado: ";
    getline(cin,contrasenia);

    cout << "\n Ingrese permiso: 1-Admin o 2- User: ";
    cin >> permiso;

    cout << "\n Ingrese puesto del empleado: ";
    cin.ignore();
    getline(cin,puesto);

    cout << "\n Ingrese sueldo del empleado: ";
    cin >> sueldo;

    cout<< "\n Ingrese dia de ingreso del empleado: ";
    cin >> dia;

    cout<< "\n Ingrese mes de ingreso del empleado: ";
    cin >> mes;

    cout<< "\n Ingrese año de ingreso del empleado: ";
    cin >> anio;

    fechaIngreso.setFecha(dia,mes,anio);

    cout<< "\n Ingrese dia de nacimiento del empleado: ";
    cin >> dia;

    cout<< "\n Ingrese mes de nacimiento del empleado: ";
    cin >> mes;

    cout<< "\n Ingrese año de nacimiento del empleado: ";
    cin >> anio;

    cout << "\n Ingrese email: ";
    cin.ignore();
    getline(cin,email);

    cout << "\n Ingrese celular: ";
    getline(cin,nCelular);

    fechaNacimiento.setFecha(dia,mes,anio);


    e= Empleado(nombre, apellido, dni,idEmpleado,contrasenia,permiso,puesto,sueldo,fechaIngreso,fechaNacimiento,estado,email,nCelular);

    if (a.guardar(e)){
        cout << "Registro guardado correctamente." << endl;
    }
    else{
        cout << "Error al guardar el registro." << endl;
    }


}

void PersonaManager::listarEmpleados(){
    ArchivoEmpleado a;
    Empleado e;

    int cantRegistros = cantidadRegistros();
    cout << "---------Lista de empleados---------" << endl;

    for (int i=0; i<cantRegistros; i++){
        e = a.leer(i);
        e.mostrar();
        cout << endl << endl;
    }
}




