#include "DetalleVentaArchivo.h"

//Constructor por omision
DetalleVentaArchivo::DetalleVentaArchivo(){
    _nombreArchivo="detalleVenta.dat";

}

//Constructor por parametro
DetalleVentaArchivo::DetalleVentaArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

bool DetalleVentaArchivo::guardar(DetalleVenta registro){
    FILE* pfile;
    bool result;

    pfile= fopen(_nombreArchivo.c_str(),"ab");
    if(pfile==nullptr){
        return false;
    }
    result = fwrite(&registro, sizeof(DetalleVenta),1, pfile);
    fclose(pfile);
    return result;

}

int DetalleVentaArchivo::getCantidadRegistros(){

    FILE* pfile;
    int tamRegistro,total,cantidad;


    pfile= fopen(_nombreArchivo.c_str(),"rb");
    if (pfile==nullptr){
        return 0;
    }
    fseek(pfile,0,SEEK_END);
    total= ftell(pfile);
    cantidad= total/ sizeof(DetalleVenta);


    fclose(pfile);
    return cantidad;

}

