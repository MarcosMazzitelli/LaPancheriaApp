#pragma once
#include <string>
#include "Fecha.h"




class ManagerVenta{
private:




public:
    void registrarVenta(std::string dniEmpleado);
    void listarVenta();
    int cantidadRegistros();
    void listarVentaFecha();
    void mostrarFechaMayorRecaudacionVenta();//muestra el dia que se registro el mayor importe total por ventas
    void mostrarFechaMayorCantidadVentas();// muestra el dia que se realizaron mas cantidad de ventas sin importar el monto
};
