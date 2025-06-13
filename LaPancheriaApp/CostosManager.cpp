#include <cstring>
#include <iostream>
#include "CostosManager.h"
#include "CostoFijoArchivo.h"
#include "CostoFijo.h"
#include "Fecha.h"
#include "Utilidades.h"
using namespace std;

void CostosManager::cargarCostosFijos(){
    int idCosto;
    float precio;
    string nombreCosto;
    Fecha fechaCosto;
    bool estado=true;
    CostoFijo costo;
    CostoFijoArchivo archi;
    bool bandera= false;
    int opc, opcion;

    while(!bandera){

    idCosto=archi.getCantidadRegistros()+1;

    cout << "Ingrese nombre del costo fijo"<<endl;
    cin.ignore();
    getline(cin,nombreCosto);

    bool confirmar = false;

    cout <<endl<< "Ingrese el precio del costo fijo $ "<<endl;
    cin >> precio;
        while(cin.fail() || precio <0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cin >> precio;
    }

    cout <<endl<< "Ingrese la fecha del costo fijo " <<endl;

    while(!fechaCosto.cargar()){
    fechaCosto.cargar();
    }

    costo = CostoFijo(idCosto, nombreCosto, precio, fechaCosto, estado);



        opc= pedirYValidarConfirmacion("Desea guardar este costo fijo? \n1) si \n0) no \n\n");
        if(opc==1){
            if(archi.guardar(costo)){
                cout<<"Costo Fijo guardado con exito"<< endl << endl;
                limpiarPantalla();
            }
            else{
                cout<<"Hubo un problema al guardar el Costo Fijo"<< endl << endl;
            }
        }

        opcion=pedirYValidarConfirmacion("Desea agregar otro costo fijo? \n1) si \n0) no \n\n");
        if(opcion==1){
            bandera=false;
            limpiarPantalla();
        }
        else{
            bandera=true;
            limpiarPantalla();
        }

    }
}

void CostosManager::buscarCostoFijoPorNombre(){
CostoFijo costoF;
string nombreCosto;
CostoFijoArchivo archi;
int cont=0;

int cantRegistros=archi.getCantidadRegistros();

cout<<"Ingrese el nombre del Costo Fijo que quiere buscar"<<endl;
cin.ignore();
getline(cin,nombreCosto);

for(int i=0;i<cantRegistros;i++){
    costoF=archi.leer(i);

    if(costoF.getNombreCosto()== nombreCosto){
        cont++;
        cout<<"Costo Fijo Encontrado"<<endl;
        cout<<endl;
        costoF.mostrarTabla();
        cout<<"--------------------------------------------------------------------------"<<endl;
        cout<<endl;
        costoF.mostrarEnLista();
        cout<<"--------------------------------------------------------------------------"<<endl;
    }
    if(cont==0){

        cout<<"No hay costos Fijos con ese nombre"<<endl;

    }
  }
}

void CostosManager::listarCostosFijos(){

    CostoFijoArchivo archi;
    CostoFijo cf;

    int cantRegistros= archi.getCantidadRegistros();

    cout<<"COSTOS FIJOS"<<endl;
    cf.mostrarTabla();
    cout<<"--------------------------------------------------------------------------"<<endl;
    cout<<endl;
    for(int i=0; i<cantRegistros;i++){
        if(cantRegistros == 0){
            cout<<"No se encontraron registros. "<<endl;
        }
        else{
            cf=archi.leer(i);
            cf.mostrarEnLista();
            cout<<"--------------------------------------------------------------------------"<<endl;
            cout<<endl <<endl;
        }
    }
}

void CostosManager::listarCostosFijosPorFecha(){

    CostoFijoArchivo archi;
    CostoFijo cf;
    Fecha aux;
    int mes,anio;

    int cantRegistros= archi.getCantidadRegistros();

    cout<<"Ingrese el mes"<<endl;
    cin>> mes;
        while(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        cin >> mes;
        }

    cout<<"Ingrese el anio"<<endl;
    cin>>anio;
        while(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Ingrese un valor valido" << endl << endl;
        cin >> anio;
        }


    cout<<endl<<"LISTADO DE COSTOS FIJOS: "<<endl;
    cout<<endl;

    int cont=0;;
    cf.mostrarTabla();
    cout<<endl;
    cout<<"-------------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
        for(int i=0;i<cantRegistros;i++){

            cf=archi.leer(i);

            if(mes == cf.getFechaCosto().getMes() && anio == cf.getFechaCosto().getAnio()){
            cont++;
            cf.mostrarEnLista();
                cout<<"-------------------------------------------------------------------------------------------"<<endl;
            }
        }
        if(cont==0){
            cout<<"No existen costos fijos en esa fecha"<<endl;
        }
}


