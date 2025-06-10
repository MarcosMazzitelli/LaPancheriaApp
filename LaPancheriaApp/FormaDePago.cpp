#include "FormaDePago.h"
#include <cstring>
#include <iostream>
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

    /*Metodos mostrar*/
    void FormaDePago::mostrar(){
        cout << "N de forma de pago: " << getFormaDePago() << endl;
        cout << "Nombre de forma de pago: " << getNombreFormaDePago() << endl;
        cout << "Descuento: " << getDescuento() << endl;
}

    std::string FormaDePago::mostrarToCsv(){
        string str = "";

        str = to_string(_formaDePago) + ",";
        str+= string(_nombreFormaDePago) + ",";
        str+= to_string(_descuento);

        return str;
    }
