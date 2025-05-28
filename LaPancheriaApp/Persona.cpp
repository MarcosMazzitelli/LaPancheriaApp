#include "Persona.h"
#include <cstring>

Persona::Persona(){

    strcpy(_nombre,"");
    _apellido[0]='\0';
    _dni[0]='\0';
}
Persona::Persona(std::string nombre, std::string apellido, std::string dni){
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
}

std::string Persona::getNombre(){
    return _nombre;
}
std::string Persona::getApellido(){
    return _apellido;
}
std::string Persona::getDni(){
    return _dni;
}

void Persona::setNombre(std::string nombre){
    strcpy(_nombre,nombre.c_str());
}
void Persona::setApellido(std::string apellido){
    _apellido=apellido;
}
void Persona::Persona(std::string dni){
    _dni=dni;
}





