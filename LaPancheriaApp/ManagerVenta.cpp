#include <string>
#include <iostream>
#include "ManagerVenta.h"
#include "Venta.h"
#include "VentaArchivo.h"
#include "Empleado.h"
#include "ArchivoEmpleado.h"
#include "Cliente.h"
#include "ArchivoCliente.h"
#include "FormaDePago.h"
#include "FormaDePagoArchivo.h"
#include "ProductosManager.h"
#include "Producto.h"
#include "ArchivoProducto.h"
#include "DetalleVenta.h"
#include "DetalleVentaArchivo.h"
#include "Fecha.h"
#include "PersonaManager.h"
#include "Utilidades.h"
#include "ArchivoIngrediente.h"
#include "Ingrediente.h"
#include "ArchivoDetalleIngrediente.h"
#include "Validador.h"

using namespace std;



void ManagerVenta::registrarVenta(std::string dniEmpleado){

    FormaDePagoArchivo fdpArchi;
    ArchivoProducto archiProd;
    VentaArchivo ventaArchi;
    DetalleVentaArchivo archiDetVenta;
    ArchivoEmpleado empArchi;
    ArchivoDetalleIngrediente archivoDetalleIng;
    ArchivoIngrediente archivoIngrediente;
    DetalleVentaArchivo archivoDetalleVenta;

    Fecha fechaVenta;
    Empleado emp;
    Producto prod;
    Venta v;
    FormaDePago fdp;
    DetalleVenta detVenta;
    DetalleIngrediente detalleIng;
    Ingrediente ing;

    PersonaManager personaManager;
    ProductosManager prodManager;

    int productosDisponibles;
    int nroFactura,idEmpleado,formaDePago, posicion;
    int posArchiFdp;
    string dniCliente;
    float importeTotal=0;
    float importeBruto, ImporteProdxCantidad, stockADescontar, cantidadIngredientePorReceta;
    int posicionEmpleado, posicionProducto, posicionProd, cantidadADescontar;
    int cantidad, opcion;
    int idProducto;
    int cantRegistrosProducto = archiProd.getCantidadRegistros();
    vector<DetalleVenta> vecDetalleVenta;
    nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico

    personaManager.cargarCliente(dniCliente);

    posicionEmpleado = empArchi.buscar(dniEmpleado);
    emp= empArchi.leer(posicionEmpleado);
    idEmpleado = emp.getIdEmpleado();


    bool cargaProductos=false;
    while (!cargaProductos){ ///ciclo para ingresar productos a una venta
        bool hayStock=true;//cada vez que se agregue un nuevo producto al detalle, la bandera se pone en TRUE
        system("cls");
        opcion = pedirYValidarConfirmacion("\nDesea filtrar productos que tengan un ingrediente en particular? \n1)Si \n0)No \n") ;
        if(opcion == 1){
            while(opcion == 1){
                if(prodManager.listarProductosPorIngredientes()){
                    //si devuelve true (encontro productos) FIN DEL WHILE
                    opcion = 0;
                }
                else{
                    //si devuelve false, (no encontro producto), se vuelve a pedir confirmacion para filtrar por ingrediente
                    opcion = pedirYValidarConfirmacion("\nDesea filtrar productos que tengan un ingrediente en particular? \n1)Si \n0)No \n");
                    if (opcion == 0){
                        // si la opcion es 0, se muestra el listado normal de productos y fin del while
                        prodManager.listarProductos(true);
                    }
                }
            }
        }
        else{
            //si la primer opcion es 0, se listan los productos normalmente
            prodManager.listarProductos(true);
        }

        cout << "Seleccione el producto que desee agregar: ";
        cin >> idProducto;
        while (cin.fail() || idProducto < 1 || idProducto > cantRegistrosProducto ){
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Ingrese un Id de producto valido" << endl << endl;
            system("pause");
            system("cls");
            prodManager.listarProductos(true);
            cout << "Seleccione el producto que desee agregar: ";
            cin >> idProducto;
        }

        posicionProducto = archiProd.buscar(idProducto);
        prod = archiProd.leer(posicionProducto);
        if (prod.getEstado()){
            cout << "Ingrese la cantidad del producto " << prod.getNombreProducto() << " a vender: ";
            cin >> cantidad;
            while (cin.fail() || cantidad <= 0){
                cin.clear(); // limpia el estado de error
                cin.ignore(1000, '\n'); // descarta el resto de la linea
                cout << "Ingrese una cantidad valida." << endl << endl;
                system("pause");
                system("cls");
                cout << "Ingrese la cantidad del producto " << prod.getNombreProducto() << " a vender: ";
                cin >> cantidad;
            }
            cantidadADescontar = cantidad; //Ultima cantidad elegida (prod actual)
            /// a partir de aca esta OK el ingreso de productos
            for (int i= 0; i < vecDetalleVenta.size(); i++){
                if(vecDetalleVenta[i].getIdProducto() == idProducto){
                    //se recorre el vector de detalles de esta venta para acumular la cantidad si es que tiene el mismo producto en otro detalle
                    cantidadADescontar += vecDetalleVenta[i].getCantProducto();
                }
            }

            for(int j=0; j < archivoDetalleIng.getCantidadRegistros(); j++){
                //recorre las recetas (Un producto puede tener una o muchas dependiendo de la cantidad de ingredientes)
                detalleIng = archivoDetalleIng.leer(j);
                if(detalleIng.getIdProducto() == idProducto){ // si el producto vendido  coincide con una receta:
                    cantidadIngredientePorReceta = detalleIng.getCantidadPorProducto(); //traigo la cantidad de ingrediente que lleva ese producto vendido
                    stockADescontar = cantidadADescontar * cantidadIngredientePorReceta;
                    //obtengo la cantidad total de ingrediente a descontar (Solo para comparar con mi stock actual, el descuento no se hace aca)
                    posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
                    if (posicion >= 0){
                        ing = archivoIngrediente.leer(posicion);
                        if (ing.getCantidadStock() < stockADescontar){
                            hayStock=false;
                            //Si el stock actual es menor a mi stock a descontar no alcanza el stock para la cantidad de productos que solicita el cliente

                            if(ing.getCantidadStock() < cantidadIngredientePorReceta){
                                //Si el stock actual es menor a la cantidad que necesito para hacer un pancho NO HAY STOCK
                                prod.setEstado(false);
                                if(archiProd.modificar(prod, posicionProducto)){
                                    cout << endl << "No hay suficiente stock de "<< ing.getNombreIngrediente() << " para preparar NINGUN producto. El mismo ha sido dado de baja" << endl;
                                    cout << "Primero debe generar stock y luego dar de alta el producto" << endl << endl;
                                }
                            }
                            else{ //si hay stock disponible mayor a un producto, pero menor a lo que el cliente pidió:
                                cout << "No hay suficiente stock de " << ing.getNombreIngrediente() << " para preparar el producto" << endl;
                                productosDisponibles = ing.getCantidadStock() / cantidadIngredientePorReceta;
                                cout << "El stock alcanza para preparar " << productosDisponibles << " "  << prod.getNombreProducto() << endl;
                            }
                        }
                    }
                }
            }
            if(hayStock){
                //Si hay stock se prepara un nuevo detalle de venta con el producto actual y se  pregunta si quiere comprar mas
                ImporteProdxCantidad = prod.getPrecioUnitario()*cantidad;
                importeBruto += ImporteProdxCantidad; //ACUMULADOR por todos los detalles que tenga una venta... se utiliza en ventas.
                detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), ImporteProdxCantidad);
                vecDetalleVenta.push_back(detVenta); //se aumenta el tamanio del vector y se coloca al final el nuevo detalle de venta
            }
        }
        else{
            cout << "El producto se encuentra dado de baja!" << endl << endl;
        }
        opcion = pedirYValidarConfirmacion("Desea ingresar mas productos? \n1) si \n0) no \n\n");
        if(opcion == 0){
            cargaProductos=true;
            ///fin carga de productos
        }
    }
    if(!vecDetalleVenta.empty()){
        //Si el vector dinamico de detalles de venta esta cargado es porque hubo ventas:

        fdp.elegirFormaDePago(formaDePago);
        posArchiFdp = fdpArchi.buscarFormaDePago(formaDePago);
        fdp = fdpArchi.leer(posArchiFdp);
        importeTotal = importeBruto - (importeBruto * fdp.getDescuento() );
        cout<<"ingrese la fecha de venta : "<<endl;

        while(cin.fail() || !fechaVenta.cargar()){
            cin.clear(); // limpia el estado de error
            cin.ignore(1000, '\n'); // descarta el resto de la linea
            cout << "Ingrese una fecha valida." << endl << endl;
            system("pause");
            system("cls");
            cout<<"ingrese la fecha de venta : "<<endl;
            fechaVenta.cargar();
        }

        cout << endl << endl;

        v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

        //Se muestra el detalle de productos en la canasta
        cout << "Detalle de venta: " << endl;
        cout << "--------------------------------" << endl;
        for (int i=0; i < vecDetalleVenta.size(); i++){
            int idProducto = vecDetalleVenta[i].getIdProducto();
            int cant = vecDetalleVenta[i].getCantProducto();
            detVenta = archivoDetalleVenta.leer(i);
            posicionProd = archiProd.buscar(idProducto);
            prod = archiProd.leer(posicionProd);
            cout << "(x" << cant << ") " << prod.getNombreProducto() << endl;
        }
        cout << "--------------------------------" << endl << endl;



        opcion = pedirYValidarConfirmacion("Desea registrar la venta? \n1) si \n0) no \n\n");
        if(opcion == 1){
            if (ventaArchi.guardar(v)){
                cout << "Venta guardada correctamente." << endl;
            }
            else{
                cout << "Hubo un problema al guardar la venta." << endl;
            }
            descontarStock(vecDetalleVenta); //Metodo para descontar stock enviando el vector de detallesVenta
        }
    }
    else{
        cout << "No se ha registrado ninguna venta..." << endl << endl;
    }
}

