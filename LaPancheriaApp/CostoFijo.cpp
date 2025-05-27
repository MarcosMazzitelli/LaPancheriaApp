#include "CostoFijo.h"
#include <cstring>
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

