#include <cstring>
#include <iostream>
#include "CostosManager.h"
#include "CostoFijoArchivo.h"
#include "CostoFijo.h"
#include "Fecha.h"
using namespace std;

void CostosManager::cargarCostosFijos(){
int idCosto;
float precio;
string nombreCosto;
Fecha fechaCosto;
bool estado;
CostoFijo costo;
CostoFijoArchivo archi;

idCosto=archi.getCantidadRegistros()+1;

cout << "Ingrese nombre del costo fijo"<<endl;
//cin.ignore(); descomentar cuando este el menu
getline(cin,nombreCosto);

//validar que ingrese numero
bool validacion = false;

while(!validacion){
cout << "Ingrese el precio del costo fijo $"<<endl;
cin >> precio;
while(cin.fail()){
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Ingrese un valor valido" << endl << endl;
    cin >> precio;
}
if(precio<0){
    cout << "Ingrese un valor valido" << endl << endl;
}
else{
    validacion=true;
}
}

cout << "Ingrese la fecha del costo fijo " <<endl;

while(!fechaCosto.cargar()){
fechaCosto.cargar();
}

costo = CostoFijo(idCosto, nombreCosto, precio, fechaCosto, estado);

if(archi.guardar(costo)){
    cout<<"Costo Fijo guardado con exito"<< endl << endl;
}
else{
    cout<<"Hubo un problema al guardar el Costo Fijo"<< endl << endl;
}

}

void CostosManager::buscarCostoFijoPorNombre(){
CostoFijo costoF;
string nombreCosto;
CostoFijoArchivo archi;
//bool encontro=false;

int cantRegistros=archi.getCantidadRegistros();

//while(!encontro){
cout<<"Ingrese el nombre del Costo Fijo que quiere buscar"<<endl;
cin.ignore();
getline(cin,nombreCosto);

for(int i=0;i<cantRegistros;i++){
    costoF=archi.leer(i);

    if(costoF.getNombreCosto()== nombreCosto){
        cout<<"Costo Fijo Encontrado"<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
        costoF.mostrarTabla();
        costoF.mostrarEnLista();
        cout<<"--------------------------------------------------------------------------"<<endl;
    }
    else{
        cout<<"No hay costos Fijos con ese nombre"<<endl;
    }
  }
 //}
}

void CostosManager::listarCostosFijos(){

CostoFijoArchivo archi;
CostoFijo cf;

int cantRegistros= archi.getCantidadRegistros();

for(int i=0; i<cantRegistros;i++){
    if(cantRegistros ==0){
        cout<<"No se encontraron registros. "<<endl;
    }
    else{
        cf=archi.leer(i);
        cout<<"COSTOS FIJOS"<<endl;
        cout<<"--------------------------------------------------------------------------"<<endl;
        cf.mostrarTabla();
        cf.mostrarEnLista();
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout<<endl <<endl;
    }
}
}
