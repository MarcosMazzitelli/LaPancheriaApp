#pragma once
#include "DetalleIngrediente.h"
#include <vector>
#include "Producto.h"

class ProductosManager{

private:

public:
    void crearProducto();
    void crearPanchoOGuarnicion(int idCategoria);
    void incorporarIngredientes(int idProducto, float &costoProducto, std::vector<DetalleIngrediente> &vecDetalleIngredientes);
    void crearBebida(int idCategoria);
    void modificarProducto();
    void menuModificacion(Producto &prod, int pos);
    int cantidadRegistrosProducto();
    int cantidadRegistrosDetalleIngredientes();

    ///Listados
    void mostrarProductosCompletos();
    void listarProductos();
    void listarProductosConIngredientes();
    void listarProductosPorCategoria(int idCategoria);
    void listarProductosPorIngredientes();


};
