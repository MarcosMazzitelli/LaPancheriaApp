#include "VentaArchivo.h"

///Constructor vacio
VentaArchivo::VentaArchivo(){
    _nombreArchivo="venta.dat";

}

//Constructor por parametro
VentaArchivo::VentaArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}
