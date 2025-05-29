#pragma once
#include <string>

class Ingrediente{
private:
    int _idIngrediente;
    char _nombreIngrediente[30];
    float _cantidadStock;
    char _tipoDeUnidad[20];
    bool _estado;

public:
    ///Constructores
    Ingrediente();
    Ingrediente(int idIngrediente, std::string nombreIngrediente, float cantidadStock, std::string tipoDeUnidad, bool estado);

    ///Setters
    void setIdIngrediente(int idIngrediente);
    void setNombreIngrediente(std::string nombreIngrediente);
    void setCantidadStock(float cantidadStock);
    void setTipoDeUnidad(std::string tipoDeUnidad);
    void setEstado(bool estado);

    ///Getters
    int getIdIngrediente();
    std::string getNombreIngrediente();
    float getCantidadStock();
    std::string getTipoDeUnidad();
    bool getEstado();

    ///Metodos
    void mostrar();
    std::string mostrarToCsv();


};
