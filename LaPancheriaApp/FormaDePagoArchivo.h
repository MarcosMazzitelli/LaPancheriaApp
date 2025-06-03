#pragma once
#include "FormaDePago.h"
#include <string>

class FormaDePagoArchivo{
private:
    std::string _nombreArchivo;
public:
    //Constructores
    FormaDePagoArchivo();
    FormaDePagoArchivo(std::string nombreArchivo);

    //Metodos
    bool guardar(FormaDePago registro);
    int getCantidadRegistros();

};



