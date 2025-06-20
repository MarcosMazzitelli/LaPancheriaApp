#pragma once
#include "CostoFijo.h"
#include <string>

class CostoFijoArchivo{
private:
    std::string _nombreArchivo;
public:
    CostoFijoArchivo();
    CostoFijoArchivo(std::string nombreArchivo);

    //Metodos
    bool guardar(CostoFijo registro);
    bool guardarModificado(CostoFijo registro, int posicion);
    int getCantidadRegistros();
    CostoFijo leer(int posicion);

};

