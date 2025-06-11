#include "PersonaManager.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoCliente.h"
#include "ArchivoEmpleado.h"
#include "Utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

int PersonaManager::cantidadRegistrosEmpleado(){
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
    // hacer un if para cuando no hayan registros, avise que no hay nada guardado
    int cantRegistros = cantidadRegistrosEmpleado();
    for (int i=0; i<cantRegistros; i++){
        e = a.leer(i);
        if(e.getEstado()){
            cout << left << setw(15) << e.getIdEmpleado();
            cout << setw(30) << e.getNombre();
            cout << setw(30) << e.getApellido();
            cout << setw(10) << e.getDni() << endl;
        }

    }
}

void PersonaManager::eliminarEmpleado(){
    ArchivoEmpleado archivo;
    Empleado empleado;
    bool modifico;

    int id, cantidadRegistros,pos;

    listarEmpleados();
    cout << "\n\n\n----------------ELIMINAR EMPLEADO------------------" <<endl;
    cout << "Ingrese el ID del empleado a eliminar " << endl << endl;
    cin >> id;
    cantidadRegistros = cantidadRegistrosEmpleado();

    for(int i=0; i<cantidadRegistros;i++){
        empleado=archivo.leer(i);
        if(empleado.getIdEmpleado()==id){

            empleado.setEstado(false);
            pos=i;
            modifico=archivo.modificarEmpleado(empleado,pos);
        }
    }
    if(modifico){
        cout<< "El empleado  de ID: " << id <<" fue dado de baja."<<endl;
    }else{
        cout << "El empleado no pudo ser dado de baja. No existente." <<endl;
    }
}

/*void PersonaManager::modificarEmpleados(){
    int idEmpleado, cantidadRegistros, pos;
    ArchivoEmpleado a;
    Empleado e;
    bool validacion;
    //pido el id del empleado que quiero modificar
    cout << "Ingrese el id del empleado a modificar: " <<endl;
    cin >> idEmpleado;

    cantidadRegistros = cantidadRegistrosEmpleado();

    //recorro el archivo comparando el id
    for(int i=0;i < cantidadRegistros;i++){
            e=a.leer(i);
            if(idEmpleado == e.getIdEmpleado()){
                pos=i;

            }else{
                cout << "No se hallo el empleado a modificar" <<endl;
            }
    }


    //si hay coincidencias lo traigo
    //pregunto que atributo desea modificar y lo seteo
    //ubico con la pos el puntero en el archivo y seteo todo el objeto

}*/

///Metodos para clientes

int PersonaManager::cantidadRegistrosCliente(){
    ArchivoCliente a;

    return a.getCantidadRegistros();
}

void PersonaManager::cargarCliente(){
    int opcion, pos;
    string nombre, apellido, dni;

    ArchivoCliente archivo;
    Cliente cliente;

    cout << "----REGISTRO CLIENTE ----"<<endl;
    cout<< "Ingrese 1 o 2. \n 1- Ticket personalizado\n 2- Ticket consumidor final"<<endl;
    cin >> opcion;

    while(cin.fail() || opcion!= 1 && opcion != 2){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese una opcion valida! \n";
        limpiarPantalla();
        cout<< "Ingrese 1 o 2. \n 1- Ticket personalizado\n 2- Ticket consumidor final"<<endl;
        cin >> opcion;
    }
    if(opcion==1){

        cout << "Ingrese dni del cliente: \n";
        cin.ignore();
        getline(cin,dni);
        limpiarPantalla();

       pos = archivo.buscar(dni);


        if(pos < 0){
            cout << "Ingrese el nombre del cliente registrar: \n";
            getline(cin,nombre);
            limpiarPantalla();

            cout << "Ingrese apellido del cliente: \n";
            getline(cin,apellido);

            limpiarPantalla();

            cliente = Cliente(nombre, apellido, dni);
            if(archivo.guardar(cliente)){
            cout <<"El cliente se registro correctamente"<<endl;
            }else{
                cout << "No se pudo guardar el registro" << endl;
            }
            //venta.setDniCliente(dni); ESTO LO TENGO QUE INTEGRAR A LA CLASE DE VENTA
        }else{
            cout << "El cliente se encuentra registado. " << endl;
            //venta.setDniCliente(dni); ESTO LO TENGO QUE INTEGRAR A LA CLASE DE VENTA
        }
    }else{
        //venta.setDniCliente(0); // Consumidor final podria estar registrado con dni 0
        cout << "Cliente como consumidor final"<< endl;
    }
}

void PersonaManager::listarClientes(){
    ArchivoCliente archivo;
    Cliente cliente;

    int cantRegistros = cantidadRegistrosCliente();

    if(cantRegistros>0){
        cliente.mostrarEnTabla();
        for(int i=0; i<cantRegistros;i++){
            cliente = archivo.leer(i);
            cout << left  << setw(30) << cliente.getNombre();
            cout << setw(30) << cliente.getApellido();
            cout << setw(10) << cliente.getDni() << endl;
        }
    }else{
        cout << "No se encontrron registros de clientes."<<endl<<endl;
    }
}

//void PersonaManager::modificarCliente(){
//}
//void PersonaManager::eliminarCliente(){
//}




