#pragma once
#include <string>


class FormaDePago{
private:
    int  _formaDePago;
    char _nombreFormaDePago[20];
    float _descuento;
    bool _estado;



public:
    FormaDePago();
    FormaDePago(int formaDePago, std::string nombreFormaDePago, float descuento, bool estado);

    //getters
    int getFormaDePago();
    std::string getNombreFormaDePago();
    float getDescuento();
    bool getEstado();



    //setters
    void setFormaDePago(int formaDePago);
    void setNombreFormaDePago(std::string nombreFormaDePago);
    void setDescuento (float descuento);
    void setEstado (bool estado);

    //metodos
    void cargarFormaDePago(); //agregar una forma de pago nueva
    void elegirFormaDePago(int &opc); //la usamos cuando cargamos una venta
    void mostrarTabla();
    void mostrarEnLista();
    void mostrar();
    std::string mostrarToCsv();
    void opcionesFormasDePago();

};

