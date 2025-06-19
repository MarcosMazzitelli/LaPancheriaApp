#include <iostream>
#include "Producto.h"
#include "Venta.h"
#include "FormaDePago.h"
#include "Tests.h"
#include "Venta.h"
#include "DetalleVenta.h"
#include "Utilidades.h"
#include "MenuManager.h"
#include "Validador.h"

using namespace std;

int main()
{
  /*  Validador v;
    string palabra;
    for(int i=0; i<5; i++){
       // cout << "Ingrese un DNI (8 digitos): ";
        cout << "Ingrese un email: ";
        getline(cin,palabra);
        if (v.esEmail(palabra)){
            //cout << "\nDNI valido!\n";
            cout << "\nEMAIL valido!\n";
            cout << palabra << endl;
        }
        else{
            //cout << "\nDNI invalido!\n";
            cout << "\nEMAIL invalido!\n";
            cout << palabra << endl;
        }
    } */
  MenuManager menu;
  menu.login();

    return 0;
}
