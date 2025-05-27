#ifndef FORMADEPAGOARCHIVO_H_INCLUDED
#define FORMADEPAGOARCHIVO_H_INCLUDED
#pragma once
#include "FormaDePago.h"
#include <string>

class FormaDePagoArchivo{
private:
    std::string _nombreArchivo;
public:
    FormaDePagoArchivo();
    FormaDePagoArchivo(std::string nombreArchivo);

};



#endif // FORMADEPAGOARCHIVO_H_INCLUDED
