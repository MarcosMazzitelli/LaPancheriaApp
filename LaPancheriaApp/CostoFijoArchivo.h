#ifndef COSTOFIJOARCHIVO_H_INCLUDED
#define COSTOFIJOARCHIVO_H_INCLUDED
#pragma once
#include "CostoFijo.h"
#include <string>

class CostoFijoArchivo{
private:
    std::string _nombreArchivo;
public:
    CostoFijoArchivo();
    CostoFijoArchivo(std::string nombreArchivo);

};

#endif // COSTOFIJOARCHIVO_H_INCLUDED