void ManagerVenta::descontarStock(std::vector<DetalleVenta> &vecDetalleVenta){
    ArchivoDetalleIngrediente archivoDetalleIng;
    ArchivoIngrediente archivoIngrediente;
    Ingrediente ing;
    DetalleIngrediente detalleIng;
    DetalleVentaArchivo archivoDetalleVenta;
    int posicion;
    float cantidadIngredientePorReceta, stockADescontar;
    int cantidadProducto;


    for (int i=0; i < vecDetalleVenta.size(); i++){//for de productos distintos de mi venta
        //Recorro el vector de instancias de detalle venta y guardo los detalles con sus productos.
        if(archivoDetalleVenta.guardar(vecDetalleVenta[i])){
                cout << "Producto guardado correctamente." << endl;
        }
        else{
            cout << "Hubo un problema al guardar el producto." << endl;
        }
        for(int j=0; j < archivoDetalleIng.getCantidadRegistros(); j++){
            //recorre todas las recetas (detalleIng)
            detalleIng = archivoDetalleIng.leer(j);
            if(vecDetalleVenta[i].getIdProducto() == detalleIng.getIdProducto()){
                // si el producto vendido(detalleVenta) coincide con la receta actual(detalleIng)
                cantidadIngredientePorReceta = detalleIng.getCantidadPorProducto(); //traigo la cantidad de ingrediente que lleva ese producto vendido
                cantidadProducto = vecDetalleVenta[i].getCantProducto(); //traigo la cantidad de ese producto vendido
                stockADescontar = cantidadProducto * cantidadIngredientePorReceta; //obtengo la cantidad total de ingrediente. luego la descuento.
                posicion = archivoIngrediente.buscar(detalleIng.getIdIngrediente());
                if (posicion >= 0){
                    ing = archivoIngrediente.leer(posicion);
                    ing.descontarStock(stockADescontar); ///METODO PROPIO DE LA CLASE INGREDIENTE
                    if (archivoIngrediente.modificar(ing,posicion)){
                        cout << "Stock descontado correctamente" << endl;
                    }
                    else{
                        cout << "Error al guardar stock "<< endl;
                    }
                }
                else{
                    cout << "No se ha encontrado el ingrediente en el archivo" << endl;
                }
            }

        }
    }
}





