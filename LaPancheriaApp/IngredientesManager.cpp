#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "ArchivoIngrediente.h"
#include "Utilidades.h"
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
    cin.ignore();
    getline(cin,nombreIngrediente);

    validacion = false;
    while (!validacion){
        cout << "Ingrese el stock inicial del ingrediente: ";
        cin >> cantidadStock;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> cantidadStock;
        }


        if(cantidadStock<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true;
        }
    }
    tipoDeUnidad = pedirTipoDeUnidad(cantidadStock);

    validacion=false;
    while (!validacion){
        cout << "Ingrese el costo unitario: $";
        cin >> costoUnitario;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> costoUnitario;
        }

        if(costoUnitario<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true;
        }
    }
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

void IngredientesManager::listarIngredientesl(){
    ArchivoIngrediente archi;
    Ingrediente ing;
    /*    cout << "ID Producto    "; //15 caracteres
    cout << "ID Categoria   "; //15 caracteres
    cout << "Nombre del producto           "; //30 caracteres
    cout << "Precio de venta     "; //20 caracteres
    cout << "Costo de preparacion";//20 caracteres
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
    for (int i=0; i<cantRegistros; i++){
        prod = prodArchi.leer(i);
        prod.mostrarEnLista();
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
*/

/**    cout << left << setw(15) << getIdIngrediente();// right lo alinea a la izquierda y setw setea el ancho del campo, lo que sobra lo rellena son espacios hasta completar esa cantidad de caracteres
    cout << left << setw(30) <<getNombreIngrediente();
    if (getTipoDeUnidad()=="Gramos"){
        cout << left << setw(15) << getCantidadStock() << " " << getTipoDeUnidad() << " (" << getCantidadStock()/1000 << " Kilos)" //cantidad en stock
    }
    else if (getTipoDeUnidad() == "Mililitros"){
        cout << left << setw(15) << getCantidadStock() << " " << getTipoDeUnidad() << " (" << getCantidadStock()/1000 << " Litros)"
    }
    else{
        cout << left << setw(15) << getCantidadStock() << " " << getTipoDeUnidad();
    }
    cout << "$ " <<  left << setw(25) << getCostoUnitario();
*/
    int cantRegistros = cantidadRegistros();
    cout << "ID Ingrediente     "; //20 caracteres
    cout << "Nombre del ingrediente        "; //30 caracteres
    cout << "Costo unitario      ";//20 caracteres
    cout << "Cantidad en stock   "; //20 caracteres
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres

    for (int i=0; i<cantRegistros; i++){
        ing = archi.leer(i);
        ing.mostrarEnLista();
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
}







