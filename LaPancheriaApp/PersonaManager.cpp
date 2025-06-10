#include "PersonaManager.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoCliente.h"
#include "ArchivoEmpleado.h"
#include "Utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

int PersonaManager::cantidadRegistros(){
    ArchivoEmpleado a;

    return a.getCantidadRegistros();
}
///metodos para Empleado
void PersonaManager::cargarEmpleado(){
    ArchivoEmpleado a;

    int idEmpleado, permiso;
    string nombre, apellido, dni, contrasenia, puesto, email, nCelular;
    float sueldo;
    Fecha fechaIngreso, fechaNacimiento;
    bool estado;
    idEmpleado = a.getCantidadRegistros()+1;
    estado=true;

    Empleado e;

    cout << "Ingrese el nombre del empleado a registrar: \n";
    cin.ignore();
    getline(cin,nombre);
    limpiarPantalla();

    cout << "Ingrese apellido del empleado: \n";
    getline(cin,apellido);
    limpiarPantalla();

    cout << "Ingrese dni del empleado: \n";
    getline(cin,dni);
    limpiarPantalla();

    cout << "Ingrese contraseña del empleado: \n";
    getline(cin,contrasenia);
    limpiarPantalla();

    cout << "Ingrese permiso: 1-Admin o 2- User: \n";
    cin >> permiso;
    while(cin.fail() || permiso!=1 && permiso!=2){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese una opcion valida! \n";
        limpiarPantalla();
        cout << "Ingrese permiso: 1- Admin o 2- User: \n";
        cin >> permiso;
    }
    limpiarPantalla();


    cout << "Ingrese puesto del empleado: \n";
    cin.ignore();
    getline(cin,puesto);
    limpiarPantalla();

    cout << "Ingrese sueldo del empleado: \n";
    cin >> sueldo;
    while(cin.fail() || sueldo<=0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese una opcion valida! \n";
        limpiarPantalla();
        cout << "Ingrese sueldo del empleado: \n";
        cin >> sueldo;
    }
    limpiarPantalla();


    cout << "FECHA DE INGRESO:  \n";
    while(!fechaIngreso.cargar()){
        cout << "Fecha invalida!" << endl;
        limpiarPantalla();
    }
    limpiarPantalla();

    cout << "FECHA DE NACIMIENTO:  \n";
    while(!fechaNacimiento.cargar()){
        cout << "Fecha invalida!" << endl;
        limpiarPantalla();
    }
    limpiarPantalla();

    cout << "Ingrese email: \n";
    cin.ignore();
    getline(cin,email);
    limpiarPantalla();


    cout << "Ingrese celular: \n";
    getline(cin,nCelular);
    limpiarPantalla();

    e= Empleado(nombre, apellido, dni,idEmpleado,contrasenia,permiso,puesto,sueldo,fechaIngreso,fechaNacimiento,estado,email,nCelular);

    if(a.buscar(e.getDni())==-1){
       a.guardar(e);
       cout << "Registro guardado correctamente." << endl;
    }else{
        cout << "Error al guardar el registro, el dni ya se encuentra registrado." << endl;
    }
}

void PersonaManager::listarEmpleados(){
    ArchivoEmpleado a;
    Empleado e;

    e.mostrarEnTabla();

    int cantRegistros = cantidadRegistros();

    for (int i=0; i<cantRegistros; i++){
        e = a.leer(i);
        cout << left << setw(15) << e.getIdEmpleado();
        cout << setw(30) << e.getNombre();
        cout << setw(30) << e.getApellido();
        cout << setw(10) << e.getDni() << endl;
    }
}



/*void PersonaManager::modificarEmpleados(){
    int idEmpleado, cantidadRegistros;
    ArchivoEmpleado a;
    Empleado e;
    //pido el id del empleado que quiero modificar
    cout << "Ingrese el id del empleado a modificar: " <<endl;
    cin >> idEmpleado;

    cantidadRegistros = cantidadRegistros();

    //recorro el archivo comparando el id
    for(int i=0,i < cantidadRegistros;i++){
            e=a.leer(i);
            if(idEmpleado == e.getIdEmpleado()){

            }else{
                cout << "No se hallo el empleado a modificar" <<endl;
            }
    }
    //si hay coincidencias lo traigo
    //pregunto que atributo desea modificar y lo seteo
    //ubico con la pos el puntero en el archivo y seteo todo el objeto

}
void PersonaManager::eliminarEmpleado(){
}
///Metodos para clientes
void PersonaManager::cargarCliente(){
}
void PersonaManager::listarClientes(){
}
void PersonaManager::modificarCliente(){
}
void PersonaManager::eliminarCliente(){
}
*/




