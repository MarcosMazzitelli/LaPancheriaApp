#pragma once
#include <string>

class MenuManager{
private:

public:

    void login();
    void menuAdmin(std::string dni);
    void menuEmpleados(std::string dni);
    void menuProductos();
    void menuIngredientes();
    void menuCostos();
    void menuReportes();
    void menuVentas(std::string dni);
    void menuVentasRestringido(std::string dni);

};
