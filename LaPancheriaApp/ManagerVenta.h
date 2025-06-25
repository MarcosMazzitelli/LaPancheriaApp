#pragma once
#include <string>
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
    void descontarStock(std::vector<DetalleVenta> &vecDetalleVenta);
    void mostrarFechaMayorRecaudacionVenta();//muestra el dia que se registro el mayor importe total por ventas
    void mostrarFechaMayorCantidadVentas();// muestra el dia que se realizaron mas cantidad de ventas sin importar el monto
    void listarVendedorMayorRecaudacion();
    void listarVendedorMenorRecaudacion();
    void listarVendedorMayorCantidadVentas();
    void listarVendedorMenorCantidadVentas();
    void listarVentasToCsv();
    void listarDetalleVentaToCsv();
    void MayorRecaudacionPorPeriodo();
    void mostrarFechaMayorCantidadVentasPorPeriodo();
    void cierreCaja();
};
