#pragma once
#include <string>
#include "Ingrediente.h"

class ArchivoIngrediente{
private:
    std::string _nombreArchivo;

public:
    ///Constructores
    ArchivoIngrediente();
    ArchivoIngrediente(std::string nombreArchivo);

    ///Metodos
    bool guardar(Ingrediente registro);
    int getCantidadRegistros();

};
