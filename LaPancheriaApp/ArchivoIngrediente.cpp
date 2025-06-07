#include "ArchivoIngrediente.h"

///Constructores
ArchivoIngrediente::ArchivoIngrediente(){
    _nombreArchivo= "Ingredientes.dat";
}
ArchivoIngrediente::ArchivoIngrediente(std::string nombreArchivo){
    _nombreArchivo= nombreArchivo;
}


///Metodos
bool ArchivoIngrediente::guardar(Ingrediente registro){
    FILE* pFile;
    bool result;

    pFile= fopen(_nombreArchivo.c_str(), "ab");

    if (pFile==nullptr){
        return false;
    }

    result = fwrite(&registro, sizeof(Ingrediente), 1, pFile);

    fclose(pFile);
    return result;
}

int ArchivoIngrediente::getCantidadRegistros(){
    FILE* pFile;
    int tamRegistro, total, cantidad;

    pFile= fopen(_nombreArchivo.c_str(), "rb");

    if (pFile==nullptr){
        return 0;
    }

    fseek(pFile, 0, SEEK_END);

    total = ftell(pFile);

    cantidad = total / sizeof(Ingrediente);

    fclose(pFile);
    return cantidad;
}


Ingrediente ArchivoIngrediente::leer(int pos){
FILE* pFile;
Ingrediente registro;

pFile = fopen(_nombreArchivo.c_str(), "rb");

if (pFile==nullptr){
    return registro;
}

fseek(pFile, sizeof(Ingrediente) * pos , SEEK_SET);
fread(&registro, sizeof(Ingrediente), 1, pFile);

fclose(pFile);
return registro;
}

int ArchivoIngrediente::buscar(int idIngrediente){
   FILE *pFile;
   Ingrediente registro;
   int posicion = 0;

   pFile = fopen(_nombreArchivo.c_str(), "rb");

   if (pFile == nullptr){
      return -2;
   }
   while(fread(&registro, sizeof(Ingrediente), 1, pFile) == 1){
      if (registro.getIdIngrediente() == idIngrediente){
         fclose(pFile);
         return posicion;
      }
      posicion++;
   }

   fclose(pFile);
   return -1; // si llega hasta aca es porque no encontro un valor valido y retorno -1
}


