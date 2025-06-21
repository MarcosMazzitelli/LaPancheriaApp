#pragma once
#include "DetalleVenta.h"
#include <string>


class DetalleVentaArchivo{
private:
    std::string _nombreArchivo;
public:
    DetalleVentaArchivo();
    DetalleVentaArchivo(std::string nombreArchivo);


    //Metodo
    bool guardar(DetalleVenta registro);
    int getCantidadRegistros();
    DetalleVenta leer(int pos);


};
