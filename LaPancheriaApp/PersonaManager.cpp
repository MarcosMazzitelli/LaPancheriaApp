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

    cout << "Ingrese el nombre del empleado a registrar: ";
    getline(cin,nombre);

    cout << "Ingrese apellido del empleado: ";
    getline(cin,apellido);

    cout << "Ingrese dni del empleado: ";
    cin >> dni;

    cout << "Ingrese contraseña del empleado: ";
    cin >> contrasenia;

    cout << "Ingrese permiso: 1-Admin o 2- User: ";
    cin >> permiso;

    cout << "Ingrese puesto del empleado: ";
    cin >> puesto;

    cout << "Ingrese sueldo del empleado: ";
    cin >> sueldo;

    cout<< "Ingrese dia de ingreso del empleado: ";
    cin >> dia;

    cout<< "Ingrese mes de ingreso del empleado: ";
    cin >> mes;

    cout<< "Ingrese año de ingreso del empleado: ";
    cin >> anio;

    fechaIngreso.setFecha(dia,mes,anio);

    cout<< "Ingrese dia de nacimiento del empleado: ";
    cin >> dia;

    cout<< "Ingrese mes de nacimiento del empleado: ";
    cin >> mes;

    cout<< "Ingrese año de nacimiento del empleado: ";
    cin >> anio;

    cout << "Ingrese email: ";
    cin>>email;

    cout << "Ingrese celular: ";
    cin>>nCelular;

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




