#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "ArchivoIngrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include "IngredientesManager.h"

#include <iostream>
using namespace std;

int ProductosManager::cantidadRegistrosProducto(){
    ArchivoProducto archi;
    int cant;

    cant=archi.getCantidadRegistros();
    return cant;
}
int ProductosManager::cantidadRegistrosDetalleIngredientes(){
    ArchivoDetalleIngrediente archi;
    int cant;

    cant=archi.getCantidadRegistros();
    return cant;
}


void ProductosManager::cargarProducto(){
    Producto prod;
    DetalleIngrediente detalleIng;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    ArchivoProducto prodArchi;
    IngredientesManager ingManager;

    int idProducto, idCategoria, idIngrediente;
    string nombreProducto;
    float precioUnitario, costoProducto, costoUnitario, cantidadPorProducto;
    bool estado = true;
    bool validacion;

    idProducto=cantidadRegistrosProducto(); //autonumerico

    validacion=false;
    while (!validacion){
        cout << "Ingrese la categoria del producto: " << endl << "1) Panchos" << endl <<"2) Guarniciones" << endl <<"3) Bebidas" << endl << endl;
        cin >> idCategoria;

        if (idCategoria!= 1 && idCategoria!= 2 && idCategoria!= 3){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true; //fin del while
        }
    } ///todavia no hace nada pero deberia mostrar un menu para separar las bebidas y cargarlas distinto que a los panchos y guarniciones ya que no deberia pedir mas de un ingrediente"

    cout << "Ingrese el nombre del nuevo producto: ";
    //proximamente va el cin.ignore() porque estara dentro de un menu.
    cin.ignore();
    getline(cin,nombreProducto);

    validacion = false;
    while (!validacion){
        cout << "Ingrese el precio unitario de venta del producto: $";
        cin >> precioUnitario;

        if(precioUnitario<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true; //fin del while
        }
    }

    bool cargaIngredientes=false;
    int opcion;
    while (!cargaIngredientes){
        cout << "Seleccione el ingrediente que desee agregar: " << endl << endl;
        ingManager.listarIngredientes();
        cin >> idIngrediente;

        while (idIngrediente < 0 || idIngrediente > ingManager.cantidadRegistros()){
            cout << "Ingrese un Id de ingrediente valido" << endl << endl;
            cout << "Seleccione el ingrediente que desee agregar: " << endl << endl;
            ingManager.listarIngredientes();
            cin >> idIngrediente;
        }
        validacion=false;
        while (!validacion){
            cout << "Ingrese la cantidad del ingrediente a colocar en el producto: ";
            cin >> cantidadPorProducto;
            if(cantidadPorProducto<0){
                cout << "Ingrese una cantidad valida" << endl << endl;
            }
            else{
                validacion=true; //fin del while
            }
        }
        // ingreso de ID ingrediente y cantidad por productos valido

        detalleIng= DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto);

        if(detalleArchi.guardar(detalleIng)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }

        //Un ingrediente guardado en el detalle

        validacion=false;
        while (!validacion){
            cout << endl << "¿Desea ingresar mas ingredientes?  " << endl <<"1) si" << endl <<"0) no" << endl << endl;
            cin>>opcion;
            if(opcion<0 || opcion >1){
                cout << "Ingrese un valor valido" << endl << endl;
            }
            else if(opcion==0){
                cargaIngredientes=true; //fin del while de carga de ingredientes
                validacion=true;
            }
            else{ //si la opcion es 1:
                validacion=true; //fin del while de validacion de opciones
            }
        }

    }

    validacion = false;
    while (!validacion){
        cout << "Ingrese el costo de hacer el producto: $";
        cin >> costoProducto;

        if(costoProducto<0){
            cout << "Ingrese un valor valido" << endl << endl;
        }
        else{
            validacion=true;
        }
    }

    prod = Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoProducto, estado);

    if (prodArchi.guardar(prod)){
        cout << "Registro guardado correctamente." << endl << endl;
    }
    else{
        cout << "Hubo un problema al guardar el registro." << endl << endl;
    }

}
void ProductosManager::modificarProducto(){
  ///sin utilizar todavia
}

void ProductosManager::listarProductos(){
    ArchivoProducto prodArchi;
    Producto prod;
    int cantRegistros;
    cantRegistros = cantidadRegistrosProducto();

    for (int i=0; i<cantRegistros; i++){
        prod = prodArchi.leer(i);
        prod.mostrar();
    }

}

void ProductosManager::listarProductosConIngredientes(){
    ArchivoProducto prodArchi;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    Producto prod;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    int cantRegistrosProducto, cantRegistrosDetalleIngrediente, pos;
    cantRegistrosProducto = cantidadRegistrosProducto();
    cantRegistrosDetalleIngrediente=cantidadRegistrosDetalleIngredientes();

    for (int i=0; i<cantRegistrosProducto; i++){
        prod = prodArchi.leer(i);
        prod.mostrar();
        cout << "Producto: " << prod.getIdProducto() << endl;
        cout << "Nombre: " << prod.getNombreProducto() << endl << endl;

        cout << "Ingredientes: " << endl << endl;

        for (int i=0; i<cantRegistrosDetalleIngrediente; i++){
            detalleIng = detalleArchi.leer(i);
            pos = ingArchi.buscar(detalleIng.getIdIngrediente());
            ing = ingArchi.leer(pos);
            cout << ing.getNombreIngrediente() << "  " << detalleIng.getCantidadPorProducto() << " " << ing.getTipoDeUnidad() << endl;

        }

        //recorrer detalleIngredientes, traer todas las instancias con ese id producto y buscar los ingredientes para mostrar sus caracteristicas

    }

}
