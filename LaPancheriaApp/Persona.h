#pragma once
#include <string>

class Persona{

    /*Atributos*/
private:
    char _nombre[50];
    char _apellido[50];
    char _dni[10];

public:
    /*Constuctores*/
    Persona();
    Persona(std::string nombre, std::string apellido, std::string dni);

    /*Setters*/
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);

    /*Getters*/
    std::string getNombre();
    std::string getApellido();
    std::string getDni();

    /*metodos mostrar*/
    void mostrar();
    std::string mostrarToCsv();
    void mostrarEnTabla();

};
