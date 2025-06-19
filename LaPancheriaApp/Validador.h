#pragma once
#include <string>

class Validador{
private:

public:
    bool esDni(std::string &cadena);
    bool esNumero (std::string &cadena);
    bool esEmail (std::string &cadena);


};
