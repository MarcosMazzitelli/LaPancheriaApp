#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "ArchivoIngrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "Utilidades.h"
#include <iomanip>
#include <iostream>
#include "Validador.h"
#include "Venta.h"
#include "DetalleVenta.h"
#include "VentaArchivo.h"
#include "DetalleVentaArchivo.h"
using namespace std;


void ProductosManager::incorporarIngredientes(int idProducto, float &costoProducto, std::vector<DetalleIngrediente> &vecDetalleIngredientes){
    IngredientesManager ingManager;
    int idIngrediente, posicion;
    DetalleIngrediente detalleIng;
    ArchivoIngrediente ingArchi;
    Ingrediente ing;
    float cantidadPorProducto;
    int cantRegistrosIngrediente = ingArchi.getCantidadRegistros();


    bool cargaIngredientes=false;
    int opcion;
    while (!cargaIngredientes){ ///ciclo para ingresar ingredientes de un producto
        cout << "A continuacion se listaran los ingredientes disponibles para agregar a su producto." << endl;
        system("pause");
        system("cls");
        ingManager.listarIngredientes(true); //solo los activos
        cout << "Seleccione el ID del ingrediente que desee agregar: " << endl << endl;
        cin >> idIngrediente;
        while(cin.fail() || idIngrediente < 1 || idIngrediente > cantRegistrosIngrediente){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            ingManager.listarIngredientes(true); //solo los activos
            cout << "Seleccione el ID del ingrediente que desee agregar: ";
            cin >> idIngrediente;
        }
        posicion = ingArchi.buscar(idIngrediente);
        ing = ingArchi.leer(posicion);
        if (ing.getEstado()){
            cout << "Ingrese la cantidad de " << ing.getNombreIngrediente() << " a colocar en el producto (en " << ing.getTipoDeUnidad() << "): ";
            cin >> cantidadPorProducto;
            while(cin.fail() || cantidadPorProducto <= 0){
                cin.clear();
                cin.ignore(1000,'\n');
                cout << "Ingrese un valor valido" << endl << endl;
                system("pause");
                system("cls");
                cout << "Ingrese la cantidad de " << ing.getNombreIngrediente() << " a colocar en el producto (en " << ing.getTipoDeUnidad() << "): ";
                cin >> cantidadPorProducto;
            }
            costoProducto+= ing.getCostoUnitario() * cantidadPorProducto;

            // a partir de aca esta OK el ingreso de ID ingrediente y cantidad por productos

            detalleIng = DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto, true); //
            vecDetalleIngredientes.push_back(detalleIng);

            //aca se guarda UN ingrediente en el detalle
            opcion = pedirYValidarConfirmacion("\nDesea agregar mas ingredientes? \n1)Si \n0)No \n\n");
            if(opcion==0){
                cargaIngredientes=true; //fin del while general de carga de ingredientes
            }
        }
        else{
            cout << "El ingrediente seleccionado se encuentra dado de baja!" << endl;
            cout << "Por favor seleccione un ID que se encuentre en la lista." << endl << endl;
        }
    }
}

void ProductosManager::crearPanchoOGuarnicion(int idCategoria){
    Producto prod;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoProducto prodArchi;
    vector<DetalleIngrediente> vecDetalleIngredientes;
    int idProducto, opcion;
    string nombreProducto;
    float precioUnitario, precioSugerido;
    float costoProducto=0;
    bool estado = true;
    cout << "Ingrese el nombre del nuevo producto: ";
    cin.ignore();
    getline(cin,nombreProducto);

    idProducto = prodArchi.getCantidadRegistros()+1; //autonumerico

    incorporarIngredientes(idProducto, costoProducto, vecDetalleIngredientes);
    cout << "El costo para hacer el producto es: $" << costoProducto << endl << endl;

    precioSugerido = costoProducto * 1.5; //un 50% mas
    cout << "El precio de venta sugerido es: $" << precioSugerido << endl;
    cout << "Desea modificarlo?" << endl << "1) si" << endl << "0) no" << endl << endl;
    cin >> opcion;
    while(cin.fail() || opcion!= 0 && opcion != 1){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "El costo para hacer el producto es: $" << costoProducto << endl << endl;
        cout << "El precio de venta sugerido es: $" << precioSugerido << endl;
        cout << "Desea modificarlo?" << endl << "1) si" << endl << "0) no" << endl << endl;
        cin >> opcion;
    }
    if(opcion==0){
        precioUnitario = precioSugerido;
    }
    else{
        cout << "Ingrese el precio unitario de venta del producto: $";
        cin >> precioUnitario;
        while(cin.fail() || precioUnitario <= 0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            cout << "Ingrese el precio unitario de venta del producto: $";
            cin >> precioUnitario;
        }
    }
    ///FIN DE CARGA DEL PRODUCTO Y SU RECETA:
    prod = Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoProducto, estado);

    opcion = pedirYValidarConfirmacion("\nDesea guardar la receta? \n1) Si \n0) No \n\n");
    if(opcion==1){ //si confirma, se guardan los detalles de ingredientes (receta) y el producto
        for (int i=0; i < vecDetalleIngredientes.size(); i++){
            if(detalleArchi.guardar(vecDetalleIngredientes[i])){
                cout << "Ingrediente aniadido a la receta con exito." << endl;
            }
            else{
                cout << "Hubo un problema al vincular el ingrediente con la receta." << endl << endl;
            }
        }
        if (prodArchi.guardar(prod)){
            cout << "Producto guardado con exito." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el producto." << endl << endl;
        }
    }
    else{ //si no desea guardar la receta:
        cout << "Creacion de producto descartada..." << endl << endl;
    }

}

