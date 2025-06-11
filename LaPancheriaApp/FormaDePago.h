#ifndef FORMADEPAGO_H_INCLUDED
#define FORMADEPAGO_H_INCLUDED
#include <string>


class FormaDePago{
private:
    int  _formaDePago;
    char _nombreFormaDePago[20];
    float _descuento;



public:
    FormaDePago();
    FormaDePago(int formaDePago, std::string nombreFormaDePago, float descuento);

    //getters
    int getFormaDePago();
    std::string getNombreFormaDePago();
    float getDescuento();



    //setters
    void setFormaDePago(int formaDePago);
    void setNombreFormaDePago(std::string nombreFormaDePago);
    void setDescuento (float descuento);

    //metodos
    void cargarFormaDePago();
    void elegirFormaDePago();
    void mostrarTabla();
    void mostrarEnLista();
    void mostrar();
    std::string mostrarToCsv();

};

#endif // FORMADEPAGO_H_INCLUDED
