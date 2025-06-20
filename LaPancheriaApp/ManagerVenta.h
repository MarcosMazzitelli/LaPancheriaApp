#pragma once
#include <string>
#include "Fecha.h"
#include <vector>
#include "DetalleVenta.h"



class ManagerVenta{
private:




public:
    void registrarVenta(std::string dniEmpleado);
    void cargaMasivaVentas(std::string dniEmpleado);

    void listarVenta();
    int cantidadRegistros();
    void listarVentaFecha();
    void listarVendedorMayorRecaudacion();
    void descontarStock(std::vector<DetalleVenta> &vecDetalleVenta);
};
