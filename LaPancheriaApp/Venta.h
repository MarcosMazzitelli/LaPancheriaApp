#pragma once
#include <string>
#include "Fecha.h"


class Venta{
private:
    int _nroFactura;
    char _dniCliente[10];
    int _idEmpleado;
    float _importeTotal;
    int _formaDePago;
    Fecha _fechaVenta;
public:
    Venta();
    Venta(int nroFactura, std::string dniCliente, int idEmpleado, float importeTotal, int formaDePago,Fecha fechaVenta);

   int getNroFactura();
   std::string getDniCliente();
   int getIdEmpleado();
   float getImporteTotal();
   int getFormaDePago();
   Fecha getFechaVenta();


    void setNroFactura (int nroFactura);
    void setDniCliente(std::string dniCliente);
    void setIdEmpleado (int idEmpleado);
    void setImporteTotal (float importeTotal);
    void setFormaDePago (int formaDePago);
    void setFechaVenta (Fecha fechaVenta);


    void mostrar();
    void mostrarEnLista();
    Fecha obtenerFechaVenta();
    void mostrarTabla();
    std::string mostrarToCsv();
};



