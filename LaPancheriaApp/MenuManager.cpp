#include "MenuManager.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Utilidades.h"
#include "PersonaManager.h"
#include "IngredientesManager.h"
#include "ProductosManager.h"
#include "ManagerVenta.h"

#include <iostream>
using namespace std;

void MenuManager::login(){
    string usuario, contrasenia;
    bool validacion=false;
    int cantidadIntentos=0;
    int pos;
    Empleado emp;
    ArchivoEmpleado archiEmp;

    cout << "========================================================" << endl;
    cout << "                      MENU DE GESTION DE COSTOS" << endl;
    cout << "========================================================" << endl << "\n\n\n\n";

    cout << "Ingrese su nombre de usuario: ";
    cin >> usuario;

    cout << "Ingrese su contrasenia: ";
    cin >> contrasenia;

    while (!validacion && cantidadIntentos<3){

        pos = verificarCoincidencia(usuario,contrasenia);
          if(pos == -1) {
            cantidadIntentos++;
            cout << "Credenciales invalidas." << endl <<"Intento "<<cantidadIntentos<<" de 3" << endl << endl;
            if(cantidadIntentos<3){
                cout << "Ingrese su nombre de usuario: ";
                cin >> usuario;

                cout << "Ingrese su contrasenia: ";
                cin >> contrasenia;
            }
        }
        else{
            //buscamos y traemos a memoria un empleado
            emp = archiEmp.leer(pos);
            validacion=true;
            if(emp.getPermiso() == 1){
                menuAdmin(usuario);
            }
            else{
                //menuEmpleado();
                cout <<"Menu empleado sin crear" << endl;
            }
        }
    }
    if (!validacion){
        cout << "Credenciales invalidas." << endl <<"Intento "<<cantidadIntentos<<" de 3" << endl << endl;
        cout << "Se han agotado los intentos." << endl << "Su usuario ha sido bloqueado!\n\n" <<  "El programa finaliza" << endl;
    }
}


void MenuManager::menuAdmin(std::string dni){

    ManagerVenta ventaManager;
    int opcion, opcionSalida;
    while(true){
        system("cls");
        cout << "========================================================" << endl;
        cout << "        SISTEMA DE ADMINISTRACION DE PANCHERIA" << endl;
        cout << "========================================================" << endl;
        cout << "1. Gestion de empleados" << endl;
        cout << "2. Gestion de productos " << endl;
        cout << "3. Gestion de ingredientes" << endl;
        cout << "4. Gestion de costos" << endl;
        cout << "5. Cargar venta" << endl;
        cout << "6. Reportes" << endl;
        cout << "7. Listar ventas" << endl;


        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la línea
            cout << "Entrada invalida. Por favor, ingrese un numero valido" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }

        switch(opcion) {
            case 1:
                system("cls");
                menuEmpleados();
                system("pause");
                break;
            case 2:
                system("cls");
                menuProductos();
                system("pause");
                break;
            case 3:
                system("cls");
                menuIngredientes();
                system("pause");
                break;
            case 4:
                system("cls");
                menuCostos();
                system("pause");
                break;
            case 5:
                system("cls");
                ventaManager.registrarVenta(dni);
                //manager cargar venta
                system("pause");
                break;
            case 6:
                system("cls");
                //menu reportes
                system("pause");
                break;
            case 7:
                system("cls");
                ventaManager.listarVenta();
                system("pause");
                break;


            case 0:
                cout << "Confirma que desea salir? 1- si  0- no\n";
                cin >> opcionSalida;
                while (opcionSalida != 1 && opcionSalida != 0){
                    cout << "Confirma que desea salir? 1- si  0- no\n";
                    cin >> opcionSalida;
                }
                if (opcionSalida == 1){
                    cout << "Saliendo del menu...\n";
                    return; //el while nunca llega a ejecutarse porque el case 0 hace return.
                }
                break;
            default:
                if (cin.fail()) {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(1000, '\n'); // descarta el resto de la línea
                    cout << "Entrada invalida. Por favor, ingrese un numero valido." << endl;
                    system("pause");
                    system("cls");
                    //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
                }
                else{
                    cout << "Opcion invalida. Por favor, ingrese un numero valido." << endl;
                    system("pause");
                }
            }
    }
}

void MenuManager::menuEmpleados(){
    PersonaManager persona;
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE EMPLEADOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo empleado" << endl;
        cout << "2. Modificar datos de un emleado " << endl;
        cout << "3. Eliminar empleado" << endl;
        cout << "4. Mostrar empleados" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la línea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue;//saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
switch(opcion) {
            case 1:
                system("cls");
                persona.cargarEmpleado();
                system("pause");
                break;
            case 2:
                system("cls");
                //manager modificar empleado
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar empleado
                system("pause");
                break;
            case 4:
                system("cls");
                persona.listarEmpleados();
                system("pause");
                break;
            case 0:
                cout << "Confirma que desea salir? 1- si  0- no\n";
                cin >> opcionSalida;
                while (opcionSalida != 1 && opcionSalida != 0){
                    cout << "Confirma que desea salir? 1- si  0- no\n";
                    cin >> opcionSalida;
                }
                if (opcionSalida == 1){
                    cout << "Saliendo del menu...\n";
                    return; //el while nunca llega a ejecutarse porque el case 0 hace return.
                }

                break;
            default:
                if (cin.fail()) {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(1000, '\n'); // descarta el resto de la línea
                    cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
                    system("pause");
                    system("cls");
                }
                else{
                    cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                    system("pause");
                }
        }

    system("cls");

    }
}

