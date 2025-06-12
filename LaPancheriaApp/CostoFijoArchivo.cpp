#include "CostoFijoArchivo.h"
#include <cstring>
#include <iostream>
using namespace std;

//Constructor por omision
CostoFijoArchivo::CostoFijoArchivo(){
    _nombreArchivo="costoFijo.dat";
}
//Constructor por parametro
CostoFijoArchivo::CostoFijoArchivo(std::string nombreArchivo){
    _nombreArchivo=nombreArchivo;
}

//Metodos

bool CostoFijoArchivo::guardar(CostoFijo registro){
    FILE* pfile;
    bool result;

    pfile= fopen(_nombreArchivo.c_str(), "ab");

    if (pfile==nullptr){
        return false;
    }
    result = fwrite(&registro, sizeof(CostoFijo), 1, pfile);

    fclose(pfile);
    return result;
}


int CostoFijoArchivo::getCantidadRegistros(){
    FILE* pfile;
    int tamRegistro, total, cantidad;

    pfile= fopen(_nombreArchivo.c_str(), "rb");

    if(pfile==nullptr){
        return 0;
    }

    fseek(pfile,0,SEEK_END);

    total= ftell(pfile);
    cantidad= total/sizeof(CostoFijo);

    fclose(pfile);
    return cantidad;
}

CostoFijo CostoFijoArchivo::leer(int posicion){
FILE *pFile;
CostoFijo costoF;
costoF.setIdCosto(-1);
pFile=fopen(_nombreArchivo.c_str(),"rb");
    if(pFile==nullptr){
    cout<<"No se pudo abrir el archivo"<<endl;
    return costoF;
}
fseek(pFile,posicion*sizeof(CostoFijo),0);
fread(&costoF,sizeof(CostoFijo),1,pFile);
fclose(pFile);
return costoF;

}



