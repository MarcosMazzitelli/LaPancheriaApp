#ifndef DETALLEVENTA_H_INCLUDED
#define DETALLEVENTA_H_INCLUDED
#include <string>


class DetalleVenta{
private:
    int _nroFactura;
    int _idProducto;
    int _cantProducto;
    float _precioUnitario;
    float _importeBruto;


public:
    ///Constructores
    DetalleVenta();
    DetalleVenta(int nroFactura, int idProducto, int cantProducto, float precioUnitario, float importeBruto);

    ///Setters
    void setNroFactura(int nroFactura);
    void setIdProducto(int idPrducto);
    void setCantProducto(int cantProducto);
    void setPrecioUnitario(float precioUnitario);
    void setImporteBruto(float importeBruto);


    ///Getters
    int getNroFactura();
    int getIdProducto();
    int getCantProducto();
    float getPrecioUnitario();
    float getImporteBruto();


    ///Metodos
    void mostrar();
    std::string mostrarToCsv();

    ///Pruebas
    //void testCargarYMostrar();
};



#endif // DETALLEVENTA_H_INCLUDED
