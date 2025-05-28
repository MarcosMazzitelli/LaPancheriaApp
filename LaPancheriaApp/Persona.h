#pragma once
#include <string>

class Persona{

private:
    char _nombre[50];
    char _apellido[50];
    char _dni[10];

public:
    Persona();
    Persona(std::string nombre, std::string apellido, std::string dni);

    std::string getNombre();
    std::string getApellido();
    std::string getDni();

    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);

};