int ManagerVenta::cantidadRegistros(){

VentaArchivo archi;
int cant;


cant= archi.getCantidadRegistros();
return cant;


}


void ManagerVenta::listarVenta(){

VentaArchivo archi;
Venta vent;

int cantRegistros = cantidadRegistros();
vent.mostrarTabla();
cout<<endl;
cout<<"================================================================================================"<<endl;
for (int i=0;i<cantRegistros;i++){
    if(cantRegistros ==0){
        cout<<"No se encontraron registros. "<<endl;
    }else{
    vent = archi.leer(i);
    vent.mostrarEnLista();
    cout<<endl <<endl;}
}
}
void ManagerVenta::listarVentaFecha(){
Venta vent;
Fecha aux;
VentaArchivo  archi;

int cantRegistro=archi.getCantidadRegistros();
int cont=0;

cout<<"LISTADO DE VENTA POR FECHA"<<endl;
while(!aux.cargar()){
    aux.cargar();
}
cout<<endl<<"Listado de Ventas: "<<endl;
cout<<endl;
vent.mostrarTabla();

for(int i=0;i<cantRegistro;i++){

    vent=archi.leer(i);

    if(aux.getDia()== vent.getFechaVenta().getDia()&&aux.getMes()== vent.getFechaVenta().getMes()&&aux.getAnio()== vent.getFechaVenta().getAnio()){
        cont++;

        cout<<endl;
        vent.mostrarEnLista();
        cout << endl;
    }
}
if(cont==0){
    cout << endl;
    cout<<"No hay ventas registradas en esta fecha. "<<endl;
}
}




