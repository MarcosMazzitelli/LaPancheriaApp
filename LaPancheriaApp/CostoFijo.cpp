#include "CostoFijo.h"
#include <cstring>
#include <iostream>
using namespace std;

//Constructor por ominisión
CostoFijo::CostoFijo(){

    _precio=0;
    _idCosto=0;
}

//Constructor por parametros
CostoFijo::CostoFijo(float precio, int idCosto){
        setPrecio(precio);
        setIdCosto(idCosto);
}

//Getters
    float CostoFijo::getPrecio(){
    return _precio;
    }
    int CostoFijo::getIdCosto(){
    return _idCosto;
    }



//Setters
    void CostoFijo::setPrecio(float precio){
        _precio=precio;
    }
    void CostoFijo::setIdCosto(int idCosto){
        _idCosto=idCosto;
    }


  /*Metodos mostrar*/
    void CostoFijo::mostrar(){
        cout << "Precio del costo fijo: " << getPrecio() << endl;
        cout << "ID del costo fijo: " << getIdCosto() << endl;
}

    std::string CostoFijo::mostrarToCsv(){
        string str = "";

        str = to_string(_precio) + ",";
        str+= to_string(_idCosto);

        return str;
    }