void MenuManager::menuProductos(){
    int opcion, opcionSalida;
    ProductosManager prodManager;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE PRODUCTOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo producto" << endl;
        cout << "2. Modificar producto " << endl;
        cout << "3. Eliminar producto" << endl;
        cout << "4. Listar productos" << endl;
        cout << "5. Listar recetas" << endl;


        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la línea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
        switch(opcion) {
            case 1:
                system("cls");
                prodManager.cargarProducto();
                //manager crear producto
                system("pause");
                break;
            case 2:
                system("cls");
                //manager modificar producto
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar productos
                system("pause");
                break;
            case 4:
                system("cls");
                prodManager.listarProductos();
                system("pause");
                break;
            case 5:
                system("cls");
                prodManager.listarProductosConIngredientes();
                system("pause");
                break;

            case 0:
                cout << "Confirma que desea salir? 1- si  0- no\n";
                cin >> opcionSalida;
                while (opcionSalida != 1 && opcionSalida != 0){
                    cout << "Confirma que desea salir? 1- si  0- no\n";
                    cin >> opcionSalida;
                }
                if (opcionSalida == 1){
                    cout << "Saliendo del menu...\n";
                    return; //el while nunca llega a ejecutarse porque el case 0 hace return.
                }

                break;
            default:
                if (cin.fail()) {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(1000, '\n'); // descarta el resto de la línea
                    cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
                    system("pause");
                    system("cls");
                }

                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                system("pause");
        }
        system("cls");
    }
}
void MenuManager::menuIngredientes(){
    IngredientesManager ingManager;
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE INGREDIENTES" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo ingrediente" << endl;
        cout << "2. Modificar stock " << endl;
        cout << "3. Eliminar ingrediente" << endl;
        cout << "4. Listar ingredientes" << endl;


        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la línea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue;  //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
        switch(opcion) {
            case 1:
                system("cls");
                //manager crear ingrediente
                ingManager.cargarIngrediente();
                system("pause");
                break;
            case 2:
                system("cls");
                //manager modificar stock
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar ingrediente
                system("pause");
                break;
            case 4:
                system("cls");
                //manager Listar ingredientes
                ingManager.listarIngredientesl();
                system("pause");
                break;

            case 0:
                cout << "Confirma que desea salir? 1- si  0- no\n";
                cin >> opcionSalida;
                while (opcionSalida != 1 && opcionSalida != 0){
                    cout << "Confirma que desea salir? 1- si  0- no\n";
                    cin >> opcionSalida;
                }
                if (opcionSalida == 1){
                    cout << "Saliendo del menu...\n";
                    return; //el while nunca llega a ejecutarse porque el case 0 hace return.
                }

                break;
            default:
                if (cin.fail()) {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(1000, '\n'); // descarta el resto de la línea
                    cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
                    system("pause");
                    system("cls");
                }

                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                system("pause");
        }
        system("cls");

    }


}

void MenuManager::menuCostos(){
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE COSTOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Cargar costo fijo" << endl;
        cout << "2. Modificar costo fijo " << endl;
        cout << "3. Eliminar costo" << endl;
        cout << "4. Listar costos fijos por mes" << endl;
        cout << "5. Listar costos totales por mes" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la línea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
        switch(opcion) {
            case 1:
                system("cls");
                //manager cargar costo fijo
                system("pause");
                break;
            case 2:
                system("cls");
                //manager modificar costo fijo
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar costo
                system("pause");
                break;
            case 4:
                system("cls");
                //manager Listar costos fijos por mes
                system("pause");
                break;
            case 5:
                system("cls");
                //manager Listar costos totales por mes
                system("pause");
                break;

            case 0:
                cout << "Confirma que desea salir? 1- si  0- no\n";
                cin >> opcionSalida;
                while (opcionSalida != 1 && opcionSalida != 0){
                    cout << "Confirma que desea salir? 1- si  0- no\n";
                    cin >> opcionSalida;
                }
                if (opcionSalida == 1){
                    cout << "Saliendo del menu...\n";
                    return; //el while nunca llega a ejecutarse porque el case 0 hace return.
                }

                break;
            default:
                if (cin.fail()) {
                    cin.clear(); // limpia el estado de error
                    cin.ignore(1000, '\n'); // descarta el resto de la línea
                    cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
                    system("pause");
                    system("cls");
                }

                cout << "Opcion invalida. Por favor, intente de nuevo." << endl;
                system("pause");
        }
        system("cls");
    }
}