void ProductosManager::crearBebida(int idCategoria){
    Producto prod;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    DetalleIngrediente detalleIng;
    Ingrediente ing;
    ArchivoProducto prodArchi;
    vector<DetalleIngrediente> vecDetalleIngredientes;
    int idProducto, idIngrediente, opcion, opcionContNeto;
    string nombreProducto, nombreIngrediente, tipoDeUnidad;
    float precioUnitario, precioSugerido, cantidadStock, costoTotal, costoUnitario;
    bool estado = true;
    bool validacion = false;
    int cantidadPorProducto;

    cout << "Ingrese el nombre de la bebida: ";
    cin.ignore();
    getline(cin,nombreProducto);

    while(!validacion) {
        cout << "\n--- Ingrese el contenido neto de la bebida --- \n";
        cout << endl;
        cout << "1. 500 ml \n";
        cout << "2. 1.25 lts \n";
        cout << "3. 2.25 lts \n";
        cout << "4. 3 lts \n";

        cout << "Seleccione una opcion: ";
        cin >> opcionContNeto;
        while(cin.fail() || opcionContNeto < 1 || opcionContNeto > 4 ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            prod.mostrar();
            cout << endl << endl;
            cout << "\n--- Ingrese el contenido neto de la bebida --- \n";
            cout << endl << endl;
            cout << "1. 500 ml \n";
            cout << "2. 1.25 lts \n";
            cout << "3. 2.25 lts \n";
            cout << "4. 3 lts \n";

            cout << "Seleccione una opcion: ";
            cin >> opcionContNeto;
        }
        switch (opcionContNeto) {
            case 1:
                nombreProducto+= " (500 ml)";
                validacion = true;
                break;
            case 2:
                nombreProducto+= " (1.25 lts)";
                validacion = true;
                break;
            case 3:
                nombreProducto+= " (2.25 lts)";
                validacion = true;
                break;
            case 4:
                nombreProducto+= " (3 lts)";
                validacion = true;
                break;
        }
    }

    cout << endl << "Ha elegido " << nombreProducto << endl << endl;

    nombreIngrediente = nombreProducto;


    idProducto = prodArchi.getCantidadRegistros()+1;  //autonumerico
    idIngrediente = ingArchi.getCantidadRegistros()+1; //autonumerico
    cout << "Ingrese el stock inicial : ";
    cin >> cantidadStock;
    while(cin.fail() || cantidadStock < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese el stock inicial : ";
        cin >> cantidadStock;
    }

    tipoDeUnidad = "Unidades";

    cout << "Ingrese el costo total de las " << cantidadStock << " unidades: ";
    cin >> costoTotal;
    while(cin.fail() || costoTotal < 0){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl;
        system("pause");
        system("cls");
        cout << "Ingrese el costo total de las " << cantidadStock << " unidades: ";
        cin >> costoTotal;
    }
    costoUnitario = costoTotal / cantidadStock;
    cout << endl << "Costo unitario: $ " << costoUnitario << endl;

    precioSugerido = costoUnitario * 1.5; //un 50% mas
    cout << "El precio de venta sugerido es: $" << precioSugerido << endl;
    cout << "Desea modificarlo?" << endl << "1) si" << endl << "0) no" << endl << endl;
    cin >> opcion;
    while(cin.fail() || opcion!= 0 && opcion != 1){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "El costo unitario es: $" << costoUnitario << endl << endl;
        cout << "El precio de venta sugerido es: $" << precioSugerido << endl;
        cout << "Desea modificarlo?" << endl << "1) si" << endl << "0) no" << endl << endl;
        cin >> opcion;
    }
    if(opcion==0){
        precioUnitario = precioSugerido;
    }
    else{
        cout << "Ingrese el precio unitario de venta del producto: $";
        cin >> precioUnitario;
        while(cin.fail() || precioUnitario <= 0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            cout << "Ingrese el precio unitario de venta del producto: $";
            cin >> precioUnitario;
        }
    }

    cantidadPorProducto = 1; //porque las bebidas se guardan en unidades

    ///FIN DE CARGA DEL PRODUCTO Y SU RECETA:
    prod = Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoUnitario, estado);
    ing = Ingrediente(idIngrediente,nombreIngrediente,cantidadStock, costoUnitario, tipoDeUnidad,estado);
    detalleIng = DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto, true); //

    opcion = pedirYValidarConfirmacion();
    if(opcion==1){ //si confirma, se guardan los detalles de ingredientes (receta) y el producto
        if (prodArchi.guardar(prod)){
            cout << "Producto guardado con exito." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el producto." << endl << endl;
        }
        if(ingArchi.guardar(ing)){
            cout << "Ingrediente con stock aniadido con exito." << endl;
        }
        else{
            cout << "Hubo un problema al guardar el ingrediente." << endl;
            }
        if (detalleArchi.guardar(detalleIng)){
            cout << "Vinculacion de ingrediente exitosa." << endl;
        }
        else{
            cout << "Hubo un problema al vincular el ingrediente." << endl;
        }
    }
    else{ //si no desea guardar la receta:
        cout << "Creacion de bebida descartada..." << endl << endl;
    }
}



