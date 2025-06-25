#include "FormaDePago.h"
#include "FormaDePagoArchivo.h"
#include "Utilidades.h"
#include "Validador.h"
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

//para agregar nuevas formas de pagos
 void FormaDePago::cargarFormaDePago(){
    int formaDePago;
    string nombreFormaDePago;
    float descuento;
    FormaDePago f;
    FormaDePagoArchivo archi;
    Validador validador;
    bool bandera=false;
    bool estado=true;

    while(!bandera){

    formaDePago=archi.getCantidadRegistros()+1;

    cout << "Ingrese el nombre" << endl;
    cin.ignore();
    getline(cin,nombreFormaDePago);
        while(!validador.esTexto(nombreFormaDePago)){
            cout << "Nombre incorrecto" << endl;
            limpiarPantalla();
            cout << "Ingrese el nombre" << endl;
            cin.ignore();
            getline(cin,nombreFormaDePago);
        }

    bool validar=false;

        while(!validar){
            cout << "\nIngrese el descuento " << endl;
            cin >> descuento;
                if(descuento<0 && descuento > 1){
                    cout<<"Valor incorrecto"<<endl;
                    validar=false;
                }
                else{
                    validar=true;
                }
        }

    f = FormaDePago(formaDePago, nombreFormaDePago, descuento, estado);

        if(archi.guardar(f)){
            cout<<"\nForma de pago guardada con exito"<< endl << endl;
        }
        else{
            cout<<"\nHubo un problema al guardar la Forma de pago"<< endl << endl;
        }

    int opcion;

    opcion=pedirYValidarConfirmacion("\nDesea cargar otra forma de pago? 1)Si 0)No");
    if(opcion==0){
        bandera=true;
        limpiarPantalla();
    }
    else{
        bandera=false;
        limpiarPantalla();
        }
    }
}




void FormaDePago::opcionesFormasDePago(){
    int opcion;
    int opcSalida;


    while(true){
        cout << "Elija una opcion:" << endl;
        cout << "1) Cargar forma de pago" << endl;
        cout << "2) Listar forma de pago" << endl;
        cout << "3) Modificar descuento de una forma de pago" << endl;
        cout << "0) Salir" << endl;
        cin >> opcion;
        while(cin.fail() || opcion != 1 && opcion != 2 && opcion != 3 && opcion != 0){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");
            cout << "Elija una opcion:" << endl;
            cout << "1) Cargar forma de pago" << endl;
            cout << "2) Listar forma de pago" << endl;
            cout << "3) Modificar descuento de una forma de pago" << endl;
            cout << "0) Salir" << endl;
            cin >> opcion;
        }
        switch (opcion){
        case 1:
            system("cls");
            cargarFormaDePago();
            system("pause");
            break;

        case 2:
            system("cls");
            mostrarEnLista();
            system("pause");
            break;
        case 3:
            system("cls");
            modificarDescuentoFormaDePago();
            system("pause");
            break;
        case 0:
            system("cls");
            opcSalida = pedirYValidarConfirmacion("\n Desea confirmar salida? \n1)Si \n0)No \n\n");
            if(opcSalida==1){
                cout << "Saliendo..." << endl;
                return;
            }
            system("pause");
            break;

        }
    }
}




void FormaDePago::elegirFormaDePago(int &opc){

    FormaDePago fdp;
    FormaDePagoArchivo aFdp;
    int posicion;
    int cantRegistros=aFdp.getCantidadRegistros();

    mostrarEnLista();

    bool confirmacion=false;
    int opcion;

    while(!confirmacion){
        cout<<"Elija el numero de forma de pago"<<endl;
        cin>> opc;
        while(cin.fail() || opc <1 && opcion > cantRegistros ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            cout << "Elija el numero de forma de pago:" << endl;
            cin >> opc;
        }

        posicion=aFdp.buscarFormaDePago(opc);
        fdp=aFdp.leer(posicion);

        bool bandera=false;

        if(fdp.getEstado()){

            while(!bandera){

                opcion= pedirYValidarConfirmacion("Desea confirmar esta opcion? 1)Si 0)No");

                if(opcion==1){
                    confirmacion=true;
                    bandera=true;
                }
                else{
                    confirmacion=false;
                    bandera=true;

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
    cout << left << setw(20) << "Nro ID:";
    cout << left << setw(20) << "Tipo";
    cout << left << setw(20) << "Descuento";
}

void FormaDePago::mostrarEnLista(){
    FormaDePago fdp;
    FormaDePagoArchivo aFdp;
    int cantRegistros=aFdp.getCantidadRegistros();
    mostrarTabla();
    cout<< endl << "-----------------------------------------------------------" << endl;
    for(int i=0; i<cantRegistros; i++){
        fdp=aFdp.leer(i);
        if(fdp.getEstado()){
            cout << left << setw(20) << fdp.getFormaDePago();
            cout << left << setw(20) << fdp.getNombreFormaDePago();
            cout << left << setw(20) << fdp.getDescuento();
            cout << endl;
        }
    }
    cout <<"-----------------------------------------------------------"<<endl;
}

bool FormaDePago::modificarDescuentoFormaDePago(){
    int nroFdp, posicion;
    float desc;
    bool modificado=false,validar=false;
    FormaDePago fdp;
    FormaDePagoArchivo archi;
    int cantRegistros=archi.getCantidadRegistros();

    fdp.mostrarEnLista();

    while(!modificado){
        cout<<"Ingrese el NRO de la forma de pago que quiere modificar: "<<endl;
        cin>> nroFdp;
        while(cin.fail() || nroFdp <1 && nroFdp > cantRegistros ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            limpiarPantalla();
            cout << "Ingrese el NRO de la forma de pago que quiere modificar: " << endl;
            cin >> nroFdp;
        }

        posicion=archi.buscarFormaDePago(nroFdp);
        fdp=archi.leer(posicion);

        if(posicion>=0){
            while(!validar){
                cout << "\nIngrese el nuevo descuento de "<<fdp.getNombreFormaDePago() << endl;
                cin >> desc;
                    if(desc<0 && desc> 1){
                        cout<<"Valor incorrecto"<<endl;
                        validar=false;
                        limpiarPantalla();
                    }
                    else{
                        fdp.setDescuento(desc);
                        validar=true;
                    }
            }

            if(archi.guardar(fdp, posicion)){
            cout<<"Descuento mofidicado correctamente"<< endl;
            modificado=true;
            limpiarPantalla();
            }
            else{
                cout<<"No se pudo mofidicar el descuento"<< endl;
                modificado=false;
                limpiarPantalla();
            }
        }
        else{
            cout<<"No existe la Forma de Pago elegida"<< endl;
            modificado=false;
        }
    }
    return modificado;
}

