#pragma once

class DetalleIngrediente{

private:
    int _idProducto;
    int _idIngrediente;
    float _cantidadPorProducto;
    bool _estado;

public:

    ///Constructores
    DetalleIngrediente();
    DetalleIngrediente(int idProducto, int idIngrediente, float cantidadPorProducto, bool estado);

    ///Setters
    void setIdProducto(int idProducto);
    void setIdIngrediente (int idIngrediente);
    void setCantidadPorProducto (float cantidadPorProducto);
    void setEstado (bool estado);

    ///Getters
    int getIdProducto();
    int getIdIngrediente();
    float getCantidadPorProducto();
    bool getEstado();


};
