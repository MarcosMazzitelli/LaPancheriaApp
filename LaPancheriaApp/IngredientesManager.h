#pragma once

class IngredientesManager{
private:

public:
    void cargarIngrediente();
    void modificarIngrediente();
    void mostrarIngredientesCompletos(bool estado);
    int cantidadRegistros();
    void listarIngredientes(bool estado);
    void comprarIngrediente();
    void modificarStock();
    void eliminarIngrediente();
    void darAltaIngrediente();
};
