#include "Cliente.h"
#include <iostream>
using namespace std;

/*Constructores por omisi�n (llamado al de clase Padre)*/
Cliente::Cliente()
    :Persona(){
}
/*Constructores por par�metros (llamando al de clase Padre)*/
Cliente::Cliente(std::string nombre, std::string apellido, std::string dni)
    :Persona(nombre,apellido,dni){
}
void Cliente::mostrarEnTabla(){
    cout << " -----------------------------------------------------------------------------"<< endl;
    cout << "                                  TABLA CLIENTE                               "<<endl;
    cout << " -----------------------------------------------------------------------------"<< endl;
    Persona::mostrarEnTabla();


}

