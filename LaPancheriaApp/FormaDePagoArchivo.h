#pragma once
#include "FormaDePago.h"
#include <string>

class FormaDePagoArchivo{
private:
    std::string _nombreArchivo;
public:
    //Constructores
    FormaDePagoArchivo();
    FormaDePagoArchivo(std::string nombreArchivo);

    //Metodos

    bool guardar(FormaDePago registro);
    bool guardar(FormaDePago registro, int posicion); //PARA GUARDAR UN REGISTRO MODIFICADO
    int getCantidadRegistros();
    int buscarFormaDePago(int formaDePago); //busca la forma de pago por el numero
    FormaDePago leer(int posicion);
    bool modificarDescuentoFormaDePago();

};



