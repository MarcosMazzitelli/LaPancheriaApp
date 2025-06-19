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
