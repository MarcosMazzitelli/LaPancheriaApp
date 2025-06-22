#pragma once
#include <string>
#include "DetalleIngrediente.h"

class ArchivoDetalleIngrediente{
private:
    std::string _nombreArchivo;

public:
    ///Constructores
    ArchivoDetalleIngrediente();
    ArchivoDetalleIngrediente(std::string nombreArchivo);

    ///Metodos
    bool guardar(DetalleIngrediente registro);
    int getCantidadRegistros();
    DetalleIngrediente leer(int pos);
    int buscar(int idProducto);
    buscarPorIngrediente(int idIngrediente);
    bool modificar(DetalleIngrediente &registro, int posicion);

};
