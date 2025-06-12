#include "FormaDePago.h"
#include "FormaDePagoArchivo.h"
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

//Constructor por ominisi�n
FormaDePago::FormaDePago(){
    _formaDePago=0;
    strcpy(_nombreFormaDePago, "");
    _descuento=0,0;
    _estado=true;
}

//Constructor por parametros
FormaDePago::FormaDePago(int formaDePago, std::string nombreFormaDePago, float descuento, bool estado){
        setFormaDePago(formaDePago);
        setNombreFormaDePago(nombreFormaDePago);
        setDescuento(descuento);
        setEstado(estado);
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
bool FormaDePago::getEstado(){
return _estado;
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
void FormaDePago::setEstado(bool estado){
    _estado=estado;
}



    //METODOS

void FormaDePago::cargarFormaDePago(){
int formaDePago;
string nombreFormaDePago;
float descuento;
FormaDePago f;
FormaDePagoArchivo archi;
bool bandera=false;
bool estado=true;

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

f = FormaDePago(formaDePago, nombreFormaDePago, descuento, estado);

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

void FormaDePago::elegirFormaDePago(){

FormaDePago fdp;
FormaDePagoArchivo aFdp;
int cantRegistros=aFdp.getCantidadRegistros();

cout<<"FORMAS DE PAGO"<<endl;
fdp.mostrarTabla();
cout<<endl;
cout<<"-----------------------------------------------------------"<<endl;

for(int i=0;i<cantRegistros;i++){
    fdp=aFdp.leer(i);
    fdp.mostrarEnLista();
}
cout<<"-----------------------------------------------------------"<<endl;

bool confirmacion=false;
int opc, opcion;

while(!confirmacion){
cout<<"Elija la forma de pago"<<endl;
cin>> opc;

for(int i=0;i<cantRegistros;i++){

fdp=aFdp.leer(i);
bool bandera=false;

if(fdp.getFormaDePago()==opc && fdp.getEstado()==true){
while(!bandera){

cout<<"Desea confirmar esta opcion? 1)Si 0)No"<<endl;
cin>>opcion;

if(opcion==1){
    confirmacion=true;
    bandera=true;
}else{
    if(opcion==0){
        confirmacion=false;
        bandera=true;
    }else{
        cout<<"Ingrese una opcion valida"<<endl;
        bandera=false;}
     }
    }
   }
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

void FormaDePago::mostrarTabla(){
cout << left << setw(20) << "NRO Forma De Pago";
cout << left << setw(20) << "Nombre Forma De Pago";
cout << left << setw(20) << "Descuento";
}

void FormaDePago::mostrarEnLista(){
FormaDePago fdp;
FormaDePagoArchivo aFdp;
int cantRegistros=aFdp.getCantidadRegistros();
for(int i=0; i<cantRegistros; i++){
fdp=aFdp.leer(i);
if(fdp.getEstado()==true){
cout << left << setw(20) << getFormaDePago();
cout << left << setw(20) << getNombreFormaDePago();
cout << left << setw(20) << getDescuento();
}
}
}


