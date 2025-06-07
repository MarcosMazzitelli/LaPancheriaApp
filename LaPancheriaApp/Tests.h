#ifndef TESTS_H_INCLUDED
#define TESTS_H_INCLUDED
#include "Persona.h"
#include "Cliente.h"
#include "Empleado.h"
#include "FormaDePago.h"
#include "CostoFijo.h"
#include "Tests.h"
#include "Venta.h"
#include "DetalleVenta.h"
#include <iostream>
using namespace std;

///PRUEBAS
void cargarYMostrarProducto(){
    int idProducto;
    int idCategoria;
    string nombreProducto;
    float precioUnitario;
    float costoProducto;
    bool estado;

    Producto p;
    cout << "Ingrese id producto: ";
    cin >> idProducto;

    cout << "Ingrese id categoria: ";
    cin >> idCategoria;

    cout << "Ingrese nombre producto: ";
    cin.ignore();
    getline(cin,nombreProducto);

    cout << "Ingrese precio unitario: ";
    cin >> precioUnitario;

    cout << "Ingrese costo producto: ";
    cin >> costoProducto;

    cout << "Ingrese estado: ";
    cin >> estado;


    p= Producto(idProducto, idCategoria, nombreProducto, precioUnitario, costoProducto, estado);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

    ///Prueba mostrar fecha de venta (no tiene que ver con clase producto)
    Venta v;
    v.getFechaVenta().mostrarFecha();

}

void cargarYMostrarPersona(){
    string nombre;
    string apellido;
    string dni;

    Persona p;
    cout << "Ingrese nombre: ";
    cin >> nombre;

    cout << "Ingrese apellido: ";
    cin >> apellido;

    cout << "Ingrese dni: ";
    cin >> dni;

    p= Persona(nombre, apellido, dni);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

}

///<<<<<<< Updated upstream
void cargarYMostrarCliente(){
    string nombre;
    string apellido;
    string dni;

    Cliente p;
    cout << "Ingrese nombre: ";
    cin >> nombre;

    cout << "Ingrese apellido: ";
    cin >> apellido;

    cout << "Ingrese dni: ";
    cin >> dni;

    p= Cliente(nombre, apellido, dni);
    cout << endl << endl << p.mostrarToCsv();
    cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

}

void cargarYMostrarEmpleado(){
    string nombre, apellido, dni, contrasenia, puesto, email, cel;
    int idEmpleado, permiso, dia, mes, anio;
    float sueldo;
    Fecha fechaIngreso;
    Fecha fechaNacimiento;
    bool estado;

    Empleado p;

    cout << "Ingrese nombre: ";
    cin >> nombre;

    cout << "Ingrese apellido: ";
    cin >> apellido;

    cout << "Ingrese dni: ";
    cin >> dni;

    cout << "Ingrese id: ";
    cin >> idEmpleado;

    cout << "Ingrese contraseña: ";
    cin >> contrasenia;

    cout << "Ingrese permiso: ";
    cin >> permiso;

    cout << "Ingrese puesto: ";
    cin >> puesto;

    cout << "Ingrese sueldo: ";
    cin >> sueldo;

    cout<< "Ingrese dia de ingreso: ";
    cin >> dia;

    cout<< "Ingrese mes de ingreso: ";
    cin >> mes;

    cout<< "Ingrese mes de ingreso: ";
    cin >> anio;
    fechaIngreso.setFecha(dia,mes,anio);

    cout<< "Ingrese dia de nacimiento: ";
    cin >> dia;

    cout<< "Ingrese mes de nacimiento: ";
    cin >> mes;

    cout<< "Ingrese mes de nacimiento: ";
    cin >> anio;

    cout<< "Ingrese estado- true/false: ";
    cin >> estado;

    cout << "Ingrese email: ";
    cin>>email;

    cout << "Ingrese celular: ";
    cin>>cel;

    fechaNacimiento.setFecha(dia,mes,anio);


    p= Empleado(nombre, apellido, dni,idEmpleado,contrasenia,permiso,puesto,sueldo,fechaIngreso,fechaNacimiento,estado,email,cel);
    //cout << endl << endl << p.mostrarToCsv();
    //cout << endl << endl;
    p.mostrar();
    cout << endl << endl;

}



