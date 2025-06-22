#pragma once
#include "Fecha.h"
#include <string>

class Validador{
private:

public:
    bool esDni(std::string &cadena);
    bool esEmail (std::string &cadena);
    bool contiene(std::string texto, std::string atributo);
    void validadorFiltroFecha(Fecha &fechaDesde, Fecha &fechaHasta);

};