void ManagerVenta::cargaMasivaVentas(std::string dniEmpleado){

    for (int i=0; i < 400; i++){
        FormaDePagoArchivo fdpArchi;
        ArchivoProducto archiProd;
        VentaArchivo ventaArchi;
        ArchivoEmpleado empArchi;
        ArchivoCliente archivoCliente;

        Fecha fechaVenta;
        Empleado emp;
        Producto prod;
        Venta v;
        FormaDePago fdp;
        DetalleVenta detVenta;
        Cliente cliente;

        PersonaManager personaManager;
        ProductosManager prodManager;

        int nroFactura,idEmpleado,formaDePago;
        float descuento;
        int posArchiFdp;
        float importeBruto= 0;
        float ImporteProdxCantidad, importeTotal;
        int posicionEmpleado, posicionProducto, posicionCliente;
        int cantidad, opcion;
        int idProducto;
        vector<DetalleVenta> vecDetalleVenta;

        string nombreCliente, apellidoCliente, dniCliente;


        nroFactura = ventaArchi.getCantidadRegistros()+1; //autonumerico

        cin.ignore();
        getline(cin,dniCliente);
        posicionCliente = archivoCliente.buscar(dniCliente);

        if(posicionCliente < 0){ //si no existe, pido los datos y los registro

            getline(cin,nombreCliente);
            getline(cin,apellidoCliente);
            cliente = Cliente(nombreCliente, apellidoCliente, dniCliente);
            if(archivoCliente.guardar(cliente)){
                cout <<"El cliente se registro correctamente"<<endl;
            }else{
                cout << "No se pudo guardar el registro" << endl;
            }
        }
        else{ //si existe, no se registra un nuevo cliente
            cout << "El cliente se encuentra registado. " << endl;
            cout << "Error no se puede efectuar carga masiva " << endl;
            return;
        }


        posicionEmpleado = empArchi.buscar(dniEmpleado);
        emp= empArchi.leer(posicionEmpleado);
        idEmpleado = emp.getIdEmpleado();


        bool cargaProductos=false;
        while (!cargaProductos){ ///ciclo para ingresar productos a una venta
            cin >> idProducto;
            posicionProducto = archiProd.buscar(idProducto);
            prod = archiProd.leer(posicionProducto);
            cin >> cantidad;
            /// a partir de aca esta OK el ingreso de productos

            ImporteProdxCantidad = prod.getPrecioUnitario()*cantidad;
            importeBruto += ImporteProdxCantidad; //Acumulador por todos los detalles que tenga una venta... se utiliza en ventas.
            detVenta = DetalleVenta(nroFactura,idProducto,cantidad, prod.getPrecioUnitario(), prod.getCostoProducto(), ImporteProdxCantidad);
            vecDetalleVenta.push_back(detVenta); //se aumenta el tamanio del vector y se coloca al final el nuevo detalle de venta

            cin >> opcion; // para ingresar mas productos (1 si, 0 no)
            if(opcion == 0){
                cargaProductos=true;
                ///fin carga de productos
            }
        }
        cin >> formaDePago;
        if (formaDePago == 1){
            descuento = 0.1;
        }
        else if(formaDePago == 2){
            descuento = 0;
        }

        fechaVenta.cargar(); //dia, mes anio
        importeTotal = importeBruto - (importeBruto * descuento );
        v=Venta(nroFactura, dniCliente,idEmpleado,importeTotal,formaDePago,fechaVenta);

        if (ventaArchi.guardar(v)){
            cout << "Registro guardado correctamente." << endl << endl;
        }
        else{
            cout << "Hubo un problema al guardar el registro." << endl << endl;
        }
        descontarStock(vecDetalleVenta);
    }
}
void ManagerVenta::mostrarFechaMayorRecaudacionVenta(){

    VentaArchivo archi;
    Venta vent;
    Fecha aux;



    int cantRegistro=archi.getCantidadRegistros();
    float mayorVenta=0.0;


    for(int i=0; i<cantRegistro;i++){
        vent=archi.leer(i);


        if(i==0){
            mayorVenta=vent.getImporteTotal();
            aux=vent.getFechaVenta();

        }else if(vent.getImporteTotal()>mayorVenta){

            mayorVenta=vent.getImporteTotal();
            aux=vent.getFechaVenta();
        }




    }

    cout<<"El monto de la mayor venta es: "<<"$"<<mayorVenta<<endl;
    cout<<endl<<"se registro el dia "<< aux.mostrarFecha()<<endl<<endl;

}
void ManagerVenta::mostrarFechaMayorCantidadVentas(){



    Fecha fecha;
    VentaArchivo archi;
    Venta vent;


    std::vector<Fecha> vecFecha{};
    std::vector<int> vecContador{};
    int cantRegistro=archi.getCantidadRegistros();
    bool coincidencia=false;
    int mayor=0;
    int cont=0;

    for(int i=0;i<cantRegistro;i++){ //carga vec de fecha y vec contador, con las ventas registradas en el archivo
        vent=archi.leer(i);
        coincidencia=false;
        if(i==0){
           vecFecha.push_back(vent.getFechaVenta());
           vecContador.push_back(1);
        }
        else{
            for(int j=0; j<vecFecha.size();j++){//comparar que no exista esa fecha en el vecFecha, y si existe solo que tiene q aumentar el vecCont

               if(vent.getFechaVenta() == vecFecha[j]){ //sobrecarga de operadores
                vecContador[j]++;
                coincidencia=true;
               }
            }
            if(!coincidencia){
                vecFecha.push_back(vent.getFechaVenta());
                vecContador.push_back(1);
            }
        }
    }
    for(int i=0;i<vecContador.size();i++){//determina cual es la fecha donde se realizaron mas ventas

        if(i==0){
            mayor=vecContador[i];

        }
        else if(vecContador[i]>mayor){
                mayor=vecContador[i];

        }

    }

    if(mayor!=0){ //para mostrar la fecha y la cant de ventas

        cout<<"La mayor cantidad de ventas que se registraron en un dia fueron: "<<mayor<<" venta/s"<<endl<<endl;
        cout<<"El/Los dia/s que se registro esa cantidad de ventas fueron: " << endl << endl << "Fechas: " << endl;

        for(int i=0; i<vecContador.size(); i++){
            if(vecContador[i] == mayor){
                fecha=vecFecha[i];
                cout<<fecha.mostrarFecha()<<endl;
            }
        }
    }
    else{
        cout<<"No hay ventas registradas"<<endl;
        }
}

