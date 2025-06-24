#include "PersonaManager.h"
#include "Cliente.h"
#include "Empleado.h"
#include "ArchivoCliente.h"
#include "ArchivoEmpleado.h"
#include "Utilidades.h"
#include "Validador.h"
#include <iostream>
#include <iomanip>
using namespace std;

///metodos para Empleado
int PersonaManager::cantidadRegistrosEmpleado(){
    ArchivoEmpleado a;

    return a.getCantidadRegistros();
}

void PersonaManager::cargarEmpleado(){
    ArchivoEmpleado a;
    Validador validador;
    Empleado e;

    int idEmpleado, permiso, opcion;
    string nombre, apellido, dni, contrasenia, puesto, email, nCelular;
    float sueldo;
    Fecha fechaIngreso, fechaNacimiento;
    bool estado=true;
    idEmpleado = a.getCantidadRegistros()+1;

    cout << "Ingrese el nombre del empleado a registrar: \n";
    cin.ignore();
    getline(cin,nombre);
    while(!validador.esTexto(nombre)){
        cout << "Nombre Invalido." << endl;
        limpiarPantalla();
        cout << "Ingrese el nombre del empleado: \n";
        getline(cin,nombre);
    }
    system("cls");

    cout << "Ingrese apellido del empleado: \n";
    getline(cin,apellido);
    while(!validador.esTexto(apellido)){
        cout << "Apellido Invalido." << endl;
        limpiarPantalla();
        cout << "Ingrese el apellido del empleado: \n";
        getline(cin,apellido);
    }
    system("cls");

    cout << "Ingrese dni del empleado: \n";
    getline(cin,dni);
    while (!validador.esDni(dni)){
        cout << "DNI Invalido." << endl;
        limpiarPantalla();
        cout << "Ingrese dni del empleado: \n";
        getline(cin,dni);
    }
    system("cls");

    cout << "Ingrese contraseña del empleado: \n";
    getline(cin,contrasenia);
    system("cls");

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
    system("cls");

    cout << "Puesto del empleado: \n";
    cout<< "Opcion: \n 1-Cocinero \n 2-Ayudante cocina \n 3-Bachero \n 4-Vendedor \n 5-Cajero \n 6-Encargado \n 7-Delivery \n 8-Mantenimiento" <<endl;
    cout << "Ingrese una opcion"<<endl;
    cin>>opcion;
    cin.ignore();
    while(cin.fail() || opcion < 1 || opcion > 8){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese una opcion valida! \n";
        limpiarPantalla();
        cout << "Puesto del empleado: \n";
        cout<< "Opcion: \n 1-Cocinero \n 2-Ayudante cocina \n 3-Bachero \n 4-Vendedor \n 5-Cajero \n 6-Encargado \n 7-Delivery \n 8-Mantenimiento" <<endl;
        cout << "Ingrese una opcion"<<endl;
        cin >> opcion;
    }
    switch(opcion){
            case 1:
                puesto= "Cocinero";
                break;
            case 2:
                puesto= "Ayudante cocina";
                break;
            case 3:
                puesto= "Bachero";
                break;
            case 4:
                puesto= "Vendedor";
                break;
            case 5:
                puesto= "Cajero";
                break;
            case 6:
                puesto= "Encargado";
                break;
            case 7:
                puesto= "Delivery";
                break;
            case 8:
                puesto= "Mantenimiento";
                break;
    }
    system("cls");


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
    system("cls");

    cout << "FECHA DE INGRESO:  \n";
    while(!fechaIngreso.cargar()){
        cout << "Fecha invalida!" << endl;
        limpiarPantalla();
    }

    cout << "FECHA DE NACIMIENTO:  \n";
    while(!fechaNacimiento.cargar()){
        cout << "Fecha invalida!" << endl;
        limpiarPantalla();
    }

    cout << "Ingrese email: \n";
    cin.ignore();
    getline(cin,email);
    while (!validador.esEmail(email)){
        cout << "Email Invalido." << endl;
        limpiarPantalla();
        cout << "Ingrese el email del empleado: \n";
        getline(cin,email);
    }
    system("cls");

    cout << "Ingrese celular: \n";
    getline(cin,nCelular);
    while (!validador.esNumero(nCelular)){
        cout << "Celular Invalido." << endl;
        limpiarPantalla();
        cout << "Ingrese el celular del empleado: \n";
        getline(cin,nCelular);
    }
    system("cls");

    e= Empleado(nombre, apellido, dni,idEmpleado,contrasenia,permiso,puesto,sueldo,fechaIngreso,fechaNacimiento,estado,email,nCelular);
    opcion = pedirYValidarConfirmacion();
    if (opcion == 1){
        if(a.buscar(e.getDni()) < 0){
           a.guardar(e);
           cout << "Registro guardado correctamente." << endl;
        }else{
            cout << a.buscar(e.getDni()) << endl << endl;
            cout << "Error al guardar el registro, el dni ya se encuentra registrado." << endl;
        }
    }
    else{
        cout << "Saliendo sin guardar..." << endl << endl;
    }
}

