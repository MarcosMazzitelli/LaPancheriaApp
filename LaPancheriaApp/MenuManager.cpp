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
                menuVentasRestringido(dni);
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
        while (cin.fail() || opcion < 0 || opcion > 6) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero valido" << endl;
            system("pause");
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

        while (cin.fail() || opcion < 0 || opcion > 505) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero valido" << endl;
            system("pause");
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
                for (int i=0; i<12; i++){
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
        }
    }
}
void MenuManager::menuVentasRestringido(std::string dni){
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
        system("cls");
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE EMPLEADOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo empleado" << endl;
        cout << "2. Modificar datos de un empleado " << endl;
        cout << "3. Baja de empleado" << endl;
        cout << "4. Mostrar empleados activos" << endl;
        cout << "5. Mostrar empleados inactivos" << endl;
        cout << "6. Alta a empleado existente" << endl;

        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        while (cin.fail() || opcion < 0 || opcion > 4) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
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
                system("pause");
                break;
            case 5:
                system("cls");
                persona.listarEmpleadosDeBaja();
                system("pause");
                break;
            case 6:
                system("cls");
                persona.altaEmpleado();
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
        }
    }
}

void MenuManager::menuProductos(){
    int opcion, opcionSalida;
    ProductosManager prodManager;
    while(true){
        system("cls");
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE PRODUCTOS" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo producto" << endl;
        cout << "2. Modificar producto " << endl;
        cout << "3. Eliminar producto" << endl;
        cout << "4. Alta de productos" << endl;
        cout << "5. Listar productos" << endl;
        cout << "6. Listar recetas" << endl;
        cout << "7. Listar productos por ingrediente" << endl;
        cout << "8. Listar productos por categoria" << endl;
        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        while (cin.fail() || opcion < 0 || opcion > 8) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            cout << "========================================================" << endl;
            cout << "        MENU DE GESTION DE PRODUCTOS" << endl;
            cout << "========================================================" << endl;
            cout << "1. Crear nuevo producto" << endl;
            cout << "2. Modificar producto " << endl;
            cout << "3. Eliminar producto" << endl;
            cout << "4. Alta de productos eliminados" << endl;
            cout << "5. Listar productos" << endl;
            cout << "6. Listar recetas" << endl;
            cout << "7. Listar productos por ingrediente" << endl;
            cout << "8. Listar productos por categoria" << endl;
            cout << "0. Salir" << endl;
            cout << "===============================" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion;
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
                prodManager.eliminarProducto();
                system("pause");
                break;
            case 4:
                system("cls");
                prodManager.darAltaProducto();
                system("pause");
                break;

            case 5:
                system("cls");
                prodManager.listarProductos(true);
                system("pause");
                break;
            case 6:
                system("cls");
                prodManager.listarProductosConIngredientes(true);
                system("pause");
                break;
            case 7:
                system("cls");
                prodManager.listarProductosPorIngredientes(); //solo activos
                system("pause");
                break;
            case 8:
                system("cls");
                cout << "Ingrese categoria 1 2 o 3" << endl;
                int idCategoria;
                cin >> idCategoria;
                prodManager.listarProductosPorCategoria(idCategoria); //solo activos
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
        }
    }
}
void MenuManager::menuIngredientes(){
    IngredientesManager ingManager;
    int opcion, opcionSalida;
    while(true){
        system("cls");
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE INGREDIENTES" << endl;
        cout << "========================================================" << endl;
        cout << "1. Crear nuevo ingrediente" << endl;
        cout << "2. Modificar ingrediente " << endl;
        cout << "3. Modificar stock " << endl;
        cout << "4. Eliminar ingrediente" << endl;
        cout << "5. Alta de ingredientes eliminados" << endl;
        cout << "6. Listar ingredientes" << endl;
        cout << "7. Comprar ingrediente" << endl;
        cout << "0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        while (cin.fail() || opcion < 0 || opcion > 7) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            cout << "========================================================" << endl;
            cout << "        MENU DE GESTION DE INGREDIENTES" << endl;
            cout << "========================================================" << endl;
            cout << "1. Crear nuevo ingrediente" << endl;
            cout << "2. Modificar ingrediente " << endl;
            cout << "3. Modificar stock " << endl;
            cout << "4. Eliminar ingrediente" << endl;
            cout << "5. Alta de ingredientes eliminados" << endl;
            cout << "6. Listar ingredientes" << endl;
            cout << "7. Comprar ingrediente" << endl;
            cout << "0. Salir" << endl;
            cout << "===============================" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion;
        }
        switch(opcion) {
            case 1:
                system("cls");
                ingManager.cargarIngrediente();
                system("pause");
                break;
            case 2:
                system("cls");
                ingManager.modificarIngrediente();
                system("pause");
                break;

            case 3:
                system("cls");
                ingManager.modificarStock();
                system("pause");
                break;
            case 4:
                system("cls");
                ingManager.eliminarIngrediente();
                system("pause");
                break;
            case 5:
                system("cls");
                ingManager.darAltaIngrediente();
                system("pause");
                break;

            case 6:
                system("cls");
                ingManager.listarIngredientes(true);
                system("pause");
                break;
            case 7:
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
        }
    }
}

