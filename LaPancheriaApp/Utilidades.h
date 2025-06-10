#pragma once
#include <string>

std::string pedirTipoDeUnidad(float &cantidadStock);
int validarConfirmacion(std::string mensaje);

void menuAdmin();

void menuEmpleados();

void menuProductos();
void menuIngredientes();
void menuCostos();

int verificarCoincidencia(std::string usuario, std::string contrasenia);
void limpiarPantalla();
