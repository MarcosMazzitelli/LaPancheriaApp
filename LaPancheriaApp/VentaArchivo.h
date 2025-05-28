#ifndef VENTAARCHIVO_H_INCLUDED
#define VENTAARCHIVO_H_INCLUDED
#pragma once
#include "Venta.h"
#include <string>

class VentaArchivo{
private:
    std::string _nombreArchivo;
public:
    VentaArchivo();
    VentaArchivo(std::string nombreArchivo);

};


#endif // VENTAARCHIVO_H_INCLUDED
