#pragma once
#include "Persona.h"
#include "Fecha.h"

class Empleado: public Persona{

 /*atributos propios*/
private:
    int _idEmpleado;
    char _contrasenia[30];
    int _permiso;
    char _puesto[30];
    float _sueldo;
    Fecha _fechaIngreso;
    Fecha _fechaNacimiento;
    bool _estado;
    char _email[50];
    char _nCelular[20];

public:
    /*constructores*/
    Empleado();
    Empleado(std::string nombre, std::string apellido, std::string dni, int idEmpleado, std::string contrasenia, int permiso, std::string puesto, float sueldo, Fecha fechaIngreso, Fecha fechaNacimiento, bool estado, std::string email, std::string cel);

    /*Setters*/
    void setIdEmpleado(int id);
    void setContrasenia(std::string contrasenia);
    void setPermiso(int permiso);
    void setPuesto(std::string puesto);
    void setSueldo(float sueldo);
    void setFechaIngreso(Fecha fecha);
    void setFechaNacimiento(Fecha fecha);
    void setEstado(bool estado);
    void setEmail(std::string email);
    void setNCelular(std::string celular);

    /*Getters*/
    int getIdEmpleado();
    std::string getContrasenia();
    int getPermiso();
    std::string getPuesto();
    float getSueldo();
    Fecha getFechaIngreso();
    Fecha getFechaNacimiento();
    bool getEstado();
    std::string getEmail();
    std::string getNCelular();

    /*metodo mostrar*/
    std::string mostrarToCsv();
    void mostrar();

};

