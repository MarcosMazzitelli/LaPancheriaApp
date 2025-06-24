#pragma once
#include "Empleado.h"
#include <string>

class ArchivoEmpleado{

private:
    std::string _nombreArchivo;
public:
    /*Constructores*/
    ArchivoEmpleado();
    ArchivoEmpleado(std::string _nombreArchivo);

    /*Metodos*/
    bool guardar(Empleado registro);
    int getCantidadRegistros();
    Empleado leer(int pos);
    int buscar(std::string dniEmpleado);
    bool modificarEmpleado(Empleado e, int pos);
};




