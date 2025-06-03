#include "CostoFijoArchivo.h"

//Constructor por omision
CostoFijoArchivo::CostoFijoArchivo(){
    _nombreArchivo="costoFijo.dat";
}
//Constructor por parametro
CostoFijoArchivo::CostoFijoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

//Metodos

bool CostoFijoArchivo::guardar(CostoFijo registro){
    FILE* pfile;
    bool result;

    pfile= fopen(_nombreArchivo.c_str(), "ab");

    if (pfile==nullptr){
        return false;
    }
    result = fwrite(&registro, sizeof(CostoFijo), 1, pfile);

    fclose(pfile);
    return result;
}


int CostoFijoArchivo::getCantidadRegistros(){
    FILE* pfile;
    int tamRegistro, total, cantidad;

    pfile= fopen(_nombreArchivo.c_str(), "rb");

    if(pfile==nullptr){
        return 0;
    }

    fseek(pfile,0,SEEK_END);

    total= ftell(pfile);
    cantidad= total/sizeof(CostoFijo);

    fclose(pfile);
    return cantidad;
}

