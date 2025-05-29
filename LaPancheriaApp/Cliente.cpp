#include "Cliente.h"

/*Constructores por omisión (llamado al de clase Padre)*/
Cliente::Cliente()
    :Persona(){
}
/*Constructores por parámetros (llamando al de clase Padre)*/
Cliente::Cliente(std::string nombre, std::string apellido, std::string dni)
    :Persona(nombre,apellido,dni){
}
