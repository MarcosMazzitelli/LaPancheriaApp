#include "ArchivoDetalleIngrediente.h"

///Constructores
ArchivoDetalleIngrediente::ArchivoDetalleIngrediente(){
    _nombreArchivo= "DetalleIngredientes.dat";
}
ArchivoDetalleIngrediente::ArchivoDetalleIngrediente(std::string nombreArchivo){
    _nombreArchivo= nombreArchivo;
}


///Metodos
bool ArchivoDetalleIngrediente::guardar(DetalleIngrediente registro){
    FILE* pFile;
    bool result;

    pFile= fopen(_nombreArchivo.c_str(), "ab");

    if (pFile==nullptr){
        return false;
    }

    result = fwrite(&registro, sizeof(DetalleIngrediente), 1, pFile);

    fclose(pFile);
    return result;
}

int ArchivoDetalleIngrediente::getCantidadRegistros(){
    FILE* pFile;
    int tamRegistro, total, cantidad;

    pFile= fopen(_nombreArchivo.c_str(), "rb");

    if (pFile==nullptr){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    total = ftell(pFile);

    cantidad = total / sizeof(DetalleIngrediente);

    fclose(pFile);
    return cantidad;
}

DetalleIngrediente ArchivoDetalleIngrediente::leer(int pos){

    FILE* pFile;
    DetalleIngrediente registro;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if (pFile==nullptr){
        return registro;
    }

    fseek(pFile, sizeof(DetalleIngrediente) * pos , SEEK_SET);
    fread(&registro, sizeof(DetalleIngrediente), 1, pFile);

    fclose(pFile);
    return registro;
}

