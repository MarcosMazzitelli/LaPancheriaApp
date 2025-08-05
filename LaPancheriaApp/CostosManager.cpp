#include <cstring>
#include <iostream>
#include <iomanip>
#include "CostosManager.h"
#include "CostoFijoArchivo.h"
#include "CostoFijo.h"
#include "Fecha.h"
#include "Utilidades.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "DetalleVenta.h"
#include "DetalleVentaArchivo.h"
#include "Validador.h"
using namespace std;


void CostosManager::cargarCostosFijos(){
    int idCosto;
    float precio;
    string nombreCosto;
    Fecha fechaCosto;
    bool estado=true;
    CostoFijo costo;
    CostoFijoArchivo archi;
    bool validacion=false;
    int opc, opcion, opcionNombre;


    idCosto=archi.getCantidadRegistros()+1;

    while(!validacion) {
        cout << "\n--- Seleccione un costo fijo --- \n";
        cout << endl;
        cout << "1. Alquiler \n";
        cout << "2. Agua \n";
        cout << "3. Luz \n";
        cout << "4. Gas \n";
        cout << "5. Internet \n";
        cout << "6. Otro \n";

        cout << "Seleccione una opcion: ";
        cin >> opcionNombre;
        while(cin.fail() || opcionNombre < 1 || opcionNombre > 6 ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese un valor valido" << endl << endl;
            system("pause");
            system("cls");

            cout << endl << endl;
            cout << "\n--- Seleccione un costo fijo --- \n";
            cout << endl;
            cout << "1. Alquiler \n";
            cout << "2. Agua \n";
            cout << "3. Luz \n";
            cout << "4. Gas \n";
            cout << "5. Internet \n";
            cout << "6. Otro \n";

            cout << "Seleccione una opcion: ";
            cin >> opcionNombre;
        }
        switch (opcionNombre) {
            case 1:
                nombreCosto= "Alquier";
                validacion = true;
                break;
            case 2:
                nombreCosto= "Agua";
                validacion = true;
                break;
            case 3:
                nombreCosto= "Luz";
                validacion = true;
                break;
            case 4:
                nombreCosto= "Gas";
                validacion = true;
                break;
            case 5:
                nombreCosto= "Internet";
                validacion = true;
                break;
            case 6:
                nombreCosto= "Otro";
                validacion = true;
                break;
        }
    }

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
                //limpiarPantalla();
            }
            else{
                cout<<"Hubo un problema al guardar el Costo Fijo"<< endl << endl;
            }
        }

}

