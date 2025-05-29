#pragma once
#include "Persona.h"

class Cliente: public Persona{

private:

public:
    /*constructores por omisión*/
    Cliente();

    /*contructor por parametros*/
    Cliente(std::string nombre, std::string apellido, std::string dni);
};

