#include "ArchivoCliente.h"

/*Constructores*/
ArchivoCliente::ArchivoCliente(){
    _nombreArchivo="Clientes.dat";
}

ArchivoCliente::ArchivoCliente(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

/*Metodos*/
bool ArchivoCliente::guardar(Cliente registro){
    bool result;
    FILE* pFile;

    pFile =fopen(_nombreArchivo.c_str(), "ab");
    if(pFile==nullptr){
        return false;
    }
    result=fwrite(&registro, sizeof(Cliente), 1, pFile);
    fclose(pFile);
    return result;
}

int ArchivoCliente::getCantidadRegistros(){
    int total,cantidad;
    FILE* pFile;

    pFile= fopen(_nombreArchivo.c_str(), "rb");
    if(pFile==nullptr){
        return 0;
    }
    fseek(pFile, 0,SEEK_END);

    total=ftell(pFile);

    cantidad=total/sizeof(Cliente);

    fclose(pFile);

    return cantidad;
}

Cliente ArchivoCliente::leer(int pos){
    FILE* pFile;

    Cliente registro;
    pFile= fopen(_nombreArchivo.c_str(),"rb");

    if(pFile==nullptr){
        return registro;
    }

    fseek(pFile, sizeof(Cliente)* pos, SEEK_SET);

    fread(&registro, sizeof(Cliente), 1, pFile);

    fclose(pFile);

    return registro;
}

int ArchivoCliente::buscar(std::string dniCliente){
   FILE *pFile;
   Cliente registro;
   int posicion = 0;

   pFile = fopen(_nombreArchivo.c_str(), "rb");

   if (pFile == nullptr){
      return -2;
   }
   while(fread(&registro, sizeof(Cliente), 1, pFile) == 1){
      if (registro.getDni() == dniCliente){
         fclose(pFile);
         return posicion;
      }
      posicion++;
   }

   fclose(pFile);
   return -1;
}

bool ArchivoCliente::modificarCliente(Cliente c, int pos){
    FILE* pFile;
    pFile = fopen(_nombreArchivo.c_str(),"rb+");

    if(pFile==nullptr){
        return false;
    }
    fseek(pFile,pos*sizeof(c),0);
    bool escribio = fwrite(&c,sizeof(c),1,pFile);
    fclose(pFile);
    return escribio;
}










