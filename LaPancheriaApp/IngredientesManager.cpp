#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "ArchivoIngrediente.h"
#include "ArchivoProducto.h"
#include "ArchivoDetalleIngrediente.h"
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

    idIngrediente=cantidadRegistros()+1; //autonumerico

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
        cout << "Registro guardado con exito." << endl << endl;
    }
    else{
        cout << "Hubo un problema al guardar el ingrediente." << endl << endl;
    }

}

void IngredientesManager::modificarIngrediente(){ ///sin realizar todavia
}

void IngredientesManager::mostrarIngredientesCompletos(bool estado){
    ArchivoIngrediente archi;
    Ingrediente ing;
    int cantRegistros = cantidadRegistros();

    if(estado){
        for (int i=0; i<cantRegistros; i++){
            ing = archi.leer(i);
            if(ing.getEstado()){
                ing.mostrar();
                cout << endl << endl;
            }
        }
    }
    else{
        for (int i=0; i<cantRegistros; i++){
            ing = archi.leer(i);
            if(!ing.getEstado()){
                ing.mostrar();
                cout << endl << endl;
            }
        }

    }
}

void IngredientesManager::listarIngredientes(bool estado){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int cantRegistros = cantidadRegistros();
    cout << left << setw(20) << "ID Ingrediente";
    cout << setw(30) << "Nombre del ingrediente";
    cout << setw(20) << "Costo unitario";
    cout << "Cantidad en stock";
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres

    if(estado){//si mandamos el parametro en true, mostramos los activos
        for (int i=0; i<cantRegistros; i++){
            ing = archi.leer(i);
            if (ing.getEstado()){
                ing.mostrarEnLista();
                cout << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
    }
    else{  //si mandamos el parametro en false, mostramos los inactivos
        for (int i=0; i<cantRegistros; i++){
            ing = archi.leer(i);
            if (!ing.getEstado()){
                ing.mostrarEnLista();
                cout << endl;
            }
        }
        cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres

    }
}



void IngredientesManager::comprarIngrediente(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    float costoTotal, costoUnitario, cantidad;
    string tipoDeUnidad;

    listarIngredientes(true); //solo los activos

    cout << endl << "Ingrese el ID del ingrediente comprado: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes(true); //solo los activos
        cout << endl << "Ingrese el ID del ingrediente comprado: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);
    ing = archi.leer(pos);
    if (ing.getEstado()){
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
                cout << "Ingrediente modificado con exito." << endl;
            }
            else{
                cout << "Hubo un error al modificar el ingrediente." << endl;
            }
        }
        else{
            cout << "No se ha efectuado la compra..." << endl << endl;
        }
    }
    else{
        cout << "El ingrediente seleccionado se encuentra dado de baja!" << endl << endl;
    }
}

void IngredientesManager::modificarStock(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    float stockReal;


    listarIngredientes(true); //solo los activos

    cout << endl << "Ingrese el ID del ingrediente a modificar stock: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes(true); //solo los activos
        cout << endl << "Ingrese el ID del ingrediente a modificar stock: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);
    ing = archi.leer(pos);
    if(ing.getEstado()){

        cout << "Ingrese el stock real del ingrediente en " << ing.getTipoDeUnidad() << ": ";
        cin >> stockReal;
            while(cin.fail() || idIngrediente <= 0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl;
            system("pause");
            system("cls");
            listarIngredientes(true); //solo los activos
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
    else{
        cout << "El ingrediente seleccionado se encuentra dado de baja!" << endl << endl;
    }

}


void IngredientesManager::eliminarIngrediente(){
    ArchivoIngrediente archivoIngrediente;
    ArchivoProducto archivoProducto;
    ArchivoDetalleIngrediente archivoDetalleIngrediente;

    DetalleIngrediente detalleIngrediente;
    Ingrediente ingrediente;
    Producto producto;
    int posicionIng, posicionDetalleIng, idIngrediente, opcion;
    int cantRegistrosDetalleIngrediente = archivoDetalleIngrediente.getCantidadRegistros();

    listarIngredientes(true); //solo los activos
    cout << endl << "Ingrese el ID del ingrediente a eliminar: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes(true); //solo los activos
        cout << endl << "Ingrese el ID del ingrediente a eliminar: ";
        cin >> idIngrediente;
    }
    posicionIng = archivoIngrediente.buscar(idIngrediente);
    ingrediente = archivoIngrediente.leer(posicionIng);
    cout << endl << "Ingrediente seleccionado: " << ingrediente.getNombreIngrediente() << endl << endl;
    if(ingrediente.getEstado()){
        if (ingrediente.getCantidadStock() > 0){
            cout << "Aun tienes " << ingrediente.getCantidadStock() << " " << ingrediente.getTipoDeUnidad() << " en stock" << endl;
            cout << "Si elimina este ingrediente tambien perdera su stock" << endl << endl;
        }

        cout << "Los siguientes productos contienen este ingrediente:" << endl << endl;
        //traerme todas los productos que tengan este ID
        for (int i=0; i < cantRegistrosDetalleIngrediente; i++){
            detalleIngrediente = archivoDetalleIngrediente.leer(i);
            if (detalleIngrediente.getIdIngrediente() == idIngrediente){
                posicionDetalleIng = archivoProducto.buscar(detalleIngrediente.getIdProducto());
                producto = archivoProducto.leer(i);
                cout << producto.getNombreProducto() << endl;
            }
        }
        opcion = pedirYValidarConfirmacion("\nAdemas del ingrediente y su stock, tambien se eliminaran los productos y su receta. \nDesea confirmar? \n1)Si \n0)No \n\n");
        if (opcion == 1){
            ingrediente.setCantidadStock(0);
            ingrediente.setEstado(false);
            if (archivoIngrediente.modificar(ingrediente, posicionIng)){
                cout << "Ingrediente eliminado con exito" << endl;
            }
            else{
                cout << "Hubo un error al dar de baja el ingrediente" << endl;
            }
            for (int i=0; i < cantRegistrosDetalleIngrediente; i++){
                detalleIngrediente = archivoDetalleIngrediente.leer(i);
                if (detalleIngrediente.getIdIngrediente() == idIngrediente){
                    detalleIngrediente.setEstado(false);
                    if (archivoDetalleIngrediente.modificar(detalleIngrediente, i)){
                        cout << "Receta eliminada con exito" << endl;
                    }
                    else{
                        cout << "Hubo un error al dar de baja la receta" << endl;
                    }
                    posicionDetalleIng = archivoProducto.buscar(detalleIngrediente.getIdProducto());
                    producto = archivoProducto.leer(i);

                    if(producto.getEstado()){
                        producto.setEstado(false);
                        if(archivoProducto.modificar(producto, i)){
                            cout << "Producto eliminado con exito" << endl;
                        }
                        else{
                            cout << "Hubo un error al eliminar el producto" << endl;
                        }
                    }

                }
            }
        }
        else{
            cout << "No se ha eliminado el ingrediente" << endl;
            cout << "Saliendo del menu..." << endl;
        }
    }
    else{
        cout << "El ingrediente seleccionado ya se encuentra dado de baja!" << endl << endl;
    }
}