void ProductosManager::crearProducto(){
    int idCategoria;

    cout << "Ingrese la categoria del producto: " << endl << "1) Panchos" << endl <<"2) Guarniciones" << endl <<"3) Bebidas" << endl << endl;
    cin >> idCategoria;
    while(cin.fail() || idCategoria!= 1 && idCategoria!= 2 && idCategoria!= 3){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "Ingrese la categoria del producto: " << endl << "1) Panchos" << endl <<"2) Guarniciones" << endl <<"3) Bebidas" << endl << endl;
        cin >> idCategoria;
    }

    if (idCategoria == 1 || idCategoria == 2){
        crearPanchoOGuarnicion(idCategoria);
    }
    else{
        crearBebida(idCategoria);
    }
///todavia no hace nada pero deberia mostrar un menu para separar las bebidas y cargarlas distinto que a los panchos y guarniciones ya que no deberia pedir mas de un ingrediente"

}
void ProductosManager::menuModificacion(Producto &prod, int pos){
    ArchivoProducto prodArchi;
    int opcion;
    string nombreProducto;
    float precioUnitario, costoProducto;

    while(true) {
        system("cls");
        cout << "\n--- Menu de Modificacion --- \n";
        prod.mostrar();
        cout << endl << endl;
        cout << "1. Modificar Nombre \n";
        cout << "2. Modificar Precio unitario \n";
        cout << "3. Modificar CostoProducto \n";
        cout << "4. Mostrar Datos \n";
        cout << "0. Salir \n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;
        while(cin.fail() || opcion < 0 || opcion > 4 ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            prod.mostrar();
            cout << endl << endl;
            cout << "\n--- Menu de Modificacion --- \n";
            cout << "1. Modificar Nombre \n";
            cout << "2. Modificar precio unitario \n";
            cout << "3. Modificar costo del producto \n";
            cout << "4. Mostrar Datos \n";
            cout << "0. Salir \n";

            cout << "Seleccione una opcion: ";
            cin >> opcion;
        }
        switch (opcion) {
            case 1:
                system("cls");
                cout << "Ingrese el nuevo nombre: ";
                cin.ignore();
                getline(cin, nombreProducto);
                prod.setNombreProducto(nombreProducto);
                cout << "Nombre modificado exitosamente.\n";
                system("pause");
                break;
            case 2:
                system("cls");
                cout << "Ingrese el nuevo precio unitario: ";
                cin >> precioUnitario;
                while (cin.fail() || precioUnitario < 0){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Ingrese un valor valido" << endl << endl;
                    system("pause");
                    system("cls");
                    cout << "Ingrese el nuevo precio unitario: ";
                    cin >> precioUnitario;
                }
                prod.setPrecioUnitario(precioUnitario);
                cout << "Precio unitario modificado.\n";
                system("pause");
                break;
            case 3:
                system("cls");
                cout << "Ingrese el nuevo costo del producto: ";
                cin >> costoProducto;
                while (cin.fail() || costoProducto < 0){
                    cin.clear();
                    cin.ignore(1000,'\n');
                    cout << "Ingrese un valor valido" << endl << endl;
                    system("pause");
                    system("cls");
                    cout << "Ingrese el nuevo costo del producto: ";
                    cin >> costoProducto;
                }
                prod.setCostoProducto(costoProducto);
                cout << "Costo del producto modificado.\n";
                system("pause");
                break;
            case 4:
                system("cls");
                cout << "\nDatos actuales del producto:\n";
                prod.mostrar();
                system("pause");
                break;
            case 0:
                system("cls");
                opcion = pedirYValidarConfirmacion("\nDesea guardar antes de salir? \n1)Si  0)No \n");
                if (opcion == 1){
                    if (prodArchi.modificar(prod, pos)){
                        cout << endl << "Registro guardado con exito." << endl << endl;
                    }
                    else{
                        cout << endl <<"Hubo un error al guardar el producto." << endl << endl;
                    }
                }
                else{
                    cout << "No se ha realizado la modificacion\n\n";
                }
                cout << "Saliendo del programa...\n";
                return;
                break;
            default:  //nunca deberia ejecutarse
                cout << "Opcion invalida. Intente nuevamente.\n";
                break;
        }
    }
}

