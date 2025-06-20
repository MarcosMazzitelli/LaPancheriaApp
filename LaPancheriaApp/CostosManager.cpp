#include <cstring>
#include <iostream>
#include <iomanip>
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
        while(cin.fail() || precio <=0){
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
    cout<<endl;
    cout<<"--------------------------------------------------------------------------------"<<endl;
    cout<<endl;
    for(int i=0; i<cantRegistros;i++){
        if(cantRegistros == 0){
            cout<<"No se encontraron registros. "<<endl;
        }
        else{
            cf=archi.leer(i);
            if(cf.getEstado()==true){
            cf.mostrarEnLista();
            cout<<endl <<endl;
            }
        }
    }
}

void CostosManager::listarCostosFijosPorFecha(){

    CostoFijoArchivo archi;
    CostoFijo cf;
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

        if(mes == cf.getFechaCosto().getMes() && anio == cf.getFechaCosto().getAnio() && cf.getEstado()==true){
            cont++;
            cf.mostrarEnLista();
            cout<<"-------------------------------------------------------------------------------------------"<<endl;
        }
    }
    if(cont==0){
        cout<<"No existen costos fijos en esa fecha"<<endl;
    }
}

void CostosManager::modificarCostoFijo(){

    CostoFijo costoF;
    CostoFijoArchivo archivo;
    Fecha fechaCosto;

    int opcion, opcionValFinal, idCostoFijo, cantidadRegistros, pos, opc;
    float precio;
    string nombreCosto;
    bool modifico, principal=false, permanecer=true, seEncontro=false;

    while(!principal){

        listarCostosFijos();
        cout << "\n\n\n--------------MODIFICAR COSTO FIJO------------------" <<endl;
        cout << "Ingrese el ID del Costo Fijo a modificar " << endl;
        cin >> idCostoFijo;
        while(cin.fail()){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarCostosFijos();
            cout << "\n\n\n--------------MODIFICAR COSTO FIJO------------------" <<endl;
            cout << "Ingrese el ID del Costo Fijo a modificar " << endl;
            cin >> idCostoFijo;

        }

        cantidadRegistros = archivo.getCantidadRegistros();

        for(int i=0; i<cantidadRegistros;i++){

            costoF=archivo.leer(i);

            if(costoF.getIdCosto()==idCostoFijo && costoF.getEstado()==true){

                pos=i;
                seEncontro=true;

                while(permanecer){

                    cout<< "Opcion a modificar: \n 1-Nombre \n 2-Precio \n 3-Fecha " <<endl;
                    cout << " Ingrese una opcion"<<endl;
                    cin>>opcion;

                    while(cin.fail()){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Ingrese una opcion valida! \n";
                        limpiarPantalla();
                        cout<< "Opcion a modificar:  \n 1-Nombre \n 2-Precio \n 3-Fecha \n 4-Salir " <<endl;
                        cout << " Ingrese una opcion"<<endl;
                        cin>>opcion;
                    }


                    switch(opcion){
                        case 1:
                            cout << "Ingrese nuevo nombre: " << endl;
                            cin.ignore();
                            getline(cin,nombreCosto);
                            costoF.setNombreCosto(nombreCosto);
                            permanecer=false;
                            limpiarPantalla();
                            break;
                        case 2:
                            cout << "Ingrese precio del costo: \n";
                            cin >> precio;
                            while(cin.fail() || precio<=0){
                                cin.clear();
                                cin.ignore(1000,'\n');
                                cout << "Ingrese una opcion valida! \n";
                                limpiarPantalla();
                                cout << "Ingrese precio del costo: \n";
                                cin >> precio;
                            }
                            costoF.setPrecio(precio);
                            permanecer=false;
                            limpiarPantalla();
                            break;
                        case 3:
                            cout << "Ingrese nueva fecha: " << endl;
                            while(!fechaCosto.cargar()){
                                fechaCosto.cargar();
                            }
                            costoF.setFechaCosto(fechaCosto);
                            permanecer=false;
                            limpiarPantalla();
                            break;

                        default:
                            cout << "Opcion invalida" <<endl;
                            limpiarPantalla();
                        }

                }

                opc= pedirYValidarConfirmacion("Desea guardar este cambio?? \n1) si \n0) no \n\n");
                if(opc==1){
                    modifico=archivo.guardarModificado(costoF,pos);
                    if(modifico){
                        cout<<"Costo Fijo modificado con exito"<< endl << endl;
                        limpiarPantalla();
                    }
                    else{
                    cout<<"Hubo un problema al modificar el Costo Fijo"<< endl << endl;
                    }
                }

            }
        }
        if(!seEncontro){
            cout<<"No se encontro un costo fijo con ID "<< idCostoFijo << endl;
        }

        opcionValFinal=pedirYValidarConfirmacion("Desea modificar otro costo fijo? \n1) si \n0) no \n\n");
        if(opcionValFinal==1){
            principal=false;
            permanecer=true;
            limpiarPantalla();
        }
        else{
            principal=true;
            limpiarPantalla();
        }

    } //fin while principal
}

void CostosManager::eliminarCostoFijo(){
    CostoFijoArchivo archivo;
    CostoFijo costoF;
    bool modifico;

    int id, cantidadRegistros,pos;

    listarCostosFijos();
    cout << "\n\n\n----------------ELIMINAR COSTO FIJO------------------" <<endl;
    cout << "Ingrese el ID del costo fijo a eliminar " << endl << endl;
    cin >> id;
    cantidadRegistros = archivo.getCantidadRegistros();

    for(int i=0; i<cantidadRegistros;i++){
        costoF=archivo.leer(i);
        if(costoF.getIdCosto()==id){

            costoF.setEstado(false);
            pos=i;
            modifico=archivo.guardarModificado(costoF,pos);
        }
    }
    if(modifico){
        cout<< "El costo fijo con ID: " << id <<" fue dado de baja."<<endl;
    }else{
        cout << "El costo fijo no pudo ser dado de baja. No existente." <<endl;
    }
}
