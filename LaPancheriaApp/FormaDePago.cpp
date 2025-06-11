#include "FormaDePago.h"
#include "FormaDePagoArchivo.h"
#include <cstring>
#include <iostream>
using namespace std;

//Constructor por ominisión
FormaDePago::FormaDePago(){
    _formaDePago=0;
    strcpy(_nombreFormaDePago, "");
    _descuento=0,0;
}

//Constructor por parametros
FormaDePago::FormaDePago(int formaDePago, std::string nombreFormaDePago, float descuento){
        setFormaDePago(formaDePago);
        setNombreFormaDePago(nombreFormaDePago);
        setDescuento(descuento);
}

///Getters
int FormaDePago::getFormaDePago(){
return _formaDePago;
}
std::string FormaDePago::getNombreFormaDePago(){
return _nombreFormaDePago;
}
float FormaDePago::getDescuento(){
return _descuento;
}



//Setters
void FormaDePago::setFormaDePago(int formaDePago){
    _formaDePago=formaDePago;
}
void FormaDePago::setNombreFormaDePago(std::string nombreFormaDePago){
strcpy(_nombreFormaDePago,nombreFormaDePago.c_str());
}
void FormaDePago::setDescuento(float descuento){
    _descuento=descuento;
}



    //METODOS

void FormaDePago::cargarFormaDePago(){
int formaDePago;
string nombreFormaDePago;
float descuento;
FormaDePago f;
FormaDePagoArchivo archi;
bool bandera=false;
while(!bandera){

formaDePago=archi.getCantidadRegistros()+1;

cout << "Ingrese el nombre" << endl;
cin.ignore();
getline(cin,nombreFormaDePago);

bool validar=false;
while(!validar){
cout << "Ingrese el descuento" << endl;
cin >> descuento;
if(descuento<0){ //falta validar que sea numero
    cout<<"Valor incorrecto"<<endl;
    validar=false;
}
else{
   validar=true;
}
}

f = FormaDePago(formaDePago, nombreFormaDePago, descuento);

if(archi.guardar(f)){
    cout<<"Forma de pago guardada con exito"<< endl << endl;
}
else{
    cout<<"Hubo un problema al guardar la Forma de pago"<< endl << endl;
}
int opcion;
cout<<"Desea cargar otra forma de pago? 1)Si 0)no"<<endl;
cin>> opcion;
if(opcion==0){
    bandera=true;
}
else{
    bandera=false;
}
}
}

void FormaDePago::mostrar(){
    cout << "N de forma de pago: " << getFormaDePago() << endl;
    cout << "Nombre de forma de pago: " << getNombreFormaDePago() << endl;
    cout << "Descuento aplicado: " << getDescuento() << endl;
}

std::string FormaDePago::mostrarToCsv(){
    string str = "";

    str = to_string(_formaDePago) + ",";
    str+= string(_nombreFormaDePago) + ",";
    str+= to_string(_descuento);

    return str;
}



