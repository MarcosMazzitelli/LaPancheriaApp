#pragma once
#include <string>

class PersonaManager{
    private:

    public:
        int cantidadRegistrosEmpleado();

        void cargarEmpleado();
        void listarEmpleados();
        void modificarEmpleados();
        void eliminarEmpleado();
        void listarEmpleadosDeBaja();
        void altaEmpleado();

        int cantidadRegistrosCliente();
        void cargarCliente(std::string &dniCliente);
        void listarClientes();
        void modificarCliente(std::string dniUsuario);
        void eliminarCliente();



};
