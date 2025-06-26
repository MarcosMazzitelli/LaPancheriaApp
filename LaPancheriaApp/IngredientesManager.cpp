#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "ArchivoIngrediente.h"
#include "ArchivoProducto.h"
#include "ArchivoDetalleIngrediente.h"
#include "Utilidades.h"
#include <iostream>
#include <iomanip>
using namespace std;

    ///Metodos principales
void IngredientesManager::cargarIngrediente(){
    int idIngrediente;
    string nombreIngrediente, tipoDeUnidad;
    float cantidadStock, costoUnitario, costoTotal;
    bool estado = true;
    Ingrediente ing;
    ArchivoIngrediente archi;
    int cantRegistrosIngrediente = archi.getCantidadRegistros();

    idIngrediente=cantRegistrosIngrediente+1; //autonumerico

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

void IngredientesManager::comprarIngrediente(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    int cantRegistrosIngrediente = archi.getCantidadRegistros();
    float costoTotal, costoUnitario, cantidad;
    string tipoDeUnidad;

    listarIngredientes(true); //solo los activos

    cout << endl << "Ingrese el ID del ingrediente comprado: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0 || idIngrediente > cantRegistrosIngrediente){
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

///ABML

void IngredientesManager::modificarIngrediente(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    int cantRegistrosIngredientes = archi.getCantidadRegistros();
    float stockReal;

    listarIngredientes(true); //solo los activos
    cout << endl << "Ingrese el ID del ingrediente a modificar: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0 || idIngrediente > cantRegistrosIngredientes ){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes(true); //solo los activos
        cout << endl << "Ingrese el ID del ingrediente a modificar: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);

    if(pos >= 0){
        ing = archi.leer(pos);
        if(ing.getEstado()){
            menuModificacion(ing, pos);
        }
        else{
            ing.mostrar();
            cout << endl << endl <<"El ingrediente se encuentra dado de baja" << endl;
            cout << "Solo esta permitido modificar ingredientes activos." << endl << endl;
        }
    }
    else{
        cout << "No se ha encontrado el ID del ingrediente en el archivo" << endl << endl;
    }
}


void IngredientesManager::menuModificacion(Ingrediente &ing, int &pos){
    ArchivoIngrediente archivoIngrediente; //prodArchi;
    int opcion;
    string nombreIngrediente;
    float costoUnitario;

    while(true) {
        system("cls");
        cout << "\n--- Menu de Modificacion --- \n";
        ing.mostrar();
        cout << endl << endl;
        cout << "1. Modificar Nombre \n";
        cout << "2. Modificar costo unitario \n";
        cout << "3. Mostrar Datos \n";
        cout << "0. Salir \n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        while(cin.fail() || opcion < 0 || opcion > 3 ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            ing.mostrar();
            cout << endl << endl;
            cout << "1. Modificar Nombre \n";
            cout << "2. Modificar costo unitario \n";
            cout << "3. Mostrar Datos \n";
            cout << "0. Salir \n";
            cout << "Seleccione una opcion: ";
            cin >> opcion;
        }
        switch (opcion) {
            case 1:
                system("cls");
                cout << "Ingrese el nuevo nombre: ";
                cin.ignore();
                getline(cin, nombreIngrediente);
                ing.setNombreIngrediente(nombreIngrediente);
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "Ingrese el nuevo costo unitario: ";
                cin >> costoUnitario;
                while (cin.fail() || costoUnitario < 0){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Ingrese un valor valido" << endl << endl;
                    system("pause");
                    system("cls");
                    cout << "Ingrese el nuevo costo unitario: ";
                    cin >> costoUnitario;
                }
                ing.setCostoUnitario(costoUnitario);
                cout << "costo unitario modificado.\n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "\nDatos actuales del ingrediente:\n";
                ing.mostrar();
                system("pause");
                break;
            case 0:
                system("cls");
                opcion = pedirYValidarConfirmacion("\nDesea guardar antes de salir? \n1)Si  0)No \n");
                if (opcion == 1){
                    if(archivoIngrediente.modificar(ing, pos)){
                        cout << endl << "Ingrediente guardado con exito." << endl << endl;
                    }
                    else{
                        cout << endl <<"Hubo un error al guardar el ingrediente." << endl << endl;
                    }
                }
                else{
                    cout << "No se ha realizado la modificacion\n\n";
                }
                cout << "Saliendo del programa...\n";
                return;
                break;
        }
    }



}

void IngredientesManager::modificarStock(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    int cantRegistrosIngredientes = archi.getCantidadRegistros();
    float stockReal;


    listarIngredientes(true); //solo los activos

    cout << endl << "Ingrese el ID del ingrediente a modificar stock: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0 || idIngrediente > cantRegistrosIngredientes ){
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
            while(cin.fail() || stockReal <= 0){
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
    DetalleIngrediente auxDetalleIngrediente;
    Ingrediente ingrediente;
    Producto producto;
    int posicionIng, posicionDetalleIng, posicionProducto, idIngrediente, opcion;
    int cantRegistrosDetalleIngrediente = archivoDetalleIngrediente.getCantidadRegistros();
    int cantRegistrosIngrediente = archivoIngrediente.getCantidadRegistros();

    listarIngredientes(true); //solo los activos
    cout << endl << "Ingrese el ID del ingrediente a eliminar: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0 || idIngrediente > cantRegistrosIngrediente){
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
        ///Muestra los productos vinculados a ese ingrediente
        cout << "Los siguientes productos contienen este ingrediente:" << endl << endl;
        for (int i=0; i < cantRegistrosDetalleIngrediente; i++){
            detalleIngrediente = archivoDetalleIngrediente.leer(i);
            if (detalleIngrediente.getIdIngrediente() == idIngrediente){
                posicionProducto = archivoProducto.buscar(detalleIngrediente.getIdProducto());
                producto = archivoProducto.leer(posicionProducto);
                cout << producto.getNombreProducto() << endl;
            }
        }
        opcion = pedirYValidarConfirmacion("\nAdemas del ingrediente y su stock, tambien se eliminaran los productos y su receta. \nDesea confirmar? \n1)Si \n0)No \n\n");
        if (opcion == 1){
            ///elimina producto, ingrediente y detalle de ingredientes(receta)
            ingrediente.setCantidadStock(0);
            ingrediente.setEstado(false);
            if (archivoIngrediente.modificar(ingrediente, posicionIng)){
                cout << "Ingrediente eliminado con exito" << endl;
            }
            else{
                cout << "Hubo un error al dar de baja el ingrediente" << endl;
            }
            for (int i=0; i < cantRegistrosDetalleIngrediente; i++){
                //recorro todas las recetas y las instancio
                detalleIngrediente = archivoDetalleIngrediente.leer(i);
                if (detalleIngrediente.getIdIngrediente() == idIngrediente){
                    //si coincide el ID ingrediente con ID de la receta (detalleIng) puedo obtener el ID PRODUCTO
                    //Recorro desde 0 nuevamente todas las recetas para rastrear desde un principio todas las recetas
                    //que contengan ese ID producto y darlas de baja a todas
                    for (int j=0; j < cantRegistrosDetalleIngrediente; j++){
                        //Se instancian con una nueva variable otras recetas (detalleIng) para comparar
                        auxDetalleIngrediente = archivoDetalleIngrediente.leer(j);
                        if(detalleIngrediente.getIdProducto() == auxDetalleIngrediente.getIdProducto()){
                            //Si coinciden ambas instancias en el atributo ID producto, por mas que no tenga el
                            //ingrediente que quiero dar de baja, también se dara de baja esa receta.
                            auxDetalleIngrediente.setEstado(false);
                            if (archivoDetalleIngrediente.modificar(auxDetalleIngrediente, j)){
                                cout << "Receta eliminada con exito" << endl;
                            }
                            else{
                                cout << "Hubo un error al dar de baja la receta" << endl;
                            }
                        }
                    }
                    posicionProducto = archivoProducto.buscar(detalleIngrediente.getIdProducto());
                    producto = archivoProducto.leer(posicionProducto);
                    if(producto.getEstado()){
                        producto.setEstado(false);
                        if(archivoProducto.modificar(producto, posicionProducto)){
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


void IngredientesManager::darAltaIngrediente(){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int idIngrediente, pos, opcion;
    int cantRegistrosIngredientes = archi.getCantidadRegistros();
    float stock;

    listarIngredientes(false); //solo los inactivos
    cout << endl << "Ingrese el ID del ingrediente a dar de alta: ";
    cin >> idIngrediente;
    while(cin.fail() || idIngrediente <= 0 || idIngrediente > cantRegistrosIngredientes ){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        listarIngredientes(false); //solo los inactivos
        cout << endl << "Ingrese el ID del ingrediente a dar de alta: ";
        cin >> idIngrediente;
    }
    pos = archi.buscar(idIngrediente);

    if(pos >= 0){
        ing = archi.leer(pos);
        if(!ing.getEstado()){
            system("cls");
            ing.mostrar();
            opcion = pedirYValidarConfirmacion("\n\nDesea asignar stock ahora? \n1)Si \n0)No \n");
            if(opcion ==1){
                cout << "Ingrese la cantidad de stock en " << ing.getTipoDeUnidad() <<" : ";
                cin >> stock;
                while (cin.fail() || stock <= 0){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Ingrese un valor valido" << endl;
                    system("pause");
                    system("cls");
                    cout << "Ingrese la cantidad de stock en " << ing.getTipoDeUnidad() <<" : ";
                    cin >> stock;
                }
                ing.setCantidadStock(stock);
            }
            opcion = pedirYValidarConfirmacion("\n\nConfirma dar de alta el ingrediente? \n\n1)Si \n0)No \n");
            if(opcion == 1){
                ing.setEstado(true);
                if(archi.modificar(ing,pos)){
                    cout << "Ingrediente dado de alta con exito" << endl;
                }
                else{
                    cout << "Hubo un error al dar de alta el ingrediente" << endl;
                }
            }
        }
        else{
            ing.mostrar();
            cout << endl << endl <<"El ingrediente ya se encuentra dado de alta" << endl << endl;
        }
    }
    else{
        cout << "No se ha encontrado el ID del ingrediente en el archivo" << endl << endl;
    }
}



void IngredientesManager::listarIngredientes(bool estado){
    ArchivoIngrediente archi;
    Ingrediente ing;

    int cantRegistros = archi.getCantidadRegistros();
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

void IngredientesManager::listarIngredientesToCsv(){
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ingrediente;

    int cantRegistrosIngrediente = archivoIngrediente.getCantidadRegistros();

    cout << "_idIngrediente),_nombreIngrediente,_cantidadStock,(_costoUnitario,_tipoDeUnidad,_estado" << endl;
    for (int i=0;i<cantRegistrosIngrediente;i++){
        ingrediente = archivoIngrediente.leer(i);
        cout << ingrediente.mostrarToCsv();
        cout << endl;
     }



}













