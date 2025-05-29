#include "DetalleIngrediente.h"

///Constructores
DetalleIngrediente::DetalleIngrediente(){
    _idProducto=0;
    _idIngrediente=0;
    _cantidadPorProducto=0.0f;
}

DetalleIngrediente::DetalleIngrediente(int idProducto, int idIngrediente, float cantidadPorProducto){
    setIdProducto(idProducto);
    setIdIngrediente(idIngrediente);
    setCantidadPorProducto(cantidadPorProducto);
}

///Setters
void DetalleIngrediente::setIdProducto(int idProducto){
    _idProducto=idProducto;
}

void DetalleIngrediente::setIdIngrediente (int idIngrediente){
    _idIngrediente=idIngrediente;
}

void DetalleIngrediente::setCantidadPorProducto (float cantidadPorProducto){
    _cantidadPorProducto=cantidadPorProducto;
}

///Getters
int DetalleIngrediente::getIdProducto(){
    return _idProducto;
}

int DetalleIngrediente::getIdIngrediente(){
    return _idIngrediente;
}

float DetalleIngrediente::getCantidadPorProducto(){
    return _cantidadPorProducto;
}
