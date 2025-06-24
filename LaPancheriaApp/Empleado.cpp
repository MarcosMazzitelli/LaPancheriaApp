#include "Empleado.h"
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

/*contructor por omisión*/
Empleado::Empleado()
:Persona(){
    _idEmpleado=0;
    _permiso=0;
    strcpy(_puesto,"");
    _sueldo=0.0f;
    _fechaIngreso= Fecha();
    _fechaNacimiento=Fecha();
    _estado=true;
    strcpy(_email,"");
    strcpy(_nCelular,"");
}

/*contructor por parametros*/
 Empleado::Empleado(std::string nombre, std::string apellido, std::string dni, int idEmpleado, std::string contrasenia, int permiso, std::string puesto, float sueldo, Fecha fechaIngreso, Fecha fechaNacimiento, bool estado, std::string email, std::string cel)
 :Persona(nombre, apellido,dni){
     setIdEmpleado(idEmpleado);
     setContrasenia(contrasenia);
     setPermiso(permiso);
     setPuesto(puesto);
     setSueldo(sueldo);
     setFechaIngreso(fechaIngreso);
     setFechaNacimiento(fechaNacimiento);
     setEstado(estado);
     setEmail(email);
     setNCelular(cel);
 }

 /*Setters*/
void Empleado::setIdEmpleado(int id){
    _idEmpleado=id;
}
void Empleado::setContrasenia(std::string contrasenia){
    strcpy(_contrasenia,contrasenia.c_str());
}
void Empleado::setPermiso(int permiso){
    _permiso=permiso;
}
void Empleado::setPuesto(std::string puesto){
    strcpy(_puesto,puesto.c_str());
}
void Empleado::setSueldo(float sueldo){
    _sueldo=sueldo;
}
void Empleado::setFechaIngreso(Fecha fecha){
    _fechaIngreso=fecha;
}
void Empleado::setFechaNacimiento(Fecha fecha){
    _fechaNacimiento=fecha;
}
void Empleado::setEstado(bool estado){
    _estado=estado;
}
void Empleado::setEmail(std::string email){
    strcpy(_email,email.c_str());
}
void Empleado::setNCelular(std::string celular){
    strcpy(_nCelular,celular.c_str());
}

/*Getters*/
int Empleado::getIdEmpleado(){
    return _idEmpleado;
}
std::string Empleado::getContrasenia(){
    return _contrasenia;
}
int Empleado::getPermiso(){
    return _permiso;
}
std::string Empleado::getPuesto(){
    return _puesto;
}
float Empleado::getSueldo(){
    return _sueldo;
}
Fecha Empleado::getFechaIngreso(){
    return _fechaIngreso;
}
Fecha Empleado::getFechaNacimiento(){
    return _fechaNacimiento;
}
bool Empleado::getEstado(){
    return _estado;
}
std::string Empleado::getEmail(){
    return _email;
}
std::string Empleado::getNCelular(){
    return _nCelular;
}

/*Metodo mostrar*/
void Empleado::mostrar(){
    Persona::mostrar();
    cout << "Id Empleado: " <<  getIdEmpleado() << endl;
    cout << "Contraseña: " << getContrasenia() << endl;
    cout << "Permiso: " << getPermiso() << endl;
    cout << "Puesto: " << getPuesto() << endl;
    cout << fixed << setprecision(2);
    cout << "Sueldo: " << getSueldo() << endl;
    cout << "Fecha de ingreso: " << getFechaIngreso().mostrarFecha()<< endl;
    cout << "Fecha de nacimiento: " << getFechaNacimiento().mostrarFecha()<< endl;
    cout << "Estado: " << getEstado() << endl;
    cout << "Email: " << getEmail() << endl;
    cout << "Celular: " << getNCelular() << endl;
}

void Empleado::mostrarEnTabla(){
    cout << " --------------------------------------------------------------------------------------------------------------------------"<< endl;
    cout << "                                            TABLA EMPLEADOS                             "<<endl;
    cout << " --------------------------------------------------------------------------------------------------------------------------"<< endl;
    cout << left << setw(15)<<"Id";
    Persona::mostrarEnTabla();
    cout << left << setw(30)<<"Puesto";
    cout << left << setw(30)<<"Sueldo" << endl;


}

