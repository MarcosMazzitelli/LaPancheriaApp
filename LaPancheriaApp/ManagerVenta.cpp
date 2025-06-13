#include <string>
#include <iostream>
#include "ManagerVenta.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Cliente.h"
#include "ArchivoCliente.h"
#include "FormaDePago.h"
#include "FormaDePagoArchivo.h"
#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "DetalleVenta.h"
#include "DetalleVentaArchivo.h"
#include "Fecha.h"
#include "PersonaManager.h"
#include "Utilidades.h"
#include "ArchivoIngrediente.h"
#include "Ingrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include <vector>

using namespace std;



void ManagerVenta::registrarVenta(std::string dniEmpleado){

    int nroFactura,idEmpleado,formaDePago,dia,mes,anio;
    FormaDePagoArchivo fdpArchi;
    FormaDePago fdp;
    int posArchiFdp;
    string dniCliente; //Cliente client; /ClienteArchivo aCliente;
    float importeTotal=0;
    float importeBruto, importePorProducto;
    VentaArchivo ventaArchi;
    DetalleVentaArchivo archiDetVenta;
    ArchivoEmpleado empArchi;
    PersonaManager pManager;
    Empleado emp;
    Fecha fechaVenta;
    Venta v;
    int pos;
    DetalleVenta detVenta;
    Producto prod;
    int cantidad, opcion, posIngArchi, posArchiDetIng;
    vector<DetalleVenta> vecDetalleVenta;
    ArchivoIngrediente ingArchi;
    Ingrediente ing;
    DetalleIngrediente detIng;
    ArchivoDetalleIngrediente archiDetIng;
    float cantidadIngredientePorProducto;
    int cantidadVendida;

    nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico

    pManager.cargarCliente(dniCliente);

    pos = empArchi.buscar(dniEmpleado);
    emp= empArchi.leer(pos);
    idEmpleado = emp.getIdEmpleado();


    ///carga de productos
    ProductosManager prodManager;
    int idProducto;
    bool cargaProductos=false;
    bool validacion=false;
    while (!cargaProductos){ ///ciclo para ingresar productos a una venta
        ArchivoProducto archiProd;
        prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
        cout << "Seleccione el producto que desee agregar: ";
        cin >> idProducto;

        while (idProducto < 0 || idProducto > prodManager.cantidadRegistrosProducto()){
            cout << "Ingrese un Id de ingrediente valido" << endl << endl;
            prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
            cout << "Seleccione el producto que desee agregar: ";
            cin >> idProducto;
        }
        validacion=false;
        while (!validacion){
            int posicion;
            posicion = archiProd.buscar(idProducto);
            prod = archiProd.leer(posicion);
            cout << "Ingrese la cantidad del producto " << prod.getNombreProducto() << " a vender: ";
            cin >> cantidad;
            if(cantidad<0){
                cout << "Ingrese una cantidad valida" << endl << endl;
            }
            else{
                validacion=true; ///fin del while de validacion
            }
        }
        // a partir de aca esta OK el ingreso de productos

        // en caso de cerrar la consola antes de terminar de cargar el producto, los ingredientes quedan guardados en el archivo
        importePorProducto = prod.getPrecioUnitario()*cantidad;
        importeBruto += importePorProducto;
        detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), importeBruto);

        vecDetalleVenta.push_back(detVenta);

        opcion = pedirYValidarConfirmacion("Desea ingresar mas productos? \n1) si \n0) no \n\n");
        if(opcion == 0){
            cargaProductos=true;
        }
    }

    fdp.elegirFormaDePago(formaDePago);
    posArchiFdp = fdpArchi.buscarFormaDePago(formaDePago);
    fdp = fdpArchi.leer(posArchiFdp);
    importeTotal = importeBruto - (importeBruto * fdp.getDescuento() );
    cout<<"ingrese la fecha de venta : "<<endl;

    while(!fechaVenta.cargar()){
        fechaVenta.cargar();
    }


    v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

    ///fin carga de productos
    int tam = vecDetalleVenta.size();
    opcion = pedirYValidarConfirmacion("Desea registrar la venta? \n1) si \n0) no \n\n");
    if(opcion == 1){
        if (ventaArchi.guardar(v)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }
        descontarStock(vecDetalleVenta, tam);
        /*for (int i=0; i < vecDetalleVenta.size() ; i++){
            if(archiDetVenta.guardar(vecDetalleVenta[i])){
                cout << "Producto guardado correctamente." << endl << endl;
               // posArchiDetIng = archiDetIng.buscar(vecDetalleVenta[i].getIdProducto());
                for (int j=0; j < archiDetIng.getCantidadRegistros(); j++){  ///recorre el archivo detalle de ingredientes (o recetas)
                    /**detIng = archiDetIng.leer(j);
                    if (vecDetalleVenta[i].getIdProducto() == detIng.getIdProducto() ){ //si coincide un producto vendido con alguna receta, traigo el ingrediente y me guardo la posicion en archivo de ingrediente para obtener el stock
                        posIngArchi = ingArchi.buscar(detIng.getIdIngrediente());//busco el id obtenido en el detalleIng
                        if (posIngArchi >= 0){ //si existe esa posicion en el archivo de ingredientes, leo la instancia y desciento el stock
                            ing = ingArchi.leer(posIngArchi);
                            cantidadVendida = vecDetalleVenta[i].getCantProducto();
                            cantidadIngredientePorProducto = cantidadVendida * detIng.getCantidadPorProducto();
                            ing.descontarStock(cantidadIngredientePorProducto);
                            if (ingArchi.modificar(ing, posIngArchi)){

                                cout << "Stock descontado correctamente." << endl;
                            }
                            else{
                                cout << "No se ha podido descontar el stock." << endl;
                            }
                        }
                        else{
                            cout << "No se encontro ninguna receta con ese ID de ingrediente" << endl;
                        }
                    }
                }
            }
            else{
                cout << "Hubo un problema al guardar el registro." << endl << endl;
            }
        }  */
    }
}

