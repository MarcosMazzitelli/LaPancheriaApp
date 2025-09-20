#pragma once
#include <string>

std::string seleccionarYConvertirUnidad(float &cantidadStock);
std::string seleccionarYConvertirUnidad(float &cantidadStock, std::string tipoDeUnidad);

int pedirYValidarConfirmacion(std::string mensaje = "\nDesea confirmar? \n1)Si \n0)No \n\n");

void menuAdmin();

void menuEmpleados();

void menuProductos();
void menuIngredientes();
void menuCostos();

int verificarCoincidencia(std::string usuario, std::string contrasenia);
void limpiarPantalla();

void encabezadoDetalleVenta();