void ManagerVenta::listarVendedorMayorRecaudacion(){
    Fecha fechaDesde,fechaHasta;
    VentaArchivo archi;
    Venta venta;
    ArchivoEmpleado archiE;
    Empleado e;
    Validador validador;

    int cantidadEmpleados=archiE.getCantidadRegistros();
    float mayorVenta=0.0;
    int id, cont = 0 ,cantidadRegistros=archi.getCantidadRegistros();

    bool* vendio = nullptr;
    float* sumatoriaVentas =nullptr;
    vendio = new bool[cantidadEmpleados];
    sumatoriaVentas = new float[cantidadEmpleados];

    if(vendio==nullptr || sumatoriaVentas==nullptr){
        cout << "Ocurrio un error en el sistema. "<< endl;
        return;
    }
    for(int i=0; i<cantidadEmpleados;i++){
        vendio[i]=false;
        sumatoriaVentas[i]=0.0;
    }

    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0;i<cantidadRegistros;i++){
        venta=archi.leer(i);
        id=venta.getIdEmpleado()-1;
        if(venta.getFechaVenta()<= fechaHasta && venta.getFechaVenta() >= fechaDesde){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
            vendio[id]=true;
            sumatoriaVentas[id]+=venta.getImporteTotal();
            if(cont==0){
                mayorVenta=sumatoriaVentas[id];
            }
            if(sumatoriaVentas[id]>mayorVenta){
                mayorVenta=sumatoriaVentas[id];
            }
            cont++;
        }
    }

    if(mayorVenta!=0){
        cout << "Empleado/s con el mayor monto de ventas acumuladas de $ " << mayorVenta<< endl;
         cout <<"---------------------------------------------------------------------------------------"<<endl;
        for(int i=0; i<cantidadEmpleados; i++){
            e=archiE.leer(i);
            if(sumatoriaVentas[i]== mayorVenta && vendio[i] && e.getEstado()){

                cout << "ID: " << e.getIdEmpleado()<<"\nNOMBRE: "<<e.getNombre()<<"\nAPELLIDO: "<<e.getApellido()<<endl;
                cout <<"---------------------------------------------------------------------------------------"<<endl;
            }
        }
    }else{
        cout<< "Aun no se han registrado ventas"<< endl;
    }
    delete[]vendio;
    delete[]sumatoriaVentas;
}

