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

    tipoDeUnidad = pedirTipoDeUnidad(cantidadStock); //devuelve un string, tipo de unidad al valor mas chico (si coloca kgs lo convierte a gramos, lo mismo con litros y mililitros)

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







