#include "Producto.h"
#include <cstring>
#include <iostream>

using namespace std;


///Constructores
Producto::Producto(){
    _idProducto=0;
    _idCategoria=0;
    strcpy(_nombreProducto,"");
    _precioUnitario=0.0f;
    _costoProducto=0.0f;
    _estado=true;
}

Producto::Producto(int idProducto, int idCategoria, std::string nombreProducto, float precioUnitario, float costoProducto, bool estado){
    setIdProducto(idProducto);
    setIdCategoria(idCategoria);
    setNombreProducto(nombreProducto);
    setPrecioUnitario(precioUnitario);
    setCostoProducto(costoProducto);
    setEstado(estado);
}

///Setters
void Producto::setIdProducto(int idProducto){
    _idProducto=idProducto;
}

void Producto::setIdCategoria(int idCategoria){
    _idCategoria=idCategoria;
}

void Producto::setNombreProducto(std::string nombreProducto){
    strcpy(_nombreProducto,nombreProducto.c_str());
}

void Producto::setPrecioUnitario(float precioUnitario){
    _precioUnitario=precioUnitario;
}

void Producto::setCostoProducto(float costoProducto){
    _costoProducto=costoProducto;
}

void Producto::setEstado(bool estado){
    _estado=estado;
}

///Getters
int Producto::getIdProducto(){
    return _idProducto;
}

int Producto::getIdCategoria(){
    return _idCategoria;
}

std::string Producto::getNombreProducto(){
    return _nombreProducto;
}

float Producto::getPrecioUnitario(){
    return _precioUnitario;
}

float Producto::getCostoProducto(){
    return _costoProducto;
}

bool Producto::getEstado(){
    return _estado;
}

///Metodos
void Producto::mostrar(){
    cout << "Id producto: " << getIdProducto() << endl;
    cout << "Id Categoria: " << getIdCategoria() << endl;
    cout << "Nombre del producto: " << getNombreProducto() << endl;
    cout << "Precio de venta unitario: " << getPrecioUnitario() << endl;
    cout << "Costo del producto: " << getCostoProducto() << endl;
}

std::string Producto::mostrarToCsv(){
    string str = "";

    str = to_string(_idProducto) + ",";
    str+= to_string(_idCategoria) + ",";
    str+= string(_nombreProducto) + ",";
    str+= to_string(_precioUnitario) + ",";
    str+= to_string(_costoProducto) + ",";
    str+= to_string(_estado);

    return str;
}
