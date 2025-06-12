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

using namespace std;



void ManagerVenta::registrarVenta(std::string dniEmpleado){

    int nroFactura,idEmpleado,formaDePago,dia,mes,anio;
    //FormaDePago fdp; //FormaDePagoArchivo aFdp;
    string dniCliente; //Cliente client; /ClienteArchivo aCliente;
    float importeTotal=0;
    float importeBruto;
    VentaArchivo ventaArchi;
    ArchivoEmpleado empArchi;
    Empleado emp;
    Fecha fechaVenta;
    Venta v;
    int pos;
    DetalleVenta detVenta;
    Producto prod;
    int cantidad, opcion;




    nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico

    cout<<"ingrese DNI cliente : "<<endl; //Llamar al cliente.cargar();
    cin.ignore();
    getline(cin, dniCliente);

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
        cout << "Seleccione el producto que desee agregar: " << endl << endl;
        prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
        cin >> idProducto;

        while (idProducto < 0 || idProducto > prodManager.cantidadRegistrosProducto()){
            cout << "Ingrese un Id de ingrediente valido" << endl << endl;
            prodManager.listarProductos(); //reemplazar esto por una funcion o metodo de mostrar ingredientes para venta que sea mas legible para el vendedor(con menos atributos)
            cout << "Seleccione el ingrediente que desee agregar: " << endl << endl;
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
        importeBruto = prod.getPrecioUnitario()*cantidad;
        importeTotal += importeBruto;
        detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), importeBruto);
        DetalleVentaArchivo archiDetVenta;
        if(archiDetVenta.guardar(detVenta)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }

        ///acá se guarda UN detalle de venta en el detalle

        validacion=false;
        while (!validacion){
            cout << endl << "¿Desea ingresar mas productos?  " << endl <<"1) si" << endl <<"0) no" << endl << endl;
            cin>>opcion;
            if(opcion<0 || opcion >1){
                cout << "Ingrese un valor valido" << endl << endl;
            }
            else if(opcion==0){
                cargaProductos=true; //fin del while general de carga de ingredientes
                validacion=true;
            }
            else{ //si la opcion es 1:
                validacion=true; //fin del while de validacion de opciones
            }
        }

    }


    cout<<"ingrese la forma de pago : "<<endl;
    cin>>  formaDePago; /// Unir con la forma de pago de Vale // formaDePago.cargar();

    cout<<"ingrese la fecha de venta : "<<endl;

    fechaVenta.cargar();
    while(!fechaVenta.cargar()){
        fechaVenta.cargar();
    }

    v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

    if (ventaArchi.guardar(v)){
        cout << "Registro guardado correctamente." << endl << endl;
    }
    else{
        cout << "Hubo un problema al guardar el registro." << endl << endl;
    }

    ///fin carga de productos



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
