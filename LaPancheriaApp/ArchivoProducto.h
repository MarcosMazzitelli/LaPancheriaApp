#pragma once
#include <string>
#include "Producto.h"

class ArchivoProducto{
private:
    std::string _nombreArchivo;

public:
    ///Constructores
    ArchivoProducto();
    ArchivoProducto(std::string nombreArchivo);

    ///Metodos
    bool guardar(Producto registro);
    int getCantidadRegistros();

};
