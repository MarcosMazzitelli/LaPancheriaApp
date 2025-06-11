#pragma once
#include "DetalleIngrediente.h"
#include <vector>

class ProductosManager{

private:

public:
    void crearProducto();
    void crearPanchoOGuarnicion(int idCategoria);
    void incorporarIngredientes(int idProducto, float &costoProducto, std::vector<DetalleIngrediente> &vecDetalleIngredientes);
    void crearBebida(int idCategoria);
    void modificarProducto();
    int cantidadRegistrosProducto();
    int cantidadRegistrosDetalleIngredientes();

    ///Listados
    void mostrarProductosCompletos();
    void listarProductos();
    void listarProductosConIngredientes();
    void listarProductosPorCategoria(int idCategoria);


};
