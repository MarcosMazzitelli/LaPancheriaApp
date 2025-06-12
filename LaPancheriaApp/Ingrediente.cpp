#include "Ingrediente.h"
#include <cstring>
#include <iostream>

using namespace std;

///Constructores

Ingrediente::Ingrediente(){
    _idIngrediente=0;
    strcpy(_nombreIngrediente,"");
    _cantidadStock=0.0f;
    _costoUnitario=0.0f;
    strcpy(_tipoDeUnidad,"");
    _estado=true;

}

Ingrediente::Ingrediente(int idIngrediente, std::string nombreIngrediente, float cantidadStock, float costoUnitario, std::string tipoDeUnidad, bool estado){
    setIdIngrediente(idIngrediente);
    setNombreIngrediente(nombreIngrediente);
    setCantidadStock(cantidadStock);
    setCostoUnitario(costoUnitario);
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

void Ingrediente::setCostoUnitario(float costoUnitario){
    _costoUnitario=costoUnitario;
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

float Ingrediente::getCostoUnitario(){
    return _costoUnitario;
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
    if (getTipoDeUnidad()=="Gramos"){
        cout << "Cantidad en stock: " << getCantidadStock() << " " << getTipoDeUnidad() << " (" << getCantidadStock()/1000 << " Kilos)" << endl;
    }
    else if (getTipoDeUnidad() == "Mililitros"){
        cout << "Cantidad en stock: " << getCantidadStock() << " " << getTipoDeUnidad() << " (" << getCantidadStock()/1000 << " Litros)" << endl;
    }
    else{
        cout << "Cantidad en stock: " << getCantidadStock() << " " << getTipoDeUnidad() << endl;
    }
    cout << "Costo unitario: $" << getCostoUnitario() << endl;

}

std::string Ingrediente::mostrarToCsv(){
    string str = "";

    str = to_string(_idIngrediente) + ",";
    str+= string(_nombreIngrediente) + ",";
    str+= to_string(_cantidadStock) + ",";
    str+= to_string(_costoUnitario) + ",";
    str+= string(_tipoDeUnidad) + ",";
    str+= to_string(_estado);

    return str;
}
