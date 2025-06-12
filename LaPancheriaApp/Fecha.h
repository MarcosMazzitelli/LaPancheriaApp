#pragma once
#include <string>

class Fecha{
    private:
        int _dia, _mes, _anio;

        bool esDiaValido(int d);
        bool esMesValido(int m);
        bool esAnioValido(int a);
        bool esDiaValidoEnMes(int d, int m, int a);

    public:

        Fecha();
        bool cargar();
        bool setFecha(int d, int m, int a);
        int getDia();
        int getMes();
        int getAnio();
        std::string mostrarFecha();
};