void ProductosManager::modificarProducto(){
    int pos, idProducto, opcion;
    Producto prod;
    DetalleIngrediente detalleIngrediente;

    ArchivoProducto prodArchi;
    ArchivoDetalleIngrediente archivoDetalleIngrediente;
    int cantRegistrosProducto = prodArchi.getCantidadRegistros();
    int cantRegistrosDetalleIngrediente = archivoDetalleIngrediente.getCantidadRegistros();

    cout << "\r\r MENU MODIFICACION" << endl << endl;
    listarProductos(true);
    cout << "Ingrese el ID del producto a modificar: ";
    cin >> idProducto;
    while(cin.fail() || idProducto <= 0 || idProducto > cantRegistrosProducto){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "\r\r MENU MODIFICACION" << endl << endl;
        listarProductos(true);
        cout << "Ingrese el ID del producto a modificar: ";
        cin >> idProducto;
    }
    pos = prodArchi.buscar(idProducto);

    if (pos >= 0){ //si se encuentra el producto en el archivo
        prod = prodArchi.leer(pos);

        if(prod.getEstado() == true){
            menuModificacion(prod, pos);

        }
        else{
            prod.mostrar();
            cout << endl << endl << "El producto se encuentra dado de baja." << endl;
            cout << "Solo esta permitido modificar productos activos." << endl << endl;
        }
    }
    else{
        cout << "No se ha encontrado el ID" << endl << endl;
    }
}

void ProductosManager::eliminarProducto(){
    ArchivoProducto archivoProducto;
    ArchivoDetalleIngrediente archivoDetalleIngrediente;
    Producto producto;
    DetalleIngrediente detalleIngrediente;

    int pos, idProducto, opcion;
    int cantRegistrosProducto = archivoProducto.getCantidadRegistros();
    int cantRegistrosDetalleIngrediente = archivoDetalleIngrediente.getCantidadRegistros();

        cout << "\r\r ELIMINAR PRODUCTOS" << endl << endl;
    listarProductos(true);
    cout << "Ingrese el ID del producto a eliminar: ";
    cin >> idProducto;
    while(cin.fail() || idProducto <= 0 || idProducto > cantRegistrosProducto){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "\r\r ELIMINAR PRODUCTOS" << endl << endl;
        listarProductos(true);
        cout << "Ingrese el ID del producto a eliminar: ";
        cin >> idProducto;
    }
    pos = archivoProducto.buscar(idProducto);

    if (pos >= 0){ //si se encuentra el producto en el archivo
        producto = archivoProducto.leer(pos);

        if(producto.getEstado() == true){
            system("cls");
            mostrarProductoYReceta(producto);
            cout << "\n\nSe eliminara el producto y la receta \n\n";
            opcion = pedirYValidarConfirmacion();
            if (opcion ==1){
                producto.setEstado(false);
                if (archivoProducto.modificar(producto,pos)){
                    cout << "Producto dado de baja con exito" << endl;
                }
                else{
                    cout << "Hubo un error al dar de baja el producto en el archivo" << endl << endl;
                }

                for (int i=0; i<cantRegistrosDetalleIngrediente; i++){
                    detalleIngrediente = archivoDetalleIngrediente.leer(i);
                    if(idProducto == detalleIngrediente.getIdProducto()){
                        detalleIngrediente.setEstado(false);
                        if(archivoDetalleIngrediente.modificar(detalleIngrediente, i)){
                            cout << "Receta dada de baja con exito" << endl;
                        }
                        else{
                            cout << "Hubo un error al dar de baja la receta en el archivo"  << endl;
                        }
                    }
                }
            }

        }
        else{
            cout << "El producto ya se encuentra dado de baja." << endl;
        }
    }
    else{
        cout << "No se ha encontrado el ID" << endl << endl;
    }

}

