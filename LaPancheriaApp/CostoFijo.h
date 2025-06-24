#ifndef COSTOFIJO_H_INCLUDED
#define COSTOFIJO_H_INCLUDED
#include <string>
#include "Fecha.h"

class CostoFijo{
private:
    int  _idCosto;
    char _nombreCosto[20];
    float _precio;
    Fecha _fechaCosto;
     bool _estado;


public:
    CostoFijo();
    CostoFijo(int idCosto, std::string nombreCosto, float precio, Fecha fechaCosto, bool estado);

    int getIdCosto();
    std::string getNombreCosto();
    float getPrecio();
    Fecha getFechaCosto();
    bool getEstado();


    void setIdCosto(int idCosto);
    void setNombreCosto(std::string nombreCosto);
    void setPrecio (float precio);
    void setFechaCosto(Fecha fechaCosto);
    void setEstado(bool estado);

    //void mostrar();
    //std::string mostrarToCsv();
    void mostrarEnLista();
    void mostrarTabla();
};



#endif // COSTOFIJO_H_INCLUDED
