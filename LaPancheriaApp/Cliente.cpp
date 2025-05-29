#include "Cliente.h"

    Cliente::Cliente()
    :Persona(){

    }

    Cliente::Cliente(std::string nombre, std::string apellido, std::string dni)
    :Persona(nombre,apellido,dni){
    }
