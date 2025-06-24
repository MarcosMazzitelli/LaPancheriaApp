#include "Validador.h"
#include <regex>
#include <iostream>
using namespace std;

bool Validador::esDni(std::string &cadena){
    regex expReg("[0-9]{7,8}");

    return regex_match(cadena, expReg);

}

bool Validador::esEmail (std::string &cadena){
    regex expReg(R"(^[A-Z0-9._+-]+@[A-Z0-9]+\.[A-Z.-]{1,}$)", regex::icase);

    return regex_match(cadena, expReg);

}

bool Validador::esTexto(std::string &cadena){
    std::regex expReg("^[A-Za-z]+( [A-Za-z]+)*$");

    return std::regex_match(cadena, expReg);
}

bool Validador::esNumero(std::string &cadena){
    std::regex expReg("^[0-9]+$");

    return std::regex_match(cadena, expReg);
}

bool Validador::contiene(std::string texto, std::string atributo){
    regex patron(texto, regex::icase);
    return regex_search(atributo, patron);

}
void Validador::validadorFiltroFecha(Fecha &fechaDesde, Fecha &fechaHasta){
    bool rangoFechaIncorrecto=true;
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout << "FECHA INICIO BALANCE" << endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    fechaDesde.cargar();
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout << "FECHA FIN BALANCE" << endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl;
    fechaHasta.cargar();

    if (fechaDesde <= fechaHasta){
        rangoFechaIncorrecto=false;
    }

    while(rangoFechaIncorrecto){
        system("cls");
        cout << "Las fechas ingresadas son invalidas. " << endl;
        cout <<  "--------------------------------------------------------------------------------"<< endl;
        cout << "FECHA INICIO BALANCE" << endl;
        cout <<  "--------------------------------------------------------------------------------"<< endl;
        fechaDesde.cargar();
        cout <<  "--------------------------------------------------------------------------------"<< endl;
        cout << "FECHA FIN BALANCE" << endl;
        cout <<  "--------------------------------------------------------------------------------"<< endl;
        fechaHasta.cargar();
        if (fechaDesde <= fechaHasta){
            rangoFechaIncorrecto=false;
        }
    }
}
