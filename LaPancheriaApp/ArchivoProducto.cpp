#include "ArchivoProducto.h"

///Constructores
ArchivoProducto::ArchivoProducto(){
    _nombreArchivo= "Productos.dat";
}
ArchivoProducto::ArchivoProducto(std::string nombreArchivo){
    _nombreArchivo= nombreArchivo;
}


///Metodos
bool ArchivoProducto::guardar(Producto registro){
    FILE* pFile;
    bool result;

    pFile= fopen(_nombreArchivo.c_str(), "ab");

    if (pFile==nullptr){
        return false;
    }

    result = fwrite(&registro, sizeof(Producto), 1, pFile);

    fclose(pFile);
    return result;
}

int ArchivoProducto::getCantidadRegistros(){
    FILE* pFile;
    int tamRegistro, total, cantidad;

    pFile= fopen(_nombreArchivo.c_str(), "rb");

    if (pFile==nullptr){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    total = ftell(pFile);

    cantidad = total / sizeof(Producto);

    fclose(pFile);
    return cantidad;
}

Producto ArchivoProducto::leer(int pos){
FILE* pFile;
Producto registro;

pFile = fopen(_nombreArchivo.c_str(), "rb");

if (pFile==nullptr){
    return registro;
}

fseek(pFile, sizeof(Producto) * pos , SEEK_SET);
fread(&registro, sizeof(Producto), 1, pFile);

fclose(pFile);
return registro;
}

