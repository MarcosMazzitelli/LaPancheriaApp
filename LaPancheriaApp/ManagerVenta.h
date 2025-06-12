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
};