void ManagerVenta::descontarStock(std::vector<DetalleVenta> &vecDetalleVenta, int tam){
    ArchivoDetalleIngrediente archivoDetalleIng;
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    DetalleVentaArchivo archivoDetalleVenta;
    int posicion;
    float cantidadProductoPorReceta, stockADescontar;
    int cantidadProducto;


    for (int i=0; i < tam; i++){//for de productos distintos de mi venta
        if(archivoDetalleVenta.guardar(vecDetalleVenta[i])){
                cout << "Producto guardado correctamente." << endl << endl;
        }
        vecDetalleVenta[i].mostrar();
        //leo una instancia de detalle venta
        for(int j=0; j < archivoDetalleIng.getCantidadRegistros(); j++){
            detalleIng = archivoDetalleIng.leer(j);
            if(vecDetalleVenta[i].getIdProducto() == detalleIng.getIdProducto()){ // si el producto vendido me coincide con el detalle recorrido en el for:
                cantidadProductoPorReceta = detalleIng.getCantidadPorProducto(); //traigo la cantidad de ingrediente que lleva ese producto vendido
                cantidadProducto = vecDetalleVenta[i].getCantProducto(); //traigo la cantidad de ese producto vendido
                stockADescontar = cantidadProducto * cantidadProductoPorReceta; //obtengo la cantidad total de ingrediente. luego la descuento.
                posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
                cout << posicion << endl;
                if (posicion >= 0){ //hacer >= cuando se actualicen los .dat
                    ing = archivoIngrediente.leer(posicion);
                    ing.descontarStock(stockADescontar);
                    cout << "Stock descontado correctamente." << endl << endl;
                    if (archivoIngrediente.modificar(ing,posicion)){
                        cout << "Registro guardado" << endl;
                    }
                    else{
                        cout << "Error al guardar stock "<< endl;
                    }
                }
                else{
                    cout << "No se ha encontrado el ingrediente en el archivo" << endl;
                }
            }

        }
    }
}
/*        for (int i=0; i < vecDetalleIngredientes.size(); i++){
            if(detalleArchi.guardar(vecDetalleIngredientes[i])){
                cout << "Ingrediente aniadido a la receta correctamente." << endl;
                /**posicion = ingArchi.buscar(vecDetalleIngredientes[i].getIdIngrediente());
                ing = ingArchi.leer(posicion);//instancia de ingrediente traida a memoria
                ing.descontarStock(vecDetalleIngredientes[i].getCantidadPorProducto() ); //es un solo parametro, descuenta la cantidad del stock que se coloca en el pancho
                if(ingArchi.modificar(ing, posicion)){
                    cout << "Stock descontado correctamente." << endl;  /// ESTO SE DEBE EJECUTAR POR CADA DETALLE DE VENTA. vecDetalleIngredientes se reemplaza por un vector de detalle ventas.
                }
            }
            else{
*/





int ManagerVenta::cantidadRegistros(){

VentaArchivo archi;
int cant;


cant= archi.getCantidadRegistros();
return cant;


}


void ManagerVenta::listarVenta(){

VentaArchivo archi;
Venta vent;

int cantRegistros = cantidadRegistros();
vent.mostrarTabla();
cout<<endl;
cout<<"================================================================================================"<<endl;
for (int i=0;i<cantRegistros;i++){
    if(cantRegistros ==0){
        cout<<"No se encontraron registros. "<<endl;
    }else{
    vent = archi.leer(i);
    vent.mostrarEnLista();
    cout<<endl <<endl;}
}
}

void ManagerVenta::listarVentaFecha(){
Venta vent;
Fecha aux;
VentaArchivo  archi;

int cantRegistro=archi.getCantidadRegistros();
int cont=0;

cout<<"LISTADO DE VENTA POR FECHA"<<endl;
while(!aux.cargar()){
    aux.cargar();
}
cout<<endl<<"Listado de Ventas: "<<endl;
cout<<endl;
vent.mostrarTabla();
for(int i=0;i<cantRegistro;i++){

    vent=archi.leer(i);

    if(aux.getDia()== vent.getFechaVenta().getDia()&&aux.getMes()== vent.getFechaVenta().getMes()&&aux.getAnio()== vent.getFechaVenta().getAnio()){
        cont++;

        cout<<endl;
        cout<<"=============================================================================================================="<<endl;
        vent.mostrarEnLista();
    }
}
if(cont==0){
    cout<<"No hay ventas registradas en esta fecha. "<<endl;
}
}
