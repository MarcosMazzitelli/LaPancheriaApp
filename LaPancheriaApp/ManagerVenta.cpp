#include <string>
#include <iostream>
#include "ManagerVenta.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "Fecha.h"

using namespace std;


void ManagerVenta::registrarVenta(){
    int nroFactura,idEmpleado,formaDePago,dia,mes,anio;
    string dniCliente;
    float importeTotal;
    Fecha fechaVenta;
    Venta v;
    cout<<"ingrese nro de Facura : "<<endl;
    cin>> nroFactura;
    cout<<"ingrese DNI cliente : "<<endl;
    cin.ignore();
    getline(cin, dniCliente);
    cout<<"ingrese ID Empleado: "<<endl;
    cin>>  idEmpleado;
    cout<<"ingrese el importe Total : "<<endl;
    cin>>  importeTotal;
    cout<<"ingrese la forma de pago : "<<endl;
    cin>>  formaDePago;
    cout<<"ingrese el dia : "<<endl;
    cin>>  dia;
    cout<<"ingrese el mes: "<<endl;
    cin>>  mes;
    cout<<"ingrese ingrese el año: "<<endl;
    cin>>  anio;

    fechaVenta.setFecha(dia,mes,anio);
    v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

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

for (int i=0;i<cantRegistros;i++){

    vent = archi.leer(i);
    vent.mostrar();
    cout<<endl <<endl;
}


}

