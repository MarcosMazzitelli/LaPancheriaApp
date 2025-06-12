#pragma once
#include <string>
#include "Fecha.h"
#include <vector>
#include "DetalleVenta.h"



class ManagerVenta{
private:




public:
    void registrarVenta(std::string dniEmpleado);
    void listarVenta();
    int cantidadRegistros();
    void listarVentaFecha();
    void descontarStock(std::vector<DetalleVenta> &vecDetalleVenta,int tam);
};
