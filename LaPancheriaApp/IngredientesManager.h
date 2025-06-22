#pragma once
#include "Ingrediente.h"

class IngredientesManager{
private:

public:

    ///Metodos principales
    void cargarIngrediente();
    void comprarIngrediente();

    ///ABML
    void modificarIngrediente();
    void menuModificacion(Ingrediente &ing, int &pos);
    void modificarStock();
    void eliminarIngrediente();
    void darAltaIngrediente();


    ///listados
    void listarIngredientes(bool estado);
    void mostrarIngredientesCompletos(bool estado);
};
