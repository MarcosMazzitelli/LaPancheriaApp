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
    bool guardar(Ingrediente &registro);
    bool modificar(Ingrediente &registro, int posicion);
    int getCantidadRegistros();
    Ingrediente leer(int pos);
    int buscar(int idIngrediente);

};