void ManagerVenta::listarVendedorMenorRecaudacion(){
    Fecha fechaDesde,fechaHasta;
    VentaArchivo archi;
    Venta venta;
    ArchivoEmpleado archiE;
    Empleado e;
    Validador validador;

    int cantidadEmpleados=archiE.getCantidadRegistros();
    float menorVenta=0.0;
    int id, cont = 0 ,cantidadRegistros=archi.getCantidadRegistros();

    bool* vendio = nullptr;
    float* sumatoriaVentas =nullptr;
    vendio = new bool[cantidadEmpleados];
    sumatoriaVentas = new float[cantidadEmpleados];

    if(vendio==nullptr || sumatoriaVentas==nullptr){
        cout << "Ocurrio un error en el sistema. "<< endl;
        return;
    }
    for(int i=0; i<cantidadEmpleados;i++){
        vendio[i]=false;
        sumatoriaVentas[i]=0.0;
    }

    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0;i<cantidadRegistros;i++){
        venta=archi.leer(i);
        id=venta.getIdEmpleado()-1;
        if(venta.getFechaVenta()<= fechaHasta && venta.getFechaVenta() >= fechaDesde){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
            vendio[id]=true;
            sumatoriaVentas[id]+=venta.getImporteTotal();
        }
    }

    for (int i=0; i< cantidadEmpleados; i++){
        if (vendio[i] ==true && cont == 0){
            menorVenta= sumatoriaVentas[i];
            cont++;
        }
        else if(vendio[i] && sumatoriaVentas[i] < menorVenta){
            menorVenta = sumatoriaVentas[i];
        }

    }

    if(menorVenta!=0){
        cout << "Empleado/s con el menor monto de ventas acumuladas de $ " << menorVenta<< endl;
        cout <<"---------------------------------------------------------------------------------------"<<endl;
        for(int i=0; i<cantidadEmpleados; i++){
            e=archiE.leer(i);
            if(sumatoriaVentas[i]== menorVenta && vendio[i] && e.getEstado()){

                cout << "ID: " << e.getIdEmpleado()<<"\nNOMBRE: "<<e.getNombre()<<"\nAPELLIDO: "<<e.getApellido()<<endl;
                cout <<"---------------------------------------------------------------------------------------"<<endl;
            }
        }
    }else{
        cout<< "Aun no se han registrado ventas"<< endl;
    }
    delete[]vendio;
    delete[]sumatoriaVentas;
 }

