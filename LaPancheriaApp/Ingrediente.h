#pragma once
#include <string>

class Ingrediente{
private:
    int _idIngrediente;
    char _nombreIngrediente[30];
    float _cantidadStock;
    float _costoUnitario;
    char _tipoDeUnidad[20];
    bool _estado;

public:
    ///Constructores
    Ingrediente();
    Ingrediente(int idIngrediente, std::string nombreIngrediente, float cantidadStock, float costoUnitario, std::string tipoDeUnidad, bool estado);

    ///Setters
    void setIdIngrediente(int idIngrediente);
    void setNombreIngrediente(std::string nombreIngrediente);
    void setCantidadStock(float cantidadStock);
    void setCostoUnitario(float costoUnitario);
    void setTipoDeUnidad(std::string tipoDeUnidad);
    void setEstado(bool estado);

    ///Getters
    int getIdIngrediente();
    std::string getNombreIngrediente();
    float getCantidadStock();
    float getCostoUnitario();
    std::string getTipoDeUnidad();
    bool getEstado();

    ///Metodos
    void mostrar();
    std::string mostrarToCsv();


};
