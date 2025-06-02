#include "ArchivoIngrediente.h"

///Constructores
ArchivoIngrediente::ArchivoIngrediente(){
    _nombreArchivo= "Ingredientes.dat";
}
ArchivoIngrediente::ArchivoIngrediente(std::string nombreArchivo){
    _nombreArchivo= nombreArchivo;
}


///Metodos
bool ArchivoIngrediente::guardar(Ingrediente registro){
    FILE* pFile;
    bool result;

    pFile= fopen(_nombreArchivo.c_str(), "ab");

    if (pFile==nullptr){
        return false;
    }

    result = fwrite(&registro, sizeof(Ingrediente), 1, pFile);

    fclose(pFile);
    return result;
}

int ArchivoIngrediente::getCantidadRegistros(){
    FILE* pFile;
    int tamRegistro, total, cantidad;

    pFile= fopen(_nombreArchivo.c_str(), "rb");

    if (pFile==nullptr){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    total = ftell(pFile);

    cantidad = total / sizeof(Ingrediente);

    fclose(pFile);
    return cantidad;
}
