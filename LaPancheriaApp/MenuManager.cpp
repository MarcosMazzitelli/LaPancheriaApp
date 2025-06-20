#include "MenuManager.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Utilidades.h"
#include "PersonaManager.h"
#include "IngredientesManager.h"
#include "ProductosManager.h"
#include "ManagerVenta.h"
#include "FormaDePago.h"
#include "CostosManager.h"

#include <iostream>
using namespace std;

void MenuManager::login(){
    string dni, contrasenia;
    bool validacion=false;
    int cantidadIntentos=0;
    int pos;
    Empleado emp;
    ArchivoEmpleado archiEmp;

    cout << "========================================================" << endl;
    cout << "        MENU INICIO DE SESION" << endl;
    cout << "========================================================" << endl << "\n";

    cout << "Ingrese su DNI: ";
    cin >> dni;

    cout << "Ingrese su contrasenia: ";
    cin >> contrasenia;

    while (!validacion && cantidadIntentos<3){

        pos = verificarCoincidencia(dni,contrasenia);
          if(pos == -1) {
            cantidadIntentos++;
            cout << "Credenciales invalidas." << endl <<"Intento "<<cantidadIntentos<<" de 3" << endl << endl;
            if(cantidadIntentos<3){
                cout << "Ingrese su nombre de DNI: ";
                cin >> dni;

                cout << "Ingrese su contrasenia: ";
                cin >> contrasenia;
            }
        }
        else{
            //buscamos y traemos a memoria un empleado
            emp = archiEmp.leer(pos);
            validacion=true;
            if(emp.getPermiso() == 1){
                menuAdmin(dni);
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
        cout << "5. Gestion de ventas" << endl;
        cout << "6. Reportes" << endl;


        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
            cout << "Entrada invalida. Por favor, ingrese un numero valido" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }

        switch(opcion) {
            case 1:
                system("cls");
                menuEmpleados(dni);
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
                menuVentas(dni);
                //manager cargar venta
                system("pause");
                break;
            case 6:
                system("cls");
                menuReportes();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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

void MenuManager::menuVentas(std::string dni){

    FormaDePago fdp;
    ManagerVenta ventaManager;
    int opcion, opcionSalida;
    while(true){
        system("cls");
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE VENTAS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Cargar venta" << endl;
        cout << "2. Listar ventas" << endl;
        cout << "3. Formas de pago" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
            cout << "Entrada invalida. Por favor, ingrese un numero valido" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }

        switch(opcion) {
            case 1:
                system("cls");
                ventaManager.registrarVenta(dni);
                //manager cargar venta
                system("pause");
                break;
            case 2:
                system("cls");
                ventaManager.listarVenta();
                system("pause");
                break;
            case 3:
                system("cls");
                fdp.opcionesFormasDePago();
                system("pause");
                break;
            case 505:
                system("cls");
                for (int i=0; i<10; i++){
                    ventaManager.cargaMasivaVentas(dni);
                }
                system("pause");

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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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


void MenuManager::menuEmpleados(std::string dni){
    PersonaManager persona;
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE EMPLEADOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo empleado" << endl;
        cout << "2. Modificar datos de un empleado " << endl;
        cout << "3. Eliminar empleado" << endl;
        cout << "4. Mostrar empleados" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
                persona.modificarEmpleados();
                system("pause");
                break;
            case 3:
                system("cls");
                persona.eliminarEmpleado();
                system("pause");
                break;
            case 4:
                system("cls");
                persona.listarEmpleados();
                persona.listarEmpleadosDeBaja();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
        cout << "6. Listar productos por ingrediente" << endl;


        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
        switch(opcion) {
            case 1:
                system("cls");
                prodManager.crearProducto();
                //manager crear producto
                system("pause");
                break;
            case 2:
                system("cls");
                prodManager.modificarProducto();
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "Ingrese categoria 1 2 o 3" << endl;
                int idCategoria;
                cin >> idCategoria;
                prodManager.listarProductosPorCategoria(idCategoria);
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
            case 6:
                system("cls");
                prodManager.listarProductosPorIngredientes();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
        cout << "5. Comprar ingrediente" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
                ingManager.modificarStock();
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar ingrediente
                system("pause");
                break;
            case 4:
                system("cls");
                ingManager.listarIngredientes();
                system("pause");
                break;
            case 5:
                system("cls");
                ingManager.comprarIngrediente();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
    CostosManager costoManager;
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE COSTOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Cargar costo fijo" << endl;
        cout << "2. Modificar costo fijo " << endl;
        cout << "3. Eliminar costo fijo" << endl;
        cout << "4. Listar costos fijos por mes" << endl;
        cout << "5. Listar costos totales por mes" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue; //saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
        switch(opcion) {
            case 1:
                system("cls");
                costoManager.cargarCostosFijos();
                system("pause");
                break;
            case 2:
                system("cls");
                costoManager.modificarCostoFijo();
                system("pause");
                break;
            case 3:
                system("cls");
                costoManager.eliminarCostoFijo();
                system("pause");
                break;
            case 4:
                system("cls");
                costoManager.listarCostosFijosPorFecha();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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

void MenuManager::menuReportes(){
    ManagerVenta vManager;
    PersonaManager personaManager;
    int opcion, opcionSalida;
    while(true){
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE REPORTES" << endl;
        cout << "========================================================" << endl;
        cout << "1. Listar ventas por fecha" << endl;
        cout << "2. Listar todos los clientes " << endl;
        /*cout << "3. Eliminar empleado" << endl;
        cout << "4. Mostrar empleados" << endl;*/

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";

        cin >> opcion;
        if (cin.fail()) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la l�nea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            continue;//saltea el switch y hace que vuelva a mostrar el menu y pedir opcion
        }
switch(opcion) {
            case 1:
                system("cls");
                vManager.listarVentaFecha();
                system("pause");
                break;
            case 2:
                system("cls");
               // vManager.listarVendedorMayorRecaudacion();
                personaManager.listarClientes();
                system("pause");
                break;
            case 3:
                system("cls");
                //manager eliminar empleado
                system("pause");
                break;
            case 4:
                system("cls");
                //persona.listarEmpleados();
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
                    cin.ignore(1000, '\n'); // descarta el resto de la l�nea
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
