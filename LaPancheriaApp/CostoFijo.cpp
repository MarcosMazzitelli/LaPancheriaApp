#include "CostoFijo.h"
#include <cstring>
#include <iostream>
#include <iomanip> //libreria para controlar el formato de los datos especialmente en los cout
using namespace std;

//Constructor por ominisión
CostoFijo::CostoFijo(){

    _idCosto=0;
    strcpy(_nombreCosto,"");
    _precio=0;
    _fechaCosto= Fecha();
     _estado=true;

}

//Constructor por parametros
CostoFijo::CostoFijo(int idCosto,std::string nombreCosto,float precio,Fecha fechaCosto, bool estado){

        setIdCosto(idCosto);
        setNombreCosto(nombreCosto);
        setPrecio(precio);
        setFechaCosto(fechaCosto);
        setEstado(estado);
}

//Getters

    int CostoFijo::getIdCosto(){
    return _idCosto;
    }

    std::string CostoFijo::getNombreCosto(){
    return _nombreCosto;
    }

    float CostoFijo::getPrecio(){
    return _precio;
    }
    Fecha CostoFijo::getFechaCosto(){
    return _fechaCosto;
}
    bool CostoFijo::getEstado(){
    return _estado;
}



//Setters

    void CostoFijo::setIdCosto(int idCosto){
        _idCosto=idCosto;
    }
    void CostoFijo::setNombreCosto( std::string nombreCosto){
        strcpy(_nombreCosto,nombreCosto.c_str());
    }
    void CostoFijo::setPrecio(float precio){
        _precio=precio;
    }
    void CostoFijo::setFechaCosto(Fecha fechaCosto){
    _fechaCosto=fechaCosto;
}
    void CostoFijo::setEstado(bool estado){
    _estado=estado;
}


  /*Metodos mostrar
    void CostoFijo::mostrar(){
        cout << "ID del costo fijo: " << getIdCosto() << endl;
        cout << "Nombre del costo fijo: " << getNombreCosto() << endl;
        cout << "Precio del costo fijo: " << getPrecio() << endl;
        // falta fecha
        cout << "Estado del costo fijo: " << getEstado() << endl;
}

    std::string CostoFijo::mostrarToCsv(){
        string str = "";

        str = to_string(_idCosto) + ",";
        str+= string(_nombreCosto);
        str+= to_string(_precio);
        str+= to_string(_fechaCosto);
        str+= to_string(_estado);

        return str;
    }*/

void CostoFijo::mostrarTabla(){
cout << left << setw(20) << "ID Costo Fijo";
cout << left << setw(20) << "Nombre Costo Fijo";
cout << "$ " << left << setw(18) <<"Precio";
cout << left << setw(20) << "Fecha";
}

void CostoFijo::mostrarEnLista(){
cout << left << setw(20) << getIdCosto();
cout << left << setw(20) << getNombreCosto();
cout << "$ " << left << setw(18) <<getPrecio();
cout << left << setw(20) ; getFechaCosto(); //corregir
}