void ProductosManager::darAltaProducto(){
    ArchivoProducto archivoProducto;
    ArchivoDetalleIngrediente archivoDetalleIngrediente;
    ArchivoIngrediente archivoIngrediente;
    Producto producto;
    Ingrediente ingrediente;
    DetalleIngrediente detalleIngrediente;
    vector<DetalleIngrediente> vecDetalleIngredientesOk;
    vector<int> vecPosDetalleIngredientesOk;
    vector<Ingrediente> vecIngredientesOk;
    vector<int> vecPosIngredientesOk;


    int posProducto, posIngrediente, idProducto, opcion;
    bool validacion = true; //arranca en true, si el producto tiene un ingrediente dado de baja y el usuario no quiere darlo de alta, se pone en false y no se realizan cambios.
    int cantRegistrosProducto = archivoProducto.getCantidadRegistros();
    int cantRegistrosDetalleIngrediente = archivoDetalleIngrediente.getCantidadRegistros();

        cout << "\r\r ALTA DE PRODUCTOS" << endl << endl;
    listarProductos(false);
    cout << "Ingrese el ID del producto a dar de alta: ";
    cin >> idProducto;
    while(cin.fail() || idProducto <= 0 || idProducto > cantRegistrosProducto){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "\r\r ALTA DE PRODUCTOS" << endl << endl;
        listarProductos(false);
        cout << "Ingrese el ID del producto a dar de alta: ";
        cin >> idProducto;
    }
    posProducto = archivoProducto.buscar(idProducto);

    if (posProducto >= 0){ //si se encuentra el producto en el archivo
        producto = archivoProducto.leer(posProducto);

        if(!producto.getEstado()){
            system("cls");
            mostrarProductoYReceta(producto);
            cout << "\n\nSe dara de alta el producto y la receta \n\n";
            opcion = pedirYValidarConfirmacion();
            if (opcion ==1){
                for (int i=0; i<cantRegistrosDetalleIngrediente; i++){
                    detalleIngrediente = archivoDetalleIngrediente.leer(i);
                    if(idProducto == detalleIngrediente.getIdProducto()){
                        detalleIngrediente.setEstado(true);
                        vecDetalleIngredientesOk.push_back(detalleIngrediente); //Seteo el detalle en true y lo guardo en el vector para modificar luego si todo esta ok
                        vecPosDetalleIngredientesOk.push_back(i); //guardo la posicion para saber EN QUE POSICION tengo que modificar en el archivo

                        posIngrediente = archivoIngrediente.buscar(detalleIngrediente.getIdIngrediente());
                        ingrediente = archivoIngrediente.leer(posIngrediente); //Traigo el ingrediente a memoria para chequear que este OK
                        if(!ingrediente.getEstado()){
                            cout << "El ingrediente " << ingrediente.getNombreIngrediente() << " se encuentra dado de baja!" << endl;
                            opcion = pedirYValidarConfirmacion("\nDesea darlo de alta? \n1)Si \n0)No \n\n"); //si el ingrediente esta dado de alta, pregunto si quiere activarlo.
                            if(opcion ==1){
                                ingrediente.setEstado(true);
                                vecIngredientesOk.push_back(ingrediente); //seteo el ingrediente en true y lo guardo en otro vector para modificar luego si todo esta ok
                                vecPosIngredientesOk.push_back(posIngrediente); //guardo la posicion para saber EN QUE POSICION tengo que modificar en el archivo
                                ///pasar
                            }
                            else{
                                validacion = false; //si no quiere dar de alta alguno de los ingredientes, la bandera se pone en false y hace que no se modifique nada luego.
                            }
                        }
                    }
                }
                if(validacion){ ///si la bandera esta en true, modifica todo, sino no modifica nada.
                    producto.setEstado(true);
                    if (archivoProducto.modificar(producto,posProducto)){
                        cout << "Producto dado de alta con exito" << endl;
                    }
                    else{
                        cout << "Hubo un error al dar de alta el producto en el archivo" << endl << endl;
                    }
                    for(int i=0; i < vecIngredientesOk.size(); i++){
                        if(archivoIngrediente.modificar(vecIngredientesOk[i], vecPosIngredientesOk[i])){
                            cout << "Ingrediente dado de alta exitosamente" << endl;
                        }
                        else{
                            cout << "Hubo un problema al dar de alta el ingrediente en el archivo" << endl;
                        }

                    }
                    for (int j=0; j< vecDetalleIngredientesOk.size(); j++){
                        if(archivoDetalleIngrediente.modificar(vecDetalleIngredientesOk[j], vecPosDetalleIngredientesOk[j] )){
                            cout << "Receta dada de alta con exito" << endl;
                        }
                        else{
                            cout << "Hubo un error al dar de alta la receta en el archivo"  << endl;
                        }
                    }
                }
                else{
                    cout << "No se puede dar de alta un producto con ingredientes inactivos" << endl;
                    cout << "No se han realizado cambios" << endl << endl;
                }
            }
            else{  //cierra con la condicion de si desea modificar o no.
                cout << "No se han realizado cambios" << endl << endl;
            }

        }
        else{
            cout << "El producto ya se encuentra dado de alta." << endl;
        }
    }
    else{
        cout << "No se ha encontrado el ID" << endl << endl;
    }

}


void ProductosManager::mostrarProductosCompletos(){
    ArchivoProducto prodArchi;
    Producto prod;
    int cantRegistros;
    cantRegistros = prodArchi.getCantidadRegistros();

    for (int i=0; i<cantRegistros; i++){
        prod = prodArchi.leer(i);
        if(prod.getEstado()){
            prod.mostrar();
            cout << endl << endl;
        }
    }

}

