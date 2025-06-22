#include <iostream>
#include "Fecha.h"

using namespace std;

Fecha::Fecha(){
    _dia=0;
    _mes=0;
    _anio=0;
}

bool Fecha::cargar(){
    int m, d, a;
        cout<<"Ingrese dia: ";
        cin>>d;
        cout<<"Ingrese mes: ";
        cin>>m;
        cout<<"Ingrese anio: ";
        cin>>a;

        if (!setFecha(d,m,a)){
            return false;
        }
        return true;
}

bool Fecha::esDiaValido(int d){
    if(d >= 1 && d <= 31){
        return true;
    }
    return false;
}

bool Fecha::esMesValido(int m){
    if(m >= 1 && m <= 12){
        return true;
    }
    return false;
}

bool Fecha::esDiaValidoEnMes(int d, int m, int a){
    switch (m) {
        case 4: case 6: case 9: case 11: //abril, junio, septiembre, noviembre
            if (d > 30){
                return false;
            }
            else {
                return true;
            }
            //no hace faltan los break luego de los return
        case 2: // Febrero
            if (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0)){
                if (d > 29){
                    return false;
                }
                else{
                    return true;
                }
            }else {
                if (d > 28){
                    return false;
                }
                else{
                    return true;
                }
            }
            //no hace faltan los break luego de los return
        default: //resto de los meses
            if (d >31){
                return false;
            }
            else{
                return true;
            }
    }

}

bool Fecha::esAnioValido(int a){
    if(a >= 1){
        return true;
    }
    return false;
}



bool Fecha::setFecha(int d, int m, int a){
    if(!esDiaValido(d)
    || !esMesValido(m)
    || !esAnioValido(a)
    || !esDiaValidoEnMes(d,m,a))
    {
        return false;
    }
    _dia=d;
    _mes=m;
    _anio=a;
    return true;
}


std::string Fecha::mostrarFecha(){
    string str = "";

    str = to_string(_dia) + "/";
    str+= to_string(_mes) + "/";
    str+= to_string(_anio);

    return str;
}

int Fecha::getDia(){
    return _dia;
}
int Fecha::getMes(){
    return _mes;
}
int Fecha::getAnio(){
    return _anio;
}
bool Fecha::operator==(Fecha aux){
    if(_dia!=aux._dia){
        return false;
    }
    if(_mes!=aux._mes){
        return false;
    }
    if(_anio!=aux._anio){
        return false;
    }
    return true;
}
