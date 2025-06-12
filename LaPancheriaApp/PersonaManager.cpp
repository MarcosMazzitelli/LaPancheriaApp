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
    bool hayActivos=false;

    e.mostrarEnTabla();
    int cantRegistros = cantidadRegistrosEmpleado();

    if(cantRegistros>0){
        for (int i=0; i<cantRegistros; i++){
            e = a.leer(i);
            if(e.getEstado()){
                cout << left << setw(15) << e.getIdEmpleado();
                cout << setw(30) << e.getNombre();
                cout << setw(30) << e.getApellido();
                cout << setw(10) << e.getDni() << endl;
                hayActivos=true;
            }
        }
        if(!hayActivos){
            cout << "No se encuentran empleados activos."<<endl;
        }
    }else{
        cout << "No se encuentran empleados registrados" << endl;
    }
}

void PersonaManager::listarEmpleadosDeBaja(){
    ArchivoEmpleado a;
    Empleado e;
    bool hayBajas=false;

    e.mostrarEnTabla();

    int cantRegistros = cantidadRegistrosEmpleado();
    if(cantRegistros>0){

        for (int i=0; i<cantRegistros; i++){
            e = a.leer(i);
            if(!e.getEstado()){
                cout << left << setw(15) << e.getIdEmpleado();
                cout << setw(30) << e.getNombre();
                cout << setw(30) << e.getApellido();
                cout << setw(10) << e.getDni() << endl;
                hayBajas = true;
            }

        }
        if(!hayBajas){
            cout << "No se encuentran empleados dados de baja"<<endl;
        }
    }else{
        cout << "No se encuentran empleados registrados" << endl;
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


void PersonaManager::modificarEmpleados(){

    Empleado empleado;
    ArchivoEmpleado archivo;


    int opcion, idEmpleado, permiso, cantidadRegistros, pos;
    float sueldo;
    string nombre, apellido,dni,contrasenia,email,celular;
    bool modifico, permanecer=true, seEncontro=false;

        listarEmpleados();
        cout << "\n\n\n--------------MODIFICAR EMPLEADO------------------" <<endl;
        cout << "Ingrese el ID del empleado a modificar " << endl;
        cin >> idEmpleado;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarEmpleados();
            cout << "\n\n\n--------------MODIFICAR EMPLEADO------------------" <<endl;
            cout << "Ingrese el ID del empleado a modificar " << endl;
            cin >> idEmpleado;
        }

        cantidadRegistros = cantidadRegistrosEmpleado();

        for(int i=0; i<cantidadRegistros;i++){

            empleado=archivo.leer(i);

            if(empleado.getIdEmpleado()==idEmpleado){

                pos=i;
                seEncontro=true;

                while(permanecer){

                    cout<< "Opcion a modificar: \n 1-Nombre \n 2-Apellido \n 3-DNI \n 4-Contrasenia \n 5-permiso \n 6-E-mail \n 7-Celular \n 8- Sueldo \n 9-Salir " <<endl;
                    cout << " Ingrese una opcion"<<endl;
                    cin>>opcion;

                    while(cin.fail()){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Ingrese una opcion valida! \n";
                        limpiarPantalla();
                        cout<< "Opcion a modificar: \n 1-Nombre \n 2-Apellido \n 3-DNI \n 4-Contrasenia \n 5-permiso \n 6-E-mail \n 7-Celular \n 8- Sueldo \n 9-Salir " <<endl;
                        cout << " Ingrese una opcion"<<endl;
                        cin>>opcion;
                    }


                    switch(opcion){
                        case 1:
                            cout << "Ingrese nuevo nombre: " << endl;
                            cin.ignore();
                            getline(cin,nombre);
                            empleado.setNombre(nombre);
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Ingrese nuevo apellido: " << endl;
                            cin.ignore();
                            getline(cin,apellido);
                            empleado.setApellido(apellido);
                            limpiarPantalla();
                            break;
                        case 3:
                            cout << "Ingrese nuevo dni: " << endl;
                            cin.ignore();
                            getline(cin,dni);
                            empleado.setDni(dni);
                            limpiarPantalla();
                            break;
                        case 4:
                            cout << "Ingrese nueva contrasenia: " << endl;
                            cin.ignore();
                            getline(cin,contrasenia);
                            empleado.setContrasenia(contrasenia);
                            limpiarPantalla();
                            break;
                        case 5:
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
                            break;
                        case 6:
                            cout << "Ingrese nuevo email: " << endl;
                            cin.ignore();
                            getline(cin,email);
                            empleado.setEmail(email);
                            limpiarPantalla();
                            break;
                        case 7:
                            cin.ignore();
                            cout << "Ingrese nuevo celular: " << endl;
                            getline(cin,celular);
                            empleado.setNCelular(celular);
                            limpiarPantalla();
                            break;
                        case 8:
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
                            break;
                            limpiarPantalla();

                        case 9:
                            cout << "Desea salir. Ingrese 1- si o 2- No" << endl;
                            cin>>opcion;
                             while(cin.fail() || opcion!=1 && opcion!=2){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                cout << "Ingrese una opcion valida! \n";
                                limpiarPantalla();
                                cout << "Desea salir. Ingrese 1- si o 2- No" << endl;
                                cin>>opcion;
                            }
                            if(opcion==1){
                                modifico=archivo.modificarEmpleado(empleado,pos);
                                if(modifico){
                                    cout<<"Registro modificado correctamente"<<endl;

                                }else{
                                    cout << "No se pudo modificar el registro."<< endl;

                                }
                                permanecer=false;
                                break;
                                limpiarPantalla();
                            }else{
                                break;
                            }
                        default:
                            cout << "Opcion invalida" <<endl;
                            limpiarPantalla();
                        }

                }

            }
        }
        if(!seEncontro){
            cout<<"No se encontro empleado con ID "<< idEmpleado << endl;
        }
    }





///Metodos para clientes

int PersonaManager::cantidadRegistrosCliente(){
    ArchivoCliente a;

    return a.getCantidadRegistros();
}

void PersonaManager::cargarCliente(std::string &dniCliente){
    int opcion, pos;
    string nombre, apellido;

    ArchivoCliente archivo;
    Cliente cliente;

    cout << "----REGISTRO CLIENTE ----"<<endl;
    opcion = pedirYValidarConfirmacion("Ingrese 1 o 0. \n 1- Ticket personalizado\n 0- Ticket consumidor final \n");
    if(opcion==1){

        cout << "Ingrese dni del cliente: \n";
        cin.ignore();
        getline(cin,dniCliente);
        limpiarPantalla();

       pos = archivo.buscar(dniCliente);


        if(pos < 0){
            cout << "Ingrese el nombre del cliente registrar: \n";
            getline(cin,nombre);
            limpiarPantalla();

            cout << "Ingrese apellido del cliente: \n";
            getline(cin,apellido);

            limpiarPantalla();

            cliente = Cliente(nombre, apellido, dniCliente);
            if(archivo.guardar(cliente)){
            cout <<"El cliente se registro correctamente"<<endl;
            }else{
                cout << "No se pudo guardar el registro" << endl;
            }
        }else{
            cout << "El cliente se encuentra registado. " << endl;
        }
    }else{
        cout << "Cliente como consumidor final"<< endl;
        dniCliente = "0";
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

/*void PersonaManager::modificarCliente(std::string dniUsuario){
    Empleado usuario;
    Cliente cliente;
    ArchivoEmpleado archiEmpleado;
    ArchivoCliente archivo;


    int opcion,cantidadRegistros, pos;
    string nombre, apellido, dniCliente;
    bool modifico, permanecer=true, seEncontro=false;
    pos=archiEmpleado.buscar(dniUsuario);
    usuario=archiEmpleado.leer(pos);

    if(usuario.getPermiso()==1){

        listarClientes();
        cout << "\n\n\n--------------MODIFICAR CLIENTE------------------" <<endl;
        cout << "Ingrese el DNI del cliente a modificar " << endl;
        cin >> dniCliente;

        cantidadRegistros = cantidadRegistrosCliente();

        for(int i=0; i<cantidadRegistros;i++){

            cliente=archivo.leer(i);

            if(cliente.getDni()==dniCliente){
                pos=i;
                seEncontro=true;

                while(permanecer){

                    //cout<< "Opcion a modificar: \n 1-Nombre \n 2-Apellido \n 3-DNI \n 4-Salir " <<endl;
                    cout<< "Opcion a modificar: \n 1-Nombre \n 2-Apellido \n 3-Salir " <<endl;
                    cout << " Ingrese una opcion"<<endl;
                    cin>>opcion;
                    limpiarPantalla();

                    switch(opcion){
                        case 1:
                            cout << "Ingrese nuevo nombre: " << endl;
                            cin.ignore();
                            getline(cin,nombre);
                            cliente.setNombre(nombre);
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Ingrese nuevo apellido: " << endl;
                            cin.ignore();
                            getline(cin,apellido);
                            cliente.setApellido(apellido);
                            limpiarPantalla();
                            break;
                        case 3:
                            cout << "Ingrese nuevo dni: " << endl;
                            cin.ignore();
                            getline(cin,dni);
                            empleado.setDni(dni);
                            limpiarPantalla();
                            break;
                        case 3:
                            cout << "Desea salir. Ingrese 1- si o 2- No" << endl;
                            cin>>opcion;
                            if(opcion==1){
                                modifico=archivo.modificarCliente(cliente,pos);
                                if(modifico){
                                    cout<<"Registro modificado correctamente"<<endl;

                                }else{
                                    cout << "No se pudo modificar el registro."<< endl;

                                }
                                permanecer=false;
                                break;
                                limpiarPantalla();
                            }else{
                                break;
                            }
                        default:
                            cout << "Opcion invalida" <<endl;
                            limpiarPantalla();
                        }

                }


            }
        }
        if(!seEncontro){
            cout<<"No se encontro cliente con DNI "<< dniCliente << endl;
        }
    }else{
        cout << "No cuenta con permiso para realizar cambios en sistema. Comuniquese con el administrador."<<endl;

    }

}


void PersonaManager::modificarCliente(){
}

*/


