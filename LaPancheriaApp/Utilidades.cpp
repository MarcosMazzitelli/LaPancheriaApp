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


int validarConfirmacion(std::string mensaje){
    int opcion;
    cout << mensaje;
    cin >> opcion;
    while(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        cin >> opcion;
    }

    while(opcion!= 1 && opcion!= 2){
        cout << "Opcion incorrecta" << endl;
        cout << mensaje;
        cin >> opcion;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> opcion;
        }
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
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> opcion;
        }

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
