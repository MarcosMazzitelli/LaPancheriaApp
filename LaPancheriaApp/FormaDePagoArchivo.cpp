#include "FormaDePagoArchivo.h"

//Constructor por omision
FormaDePagoArchivo::FormaDePagoArchivo(){
    _nombreArchivo="formaDePago.dat";

}

//Constructor por parametro
FormaDePagoArchivo::FormaDePagoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}
