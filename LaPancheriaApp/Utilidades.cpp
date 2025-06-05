#include "Utilidades.h"
#include "ArchivoEmpleado.h"
#include "Empleado.h"

#include <iostream>
using namespace std;


int verificarCoincidencia(std::string usuario, std::string contrasenia){
    ArchivoEmpleado archiEmp;
    Empleado emp;
    int cantRegistros = archiEmp.getCantidadRegistros();

    for (int i=0; i<cantRegistros; i++){
        emp = archiEmp.leer(i);
        if(emp.getDni() == usuario && emp.getContrasenia() == contrasenia){
            return i;
        }
    }
    return -1;


}
/*
void menuAdmin(){


    int opcion, opcionSalida;
    do{
    cout << "========================================================" << endl;
    cout << "        SISTEMA DE ADMINISTRACION DE PANCHERIA" << endl;
    cout << "========================================================" << endl;
    cout << "1. Gestion de empleados" << endl;
    cout << "2. Gestion de productos " << endl;
    cout << "3. Gestion de ingredientes" << endl;
    cout << "4. Gestion de costos" << endl;
    cout << "5. Cargar venta" << endl;
    cout << "6. Reportes" << endl;

    cout << "0. Salir" << endl;
    cout << "===============================" << endl;
    cout << "Ingrese una opcion: ";

    cin >> opcion;

    switch(opcion) {
            case 1:
                system("cls");
                //menuEmpleados
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
                //manager cargar venta
                system("pause");
                break;
            case 6:
                system("cls");
                //menu reportes
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
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
                system("pause");
        }

      system("cls");

    } while(opcion != 0);
}

void menuEmpleados(){
    int opcion, opcionSalida;
    do{
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

    switch(opcion) {
            case 1:
                system("cls");
                //manager crear empleado
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
                //manager mostrar empleados
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
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
                system("pause");
        }

      system("cls");

    } while(opcion != 0);
}

void menuProductos(){
    int opcion, opcionSalida;
    do{
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

    switch(opcion) {
            case 1:
                system("cls");
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
                //manager Listar productos
                system("pause");
                break;
            case 5:
                system("cls");
                //manager Listar recetas
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
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
                system("pause");
        }

      system("cls");

    } while(opcion != 0);
}
void menuIngredientes(){
    int opcion, opcionSalida;
    do{
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

    switch(opcion) {
            case 1:
                system("cls");
                //manager crear ingrediente
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
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
                system("pause");
        }

      system("cls");

    } while(opcion != 0);


}

void menuCostos(){
    int opcion, opcionSalida;
    do{
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
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
                system("pause");
        }

      system("cls");

    } while(opcion != 0);

}

 */



int validarConfirmacion(std::string mensaje){
    int opcion;
    cout << mensaje;
    cin >> opcion;
    while(opcion!= 1 && opcion!= 2){
        cout << "Opcion incorrecta" << endl;
        cout << mensaje;
        cin >> opcion;
    }
    return opcion;
}

std::string pedirTipoDeUnidad(float &cantidadStock){
    int opcion;
    int confirmacion;
    string tipoDeUnidad;
    while (true){
        cout << "Especifique el tipo de unidad \n\n" << "1) Unidades \n" << "2) Gramos \n" << "3) Kilos \n" << "4) Litros \n" << "5) Mililitros \n" ;
        cin >> opcion;
        switch (opcion) {
            case 1:
                tipoDeUnidad = "Unidades";

                cout << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= validarConfirmacion("Desea confirmar? \n 1)Si\n 2)No\n");
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }

                break;
            case 2:
                tipoDeUnidad = "Gramos";
                cout << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= validarConfirmacion("Desea confirmar? \n 1)Si\n 2)No\n");
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }
                break;
            case 3:
                tipoDeUnidad = "Kilos";
                cout << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= validarConfirmacion("Desea confirmar? \n 1)Si\n 2)No\n");
                if (confirmacion == 1){
                    cantidadStock = cantidadStock*1000;
                    tipoDeUnidad="Gramos";
                    cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                    return tipoDeUnidad;
                }
                break;
            case 4:
                tipoDeUnidad = "Litros";
                cout << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= validarConfirmacion("Desea confirmar? \n 1)Si\n 2)No\n");
                if (confirmacion == 1){
                    cantidadStock = cantidadStock*1000;
                    tipoDeUnidad="Mililitros";
                    cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                    return tipoDeUnidad;
                }
                break;
            case 5:
                tipoDeUnidad = "Mililitros";
                cout << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= validarConfirmacion("Desea confirmar? \n 1)Si\n 2)No\n");
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }

                break;
            default:
                cout << "Entrada inválida. Por favor, ingresá un número entre 1 y 5.\n";
                break;
        }



    }
}