void CostosManager::buscarCostoFijoPorNombre(){
    CostoFijo costoF;
    string nombreCosto;
    CostoFijoArchivo archi;
    Validador validador;
    int cont=0;

    int cantRegistros=archi.getCantidadRegistros();

    cout<<"Ingrese el nombre del Costo Fijo que quiere buscar"<<endl;
    cin.ignore();
    getline(cin,nombreCosto);
    while(!validador.esTexto(nombreCosto)){
        cout<<"Caracter incorrecto"<<endl;
        cout<<"Ingrese el nombre del Costo Fijo que quiere buscar"<<endl;
        cin.ignore();
        getline(cin,nombreCosto);
    }

    for(int i=0;i<cantRegistros;i++){
        costoF=archi.leer(i);

        if(validador.contiene(nombreCosto, costoF.getNombreCosto()) && costoF.getEstado()){
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
            if(cf.getEstado()){
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

        }
    }
    if(cont==0){
        cout<<"No existen costos fijos en esa fecha"<<endl<<endl;
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

    cantidadRegistros = archivo.getCantidadRegistros();

    while(!principal){

        listarCostosFijos();
        cout << "\n\n\n--------------MODIFICAR COSTO FIJO------------------" <<endl;
        cout << "Ingrese el ID del Costo Fijo a modificar " << endl;
        cin >> idCostoFijo;
        while(cin.fail() || idCostoFijo <1 || idCostoFijo > cantidadRegistros){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarCostosFijos();
            cout << "\n\n\n--------------MODIFICAR COSTO FIJO------------------" <<endl;
            cout << "Ingrese el ID del Costo Fijo a modificar " << endl;
            cin >> idCostoFijo;
        }

            pos=archivo.buscar(idCostoFijo);

            costoF=archivo.leer(pos);

            if(costoF.getEstado()){

                while(permanecer){

                    cout<< "Opcion a modificar: \n 1-Precio \n 2-Fecha " <<endl;
                    cout << " Ingrese una opcion"<<endl;
                    cin>>opcion;

                    while(cin.fail()){
                        cin.clear();
                        cin.ignore(1000,'\n');
                        cout << "Ingrese una opcion valida! \n";
                        limpiarPantalla();
                        cout<< "Opcion a modificar:  \n 1-Precio \n 2-Fecha " <<endl;
                        cout << " Ingrese una opcion"<<endl;
                        cin>>opcion;
                    }


                    switch(opcion){
                        case 1:
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
                        case 2:
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

    int idCosto, cantidadRegistros,pos;
    cantidadRegistros = archivo.getCantidadRegistros();

    listarCostosFijos();
    cout << "\n\n\n----------------ELIMINAR COSTO FIJO------------------" <<endl;
    cout << "Ingrese el ID del costo fijo a eliminar " << endl << endl;
    cin >> idCosto;
            while(cin.fail() || idCosto <1 || idCosto > cantidadRegistros){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Ingrese una opcion valida! \n";
            limpiarPantalla();
            listarCostosFijos();
            cout << "\n\n\n--------------MODIFICAR COSTO FIJO------------------" <<endl;
            cout << "Ingrese el ID del Costo Fijo a modificar " << endl;
            cin >> idCosto;
        }

    pos=archivo.buscar(idCosto);
    costoF=archivo.leer(pos);

        if(costoF.getEstado()){
            costoF.setEstado(false);
            modifico=archivo.guardarModificado(costoF,pos);
        }

    if(modifico){
        cout<< "El costo fijo con ID: " << idCosto <<" fue dado de baja."<<endl;
    }else{
        cout << "El costo fijo no pudo ser dado de baja. No existente." <<endl;
    }
}

void CostosManager::balanceGananciaPorMes(){
    CostoFijo costoF;
    CostoFijoArchivo archiCostoF;
    Empleado empleado;
    ArchivoEmpleado archiEmpleado;
    Venta venta;
    VentaArchivo archiVenta;
    DetalleVenta detalleV;
    DetalleVentaArchivo archiDetalleV;
    Fecha fecha;

    int mes, anio, nroF;
    float sueldo, acuCostoF=0, acuCostoEmpleado=0,acuCostoIngrediente=0,acuCantidad=0,acuVentaTotal=0, costosDelMes, ganancia;

    //while()

    //ingresa el mes (y el anio) del balance

    cout <<"Ingrese el mes "<< endl;
    cin>>mes;
    while(cin.fail()){
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Ingrese un valor valido" << endl << endl;
    cin >> mes;
    }

    cout <<"Ingrese el anio "<< endl;
    cin>>anio;
    while(cin.fail()){
    cin.clear();
    cin.ignore(1000,'\n');
    cout << "Ingrese un valor valido" << endl << endl;
    cin >> anio;
    }
    cout << endl << endl;

    //costos fijos
    int cantRegistroCostoF=archiCostoF.getCantidadRegistros();
    for(int i=0; i<cantRegistroCostoF; i++){
        costoF=archiCostoF.leer(i);
        if(mes == costoF.getFechaCosto().getMes() && anio == costoF.getFechaCosto().getAnio() && costoF.getEstado()){
            acuCostoF+=costoF.getPrecio();
        }
    }
    cout<<" TOTAL COSTOS FIJOS DEL MES "<<mes<<" del anio "<<anio<< " ES DE: $"<<acuCostoF<<endl<<endl;

    //costo empleados
    int cantRegistroEmpleado=archiEmpleado.getCantidadRegistros();
    for(int i=0; i<cantRegistroEmpleado; i++){
        empleado=archiEmpleado.leer(i);
        if(empleado.getEstado() &&
           (empleado.getFechaIngreso().getAnio() < anio ||
           (empleado.getFechaIngreso().getAnio() == anio && empleado.getFechaIngreso().getMes() <= mes ))){
            acuCostoEmpleado+=empleado.getSueldo();
        }
    }
    cout<<" TOTAL COSTO DE EMPLEADOS DEL MES "<<mes<<" del anio "<<anio<< " ES DE:  $"<<  fixed << setprecision(2) << acuCostoEmpleado<<endl<<endl;

    //costo ingredientes
    int cantRegistroVenta=archiVenta.getCantidadRegistros();
    int cantRegistroDetalleV=archiDetalleV.getCantidadRegistros();

    for(int i=0; i<cantRegistroVenta; i++){
        venta=archiVenta.leer(i);
        if(mes == venta.getFechaVenta().getMes() && anio == venta.getFechaVenta().getAnio()){
            nroF=venta.getNroFactura();
            for(int j=0; j<cantRegistroDetalleV; j++){
                detalleV=archiDetalleV.leer(j);
                if(detalleV.getNroFactura()== nroF){
                    acuCantidad=detalleV.getCostoUnitario()*detalleV.getCantProducto();
                    acuCostoIngrediente+=acuCantidad;
                }
            }
        }
    }
    cout<<" TOTAL COSTO DE PRODUCTOS VENDIDOS DEL MES "<<mes<<" DEL ANIO "<<anio<< " ES DE: $"<<acuCostoIngrediente<<endl<<endl;

    //balance ganancias del mes
    costosDelMes=acuCostoF+acuCostoEmpleado+acuCostoIngrediente;

    for(int i=0; i<cantRegistroVenta;i++){
        venta=archiVenta.leer(i);
        if(mes == venta.getFechaVenta().getMes() && anio == venta.getFechaVenta().getAnio()){
            acuVentaTotal+=venta.getImporteTotal();
        }
    }

    ganancia=acuVentaTotal-costosDelMes;

    cout<<" TOTAL RECAUDADO POR VENTAS DEL MES "<<mes<<" DEL ANIO "<<anio<< " ES DE: $"<<acuVentaTotal<<endl<<endl;

    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout<<"BALANCE DEL MES "<<mes<<" DEL ANIO "<<anio<< " ES DE: $"<<ganancia<<endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl << endl;

}
void CostosManager::balancePorFecha(){
    CostoFijo costoF;
    CostoFijoArchivo archiCostoF;
    Empleado empleado;
    ArchivoEmpleado archiEmpleado;
    Venta venta;
    VentaArchivo archiVenta;
    DetalleVenta detalleV;
    DetalleVentaArchivo archiDetalleV;
    Fecha fechaDesde, fechaHasta;
    Validador validador;

    int mes, anio, nroF, cantSueldos;
    float sueldo, acuCostoF=0, acuCostoEmpleado=0,acuCostoIngrediente=0,acuCantidad=0,acuVentaTotal=0, costosDelPeriodo, ganancia;


    validador.validadorFiltroFecha(fechaDesde,fechaHasta);
    cout<<endl;
    //costos fijos
    int cantRegistroCostoF=archiCostoF.getCantidadRegistros();

    for(int i=0; i<cantRegistroCostoF; i++){
        costoF=archiCostoF.leer(i);

        if (costoF.getFechaCosto() <= fechaHasta ){ ///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)

            if (costoF.getFechaCosto() >= fechaDesde ){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)

                if(costoF.getEstado()){
                    acuCostoF+=costoF.getPrecio();
                }
            }
        }
    }

    cout << "TOTAL DE COSTOS FIJOS DESDE: " <<  fechaDesde.mostrarFecha() << " HASTA: " <<   fechaHasta.mostrarFecha() << " $"<<acuCostoF<< endl;




    //costo empleados

    int cantRegistroEmpleado = archiEmpleado.getCantidadRegistros();

    for(int i = 0; i < cantRegistroEmpleado; i++){
        empleado = archiEmpleado.leer(i);

        if(empleado.getEstado() == true){

            // Si el empleado ingresó después de la fechaHasta, no se cuenta
            if(empleado.getFechaIngreso() <= fechaHasta){

                Fecha ingreso = empleado.getFechaIngreso();
                int cantSueldos = 0;

                // Si ingresó antes del período, entonces trabajó todo el período
                if(ingreso <= fechaDesde){
                    if (fechaDesde.getAnio() == fechaHasta.getAnio()) {
                        cantSueldos = fechaHasta.getMes() - fechaDesde.getMes() + 1;
                    }
                    else{
                        cantSueldos = ((fechaHasta.getAnio() - fechaDesde.getAnio()) * 12) + fechaHasta.getMes() - fechaDesde.getMes() + 1;
                    }
                }
                // Si ingresó dentro del período
                else if(ingreso >= fechaDesde && ingreso <= fechaHasta && !(ingreso == fechaDesde)){

                    if (ingreso.getAnio() == fechaHasta.getAnio()) {
                        cantSueldos = fechaHasta.getMes() - ingreso.getMes() + 1;
                    }
                    else{
                        cantSueldos = ((fechaHasta.getAnio() - ingreso.getAnio()) * 12) + fechaHasta.getMes() - ingreso.getMes() + 1;
                    }
                }

                // Sumar sueldo por los meses que trabajó en el período
                if(cantSueldos > 0){
                    sueldo = empleado.getSueldo() * cantSueldos;
                    acuCostoEmpleado += sueldo;
                }
            }
        }
    }


    cout << "TOTAL DE COSTOS EMPLEADOS DESDE: " <<  fechaDesde.mostrarFecha() << " HASTA: " <<   fechaHasta.mostrarFecha() <<" $"<<  fixed << setprecision(2) << acuCostoEmpleado << endl;



    //costo ingredientes
    int cantRegistroVenta=archiVenta.getCantidadRegistros();
    int cantRegistroDetalleV=archiDetalleV.getCantidadRegistros();

    for(int i=0; i<cantRegistroVenta; i++){
        venta=archiVenta.leer(i);
        for(int j=0; j<cantRegistroDetalleV; j++){
            detalleV=archiDetalleV.leer(j);
            if (venta.getFechaVenta() <= fechaHasta ){ ///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)

                if (venta.getFechaVenta() >= fechaDesde ){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)

                    if(venta.getNroFactura() == detalleV.getNroFactura()){
                        acuCantidad=detalleV.getCostoUnitario()*detalleV.getCantProducto();
                        acuCostoIngrediente+=acuCantidad;
                    }
                }
            }
        }
    }


    cout << "TOTAL DE COSTOS DE PRODUCTOS VENDIDOS DESDE: " <<  fechaDesde.mostrarFecha() << " HASTA: " <<   fechaHasta.mostrarFecha()<<" $"<<acuCostoIngrediente << endl;



    //costos del periodo
    costosDelPeriodo=acuCostoF+acuCostoEmpleado+acuCostoIngrediente;

    for(int i=0; i<cantRegistroVenta;i++){
        venta=archiVenta.leer(i);
        if (venta.getFechaVenta() <= fechaHasta ){ ///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
            if (venta.getFechaVenta() >= fechaDesde ){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
                acuVentaTotal+=venta.getImporteTotal();
            }
        }
    }

    cout<<" TOTAL RECAUDADO POR VENTAS DESDE "<<fechaDesde.mostrarFecha()<<" HASTA "<<fechaHasta.mostrarFecha()<< " ES DE: $"<<acuVentaTotal<<endl<<endl;

    ganancia=acuVentaTotal-costosDelPeriodo;

    cout <<  "--------------------------------------------------------------------------------"<< endl;
    cout << "BALANCE DEL PERIODO: " <<  fechaDesde.mostrarFecha() << " HASTA: " <<   fechaHasta.mostrarFecha() <<" $"<<ganancia<< endl;
    cout <<  "--------------------------------------------------------------------------------"<< endl << endl;

}