void ProductosManager::listarProductos(bool estado){
    ArchivoProducto prodArchi;
    Producto prod;
    int cantRegistros;
    cantRegistros = prodArchi.getCantidadRegistros();


    cout << left << setw(15) << "ID Producto";
    cout << setw(15) << "ID Categoria";
    cout << setw(30) << "Nombre del producto";
    cout << setw(20) << "Precio de venta";
    cout << setw(20) << "Costo de preparacion" << endl;

    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
    if (estado){ //si se envia true por parametro, se muestran los activos
        for (int i=0; i<cantRegistros; i++){
            prod = prodArchi.leer(i);
            if (prod.getEstado()){
                prod.mostrarEnLista();
                cout << endl;
            }
        }
    }
    else{ //si se envia false por parametro, se muestran los inactivos
        for (int i=0; i<cantRegistros; i++){
            prod = prodArchi.leer(i);
            if (!prod.getEstado()){
                prod.mostrarEnLista();
                cout << endl;
            }
        }

    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres


}




void ProductosManager::listarProductosConIngredientes(bool estado){
    ArchivoProducto prodArchi;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    Producto prod;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    int cantRegistrosProducto, cantRegistrosDetalleIngrediente, pos;
    cantRegistrosProducto = prodArchi.getCantidadRegistros();
    cantRegistrosDetalleIngrediente = detalleArchi.getCantidadRegistros();

    for (int i=0; i<cantRegistrosProducto; i++){ //recorre el archivo de productos
        prod = prodArchi.leer(i);
        if(estado){ ///si se envia por parametro un valor verdadero, muestra los activos
            if(prod.getEstado() && prod.getIdCategoria() != 3){ //las bebidas no se listan // si se envia true por parametro, muestra los activos
                cout << "==============================================" << endl;
                cout << "ID Producto: " << prod.getIdProducto() << endl;
                cout << "Nombre: " <<  prod.getNombreProducto() << endl;
                cout << "Ingredientes: " << endl;
                cout << "----------------------------------------------" << endl;
                cout << left << setw(25) << "Nombre Ingrediente";
                cout << setw(10) << "Cantidad";
                cout << setw(10) << "Unidad" << endl;

                for (int j=0; j<cantRegistrosDetalleIngrediente; j++){ //recorre el archivo detalle de ingredientes
                    detalleIng = detalleArchi.leer(j);
                    if(detalleIng.getEstado() && detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
                        pos = ingArchi.buscar(detalleIng.getIdIngrediente());//lo busca en el archivo de ingredientes
                        ing = ingArchi.leer(pos); //trae el ingrediente a memoria y lo informa
                        cout << left << setw(25) << ing.getNombreIngrediente();
                        cout << setw(10) << detalleIng.getCantidadPorProducto();
                        cout << setw(10) << ing.getTipoDeUnidad() << endl;
                    }
                }
                cout << "==============================================" << endl << endl;
            }
        }
        else if (!estado){ ///si se envia por parametro un valor falso, muestra los inactivos
            if(!prod.getEstado() && prod.getIdCategoria() != 3){ //las bebidas no se listan // si se envia false por parametro, muestra los inactivos
                cout << "==============================================" << endl;
                cout << "ID Producto: " << prod.getIdProducto() << endl;
                cout << "Nombre: " <<  prod.getNombreProducto() << endl;
                cout << "Ingredientes: " << endl;
                cout << "----------------------------------------------" << endl;
                cout << left << setw(25) << "Nombre Ingrediente";
                cout << setw(10) << "Cantidad";
                cout << setw(10) << "Unidad" << endl;

                for (int j=0; j<cantRegistrosDetalleIngrediente; j++){ //recorre el archivo detalle de ingredientes
                    detalleIng = detalleArchi.leer(j);
                    if(!detalleIng.getEstado() && detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
                        pos = ingArchi.buscar(detalleIng.getIdIngrediente());//lo busca en el archivo de ingredientes
                        ing = ingArchi.leer(pos); //trae el ingrediente a memoria y lo informa
                        cout << left << setw(25) << ing.getNombreIngrediente();
                        cout << setw(10) << detalleIng.getCantidadPorProducto();
                        cout << setw(10) << ing.getTipoDeUnidad() << endl;
                    }
                }
                cout << "==============================================" << endl << endl;
            }
        }
    }
}

void ProductosManager::listarProductosPorCategoria(int idCategoria){
    ArchivoProducto prodArchi;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    Producto prod;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    int cantRegistrosProducto, cantRegistrosDetalleIngrediente, pos;
    int productosDisponibles;
    cantRegistrosProducto = prodArchi.getCantidadRegistros();
    cantRegistrosDetalleIngrediente = detalleArchi.getCantidadRegistros();

    cout << left << setw(15) << "ID Producto";
    cout << setw(15) << "ID Categoria";
    cout << setw(30) << "Nombre del producto";
    cout << setw(20) << "Precio de venta";
    cout << setw(20) << "Costo de preparacion" << endl;

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;//180 caracteres

    for (int i=0; i<cantRegistrosProducto; i++){ //recorre el archivo de productos
        prod = prodArchi.leer(i);
        if(prod.getIdCategoria() == idCategoria && prod.getEstado() == true){ ///filtro por categoria y por productos activos.
            prod.mostrarEnLista();
            for (int j=0; j<cantRegistrosDetalleIngrediente; j++){ //recorre el archivo detalle de ingredientes
                detalleIng = detalleArchi.leer(j);
                if(detalleIng.getEstado() && detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
                    pos = ingArchi.buscar(detalleIng.getIdIngrediente());//lo busca en el archivo de ingredientes
                    ing = ingArchi.leer(pos); //trae el ingrediente a memoria y lo informa
                    productosDisponibles = ing.getCantidadStock() / detalleIng.getCantidadPorProducto(); //NO APLICA PARA BEBIDAS

                    if(idCategoria!= 3 && productosDisponibles<= 10){
                        cout << "Alerta: Stock bajo de " << ing.getNombreIngrediente() << " Alcanza para " << productosDisponibles << " " << prod.getNombreProducto() << " mas.";
                    }
                    else if (idCategoria == 3 && ing.getCantidadStock() <= 10){
                        cout << "Alerta: Stock bajo de " << ing.getNombreIngrediente() << " Solo quedan " << ing.getCantidadStock() << " Unidades.";
                    }
                }
            }
            cout << endl;
        }
    }
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;//180 caracteres

}

bool ProductosManager::listarProductosPorIngredientes(){
    Ingrediente ing;
    ArchivoDetalleIngrediente archivoDetalleIng;
    DetalleIngrediente detalleIng;
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ingrediente;
    ArchivoProducto archivoProducto;
    Producto producto;
    int cantRegistrosDetalleIng = archivoDetalleIng.getCantidadRegistros();
    int cantRegistrosIng = archivoIngrediente.getCantidadRegistros();
    int posicion;
    bool encontrado = false;
    Validador validador;
    string nombreIngrediente;
    cout << "Escriba el nombre del ingrediente y a continuacion se listaran los productos que lo contengan: ";
    cin.ignore();
    getline(cin,nombreIngrediente);

    for (int i=0; i< cantRegistrosDetalleIng; i++){ //recorro todo el archivo de detalle de ingredientes (recetas) donde hay un registro por cada ingrediente que contenga cada producto
        detalleIng = archivoDetalleIng.leer(i);
        if (detalleIng.getEstado()){  //filtro de detalles activos.
            posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
            ing = archivoIngrediente.leer(posicion); //busca ese ID de ingrediente dentro del archivo de ingredientes y lo instancia para obtener el nombre
            if(ing.getEstado() && validador.contiene(nombreIngrediente, ing.getNombreIngrediente() ) ){  //Si el ingrediente esta activo y Si coincide el patron ingresado con el nombre del ingrediente devuelve true
                posicion = archivoProducto.buscar(detalleIng.getIdProducto());
                producto = archivoProducto.leer(posicion); //una vez que esta asegurada la coincidencia, se instancia el producto para obtener todos los datos para la venta
                if(producto.getEstado()){ //por ultimo, si tambien el producto esta activo, se muestra el producto y sus ingredientes.
                    mostrarProductoYReceta(producto);
                    encontrado=true;
                    return true;
                }
            }
        }
    }
    if(!encontrado){
        cout << "Ningun producto activo contiene el ingrediente mencionado..." << endl << endl;
        return false;
    }
}

void ProductosManager::mostrarProductoYReceta(Producto &producto){
    ArchivoDetalleIngrediente archivoDetalleIng;
    ArchivoIngrediente archivoIngrediente;
    DetalleIngrediente detalleIng;
    Ingrediente ing;
    int posicion;
    int cantRegistrosDetalleIng = archivoDetalleIng.getCantidadRegistros();


    cout << "==============================================" << endl;
    cout << "ID Producto: " << producto.getIdProducto() << endl;
    cout << "Nombre: " <<  producto.getNombreProducto() << endl;
    cout << "Precio de venta: $" << producto.getPrecioUnitario() << endl;
    cout << "Ingredientes: " << endl;
    cout << "----------------------------------------------" << endl;
    cout << left << setw(25) << "Nombre Ingrediente";
    cout << setw(10) << "Cantidad";
    cout << setw(10) << "Unidad" << endl;
    for (int i=0; i< cantRegistrosDetalleIng; i++){ //Bucle solo para mostrar todos los ingredientes que tiene ese producto
        detalleIng = archivoDetalleIng.leer(i); //se instancian nuevamente las recetas
        if(detalleIng.getIdProducto() == producto.getIdProducto()){ //Si las instancias son iguales al producto hallado anteriormente que coincide con el patron buscado:

            posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
            ing = archivoIngrediente.leer(posicion); //instancio cada ingrediente que contiene ese producto y lo muestro
            cout << left << setw(25) << ing.getNombreIngrediente();
            cout << setw(10) << detalleIng.getCantidadPorProducto();
            cout << setw(10) << ing.getTipoDeUnidad() << endl;
        }
    }
    cout << "==============================================" << endl << endl;
    cout << endl << endl;
}

void ProductosManager::rankingProductosMasVendidos(){
    Fecha fechaDesde,fechaHasta;
    Venta venta;
    DetalleVenta detalleVenta;
    VentaArchivo archivoVenta;
    DetalleVentaArchivo archivoDetalleVenta;
    Producto producto;
    ArchivoProducto archivoProducto;
    Validador validador;
    int cantRegistrosProducto = archivoProducto.getCantidadRegistros();
    int cantRegistrosDetalleVenta = archivoDetalleVenta.getCantidadRegistros();
    int cantRegistrosVenta = archivoVenta.getCantidadRegistros();
    int posicion;


    int* vectorProductosVendidos = nullptr;
    int* vectorIdProductosVendidos = nullptr;
    vectorProductosVendidos = new int [cantRegistrosProducto] ;
    vectorIdProductosVendidos = new int [cantRegistrosProducto];
    if(vectorProductosVendidos == nullptr || vectorIdProductosVendidos == nullptr){
        cout << "Ocurrio un error en el sistema" << endl;
        return;
    }

    for (int i=0; i < cantRegistrosProducto; i++){
        vectorProductosVendidos[i] = 0;
        vectorIdProductosVendidos[i] = 0;
    }

    validador.validadorFiltroFecha(fechaDesde,fechaHasta);
    for (int i=0; i < cantRegistrosVenta; i++){
        venta = archivoVenta.leer(i);

        for (int j=0; j < cantRegistrosDetalleVenta; j++){
            detalleVenta = archivoDetalleVenta.leer(j);
            if(venta.getFechaVenta() <= fechaHasta && venta.getFechaVenta() >= fechaDesde
            && venta.getNroFactura() == detalleVenta.getNroFactura() ){
                vectorProductosVendidos[detalleVenta.getIdProducto() -1] += detalleVenta.getCantProducto();
                vectorIdProductosVendidos[detalleVenta.getIdProducto() -1] = detalleVenta.getIdProducto();

            }
        }
    }

    int auxId, auxCantProductos;
    ///Metodo burbujeo, en cada vuelta de I coloca el valor maximo en la posicion de I.
    for(int i=0; i<cantRegistrosProducto; i++){
        for(int j = i+1; j<cantRegistrosProducto; j++){
            if(vectorProductosVendidos[j] > vectorProductosVendidos[i]){
                //intercambio de cantidades
                auxCantProductos = vectorProductosVendidos[j];
                vectorProductosVendidos[j] = vectorProductosVendidos[i];
                vectorProductosVendidos[i] = auxCantProductos;
                //intercambio de Ids
                auxId = vectorIdProductosVendidos[j];
                vectorIdProductosVendidos[j] = vectorIdProductosVendidos[i];
                vectorIdProductosVendidos[i] = auxId;
            }
        }
    }
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout << "RANKING DE PRODUCTOS VENDIDOS DESDE: " <<  fechaDesde.getDia() << "/" << fechaDesde.getMes() << "/" << fechaDesde.getAnio() << ", HASTA: " <<   fechaHasta.getDia() << "/" << fechaHasta.getMes() << "/" << fechaHasta.getAnio() << endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl << endl;
    cout << left << setw(10) << "Posicion" << setw(19) << "Cantidad vendida" << setw(10) << "Nombre del producto" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    for (int i=0; i < 10 ; i++){
        if(vectorProductosVendidos[i] > 0){
            posicion = archivoProducto.buscar(vectorIdProductosVendidos[i]);
            producto = archivoProducto.leer(posicion);
            cout << left << setw(1) << "#" << setw (9) << i+1 << setw(19) << vectorProductosVendidos[i] << setw(10) << producto.getNombreProducto() << endl;
        }
    }
    cout <<  "--------------------------------------------------------------------------------" << endl << endl;


   ///marcosssssssssss
}


void ProductosManager::cantidadProductosVendidosPorFecha(){
    Fecha fechaDesde,fechaHasta;
    Venta venta;
    DetalleVenta detVenta;
    VentaArchivo archiVenta;
    DetalleVentaArchivo archiDetalleV;
    Producto producto;
    ArchivoProducto archiProd;
    Validador validador;


    int cantidadProductos = archiProd.getCantidadRegistros();

    int* vectorProductosVendidos = nullptr;
    vectorProductosVendidos = new int[cantidadProductos];

    if(vectorProductosVendidos==nullptr){
        cout << "Ocurrio un error en el sistema. "<< endl;
        return;
    }else{
        for (int i=0; i<cantidadProductos; i++){
            vectorProductosVendidos[i]=0;
        }
    }



    int cantidadDetallesVenta = archiDetalleV.getCantidadRegistros();
    int cantidadVentas = archiVenta.getCantidadRegistros();
    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0; i<cantidadVentas; i++){
        venta = archiVenta.leer(i);
        for (int x=0; x<cantidadDetallesVenta;x++){
            detVenta = archiDetalleV.leer(x);

            if (venta.getFechaVenta() <= fechaHasta ){ ///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
                if (venta.getFechaVenta() >= fechaDesde ){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
                    if(venta.getNroFactura() == detVenta.getNroFactura()){
                        vectorProductosVendidos[detVenta.getIdProducto()-1] +=  detVenta.getCantProducto();
                    }
                }
            }

        }
    }
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout << "CANTIDAD DE PRODUCTOS VENDIDOS DESDE: " <<  fechaDesde.getDia() << "/" << fechaDesde.getMes() << "/" << fechaDesde.getAnio() << ", HASTA: " <<   fechaHasta.getDia() << "/" << fechaHasta.getMes() << "/" << fechaHasta.getAnio() << endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl << endl;
    for(int i=0; i<cantidadProductos; i++){
            producto = archiProd.leer(i);
            if(vectorProductosVendidos[i]>0){
                cout<< "PRODUCTO ID: " << i+1 << " | " <<  producto.getNombreProducto() << ". Cantidad: "<< vectorProductosVendidos[i] << endl;
            }
    }
    delete[]vectorProductosVendidos;
}
