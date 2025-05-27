#include "CostoFijoArchivo.h"

//Constructor por omision
CostoFijoArchivo::CostoFijoArchivo(){
    _nombreArchivo="costoFijo.dat";

}

//Constructor por parametro
CostoFijoArchivo::CostoFijoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}
