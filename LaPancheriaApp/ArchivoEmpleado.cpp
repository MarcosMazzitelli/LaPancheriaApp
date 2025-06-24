#include "ArchivoEmpleado.h"

/*Constructores*/
ArchivoEmpleado::ArchivoEmpleado(){
    _nombreArchivo="Empleados.dat";
}

ArchivoEmpleado::ArchivoEmpleado(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

/*Metodos*/
bool ArchivoEmpleado::guardar(Empleado registro){
    bool result;
    FILE* pFile;

    pFile =fopen(_nombreArchivo.c_str(), "ab");
    if(pFile==nullptr){
        return false;
    }
    result=fwrite(&registro, sizeof(Empleado), 1, pFile);

    fclose(pFile);

    return result;
}

int ArchivoEmpleado::getCantidadRegistros(){
    int total,cantidad;
    FILE* pFile;

    pFile= fopen(_nombreArchivo.c_str(), "rb");
    if(pFile==nullptr){
        return 0;
    }
    fseek(pFile, 0,SEEK_END);

    total=ftell(pFile);

    cantidad=total/sizeof(Empleado);

    fclose(pFile);

    return cantidad;
}

Empleado ArchivoEmpleado::leer(int pos){
    FILE* pFile;

    Empleado registro;

    pFile = fopen(_nombreArchivo.c_str(), "rb");

    if(pFile==nullptr){
        return registro;
    }

    fseek(pFile, sizeof(Empleado)* pos, SEEK_SET);

    fread(&registro, sizeof(Empleado), 1, pFile);

    fclose(pFile);

    return registro;
}


int ArchivoEmpleado::buscar(std::string dniEmpleado){
   FILE *pFile;
   Empleado registro;
   int posicion = 0;

   pFile = fopen(_nombreArchivo.c_str(), "rb");

   if (pFile == nullptr){
      return -2;
   }
   while(fread(&registro, sizeof(Empleado), 1, pFile) == 1){
      if (registro.getDni() == dniEmpleado){
         fclose(pFile);
         return posicion;
      }
      posicion++;
   }

   fclose(pFile);
   return -1;
}

bool ArchivoEmpleado::modificarEmpleado(Empleado e, int pos){
    FILE* pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb+");

    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,pos*sizeof(e),0);
    bool escribio = fwrite(&e,sizeof(e),1,pFile);
    fclose(pFile);
    return escribio;
}


