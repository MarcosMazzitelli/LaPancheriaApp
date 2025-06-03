#include "FormaDePagoArchivo.h"

//Constructor por omision
FormaDePagoArchivo::FormaDePagoArchivo(){
    _nombreArchivo="formaDePago.dat";
}

//Constructor por parametro
FormaDePagoArchivo::FormaDePagoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

//Metodos
bool FormaDePagoArchivo::guardar(FormaDePago registro){
    FILE* pfile;
    bool result;

    pfile= fopen(_nombreArchivo.c_str(), "ab");

    if (pfile==nullptr){
        return false;
    }
    result = fwrite(&registro, sizeof(FormaDePago), 1, pfile);

    fclose(pfile);
    return result;
}

int FormaDePagoArchivo::getCantidadRegistros(){
    FILE* pfile;
    int tamRegistro, total, cantidad;

    pfile= fopen(_nombreArchivo.c_str(), "rb");

    if(pfile==nullptr){
        return 0;
    }

    fseek(pfile,0,SEEK_END);

    total= ftell(pfile);
    cantidad= total/sizeof(FormaDePago);

    fclose(pfile);
    return cantidad;
}
