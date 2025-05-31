#ifndef COSTOFIJO_H_INCLUDED
#define COSTOFIJO_H_INCLUDED
#include <string>

class CostoFijo{
private:
    float _precio;
    int  _idCosto;

public:
    CostoFijo();
    CostoFijo(float precio, int idCosto);

    float getPrecio();
    int getIdCosto();

    void setPrecio (float precio);
    void setIdCosto(int idCosto);

    void mostrar();
    std::string mostrarToCsv();
};



#endif // COSTOFIJO_H_INCLUDED
