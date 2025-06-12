#pragma once
#include <iostream>

class PersonaManager{
    private:

    public:
        int cantidadRegistrosEmpleado();

        void cargarEmpleado();
        void listarEmpleados();
        void modificarEmpleados(std::string dni);
        void eliminarEmpleado();
        void listarEmpleadosDeBaja();

        int cantidadRegistrosCliente();
        void cargarCliente();
        void listarClientes();
        void modificarCliente(std::string dniUsuario);
        void eliminarCliente();



};
