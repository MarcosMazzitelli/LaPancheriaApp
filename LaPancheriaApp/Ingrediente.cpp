#include "Ingrediente.h"
#include <cstring>
#include <iostream>

using namespace std;

///Constructores

Ingrediente::Ingrediente(){
    _idIngrediente=0;
    strcpy(_nombreIngrediente,"");
    _cantidadStock=0.0f;
    strcpy(_tipoDeUnidad,"");
    _estado=true;

}

Ingrediente::Ingrediente(int idIngrediente, std::string nombreIngrediente, float cantidadStock, std::string tipoDeUnidad, bool estado){
    setIdIngrediente(idIngrediente);
    setNombreIngrediente(nombreIngrediente);
    setCantidadStock(cantidadStock);
    setTipoDeUnidad(tipoDeUnidad);
    setEstado(estado);

}

///Setters

void Ingrediente::setIdIngrediente(int idIngrediente){
    _idIngrediente=idIngrediente;
}

void Ingrediente::setNombreIngrediente(std::string nombreIngrediente){
    strcpy(_nombreIngrediente,nombreIngrediente.c_str());
}

void Ingrediente::setCantidadStock(float cantidadStock){
    _cantidadStock=cantidadStock;
}

void Ingrediente::setTipoDeUnidad(std::string tipoDeUnidad){
    strcpy(_tipoDeUnidad,tipoDeUnidad.c_str());
}

void Ingrediente::setEstado(bool estado){
    _estado=estado;
}

///Getters

int Ingrediente::getIdIngrediente(){
    return _idIngrediente;
}

std::string Ingrediente::getNombreIngrediente(){
    return _nombreIngrediente;
}

float Ingrediente::getCantidadStock(){
    return _cantidadStock;
}

std::string Ingrediente::getTipoDeUnidad(){
    return _tipoDeUnidad;
}

bool Ingrediente::getEstado(){
    return _estado;
}


///Metodos
void Ingrediente::mostrar(){
    cout << "Id Ingrediente: " << getIdIngrediente() << endl;
    cout << "Nombre del ingrediente: " << getNombreIngrediente() << endl;
    cout << "Cantidad en stock: " << getCantidadStock() << " " << getTipoDeUnidad() << endl;
}

std::string Ingrediente::mostrarToCsv(){
    string str = "";

    str = to_string(_idIngrediente) + ",";
    str+= string(_nombreIngrediente) + ",";
    str+= to_string(_cantidadStock) + ",";
    str+= string(_tipoDeUnidad) + ",";
    str+= to_string(_estado);

    return str;
}
