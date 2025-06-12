#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "ArchivoIngrediente.h"
#include "Utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

int IngredientesManager::cantidadRegistros(){
    ArchivoIngrediente archi;
    int cant;

    cant=archi.getCantidadRegistros();
    return cant;
}

void IngredientesManager::cargarIngrediente(){
    int idIngrediente;
    string nombreIngrediente, tipoDeUnidad;
    float cantidadStock, costoUnitario, costoTotal;
    bool estado = true;
    Ingrediente ing;
    ArchivoIngrediente archi;

    idIngrediente=cantidadRegistros(); //autonumerico

    cout << "Ingrese el nombre del nuevo ingrediente: ";
    //proximamente va el cin.ignore() porque estara dentro de un menu.
    cin.ignore();
    getline(cin,nombreIngrediente);

    cout << "Ingrese el stock inicial del ingrediente: ";
    cin >> cantidadStock;
    while(cin.fail() || cantidadStock < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese el stock inicial del ingrediente: ";
        cin >> cantidadStock;
    }

    tipoDeUnidad = seleccionarYConvertirUnidad(cantidadStock); //devuelve un string, tipo de unidad al valor mas chico y en caso de que haga falta, actualiza la cantidad de stock ya que se envia por referencia
//                                                    (si coloca kgs lo convierte a gramos, lo mismo con litros y mililitros)
    cout << "Ingrese el costo del ingrediente: $";
    cin >> costoTotal;
    while(cin.fail() || costoTotal < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese el costo del ingrediente: $";
        cin >> costoTotal;
    }
    costoUnitario = costoTotal / cantidadStock;
    cout << endl << "Costo unitario: $ " << costoUnitario << endl;
    ing = Ingrediente(idIngrediente,nombreIngrediente,cantidadStock, costoUnitario, tipoDeUnidad,estado);

    if (archi.guardar(ing)){
        cout << "Registro guardado correctamente." << endl << endl;
    }
    else{
        cout << "Hubo un problema al guardar el registro." << endl << endl;
    }

}

void IngredientesManager::modificarIngrediente(){ ///sin realizar todavia
}

void IngredientesManager::mostrarIngredientesCompletos(){
    ArchivoIngrediente archi;
    Ingrediente ing;
    int cantRegistros = cantidadRegistros();

    for (int i=0; i<cantRegistros; i++){
        ing = archi.leer(i);
        ing.mostrar();
        cout << endl << endl;
    }
}

void IngredientesManager::listarIngredientes(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int cantRegistros = cantidadRegistros();
    cout << left << setw(20) << "ID Ingrediente";
    cout << setw(30) << "Nombre del ingrediente";
    cout << setw(20) << "Costo unitario";
    cout << "Cantidad en stock";
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres

    for (int i=0; i<cantRegistros; i++){
        ing = archi.leer(i);
        ing.mostrarEnLista();
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
}



void IngredientesManager::comprarIngrediente(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    float costoTotal, costoUnitario, cantidad;
    string tipoDeUnidad;
    /*    int _idIngrediente;
    char _nombreIngrediente[30];
    float _cantidadStock;
    float _costoUnitario;
    char _tipoDeUnidad[20];
    bool _estado;
*/
    listarIngredientes();

    cout << endl << "Ingrese el ID del ingrediente comprado: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes();
        cout << endl << "Ingrese el ID del ingrediente comprado: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);
    ing = archi.leer(pos);
    cout << "Ingrese la cantidad comprada: ";
    cin >> cantidad;
    while(cin.fail() || cantidad < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese la cantidad comprada: ";
        cin >> cantidad;
    }

    seleccionarYConvertirUnidad(cantidad, ing.getTipoDeUnidad() );

    cout << "Ingrese el costo total de la compra: $";
    cin >> costoTotal;
    while(cin.fail() || costoTotal < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese el costo total de la compra: $";
        cin >> costoTotal;
    }
    costoUnitario = costoTotal / cantidad;

    cout << endl << "El costo unitario actual es: $" << costoUnitario << endl;
    cout << "Costo unitario anterior: $" << ing.getCostoUnitario() << endl;
    cout << "Desea actualizar el costo unitario del ingrediente?" << endl << "1) Si" << endl << "0) No" << endl << endl;
    cin >> opcion;
    while(cin.fail() || opcion!= 1 && opcion!= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << endl << "El costo unitario actual es: $" << costoUnitario << endl;
        cout << "Costo unitario anterior: $" << ing.getCostoUnitario() << endl;
        cout << "Desea actualizar el costo unitario del ingrediente?" << endl << "1) Si" << endl << "0) No" << endl;
        cin >> opcion;
    }

    if (opcion == 1){
        ing.setCostoUnitario(costoUnitario);
        cout << "Se ha actualizado el costo unitario del ingrediente." << endl;
    }
    else{
        cout << "No se ha actualizado el costo unitario del ingrediente." << endl;
    }

    opcion = pedirYValidarConfirmacion("\n\nConfirma la compra? \n1) Si \n0) No\n\n");
    if(opcion == 1){
        ing.aniadirStock(cantidad);
        if(archi.modificar(ing, pos) ){
            cout << "Registro modificado correctamente." << endl;
        }
    }
    else{
        cout << "No se ha efectuado la compra..." << endl << endl;
    }

}

void IngredientesManager::modificarStock(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    float stockReal;


    listarIngredientes();

    cout << endl << "Ingrese el ID del ingrediente a modificar stock: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes();
        cout << endl << "Ingrese el ID del ingrediente a modificar stock: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);
    ing = archi.leer(pos);

    cout << "Ingrese el stock real del ingrediente en " << ing.getTipoDeUnidad() << ": ";
    cin >> stockReal;
        while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes();
        cout << "Ingrese el stock real del ingrediente: ";
        cin >> stockReal;
    }

    opcion = pedirYValidarConfirmacion();

    if(opcion == 1){
        ing.setCantidadStock(stockReal);
        if (archi.modificar(ing, pos)){
            cout << "Stock actualizado..." << endl << endl;
        }
        else{
            cout << "No se ha podido guardar el registro." << endl;
        }
    }
    else{
        cout << "No se han realizado modificaciones..." << endl << endl;
    }


}