void PersonaManager::listarEmpleados(){
    ArchivoEmpleado a;
    Empleado e;
    bool hayActivos=false;
    int cantRegistros = cantidadRegistrosEmpleado();
    e.mostrarEnTabla();

    if(cantRegistros>0){
        for (int i=0; i<cantRegistros; i++){
            e = a.leer(i);
            if(e.getEstado()){
                cout << left << setw(15) << e.getIdEmpleado();
                cout << setw(30) << e.getNombre();
                cout << setw(30) << e.getApellido();
                cout << setw(30) << e.getPuesto();
                cout << fixed << setprecision(2);
                cout << setw(30) << e.getSueldo() << endl;
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
    int cantRegistros = cantidadRegistrosEmpleado();

    e.mostrarEnTabla();
    if(cantRegistros>0){
        for (int i=0; i<cantRegistros; i++){
            e = a.leer(i);
            if(!e.getEstado()){
                cout << left << setw(15) << e.getIdEmpleado();
                cout << setw(30) << e.getNombre();
                cout << setw(30) << e.getApellido();
                cout << setw(30) << e.getPuesto();
                cout << fixed << setprecision(2);
                cout << setw(30) << e.getSueldo() << endl;
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

void PersonaManager::altaEmpleado(){
    ArchivoEmpleado archivo;
    Empleado empleado;
    bool modifico;

    int id, cantidadRegistros,pos;
    cantidadRegistros = cantidadRegistrosEmpleado();
    listarEmpleadosDeBaja();
    cout << "\n\n\n----------------ACTIVAR EMPLEADO------------------" <<endl;
    cout << "Ingrese el ID del empleado activar" << endl << endl;
    cin >> id;
        while(cin.fail() || id < 0 || id > cantidadRegistros){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarEmpleados();
            cout << "\n\n\n---------------MODIFICAR EMPLEADO------------------" <<endl;
            cout << "Ingrese el ID del empleado a modificar " << endl;
            cin >> id;
        }
    for(int i=0; i<cantidadRegistros;i++){
        empleado=archivo.leer(i);
        if(empleado.getIdEmpleado()==id && !empleado.getEstado()){

            empleado.setEstado(true);
            pos=i;
            modifico=archivo.modificarEmpleado(empleado,pos);
        }
    }
    if(modifico){
        cout<< "El empleado  de ID: " << id <<" se reactivo."<<endl;
    }else{
        cout << "El empleado no pudo ser dado de alta." <<endl;
    }
}

void PersonaManager::eliminarEmpleado(){
    ArchivoEmpleado archivo;
    Empleado empleado;
    bool modifico;

    int id, cantidadRegistros,pos;
    cantidadRegistros = cantidadRegistrosEmpleado();
    listarEmpleados();
    cout << "\n\n\n----------------ELIMINAR EMPLEADO------------------" <<endl;
    cout << "Ingrese el ID del empleado activar" << endl << endl;
    cin >> id;
    while(cin.fail() || id < 0 || id > cantidadRegistros){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese una opcion valida! \n";
        limpiarPantalla();
        listarEmpleados();
        cout << "\n\n\n---------------MODIFICAR EMPLEADO------------------" <<endl;
        cout << "Ingrese el ID del empleado a modificar " << endl;
        cin >> id;
    }
    for(int i=0; i<cantidadRegistros;i++){
        empleado=archivo.leer(i);
        if(empleado.getIdEmpleado()==id && empleado.getEstado()){

            empleado.setEstado(false);
            pos=i;
            modifico=archivo.modificarEmpleado(empleado,pos);
        }
    }
    if(modifico){
        cout<< "El empleado  de ID: " << id <<" fue dado de baja."<<endl;
    }else{
        cout << "El empleado no pudo ser dado de baja." <<endl;
    }
}


void PersonaManager::modificarEmpleados(){

    Empleado empleado;
    ArchivoEmpleado archivo;
    Validador validador;

    int opcion, opcionP, idEmpleado, permiso, cantidadRegistros, pos;
    float sueldo;
    string nombre, apellido,dni,contrasenia,email,nCelular, puesto;
    bool modifico=false, permanecer=true, seEncontro=false;
    cantidadRegistros = cantidadRegistrosEmpleado();

        listarEmpleados();
        cout << "\n\n\n---------------MODIFICAR EMPLEADO------------------" <<endl;
        cout << "Ingrese el ID del empleado a modificar " << endl;
        cin >> idEmpleado;
        while(cin.fail() || idEmpleado < 0 || idEmpleado > cantidadRegistros){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarEmpleados();
            cout << "\n\n\n---------------MODIFICAR EMPLEADO------------------" <<endl;
            cout << "Ingrese el ID del empleado a modificar " << endl;
            cin >> idEmpleado;
        }
        system("cls");

        for(int i=0; i<cantidadRegistros;i++){
            empleado=archivo.leer(i);

            if(empleado.getIdEmpleado()==idEmpleado){

                pos=i;
                seEncontro=true;

                while(permanecer){

                    cout<< "Opcion a modificar: \n 1- Nombre \n 2- Apellido \n 3- DNI \n 4- Contrasenia \n 5- Permiso \n 6- Puesto \n 7- E-mail \n 8- Celular \n 9- Sueldo \n 0- Salir " <<endl;
                    cout << " Ingrese una opcion"<<endl;
                    cin>>opcion;

                    while(cin.fail()){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Ingrese una opcion valida! \n";
                        limpiarPantalla();
                        cout<< "Opcion a modificar: \n 1- Nombre \n 2- Apellido \n 3- DNI \n 4- Contrasenia \n 5- Permiso \n 6- Puesto \n 7- E-mail \n 8- Celular \n 9- Sueldo \n 0- Salir " <<endl;
                        cout << " Ingrese una opcion"<<endl;
                        cin>>opcion;
                    }
                    system("cls");

                    switch(opcion){
                        case 1:
                            cout << "Ingrese nuevo nombre del empleado a registrar: \n";
                            cin.ignore();
                            getline(cin,nombre);
                            while(!validador.esTexto(nombre)){
                                cout << "Nombre Invalido." << endl;
                                limpiarPantalla();
                                cout << "Ingrese el nombre del empleado: \n";
                                getline(cin,nombre);
                            }
                            empleado.setNombre(nombre);
                            limpiarPantalla();
                            modifico=true;
                            break;
                        case 2:
                            cout << "Ingrese nuevo apellido del empleado: \n";
                            cin.ignore();
                            getline(cin,apellido);
                            while(!validador.esTexto(apellido)){
                                cout << "Apellido Invalido." << endl;
                                limpiarPantalla();
                                cout << "Ingrese el apellido del empleado: \n";
                                getline(cin,apellido);
                            }
                            empleado.setApellido(apellido);
                            limpiarPantalla();
                            modifico=true;
                            break;
                        case 3:
                            cout << "Ingrese dni del empleado: \n";
                            cin.ignore();
                            getline(cin,dni);
                            while (!validador.esDni(dni)){
                                cout << "DNI Invalido." << endl;
                                limpiarPantalla();
                                cout << "Ingrese dni del empleado: \n";
                                getline(cin,dni);
                            }
                            empleado.setDni(dni);
                            limpiarPantalla();
                            modifico=true;
                            break;
                        case 4:
                            cout << "Ingrese nueva contrasenia: " << endl;
                            cin.ignore();
                            getline(cin,contrasenia);
                            empleado.setContrasenia(contrasenia);
                            limpiarPantalla();
                            modifico=true;
                            break;
                        case 5:
                            cout << "Ingrese permiso: 1-Admin o 2- User: \n";
                            cin >> permiso;
                            while(cin.fail() || permiso!=1 && permiso!=2){
                                cin.clear();
                                cout << "Ingrese una opcion valida! \n";
                                limpiarPantalla();
                                cout << "Ingrese permiso: 1- Admin o 2- User: \n";
                                cin >> permiso;
                            }
                            modifico=true;
                            empleado.setPermiso(permiso);
                            limpiarPantalla();
                            break;
                         case 6:
                            cout << "Nuevo puesto del empleado: \n";
                            cout<< "Opcion: \n 1-Cocinero \n 2-Ayudante cocina \n 3-Bachero \n 4-Vendedor \n 5-Cajero \n 6-Encargado \n 7-Delivery \n 8-Mantenimiento" <<endl;
                            cout << "Ingrese una opcion"<<endl;
                            cin>>opcionP;
                            while(cin.fail() || opcionP < 1 || opcionP > 8){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                cout << "Ingrese una opcion valida! \n";
                                limpiarPantalla();
                                cout << "Nuevo puesto del empleado: \n";
                                cout<< "Opcion: \n 1-Cocinero \n 2-Ayudante cocina \n 3-Bachero \n 4-Vendedor \n 5-Cajero \n 6-Encargado \n 7-Delivery \n 8-Mantenimiento" <<endl;
                                cout << "Ingrese una opcion"<<endl;
                                cin >> opcionP;
                            }
                            switch(opcionP){
                                    case 1:
                                        puesto= "Cocinero";
                                        break;
                                    case 2:
                                        puesto= "Ayudante cocina";
                                        break;
                                    case 3:
                                        puesto= "Bachero";
                                        break;
                                    case 4:
                                        puesto= "Vendedor";
                                        break;
                                    case 5:
                                        puesto= "Cajero";
                                        break;
                                    case 6:
                                        puesto= "Encargado";
                                        break;
                                    case 7:
                                        puesto= "Delivery";
                                        break;
                                    case 8:
                                        puesto= "Mantenimiento";
                                        break;
                                    }
                            modifico=true;
                            empleado.setPuesto(puesto);
                            system("cls");
                            break;
                        case 7:
                            cout << "Ingrese nuevo email: \n";
                            cin.ignore();
                            getline(cin,email);
                            while (!validador.esEmail(email)){
                                cout << "Email Invalido." << endl;
                                limpiarPantalla();
                                cout << "Ingrese el email del empleado: \n";
                                getline(cin,email);
                            }
                            empleado.setEmail(email);
                            limpiarPantalla();
                            modifico=true;
                            break;
                        case 8:
                            cout << "Ingrese nuevo celular: \n";
                            cin.ignore();
                            getline(cin,nCelular);
                            while (!validador.esNumero(nCelular)){
                                cout << "Celular Invalido." << endl;
                                limpiarPantalla();
                                cout << "Ingrese nuevo celular del empleado: \n";
                                getline(cin,nCelular);
                            }
                            empleado.setNCelular(nCelular);
                            modifico=true;
                            system("cls");
                            break;
                        case 9:
                            cout << "Ingrese nuevo sueldo del empleado: \n";
                            cin >> sueldo;
                            while(cin.fail() || sueldo<=0){
                                cin.clear();
                                cin.ignore();
                                cout << "Ingrese una opcion valida! \n";
                                limpiarPantalla();
                                cout << "Ingrese nuevo sueldo del empleado: \n";
                                cin >> sueldo;
                            }
                            empleado.setSueldo(sueldo);
                            modifico=true;
                            system("cls");
                            break;
                        case 0:
                            opcion = pedirYValidarConfirmacion("\nDesea guardar antes de salir? \n1)Si  0)No \n");
                            if(opcion==1){
                                if(modifico){
                                    if(archivo.modificarEmpleado(empleado,pos)){
                                        cout<<"Registro modificado correctamente"<<endl;
                                    }
                                    else{
                                        cout << "No se pudo modificar el registro."<< endl;
                                    }
                                }else{
                                    cout << "No se han guardado cambios." << endl;
                                }
                                permanecer=false;
                                cout << "Saliendo del programa...\n";
                                break;
                                limpiarPantalla();
                            }else{
                                cout << "Saliendo del programa...\n";
                                permanecer=false;
                                break;
                            }
                        default:
                            cout << "Opcion invalida" <<endl;
                            limpiarPantalla();
                        }

                }

            }
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


        if(cin.fail() || pos < 0){
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

/*void PersonaManager::modificarCliente(){
    Empleado usuario;
    Cliente cliente;
    ArchivoEmpleado archiEmpleado;
    ArchivoCliente archivo;


    int opcion,cantidadRegistros, pos;
    string nombre, apellido, dniCliente;
    bool modifico, permanecer=true, seEncontro=false;
    pos=archiEmpleado.buscar(dniUsuario);
    usuario=archiEmpleado.leer(pos);

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

}*/



