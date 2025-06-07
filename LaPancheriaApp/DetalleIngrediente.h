#pragma once

class DetalleIngrediente{

private:
    int _idProducto;
    int _idIngrediente;
    float _cantidadPorProducto;

public:

    ///Constructores
    DetalleIngrediente();
    DetalleIngrediente(int idProducto, int idIngrediente, float cantidadPorProducto);

    ///Setters
    void setIdProducto(int idProducto);
    void setIdIngrediente (int idIngrediente);
    void setCantidadPorProducto (float cantidadPorProducto);

    ///Getters
    int getIdProducto();
    int getIdIngrediente();
    float getCantidadPorProducto();


};
