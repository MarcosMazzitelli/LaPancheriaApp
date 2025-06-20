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

    FormaDePagoArchivo fdpArchi;
    ArchivoProducto archiProd;
    VentaArchivo ventaArchi;
    DetalleVentaArchivo archiDetVenta;
    ArchivoEmpleado empArchi;

    Fecha fechaVenta;
    Empleado emp;
    Producto prod;
    Venta v;
    FormaDePago fdp;
    DetalleVenta detVenta;

    PersonaManager personaManager;
    ProductosManager prodManager;

    int nroFactura,idEmpleado,formaDePago;
    int posArchiFdp;
    string dniCliente; //Cliente client; /ClienteArchivo aCliente;
    float importeTotal=0;
    float importeBruto, ImporteProdxCantidad;
    int posicionEmpleado, posicionProducto;
    int cantidad, opcion;
    int idProducto;
    vector<DetalleVenta> vecDetalleVenta;

    nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico

    personaManager.cargarCliente(dniCliente);

    posicionEmpleado = empArchi.buscar(dniEmpleado);
    emp= empArchi.leer(posicionEmpleado);
    idEmpleado = emp.getIdEmpleado();


    bool cargaProductos=false;
    while (!cargaProductos){ ///ciclo para ingresar productos a una venta
        prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)

        cout << "Seleccione el producto que desee agregar: ";
        cin >> idProducto;
        while (cin.fail() || idProducto < 1 || idProducto > prodManager.cantidadRegistrosProducto()){
            cout << "Ingrese un Id de producto valido" << endl << endl;
            system("pause");
            system("cls");
            prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
            cout << "Seleccione el producto que desee agregar: ";
            cin >> idProducto;
        }
        posicionProducto = archiProd.buscar(idProducto);
        prod = archiProd.leer(posicionProducto);
        cout << "Ingrese la cantidad del producto " << prod.getNombreProducto() << " a vender: ";
        cin >> cantidad;
        while (cin.fail() || cantidad <= 0){
            cout << "Ingrese una cantidad valida." << endl << endl;
            system("pause");
            system("cls");
            cout << "Ingrese la cantidad del producto " << prod.getNombreProducto() << " a vender: ";
            cin >> cantidad;
        }
        /// a partir de aca esta OK el ingreso de productos

        ImporteProdxCantidad = prod.getPrecioUnitario()*cantidad;
        importeBruto += ImporteProdxCantidad; //Acumulador por todos los detalles que tenga una venta... se utiliza en ventas.
        detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), ImporteProdxCantidad);
        vecDetalleVenta.push_back(detVenta); //se aumenta el tama�o del vector y se coloca al final el nuevo detalle de venta

        opcion = pedirYValidarConfirmacion("Desea ingresar mas productos? \n1) si \n0) no \n\n");
        if(opcion == 0){
            cargaProductos=true;
            ///fin carga de productos
        }
    }

    fdp.elegirFormaDePago(formaDePago);
    posArchiFdp = fdpArchi.buscarFormaDePago(formaDePago);
    fdp = fdpArchi.leer(posArchiFdp);
    importeTotal = importeBruto - (importeBruto * fdp.getDescuento() );
    cout<<"ingrese la fecha de venta : "<<endl;

    while(!fechaVenta.cargar()){
        cout << "Ingrese una fecha valida." << endl << endl;
        system("pause");
        system("cls");
        cout<<"ingrese la fecha de venta : "<<endl;
        fechaVenta.cargar();
    }


    v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

    opcion = pedirYValidarConfirmacion("Desea registrar la venta? \n1) si \n0) no \n\n");
    if(opcion == 1){
        if (ventaArchi.guardar(v)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }
        descontarStock(vecDetalleVenta);
    }
}

void ManagerVenta::descontarStock(std::vector<DetalleVenta> &vecDetalleVenta){
    ArchivoDetalleIngrediente archivoDetalleIng;
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    DetalleVentaArchivo archivoDetalleVenta;
    int posicion;
    float cantidadProductoPorReceta, stockADescontar;
    int cantidadProducto;


    for (int i=0; i < vecDetalleVenta.size(); i++){//for de productos distintos de mi venta
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



///pruebaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void ManagerVenta::cargaMasivaVentas(std::string dniEmpleado){

    FormaDePagoArchivo fdpArchi;
    ArchivoProducto archiProd;
    VentaArchivo ventaArchi;
    ArchivoEmpleado empArchi;
    ArchivoCliente archivoCliente;

    Fecha fechaVenta;
    Empleado emp;
    Producto prod;
    Venta v;
    FormaDePago fdp;
    DetalleVenta detVenta;
    Cliente cliente;

    PersonaManager personaManager;
    ProductosManager prodManager;

    int nroFactura,idEmpleado,formaDePago;
    float descuento;
    int posArchiFdp;
    float importeTotal=0;
    float importeBruto, ImporteProdxCantidad;
    int posicionEmpleado, posicionProducto, posicionCliente;
    int cantidad, opcion;
    int idProducto;
    vector<DetalleVenta> vecDetalleVenta;

    string nombreCliente, apellidoCliente, dniCliente;


    nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico


    cin.ignore();
    getline(cin,dniCliente);
    posicionCliente = archivoCliente.buscar(dniCliente);

    if(posicionCliente < 0){

        getline(cin,nombreCliente);
        getline(cin,apellidoCliente);
        cliente = Cliente(nombreCliente, apellidoCliente, dniCliente);
        if(archivoCliente.guardar(cliente)){
            cout <<"El cliente se registro correctamente"<<endl;
        }else{
            cout << "No se pudo guardar el registro" << endl;
        }
    }
    else{
        cout << "El cliente se encuentra registado. " << endl;
    }


    posicionEmpleado = empArchi.buscar(dniEmpleado);
    emp= empArchi.leer(posicionEmpleado);
    idEmpleado = emp.getIdEmpleado();


    bool cargaProductos=false;
    while (!cargaProductos){ ///ciclo para ingresar productos a una venta
        cin >> idProducto;
        posicionProducto = archiProd.buscar(idProducto);
        prod = archiProd.leer(posicionProducto);
        cin >> cantidad;
        /// a partir de aca esta OK el ingreso de productos

        ImporteProdxCantidad = prod.getPrecioUnitario()*cantidad;
        importeBruto += ImporteProdxCantidad; //Acumulador por todos los detalles que tenga una venta... se utiliza en ventas.
        detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), ImporteProdxCantidad);
        vecDetalleVenta.push_back(detVenta); //se aumenta el tama�o del vector y se coloca al final el nuevo detalle de venta

        cin >> opcion; // para ingresar mas productos (1 si, 0 no)
        if(opcion == 0){
            cargaProductos=true;
            ///fin carga de productos
        }
    }
    cin >> formaDePago;
    if (formaDePago==1){
        descuento = 0.1;
    }
    else if(formaDePago = 2){
        descuento = 0;
    }

    fechaVenta.cargar(); //dia, mes anio
    importeTotal = importeBruto - (importeBruto * descuento );
    v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

    if (ventaArchi.guardar(v)){
        cout << "Registro guardado correctamente." << endl << endl;
    }
    else{
        cout << "Hubo un problema al guardar el registro." << endl << endl;
    }
    descontarStock(vecDetalleVenta);
}