void MenuManager::menuCostos(){
    CostosManager costoManager;
    int opcion, opcionSalida;
    while(true){
        system("cls");
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

        while (cin.fail() || opcion < 0 || opcion > 5) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
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
        }
    }
}

void MenuManager::menuReportes(){
    ManagerVenta vManager;
    PersonaManager personaManager;
    CostosManager costoManager;
    ProductosManager prodManager;
    int opcion, opcionSalida;
    while(true){
        system("cls");
        cout << "========================================================" << endl;
        cout << "        MENU DE GESTION DE REPORTES" << endl;
        cout << "========================================================" << endl;
        cout << " VENTAS:" << endl << endl;
        cout << " 1. Listar ventas por fecha" << endl;
        cout << " 2. Mostrar fecha de la venta que mas recaudo" << endl;
        cout << " 3. Mostrar fecha que hubo mayor cantidad de ventas" << endl;
        cout << " 9. La mayor recaudacion por periodo" << endl;
        cout << " 10.La mayor cantidad de ventas por periodo" << endl;
        cout << endl;
        cout << " CLIENTES:" << endl << endl;
        cout << " 4. Listar todos los clientes " << endl;
        cout << endl;
        cout << " EMPLEADO:" << endl << endl;
        cout << " 5. Empleado que mas recaudo por fecha" << endl;
        cout << endl;
        cout << " PRODUCTOS:" << endl << endl;
        cout << " 6. Listar cantidad de productos vendidos por fecha" << endl <<endl;
        cout << endl;
        cout << " COSTOS:" << endl << endl;
        cout << " 7. Balance por mes" << endl;
        cout << " 8. Balance por fecha" << endl;
        cout << endl;
        cout << " 0. Salir" << endl;
        cout << "===============================" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        while (cin.fail() || opcion < 0 || opcion > 10) {
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Entrada invalida. Por favor, ingrese un numero correcto" << endl;
            system("pause");
            system("cls");
            cout << "========================================================" << endl;
            cout << "        MENU DE GESTION DE REPORTES" << endl;
            cout << "========================================================" << endl;
            cout << " VENTAS:" << endl << endl;
            cout << " 1. Listar ventas por fecha" << endl;
            cout << " 2. Mostrar fecha de la venta que mas recaudo (historica)" << endl;
            cout << " 3. Mostrar fecha que hubo mayor cantidad de ventas" << endl;
            cout << " 9. La mayor recaudacion por periodo" << endl;
            cout << " 10.La mayor cantidad de ventas por periodo" << endl;
            cout << endl;
            cout << " CLIENTES:" << endl << endl;
            cout << " 4. Listar todos los clientes " << endl;
            cout << endl;
            cout << " EMPLEADO:" << endl << endl;
            cout << " 5. Empleado que mas recaudo por fecha" << endl;
            cout << endl;
            cout << " PRODUCTOS:" << endl << endl;
            cout << " 6. Listar cantidad de productos vendidos por fecha" << endl <<endl;
            cout << " 7. Balance por mes" << endl;
            cout << " 8. Balance por fecha" << endl;
            cout << endl;
            cout << " 0. Salir" << endl;
            cout << "===============================" << endl;
            cout << "Ingrese una opcion: ";
            cin >> opcion;
        }

        switch(opcion) {
            case 1:
                system("cls");
                vManager.listarVentaFecha();
                system("pause");
                break;
            case 2:
                system("cls");
                vManager.mostrarFechaMayorRecaudacionVenta();
                system("pause");
                break;
            case 3:
                system("cls");
                vManager.mostrarFechaMayorCantidadVentas();
                system("pause");
                break;
            case 4:
                system("cls");
                personaManager.listarClientes();
                system("pause");
                break;
            case 5:
                system("cls");
                vManager.listarVendedorMayorRecaudacion();
                system("pause");
                break;
            case 6:
                system("cls");
                prodManager.cantidadProductosVendidosPorFecha();
                system("pause");
                break;
            case 7:
                system("cls");
                costoManager.balanceGananciaPorMes();
                system("pause");
                break;
            case 9:
                system("cls");
                vManager.MayorRecaudacionPorPeriodo();
                system("pause");
                break;
            case 10:
                system("cls");
                vManager.MayorRecaudacionPorPeriodo();
            case 8:
                system("cls");
                costoManager.balancePorFecha();
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
        }
    }
}
