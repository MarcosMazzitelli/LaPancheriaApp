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
    int cantidad, opcion;
    vector<DetalleVenta> vecDetalleVenta;


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

    opcion = pedirYValidarConfirmacion("Desea registrar la venta? \n1) si \n0) no \n\n");
    if(opcion == 1){
        if (ventaArchi.guardar(v)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }
        for (int i=0; i < vecDetalleVenta.size() ; i++){
            if(archiDetVenta.guardar(vecDetalleVenta[i])){
                cout << "Producto guardado correctamente." << endl << endl;
            }
            else{
                cout << "Hubo un problema al guardar el registro." << endl << endl;
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
void ManagerVenta::mostrarFechaMayorRecaudacionVenta(){

    VentaArchivo archi;
    Venta vent;
    Fecha aux;

    int cantRegistro=archi.getCantidadRegistros();

    float mayorVenta=0.0;
    for(int i=0; i<cantRegistro;i++){
        vent=archi.leer(i);


        if(i==0){
            mayorVenta=vent.getImporteTotal();
            aux=vent.getFechaVenta();

        }else if(vent.getImporteTotal()>mayorVenta){

            mayorVenta=vent.getImporteTotal();
            aux=vent.getFechaVenta();
        }




    }

    cout<<"El monto de la mayor venta es: "<<"$"<<mayorVenta<<endl;
    cout<<endl<<"se registro el dia "<< aux.mostrarFecha()<<endl<<endl;

}
/*void ManagerVenta::mostrarFechaMayorCantidadVentas(){



    Fecha fecha;
    VentaArchivo archi;
    Venta vent;

    std::vector<Fecha> vecFecha;
    std::vector<int> vecContador;
   int cantRegistro=archi.getCantidadRegistros();
   bool coincidencia=false;
   int mayor=0;

    int cont=0;

    for(int i=0;i<cantRegistro;i++){
        vent=archi.leer(i);
        coincidencia=false;
        if(i==0){
           vecFecha[i]=vent.getFechaVenta();
           vecContador[i]++;
        }
        else{
            for(int j=0; j<vecFecha.size();j++){

               if(vent.getFechaVenta() == vecFecha[j]){
                vecContador[j]++;
                coincidencia=true;
               }
            }
            if(!coincidio){
                vecFecha[i]=vent.getFechaVenta();
                vecContador[i]++;
            }
        }
    }
    for(i=0;i<vecContador.size();i++){

        if(i==0){
            mayor=vecContador[i];
            fecha=vecFecha[i];
        }
        else if(vecContador[i]>mayor){
                mayor=vecContador[i];
                fecha=vecFecha[i];
        }
    }
    cout<<"el dia que se registraron la mayor cantidad de ventas fue el "<<fecha.mostrarFecha()<<endl;
    cout<<"y la cantidad de ventas que se realizaron ese dia fueron "<<mayor<<" ventas"<<endl;
*/
