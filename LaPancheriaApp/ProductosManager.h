#pragma once
#include "DetalleIngrediente.h"
#include <vector>
#include "Producto.h"

class ProductosManager{

private:

public:
    ///Metodos principales
    void crearProducto();
    void crearPanchoOGuarnicion(int idCategoria);
    void incorporarIngredientes(int idProducto, float &costoProducto, std::vector<DetalleIngrediente> &vecDetalleIngredientes);
    void crearBebida(int idCategoria);

    ///ABML
    void modificarProducto();
    void menuModificacion(Producto &prod, int pos);
    void eliminarProducto();
    void darAltaProducto();

    ///Listados
    void mostrarProductoYReceta(Producto &producto);
    void mostrarProductosCompletos();
    void listarProductos(bool estado);
    void listarProductosConIngredientes(bool estado);
    void listarProductosPorCategoria(int idCategoria);
    void listarProductosPorIngredientes();


};
