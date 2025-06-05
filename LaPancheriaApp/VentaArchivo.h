
#pragma once
#include "Venta.h"
#include <string>

class VentaArchivo{
private:
    std::string _nombreArchivo;
public:
    VentaArchivo();
    VentaArchivo(std::string nombreArchivo);
    //Metodos
    bool guardar(Venta registro);
    int getCantidadRegistros();
    Venta leer(int pos);

};



