#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "ArchivoIngrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include "IngredientesManager.h"
#include "Ingrediente.h"
#include "Utilidades.h"
//#include <vector>
#include <iomanip>
#include <iostream>
#include "Validador.h"
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

void ProductosManager::incorporarIngredientes(int idProducto, float &costoProducto, std::vector<DetalleIngrediente> &vecDetalleIngredientes){
    IngredientesManager ingManager;
    int idIngrediente, posicion;
    DetalleIngrediente detalleIng;
    ArchivoIngrediente ingArchi;
    Ingrediente ing;
    float cantidadPorProducto;


    bool cargaIngredientes=false;
    int opcion;
    while (!cargaIngredientes){ ///ciclo para ingresar ingredientes de un producto
        cout << "A continuacion se listaran los ingredientes disponibles para agregar a su producto." << endl;
        system("pause");
        system("cls");
        ingManager.listarIngredientes(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
        cout << "Seleccione el ID del ingrediente que desee agregar: " << endl << endl;
        cin >> idIngrediente;
        while(cin.fail() || idIngrediente < 1 || idIngrediente > ingManager.cantidadRegistros()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            ingManager.listarIngredientes();
            cout << "Seleccione el ID del ingrediente que desee agregar: ";
            cin >> idIngrediente;
        }
        posicion = ingArchi.buscar(idIngrediente);
        ing = ingArchi.leer(posicion);
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

        // en caso de cerrar la consola antes de terminar de cargar el producto, los ingredientes quedan guardados en el archivo
        detalleIng = DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto); //
        vecDetalleIngredientes.push_back(detalleIng);

        //ac� se guarda UN ingrediente en el detalle
        opcion = pedirYValidarConfirmacion("\nDesea agregar mas ingredientes? \n1)Si \n0)No \n\n");
        if(opcion==0){
            cargaIngredientes=true; //fin del while general de carga de ingredientes
        }
    }

}

void ProductosManager::crearPanchoOGuarnicion(int idCategoria){
    Producto prod;
    ArchivoDetalleIngrediente detalleArchi;
    //ArchivoIngrediente ingArchi; solo lo usamos si descontamos stock y no corresponde
    //Ingrediente ing; solo lo usamos si descontamos stock y no corresponde
    //int posicion; solo lo usamos si descontamos stock y no corresponde
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

    idProducto=cantidadRegistrosProducto()+1; //autonumerico

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
                cout << "Ingrediente aniadido a la receta correctamente." << endl;
                /**posicion = ingArchi.buscar(vecDetalleIngredientes[i].getIdIngrediente());
                ing = ingArchi.leer(posicion);//instancia de ingrediente traida a memoria
                ing.descontarStock(vecDetalleIngredientes[i].getCantidadPorProducto() ); //es un solo parametro, descuenta la cantidad del stock que se coloca en el pancho
                if(ingArchi.modificar(ing, posicion)){
                    cout << "Stock descontado correctamente." << endl;  /// ESTO SE DEBE EJECUTAR POR CADA DETALLE DE VENTA. vecDetalleIngredientes se reemplaza por un vector de detalle ventas.
                } */
            }
            else{
                cout << "Hubo un problema al guardar el registro." << endl << endl;
            }
        }
        if (prodArchi.guardar(prod)){
            cout << "Producto guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
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
    //int posicion; solo lo usamos si descontamos stock y no corresponde
    ArchivoProducto prodArchi;
    vector<DetalleIngrediente> vecDetalleIngredientes;
    int idProducto, idIngrediente, opcion;
    string nombreProducto, nombreIngrediente, tipoDeUnidad;
    float precioUnitario, precioSugerido, cantidadStock, costoTotal, costoUnitario;
    bool estado = true;
    int cantidadPorProducto;

    cout << "Ingrese el nombre de la bebida: ";
    cin.ignore();
    getline(cin,nombreProducto);
    nombreIngrediente = nombreProducto;

    idProducto=cantidadRegistrosProducto()+1; //autonumerico
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

    cantidadPorProducto = 1;

    ///FIN DE CARGA DEL PRODUCTO Y SU RECETA:
    prod = Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoUnitario, estado);
    ing = Ingrediente(idIngrediente,nombreIngrediente,cantidadStock, costoUnitario, tipoDeUnidad,estado);
    detalleIng = DetalleIngrediente(idProducto, idIngrediente, cantidadPorProducto); //

    opcion = pedirYValidarConfirmacion();
    if(opcion==1){ //si confirma, se guardan los detalles de ingredientes (receta) y el producto
        if (prodArchi.guardar(prod)){
            cout << "Producto guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }
        if(ingArchi.guardar(ing)){
            cout << "Stock a�adido correctamente." << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl;
            }
        if (detalleArchi.guardar(detalleIng)){
            cout << "Ingrediente vinculado correctamente." << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl;
        }
    }
    else{ //si no desea guardar la receta:
        cout << "Creacion de bebida descartada..." << endl << endl;
    }
}



