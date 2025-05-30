#include "DetalleVenta.h"

//Constructor por omision
DetalleVentaArchivo::DetalleVentaArchivo(){
    _nombreArchivo="detalleVenta.dat";

}

//Constructor por parametro
DetalleVentaArchivo::DetalleVentaArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}
