#include "FormaDePago.h"
#include <cstring>
using namespace std;

//Constructor por ominisión
FormaDePago::FormaDePago(){

    _formaDePago=0;
    _descuento=0;
    strcpy(_nombreFormaDePago, "");
}

//Constructor por parametros
FormaDePago::FormaDePago(int formaDePago, float descuento, std::string nombreFormaDePago){
        setFormaDePago(formaDePago);
        setDescuento(descuento);
        setNombreFormaDePago(nombreFormaDePago);
}

///Getters
    int FormaDePago::getFormaDePago(){
    return _formaDePago;
    }
    float FormaDePago::getDescuento(){
    return _descuento;
    }
    std::string FormaDePago::getNombreFormaDePago(){
    return _nombreFormaDePago;
    }

//Setters
    void FormaDePago::setFormaDePago(int formaDePago){
        _formaDePago=formaDePago;
    }
    void FormaDePago::setDescuento(float descuento){
        _descuento=descuento;
    }
    void FormaDePago::setNombreFormaDePago(std::string nombreFormaDePago){
        strcpy(_nombreFormaDePago,nombreFormaDePago.c_str());
    }
