#pragma once

#include <string>
#include <vector>

// Definiciones de colores para usar con los fondos
namespace Fondos {
    // Matrices para los diferentes fondos
    extern std::vector<std::vector<int>> fondoMenuPrincipal;
    extern std::vector<std::vector<int>> fondoSecundario;
    extern std::vector<std::vector<int>> logoAirPacific;
    extern std::vector<std::vector<int>> logoGloboTerrestre;

    // Funciones para dibujar fondos
    void DibujarFondoMenuPrincipal();
    void DibujarFondoSecundario();
    void DibujarLogoMenuPrincipal(int x, int y);
    void DibujarBordeMenu(int x, int y, int ancho, int alto, System::ConsoleColor color);
    void InicializarFondos();
}