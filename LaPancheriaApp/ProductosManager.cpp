#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "ArchivoIngrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include "IngredientesManager.h"
#include "Ingrediente.h"

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
    Ingrediente ing;

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
            validacion=true; //fin del while de validacion
        }
    } ///todavia no hace nada pero deberia mostrar un menu para separar las bebidas y cargarlas distinto que a los panchos y guarniciones ya que no deberia pedir mas de un ingrediente"

    cout << "Ingrese el nombre del nuevo producto: ";
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
            validacion=true; //fin del while de validacion
        }
    }
 ///desde linea 73 hasta  linea 126 se puede hacer una funcion o metodo cargarIngredientes, en este caso está hecho para panchos o guarniciones. No bebidas (solo deberia pedir un ingrediente).
    bool cargaIngredientes=false;
    int opcion;
    while (!cargaIngredientes){ ///ciclo para ingresar ingredientes de un producto
        cout << "Seleccione el ingrediente que desee agregar: " << endl << endl;
        ingManager.listarIngredientes(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
        cin >> idIngrediente;

        while (idIngrediente < 0 || idIngrediente > ingManager.cantidadRegistros()){
            cout << "Ingrese un Id de ingrediente valido" << endl << endl;
            ingManager.listarIngredientes(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
            cout << "Seleccione el ingrediente que desee agregar: " << endl << endl;
            cin >> idIngrediente;
        }
        validacion=false;
        while (!validacion){
            int posicion;
            posicion = ingArchi.buscar(idIngrediente);
            ing = ingArchi.leer(posicion);
            cout << "Ingrese la cantidad de " << ing.getNombreIngrediente() << " a colocar en el producto en " << ing.getTipoDeUnidad() << ": ";
            cin >> cantidadPorProducto;
            if(cantidadPorProducto<0){
                cout << "Ingrese una cantidad valida" << endl << endl;
            }
            else{
                validacion=true; //fin del while de validacion
            }
        }
        // a partir de aca esta OK el ingreso de ID ingrediente y cantidad por productos

        // en caso de cerrar la consola antes de terminar de cargar el producto, los ingredientes quedan guardados en el archivo
        detalleIng = DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto);

        if(detalleArchi.guardar(detalleIng)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }

        //acá se guarda UN ingrediente en el detalle

        validacion=false;
        while (!validacion){
            cout << endl << "¿Desea ingresar mas ingredientes?  " << endl <<"1) si" << endl <<"0) no" << endl << endl;
            cin>>opcion;
            if(opcion<0 || opcion >1){
                cout << "Ingrese un valor valido" << endl << endl;
            }
            else if(opcion==0){
                cargaIngredientes=true; //fin del while general de carga de ingredientes
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
            validacion=true;  //fin del while de validacion
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

    for (int i=0; i<cantRegistrosProducto; i++){ //recorre el archivo de productos
        prod = prodArchi.leer(i);
        prod.mostrar();
        cout << "Producto: " << prod.getIdProducto() << endl;
        cout << "Nombre: " << prod.getNombreProducto() << endl << endl;

        cout << "Ingredientes: " << endl << endl;

        for (int i=0; i<cantRegistrosDetalleIngrediente; i++){ //recorre el archivo detalle de ingredientes
            detalleIng = detalleArchi.leer(i);
            if(detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
                pos = ingArchi.buscar(detalleIng.getIdIngrediente());//lo busca en el archivo de ingredientes
                ing = ingArchi.leer(pos); //trae el ingrediente a memoria y lo informa
                cout << ing.getNombreIngrediente() << "  " << detalleIng.getCantidadPorProducto() << " " << ing.getTipoDeUnidad() << endl;
            }
        }
        cout << endl << endl;

    }

}
