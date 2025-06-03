#include "VentaArchivo.h"

///Constructor vacio
VentaArchivo::VentaArchivo(){
    _nombreArchivo="venta.dat";

}

//Constructor por parametro
VentaArchivo::VentaArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}
//Metodos
//Cargar un Registro
bool VentaArchivo::guardar(Venta registro){
    FILE* pfile;
    bool result;

    pfile= fopen(_nombreArchivo.c_str(),"ab");
    if(pfile==nullptr){
        return false;
    }
    result = fwrite(&registro, sizeof(Venta),1, pfile);
    fclose(pfile);
    return result;

}
//Leer un Archivo
int VentaArchivo::getCantidadRegistros(){

    FILE* pfile;
    int tamRegistro,total,cantidad;


    pfile= fopen(_nombreArchivo.c_str(),"rb");
    if (pfile==nullptr){
        return 0;
    }
    fseek(pfile,0,SEEK_END);
    total= ftell(pfile);
    cantidad= total/ sizeof(Venta);


    fclose(pfile);
    return cantidad;

}
