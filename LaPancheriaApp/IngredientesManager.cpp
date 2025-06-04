#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "ArchivoIngrediente.h"
#include <iostream>
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
    float cantidadStock, costoUnitario;
    bool estado = true;
    bool validacion;
    Ingrediente ing;
    ArchivoIngrediente archi;

    idIngrediente=cantidadRegistros(); //autonumerico

    cout << "Ingrese el nombre del nuevo ingrediente: ";
    //proximamente va el cin.ignore() porque estara dentro de un menu.
    getline(cin,nombreIngrediente);

    validacion = false;
    while (!validacion){
        cout << "Ingrese el stock inicial del ingrediente: ";
        cin >> cantidadStock;

        if(cantidadStock<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true;
        }
    }
    validacion=false;
    while (!validacion){
        cout << "Ingrese el costo unitario: $";
        cin >> costoUnitario;
        if(costoUnitario<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true;
        }
    }
    cout << "Especifique el tipo de unidad (unidades, gramos, kgs, litros): ";
    cin.ignore();
    getline(cin,tipoDeUnidad); //validar luego

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

void IngredientesManager::listarIngredientes(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int cantRegistros = cantidadRegistros();

    for (int i=0; i<cantRegistros; i++){
        ing = archi.leer(i);
        ing.mostrar();
        cout << endl << endl;
    }

}




