#pragma once
#include <string>

class Producto{
private:
    int _idProducto;
    int _idCategoria; //1) Panchos  2)Guarniciones  3)Bebidas
    char _nombreProducto[50];
    float _precioUnitario;
    float _costoProducto;
    bool _estado;

public:
    ///Constructores
    Producto();
    Producto(int idProducto, int idCategoria, std::string nombreProducto, float precioUnitario, float costoProducto, bool estado);

    ///Setters
    void setIdProducto(int idProducto);
    void setIdCategoria(int idCategoria);
    void setNombreProducto(std::string nombreProducto);
    void setPrecioUnitario(float precioUnitario);
    void setCostoProducto(float costoProducto);
    void setEstado(bool estado);

    ///Getters
    int getIdProducto();
    int getIdCategoria();
    std::string getNombreProducto();
    float getPrecioUnitario();
    float getCostoProducto();
    bool getEstado();

    ///Metodos
    void mostrar();
    std::string mostrarToCsv();

    ///Pruebas
    void testCargarYMostrar();
};
