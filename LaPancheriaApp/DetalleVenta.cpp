#include "DetalleVenta.h"
#include <cstring>
#include <iostream>

using namespace std;


///Constructores
DetalleVenta::DetalleVenta(){
    _nroFactura=0;
    _idProducto=0;
    _cantidadProducto=0;
    _precioUnitario=0.0f;
    _importeBruto=0.0f;

}

DetalleVenta::DetalleVenta(int nroFactura, int idProducto, int cantidadProducto, float precioUnitario, float importeTotal){
    setNroFactura(nroFactura);
    setIdProducto(idProducto);
    setCantidadProducto(cantidadProducto);
    setPrecioUnitario(precioUnitario);
    setImporteBruto(importeBruto);
}

///Setters
void DetalleVenta::setNroFactura(int nroFactura){
    _nroFactura=nroFactura;
}

void DetalleVenta::setIdProducto(int idProducto){
    _idProducto=idProducto;
}

void DetalleVenta::setCantidadProducto(int cantidadProducto){
    _cantidadProducto=cantidadProducto;

void DetalleVenta::setPrecioUnitario(float precioUnitario){
    _precioUnitario=precioUnitario;
}

void DetalleVenta::setImporteBruto(float importeBruto){
    _importeBruto=importeBruto;
}


///Getters
int DetalleVenta::getNroFactura(){
    return _nroFactura;
}

int DetalleVenta::getIdProducto(){
    return _idProducto;
}

int DetalleVenta::getCantidadProducto(){
    return _cantProducto;
}

float DetalleVenta::getPrecioUnitario(){
    return _precioUnitario;
}

float DetalleVenta::getImporteBruto(){
    return _importeBruto;
}


///Metodos
void DetalleVenta::mostrar(){
    cout << "Numero de Factura: " << getNroFactura() << endl;
    cout << "Id Producto: " << getIdProducto() << endl;
    cout << "Cantidad de Producto: " << getCantidadProducto() << endl;
    cout << "Precio unitario: " << getPrecioUnitario() << endl;
    cout << "Importe Bruto: " << getImporteBruto() << endl;
}

std::string DetalleVenta::mostrarToCsv(){
    string str = "";

    str = to_string(_nroFactura) + ",";
    str+= to_string(_idProducto) + ",";
    str+= to_string(_cantProducto) + ",";
    str+= to_string(_precioUnitario) + ",";
    str+= to_string(_importeBruto) + ",";

    return str;
}