void ManagerVenta::listarVendedorMenorCantidadVentas(){
    Fecha fechaDesde,fechaHasta;
    VentaArchivo archi;
    Venta venta;
    ArchivoEmpleado archiE;
    Empleado e;
    Validador validador;

    int cantidadEmpleados=archiE.getCantidadRegistros();
    int cantVentas=0,menorCantidadVentas=0;
    int id,cantidadRegistros=archi.getCantidadRegistros();
    bool ventasRegistradas=false;
    bool* vendio = nullptr;
    float* sumatoriaVentas =nullptr;
    vendio = new bool[cantidadEmpleados];
    sumatoriaVentas = new float[cantidadEmpleados];
    int cont=0;

    if(vendio==nullptr || sumatoriaVentas==nullptr){
        cout << "Ocurrio un error en el sistema. "<< endl;
        return;
    }
    for(int i=0; i<cantidadEmpleados;i++){
        vendio[i]=false;
        sumatoriaVentas[i]=0.0;
    }

    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0;i<cantidadRegistros;i++){
        venta=archi.leer(i);
        id=venta.getIdEmpleado()-1;
        if(venta.getFechaVenta()<= fechaHasta && venta.getFechaVenta() >= fechaDesde){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
            vendio[id]=true;
            sumatoriaVentas[id]+=1;
            ventasRegistradas=true;
        }
    }

    for(int i=0; i<cantidadEmpleados;i++){
        if(cont == 0 && vendio[i]){
            menorCantidadVentas=sumatoriaVentas[i];
            cont++;
        }else if(sumatoriaVentas[i] < menorCantidadVentas && vendio[i]){
            menorCantidadVentas=sumatoriaVentas[i];
        }
    }

    if(ventasRegistradas){
        cout << "Empleado/s con menor cantidas de ventas es: " << menorCantidadVentas<< endl;
         cout <<"---------------------------------------------------------------------------------------"<<endl;
        for(int i=0; i<cantidadEmpleados; i++){
            e=archiE.leer(i);
            if(sumatoriaVentas[i]== menorCantidadVentas && vendio[i] && e.getEstado()){

                cout << "ID: " << e.getIdEmpleado()<<"\nNOMBRE: "<<e.getNombre()<<"\nAPELLIDO: "<<e.getApellido()<<endl;
                cout <<"---------------------------------------------------------------------------------------"<<endl;
            }
        }
    }else{
        cout<< "Aun no se han registrado ventas"<< endl;
    }
    delete[]vendio;
    delete[]sumatoriaVentas;

}
void ManagerVenta::listarVendedorMayorCantidadVentas(){
    Fecha fechaDesde,fechaHasta;
    VentaArchivo archi;
    Venta venta;
    ArchivoEmpleado archiE;
    Empleado e;
    Validador validador;

    int cantidadEmpleados=archiE.getCantidadRegistros();
    int cantVentas=0,mayorCantidadVentas=0;
    int id,cantidadRegistros=archi.getCantidadRegistros();
    bool ventasRegistradas=false;
    bool* vendio = nullptr;
    float* sumatoriaVentas =nullptr;
    vendio = new bool[cantidadEmpleados];
    sumatoriaVentas = new float[cantidadEmpleados];

    if(vendio==nullptr || sumatoriaVentas==nullptr){
        cout << "Ocurrio un error en el sistema. "<< endl;
        return;
    }
    for(int i=0; i<cantidadEmpleados;i++){
        vendio[i]=false;
        sumatoriaVentas[i]=0.0;
    }

    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0;i<cantidadRegistros;i++){
        venta=archi.leer(i);
        id=venta.getIdEmpleado()-1;
        if(venta.getFechaVenta()<= fechaHasta && venta.getFechaVenta() >= fechaDesde){///Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
            vendio[id]=true;
            sumatoriaVentas[id]+=1;
            ventasRegistradas=true;
        }
    }

    for(int i=0; i<cantidadEmpleados;i++){
        if(i==0){
            mayorCantidadVentas=sumatoriaVentas[i];
        }else if(sumatoriaVentas[i] > mayorCantidadVentas){
            mayorCantidadVentas=sumatoriaVentas[i];
        }
    }

    if(ventasRegistradas){
        cout << "Empleado/s con mmayor cantidad de ventas es: " << mayorCantidadVentas<< endl;
         cout <<"---------------------------------------------------------------------------------------"<<endl;
        for(int i=0; i<cantidadEmpleados; i++){
            e=archiE.leer(i);
            if(sumatoriaVentas[i]== mayorCantidadVentas && vendio[i] && e.getEstado()){

                cout << "ID: " << e.getIdEmpleado()<<"\nNOMBRE: "<<e.getNombre()<<"\nAPELLIDO: "<<e.getApellido()<<endl;
                cout <<"---------------------------------------------------------------------------------------"<<endl;
            }
        }
    }else{
        cout<< "No hay ventas registradas en el periodo ingresado"<< endl;
    }
    delete[]vendio;
    delete[]sumatoriaVentas;
}
void ManagerVenta::MayorRecaudacionPorPeriodo(){

    VentaArchivo archi;
    Venta vent;
    Fecha aux,fechaDesde,fechaHasta;
    Validador validador;

    float mayorVenta=0.0;


   int cantRegistro=archi.getCantidadRegistros();
    validador.validadorFiltroFecha(fechaDesde,fechaHasta);

    for(int i=0;i< cantRegistro;i++){
        vent=archi.leer(i);
        if (vent.getFechaVenta() <= fechaHasta ){

            if (vent.getFechaVenta() >= fechaDesde ){ //Sobrecarga de operadores: El objeto de la izquierda llama al operador y el de la derecha se envia por parametro (aux)
                   if(i==0){
                        mayorVenta=vent.getImporteTotal();
                        aux=vent.getFechaVenta();

                    }else if(vent.getImporteTotal()>mayorVenta){

                            mayorVenta=vent.getImporteTotal();
                            aux=vent.getFechaVenta();
                        }
            }
        }
    }
    if(mayorVenta<=0){
        cout<<endl;
        cout<<"NO HAY VENTAS REGISTRADAS EN ESE PERIODO DE TIEMPO"<<endl;
    }else{
        cout <<  "--------------------------------------------------------------------------------"<< endl;
        cout << "EL DIA QUE MAS RECAUDO EN EL PERIODO DESDE: " << fechaDesde.mostrarFecha()<<" HASTA "<<fechaHasta.mostrarFecha()<<endl;
        cout <<  "--------------------------------------------------------------------------------"<< endl << endl;
        cout<< aux.mostrarFecha()<< " Y EL MONTO RECAUDADO FUE DE:  $" <<  mayorVenta << endl;

    }
}

