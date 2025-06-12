#pragma once
#include <string>
#include "Empleado.h"

class MenuManager{
private:

public:

    void login();
    void menuAdmin(std::string dni);
    void menuEmpleados(std::string dni);
    void menuProductos();
    void menuIngredientes();
    void menuCostos();


};
