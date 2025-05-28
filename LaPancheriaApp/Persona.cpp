#include "Persona.h"
#include <cstring>
#include <iostream>
using namespace std;

/*Constructores por omisión*/
Persona::Persona(){
    strcpy(_nombre,"");
    strcpy(_apellido,"");
    strcpy(_dni,"");
}

/*Constructor por parametros*/
Persona::Persona(std::string nombre, std::string apellido, std::string dni){
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
}

/*Getter*/
std::string Persona::getNombre(){
    return _nombre;
}

std::string Persona::getApellido(){
    return _apellido;
}

std::string Persona::getDni(){
    return _dni;
}

/*Setters*/
void Persona::setNombre(std::string nombre){
    strcpy(_nombre,nombre.c_str());
}

void Persona::setApellido(std::string apellido){
    strcpy(_apellido,apellido.c_str());
}

void Persona::setDni(std::string dni){
    strcpy(_dni,dni.c_str());
}

/*Metodos mostrar*/
void Persona::mostrar(){
    cout << "Nombre: " << getNombre() << endl;
    cout << "Nombre: " << getApellido() << endl;
    cout << "Nombre: " << getDni() << endl;
}

std::string Persona::mostrarToCsv(){
    string str = "";

    str = string(_nombre) + ",";
    str+= string(_apellido) + ",";
    str+= string(_dni);

    return str;
}