///=======
///>>>>>>> Stashed changes
void cargarPancho(){
    int idCategoria;
    string nombreProducto;
    float precioUnitario;
    float costoProducto;
    bool estado;

    int idProducto=1; //autonumerico

    cout << "Ingrese la categoria 1)Panchos   2)Guarniciones   3)Bebidas)\n";
    cin >> idCategoria;

    cout << "Ingrese el nombre del producto: ";
    cin.ignore();
    getline(cin,nombreProducto);

    cout << "Ingrese el precio de venta del producto: ";
    cin >> precioUnitario;

    cout << "Ingrese el costo del producto: ";
    cin >> costoProducto;

    int opcion=0;
    int idProductoDetalle, idIngrediente;
    float cantidadPorProducto;
    bool bandera=false;
    while (bandera==false){
        idProductoDetalle=idProducto;
        cout << "Listado de ingredientes: \n\n";
        cout << "0: Pan" << endl;
        cout << "1: Salchicha" << endl;
        cout << "2: Papas fritas" << endl;
        cout << "3: Bacon" << endl;
        cout << "4: Chochlo" << endl;
        cout << "5: Arvejas" << endl << endl;

        cout << "Seleccione un ingrediente para su producto: ";
        cin >> idIngrediente;

        cout << "Ingrese la cantidad de ese ingrediente que llevara el producto: ";
        cin >> cantidadPorProducto;

        cout << "\n\nDesea ingresar otro ingrediente? 1)si  2)no" << endl;
        cin >> opcion;
        if(opcion==2){
            bandera=true;
            cout << "Producto " << nombreProducto << " creado!\n\n";
        }
    }
}

void cargarYMostrarFormaDePago(){
    int formaDePago;
    string nombreFormaDePago;
    float descuento=0;

    FormaDePago f;
    cout << "Ingrese la opcion de pago: 1- Efectivo 2- Debito 3- Creidto " << endl;
    cin >> formaDePago;

    switch(formaDePago){
    case 1:
        nombreFormaDePago="Efectivo";
        descuento=10,5;
        break;
    case 2:
        nombreFormaDePago="Debito";
        descuento=0,0;
        break;
    case 3:
        nombreFormaDePago="Credito";
        descuento=0,0;
        break;
    default:
        cout<<"No corresponde a una opcion válida"<<endl;
    }


    f = FormaDePago(formaDePago,descuento, nombreFormaDePago);
    cout << endl << endl << f.mostrarToCsv();
    cout << endl << endl;
    f.mostrar();
    cout << endl << endl;
}

void cargarYMostrarCostoFijo(){
    float precio;
    int idCostoFijo=0; //autonumerico
    int opc;
    bool bandera=true;

    CostoFijo c;

    while(bandera){
        cout<<"Ingrese precio del costo fijo"<< endl;
        cin>> precio;

        idCostoFijo++;
        cout<<"Quiere agregar otro costo fijo? Opcion 1- Si 2- No"<< endl;
        cin>> opc;

        if(opc==1){
            bandera=true;
        }else{
            bandera=false;
        }
    }
     c = CostoFijo(precio, idCostoFijo);
    cout << endl << endl << c.mostrarToCsv();
    cout << endl << endl;
    c.mostrar();
    cout << endl << endl;
}

void CargarYMostrarVenta(){

    int nroFactura,idEmpleado,formaDePago,dia,mes,anio;
    string dniCliente;
    float importeTotal;
    Fecha fechaVenta;
    Venta v;

    cout<<"Ingrese numero de factura: "<<endl;
    cin>>nroFactura;
    cout<<"Ingrese el ID del empleado: "<<endl;
    cin>>idEmpleado;
    cout<<"Ingrese la forma de pago: "<<endl;
    cin>>formaDePago;
    cout<<"Ingrese el DNI del cliente: "<<endl;
    cin>>dniCliente;
    cout<<"Ingrese el importe total: "<<endl;
    cin>>importeTotal;
    cout<<"Ingrese el dia de la venta : "<<endl;
    cin>>dia;
    cout<<"Ingrese el mes de la venta : "<<endl;
    cin>>mes;
    cout<<"Ingrese el año de la venta : "<<endl;
    cin>>anio;
    fechaVenta.setFecha(dia, mes, anio);
    v= Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);
    v.mostrar();
}

/*void CargarYMostrarDetalleVenta(){
int nroFactura,idProducto,cantProducto;
float precioUnitario,importeBruto;
DetalleVenta d;


cout<<"Ingrese el Nro de Factura: "<<endl;
cin>>nroFactura;
cout<<"Ingrese el ID del producto: "<<endl;
cin>>idProducto;
cout<<"Ingrese la cantidad del producto: "<<endl;
cin>>cantProducto;
cout<<"Ingrese el precio unitario: "<<endl;
cin>>precioUnitario;
cout<<"Ingrese el ID del producto: "<<endl;
cin>>importeBruto;
d= DetalleVenta(nroFactura, idProducto, cantProducto,precioUnitario, importeBruto);
d.mostrar();
}
*/









#endif // TESTS_H_INCLUDED