void ManagerVenta::mostrarFechaMayorCantidadVentasPorPeriodo(){



    Fecha fecha,fechaDesde,fechaHasta;
    VentaArchivo archi;
    Venta vent;
    Validador validador;


    std::vector<Fecha> vecFecha{};
    std::vector<int> vecContador{};
    int cantRegistro=archi.getCantidadRegistros();
    validador.validadorFiltroFecha(fechaDesde,fechaHasta);
    bool coincidencia=false;

    int mayor=0;
    int cont=0;

    for(int i=0;i<cantRegistro;i++){ //carga vec de fecha y vec contador, con las ventas registradas en el archivo
        vent=archi.leer(i);
        coincidencia=false;
        if (vent.getFechaVenta() <= fechaHasta ){
            if (vent.getFechaVenta() >= fechaDesde ){
                    if(i==0){
                    vecFecha.push_back(vent.getFechaVenta());
                    vecContador.push_back(1);
                    }
                    else{
                        for(int j=0; j<vecFecha.size();j++){//comparar que no exista esa fecha en el vecFecha, y si existe solo que tiene q aumentar el vecCont

                            if(vent.getFechaVenta() == vecFecha[j]){ //sobrecarga de operadores
                            vecContador[j]++;
                            coincidencia=true;
                            }
                        }
                        if(!coincidencia){
                        vecFecha.push_back(vent.getFechaVenta());
                        vecContador.push_back(1);
                        }
                    }
            }
        }
    }
    for(int i=0;i<vecContador.size();i++){//determina cual es la fecha donde se realizaron mas ventas

        if(i==0){
            mayor=vecContador[i];
            fecha=vecFecha[i];
        }
        else if(vecContador[i]>mayor){
                mayor=vecContador[i];
                fecha=vecFecha[i];
        }

    }
    if(mayor!=0){ //para mostrar la fecha y la cant de ventas

        cout<<"La mayor cantidad de ventas que se registraron en el periodo de tiempo desde "<<fechaDesde.mostrarFecha()<<" hasta "<<fechaHasta.mostrarFecha()<<endl<<endl;
        cout<<"la fecha es: "<<fecha.mostrarFecha() << endl;
        cout<<"La mayor cantidad de ventas registrada fue de: "<<mayor<<endl;


    }
    else{
        cout<<"No hay ventas registradas"<<endl;
    }
}

void ManagerVenta::cierreCaja(){
    Fecha diaActual;
    Venta venta;
    VentaArchivo archiVent;
    int cantidadRegistros = archiVent.getCantidadRegistros();
    float acumuladorVentasEfectivo=0;

    cout<< "FECHA DE CIERRE DE CAJA: " << endl << endl;
    diaActual.cargar();

    for(int i = 0; i< cantidadRegistros; i++){
        venta = archiVent.leer(i);
        if(diaActual==venta.getFechaVenta() && venta.getFormaDePago() == 3 ){
            acumuladorVentasEfectivo+= venta.getImporteTotal();

        }
    }
    system("cls");
    cout<< "CIERRE DE CAJA: " << endl << endl;
    cout << endl << "El cierre de caja en la fecha " << diaActual.mostrarFecha() << " debe ser: " << acumuladorVentasEfectivo << endl << endl;

}

void ManagerVenta::listarVentasToCsv(){
    VentaArchivo archivoVenta;
    Venta venta;

    int cantRegistrosVenta = archivoVenta.getCantidadRegistros();

    cout << "_nroFactura,_idEmpleado,_importeTotal,_formaDePago,Anio,Mes,Dia" << endl;

    for (int i=0;i<cantRegistrosVenta;i++){
        venta = archivoVenta.leer(i);
        cout << venta.mostrarToCsv();
        cout << endl;
     }
}

void ManagerVenta::listarDetalleVentaToCsv(){
    DetalleVentaArchivo archivoDetalleVenta;
    DetalleVenta detalleVenta;

    int cantRegistrosDetalleVenta = archivoDetalleVenta.getCantidadRegistros();
    cout << "_nroFactura,_idProducto,_cantProducto,_precioUnitario,_costoUnitario,_importeBruto" << endl;
    for (int j=0; j < cantRegistrosDetalleVenta; j++ ){
        detalleVenta = archivoDetalleVenta.leer(j);
        cout << detalleVenta.mostrarToCsv();
        cout << endl;
    }

}





