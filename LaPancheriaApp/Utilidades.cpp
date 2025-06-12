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

void limpiarPantalla(){
    system("pause");
    system("cls");
}
/*
void menuAdmin(){


int pedirYValidarConfirmacion(std::string mensaje){
    int opcion;
    cout << mensaje;
    cin >> opcion;
    while(cin.fail() || opcion!= 1 && opcion!= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << mensaje << endl;
        cin >> opcion;
    }
    return opcion;
}

std::string seleccionarYConvertirUnidad(float &cantidadStock){
    int opcion;
    int confirmacion;
    string tipoDeUnidad;
    while (true){
        cout << "Especifique el tipo de unidad \n\n" << "1) Unidades \n" << "2) Gramos \n" << "3) Kilos \n" << "4) Litros \n" << "5) Mililitros \n" ;
        cin >> opcion;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> opcion;
        }

        switch (opcion) {
            case 1:
                tipoDeUnidad = "Unidades";

                cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= pedirYValidarConfirmacion();
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }

                break;
            case 2:
                tipoDeUnidad = "Gramos";
                cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= pedirYValidarConfirmacion();
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }
                break;
            case 3:
                tipoDeUnidad = "Kilos";
                cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= pedirYValidarConfirmacion();
                if (confirmacion == 1){
                    cantidadStock = cantidadStock*1000;
                    tipoDeUnidad="Gramos";
                    cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                    return tipoDeUnidad;
                }
                break;
            case 4:
                tipoDeUnidad = "Litros";
                cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= pedirYValidarConfirmacion();
                if (confirmacion == 1){
                    cantidadStock = cantidadStock*1000;
                    tipoDeUnidad="Mililitros";
                    cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                    return tipoDeUnidad;
                }
                break;
            case 5:
                tipoDeUnidad = "Mililitros";
                cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                confirmacion= pedirYValidarConfirmacion();
                if (confirmacion == 1){
                    return tipoDeUnidad;
                }

                break;
            default:
                cout << "Entrada invalida. Por favor, ingresa un numero entre 1 y 5.\n";
                break;
        }
    }
}


std::string seleccionarYConvertirUnidad(float &cantidadStock, std::string tipoDeUnidad){
    int opcion, confirmacion;
    if(tipoDeUnidad == "Gramos"){
            while (true){
            cout << "Especifique el tipo de unidad \n\n" << "1) Gramos \n" << "2) Kilos \n" ;
            cin >> opcion;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Ingrese un valor valido" << endl << endl;
                cin >> opcion;
            }

            switch (opcion) {
                case 1:
                    tipoDeUnidad = "Gramos";
                    cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                    confirmacion= pedirYValidarConfirmacion();
                    if (confirmacion == 1){
                        return tipoDeUnidad;
                    }
                    break;
                case 2:
                    tipoDeUnidad = "Kilos";
                    cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                    confirmacion= pedirYValidarConfirmacion();
                    if (confirmacion == 1){
                        cantidadStock = cantidadStock*1000;
                        tipoDeUnidad="Gramos";
                        cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                        return tipoDeUnidad;
                    }
                    break;
                default:
                    cout << "Entrada invalida. Por favor, ingresa un numero entre 1 y 2.\n";
                    break;
            }
        }
    }
    else if (tipoDeUnidad == "Mililitros"){
        while (true){
            cout << "Especifique el tipo de unidad \n\n" << "1) Litros \n" << "2) Mililitros \n" ;
            cin >> opcion;
            while(cin.fail()){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Ingrese un valor valido" << endl << endl;
                cin >> opcion;
            }

            switch (opcion) {
                case 1:
                    tipoDeUnidad = "Litros";
                    cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                    confirmacion= pedirYValidarConfirmacion();
                    if (confirmacion == 1){
                        cantidadStock = cantidadStock*1000;
                        tipoDeUnidad="Mililitros";
                        cout << "Stock convertido a " << cantidadStock << " " << tipoDeUnidad << endl;
                        return tipoDeUnidad;
                    }
                    break;
                case 2:
                    tipoDeUnidad = "Mililitros";
                    cout << endl << "Ha elegido " << tipoDeUnidad << endl;
                    confirmacion= pedirYValidarConfirmacion();
                    if (confirmacion == 1){
                        return tipoDeUnidad;
                    }

                    break;
                default:
                    cout << "Entrada invalida. Por favor, ingresa un numero entre 1 y 2.\n";
                    break;
            }
        }
    }
}

