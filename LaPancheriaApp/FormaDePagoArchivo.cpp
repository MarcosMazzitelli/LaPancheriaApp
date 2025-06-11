#include "FormaDePagoArchivo.h"
#include <cstring>
#include <iostream>
using namespace std;

//Constructor por omision
FormaDePagoArchivo::FormaDePagoArchivo(){
    _nombreArchivo="formaDePago.dat";
}

//Constructor por parametro
FormaDePagoArchivo::FormaDePagoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

//Metodos
bool FormaDePagoArchivo::guardar(FormaDePago registro){
FILE *pFile;
bool result;

pFile= fopen(_nombreArchivo.c_str(), "ab");

if (pFile==nullptr){
    return false;
}
result = fwrite(&registro, sizeof(FormaDePago), 1, pFile);

fclose(pFile);
return result;
}


int FormaDePagoArchivo::getCantidadRegistros(){
FILE *pFile;
int tamRegistro, total, cantidad;

pFile= fopen(_nombreArchivo.c_str(), "rb");

if(pFile==nullptr){
    return 0;
}

fseek(pFile,0,SEEK_END);

total= ftell(pFile);
cantidad= total/sizeof(FormaDePago);

fclose(pFile);
return cantidad;
}


int FormaDePagoArchivo::buscarFormaDePago(int formaDePago){
FormaDePago fdp;
FormaDePagoArchivo archi;

int cantRegistros=archi.getCantidadRegistros();
int posicion=0;

for(int i=0; i<cantRegistros;i++){
    fdp=archi.leer(i);

    if(fdp.getFormaDePago()==formaDePago){
        return posicion;
    }
    posicion++;
}
return -1;
}

//PARA GUARDAR UN REGISTRO MODIFICADO
bool FormaDePagoArchivo::guardar(FormaDePago registro, int posicion){
FILE *pFile;
bool result;

pFile= fopen(_nombreArchivo.c_str(), "rb+");

    if(pFile==nullptr){
        cout<<"No se pudo abrir el archivo"<<endl;
        return false;
}
fseek(pFile,posicion*sizeof(FormaDePago),SEEK_SET);
result= fwrite(&registro, sizeof(FormaDePago), 1, pFile);
fclose(pFile);
return result;
}

FormaDePago FormaDePagoArchivo::leer(int posicion){
FILE *pFile;
FormaDePago fdp;
fdp.setFormaDePago(-1);
pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr){
    cout<<"No se pudo abrir el archivo"<<endl;
    return fdp;
}
fseek(pFile,posicion*sizeof(FormaDePago),0);
fread(&fdp,sizeof(FormaDePago),1,pFile);
fclose(pFile);
return fdp;
}

bool FormaDePagoArchivo::modificarDescuentoFormaDePago(){
int nroFdp, posicion;
float desc;
bool modificado=false;

while(!modificado){
cout<<"Ingrese la forma de pago que quiere modificar:  1) Efectivo 2)Debito 3) Credito "<<endl;
cin>> nroFdp;

FormaDePagoArchivo archi;
posicion=archi.buscarFormaDePago(nroFdp);

if(posicion>=0){
    FormaDePago fdp = archi.leer(posicion);
    cout<<"Ingresa el nuevo descuento"<< endl;
    cin>> desc;
    fdp.setDescuento(desc);

    if(archi.guardar(fdp, posicion)){
        cout<<"Descuento mofidicado correctamente"<< endl;
        modificado=true;
    }
    else{
        cout<<"No se pudo mofidicar el descuento"<< endl;
        modificado=false;
    }
}
    else{
        cout<<"No existe la Forma de Pago elegida"<< endl;
        modificado=false;
    }
}
return modificado;
}