void ProductosManager::crearProducto(){
    Producto prod;
    DetalleIngrediente detalleIng;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    ArchivoProducto prodArchi;
    IngredientesManager ingManager;
    Ingrediente ing;
    vector<DetalleIngrediente> vecDetalleIngredientes;
    int idProducto, idCategoria, idIngrediente, posicion;
    string nombreProducto;
    float precioUnitario, cantidadPorProducto, precioSugerido;
    float costoProducto=0;
    bool estado = true;


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
                        cout << endl << "Registro guardado correctamente." << endl << endl;
                    }
                    else{
                        cout << endl <<"Hubo un error al guardar el registro." << endl << endl;
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
    ArchivoProducto prodArchi;


    cout << "\r\r MENU MODIFICACION" << endl << endl;
    listarProductos();
    cout << "Ingrese el ID del producto a modificar: ";
    cin >> idProducto;
    listarProductos();
    while(cin.fail() || idProducto <= 0 || idProducto > cantidadRegistrosProducto()+1){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        system("pause");
        system("cls");
        cout << "\r\r MENU MODIFICACION" << endl << endl;
        listarProductos();
        cout << "Ingrese el ID del producto a modificar: ";
        cin >> idProducto;
    }
    pos = prodArchi.buscar(idProducto);

    if (pos > 0){
        prod = prodArchi.leer(pos);

        if(prod.getEstado() == true){
            system("cls");
            menuModificacion(prod, pos);

        }
        else{
            cout << "El producto se encuentra dado de baja." << endl;
            prod.mostrar();
            opcion = pedirYValidarConfirmacion("\nDesea darlo de alta? \n1)Si \n0)No \n");
            if (opcion == 1){
                prod.setEstado(true);
                if(prodArchi.modificar(prod, pos)){
                    cout << "El producto ha sido dado de alta." << endl << endl;
                }
                else{
                    cout << "Hubo un error al guardar el registro." << endl << endl;
                }
            }
            else{
                cout << "Saliendo sin guardar..." << endl << endl;
            }
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
    cantRegistros = cantidadRegistrosProducto();

    for (int i=0; i<cantRegistros; i++){
        prod = prodArchi.leer(i);
        prod.mostrar();
        cout << endl << endl;
    }

}

void ProductosManager::listarProductos(){
    ArchivoProducto prodArchi;
    Producto prod;
    int cantRegistros;
    cantRegistros = cantidadRegistrosProducto();


    cout << left << setw(15) << "ID Producto";
    cout << setw(15) << "ID Categoria";
    cout << setw(30) << "Nombre del producto";
    cout << setw(20) << "Precio de venta";
    cout << setw(20) << "Costo de preparacion" << endl;

    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres
    for (int i=0; i<cantRegistros; i++){
        prod = prodArchi.leer(i);
        prod.mostrarEnLista();
        cout << endl;
    }
    cout << "----------------------------------------------------------------------------------------------------" << endl;//110 caracteres


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
    cantRegistrosDetalleIngrediente = cantidadRegistrosDetalleIngredientes();

    for (int i=0; i<cantRegistrosProducto; i++){ //recorre el archivo de productos
        prod = prodArchi.leer(i);
        if(prod.getIdCategoria() != 3){ //las bebidas no se listan
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
                if(detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
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

void ProductosManager::listarProductosPorCategoria(int idCategoria){
    ArchivoProducto prodArchi;
    ArchivoDetalleIngrediente detalleArchi;
    ArchivoIngrediente ingArchi;
    Producto prod;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    int cantRegistrosProducto, cantRegistrosDetalleIngrediente, pos;
    int productosDisponibles;
    cantRegistrosProducto = cantidadRegistrosProducto();
    cantRegistrosDetalleIngrediente = cantidadRegistrosDetalleIngredientes();

    cout << left << setw(15) << "ID Producto";
    cout << setw(15) << "ID Categoria";
    cout << setw(30) << "Nombre del producto";
    cout << setw(20) << "Precio de venta";
    cout << setw(20) << "Costo de preparacion" << endl;

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;//180 caracteres

    for (int i=0; i<cantRegistrosProducto; i++){ //recorre el archivo de productos
        prod = prodArchi.leer(i);
        if(prod.getIdCategoria() == idCategoria && prod.getEstado() == true){
            prod.mostrarEnLista();
            for (int j=0; j<cantRegistrosDetalleIngrediente; j++){ //recorre el archivo detalle de ingredientes
                detalleIng = detalleArchi.leer(j);
                if(detalleIng.getIdProducto() == prod.getIdProducto()){ //Si encuentra el ID del producto en el archivo detalle de ingredientes
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

void ProductosManager::listarProductosPorIngredientes(){
    Ingrediente ing;
    ArchivoDetalleIngrediente archivoDetalleIng;
    DetalleIngrediente detalleIng;
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ingrediente;
    ArchivoProducto archivoProducto;
    Producto producto;
    int cantRegistrosDetalleIng = cantidadRegistrosDetalleIngredientes();
    int cantRegistrosIng = archivoIngrediente.getCantidadRegistros();
    int posicion;
    Validador validador;
    string nombreIngrediente;
    cout << "Escriba el nombre del ingrediente y a continuacion se listaran los productos que lo contengan: ";
    cin.ignore();
    getline(cin,nombreIngrediente);

    for (int i=0; i< cantRegistrosDetalleIng; i++){ //recorro todo el archivo de detalle de ingredientes (recetas) donde hay un registro por cada ingrediente que contenga cada producto
        detalleIng = archivoDetalleIng.leer(i);

        posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
        ing = archivoIngrediente.leer(posicion); //busca ese ID de ingrediente dentro del archivo de ingredientes y lo instancia para obtener el nombre
        if(validador.contiene(nombreIngrediente, ing.getNombreIngrediente() ) ){  //Si coincide el patron ingresado con el nombre del ingrediente devuelve true
            posicion = archivoProducto.buscar(detalleIng.getIdProducto());
            producto = archivoProducto.leer(posicion); //una vez que esta asegurada la coincidencia, se instancia el producto para obtener todos los datos para la venta

            cout << "==============================================" << endl;
            cout << "ID Producto: " << producto.getIdProducto() << endl;
            cout << "Nombre: " <<  producto.getNombreProducto() << endl;
            cout << "Precio de venta: $" << producto.getPrecioUnitario() << endl;
            cout << "Ingredientes: " << endl;
            cout << "----------------------------------------------" << endl;
            cout << left << setw(25) << "Nombre Ingrediente";
            cout << setw(10) << "Cantidad";
            cout << setw(10) << "Unidad" << endl;
            for (int j=0; j< cantRegistrosDetalleIng; j++){ //Bucle solo para mostrar todos los ingredientes que tiene ese producto
                detalleIng = archivoDetalleIng.leer(j); //se instancian nuevamente las recetas
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
    }
}
