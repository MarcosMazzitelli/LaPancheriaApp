#include "Venta.h"
#include <cstring>
using namespace std;

///Constructor por ominisi�n
Venta::Venta(){
    _nroFactura=0;
    strcpy(_dniCliente,"");
    _idEmpleado=0;
    _importeTotal=0;
    _formaDePago=0;
    _fechaVenta=Fecha(); //llama al constructor vacio de fecha

}

///Constructor por parametros
Venta::Venta(int nroFactura, std::string dniCliente, int idEmpleado, float importeTotal, int formaDePago,Fecha fechaVenta){
        setNroFactura(nroFactura);
        setDniCliente(dniCliente);
        setIdEmpleado(idEmpleado);
        setImporteTotal(importeTotal);
        setFormaDePago(formaDePago);
        setFechaVenta(fechaVenta);
}

///Getters
    int Venta::getNroFactura(){
    return _nroFactura;
    }
    std::string Venta::getDniCliente(){
    return _dniCliente;
    }
    int Venta::getIdEmpleado(){
    return _idEmpleado;
    }
    float Venta::getImporteTotal(){
    return _importeTotal;
    }
    int Venta::getFormaDePago(){
    return _formaDePago;
    }
    Fecha Venta::getFechaVenta(){
    return _fechaVenta;
    }



///Setters
    void Venta::setNroFactura(int nroFactura){
        _nroFactura=nroFactura;
    }
    void Venta::setDniCliente( std::string dniCliente){
        strcpy(_dniCliente,dniCliente.c_str());
       // _dniCliente=dniCliente;
    }
    void Venta::setIdEmpleado(int idEmpleado){
        _idEmpleado=idEmpleado;
    }
    void Venta::setImporteTotal(float importeTotal){
        _importeTotal=importeTotal;
    }
    void Venta::setFormaDePago(int formaDePago){
        _formaDePago=formaDePago;
    }
    void Venta::setFechaVenta(Fecha fechaVenta){
        _fechaVenta=fechaVenta;
    }


