#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED
#include <string>

#include <cstring>
#include <iostream>

class DetalleVenta{
private:
    int _nroFactura;
    int _idProducto;
    int _cantProducto;
    float _precioUnitario;
    float _costoUnitario;
    float _importeBruto;


public:
    ///Constructores
    DetalleVenta();
    DetalleVenta(int nroFactura, int idProducto, int cantProducto, float precioUnitario,float costoUnitario, float importeBruto);

    ///Setters
    void setNroFactura(int nroFactura);
    void setIdProducto(int idPrducto);
    void setCantProducto(int cantProducto);
    void setPrecioUnitario(float precioUnitario);
    void setCostoUnitario(float costoUnitario);
    void setImporteBruto(float importeBruto);


    ///Getters
    int getNroFactura();
    int getIdProducto();
    int getCantProducto();
    float getPrecioUnitario();
    float getCostoUnitario();
    float getImporteBruto();


    ///Metodos
    void mostrar();
    std::string mostrarToCsv();

    ///Pruebas
    //void testCargarYMostrar();
};



#endif // DETALLEVENTA_H_INCLUDED
