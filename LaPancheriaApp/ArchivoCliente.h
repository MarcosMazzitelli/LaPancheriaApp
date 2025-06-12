#pragma once
#include "Cliente.h"

#include <string>

class ArchivoCliente{

    private:
        std::string _nombreArchivo;
    public:
        /*Constructores*/
        ArchivoCliente();
        ArchivoCliente(std::string _nombreArchivo);

        /*Metodos*/
        bool guardar(Cliente registro);
        int getCantidadRegistros();
        Cliente leer(int pos);
};



