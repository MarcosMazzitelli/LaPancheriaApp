#ifndef FORMADEPAGO_H_INCLUDED
#define FORMADEPAGO_H_INCLUDED
#include <string>

class FormaDePago{
private:
    int  _formaDePago;
    float _descuento;
    char _nombreFormaDePago[20];

public:
    FormaDePago();
    FormaDePago(int formaDePago, float descuento, std::string nombreFormaDePago);

    int getFormaDePago();
    float getDescuento();
    std::string getNombreFormaDePago();


    void setFormaDePago(int formaDePago);
    void setDescuento (float descuento);
    void setNombreFormaDePago(std::string nombreFormaDePago);

    void mostrar();
    std::string mostrarToCsv();


};

#endif // FORMADEPAGO_H_INCLUDED
