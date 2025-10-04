#include "pch.h"
#include "Fondos.h"
#include <iostream>
#include <vector>
#include <string>

using namespace System;
using namespace std;

namespace Fondos {
    // Matrices para los diferentes fondos
    vector<vector<int>> fondoMenuPrincipal;
    vector<vector<int>> fondoSecundario;
    vector<vector<int>> logoAirPacific;
    vector<vector<int>> logoGloboTerrestre;

    // Inicializar todas las matrices de fondos
    void InicializarFondos() {
        // Fondo del menú principal (franjas horizontales azul claro)
        fondoMenuPrincipal = vector<vector<int>>(35, vector<int>(110, 0));
        for (int y = 0; y < 35; y++) {
            for (int x = 0; x < 110; x++) {
                // Crear franjas horizontales
                if (y < 2 || y > 32 || (y > 6 && y < 9) || (y > 25 && y < 28)) {
                    fondoMenuPrincipal[y][x] = 1; // Azul claro
                }
                else {
                    fondoMenuPrincipal[y][x] = 0; // Gris claro
                }
            }
        }

        // Fondo secundario (bordes verdes)
        fondoSecundario = vector<vector<int>>(35, vector<int>(110, 0));
        for (int y = 0; y < 35; y++) {
            for (int x = 0; x < 110; x++) {
                // Crear bordes verdes
                if (x < 2 || x > 107 || y < 2 || y > 32) {
                    fondoSecundario[y][x] = 2; // Verde
                }
                else {
                    fondoSecundario[y][x] = 0; // Gris claro
                }
            }
        }

        // Logo "AIR PACIFIC" (píxeles en negro)
        logoAirPacific = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0},
            {1,0,0,0,1,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        // Logo del globo terrestre (verde y azul)
        logoGloboTerrestre = {
            {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
            {0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
            {0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0},
            {0,1,2,2,2,1,1,2,2,1,2,2,2,2,1,0},
            {1,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1},
            {1,2,2,1,1,2,2,2,2,2,1,1,2,2,2,1},
            {1,2,1,1,2,2,2,2,2,2,2,1,1,2,2,1},
            {1,2,1,2,2,2,2,2,2,2,2,2,1,2,2,1},
            {1,2,1,2,2,2,2,2,2,2,2,2,1,2,2,1},
            {1,2,1,1,2,2,2,2,2,2,2,1,1,2,2,1},
            {1,2,2,1,1,2,2,2,2,2,1,1,2,2,2,1},
            {0,1,2,2,2,1,1,1,1,1,2,2,2,2,1,0},
            {0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0},
            {0,0,0,1,1,2,2,2,2,2,2,1,1,0,0,0},
            {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0}
        };
    }

    // Dibujar el fondo del menú principal
    void DibujarFondoMenuPrincipal() {
        Console::BackgroundColor = ConsoleColor::DarkGray;
        Console::Clear();

        for (size_t y = 0; y < fondoMenuPrincipal.size(); y++) {
            for (size_t x = 0; x < fondoMenuPrincipal[y].size(); x++) {
                Console::SetCursorPosition((int)x, (int)y);
                if (fondoMenuPrincipal[y][x] == 1) {
                    Console::BackgroundColor = ConsoleColor::Cyan;
                    Console::Write(" ");
                }
            }
        }
        Console::BackgroundColor = ConsoleColor::Black;
    }

    // Dibujar fondo secundario con bordes verdes
    void DibujarFondoSecundario() {
        Console::BackgroundColor = ConsoleColor::DarkGray;
        Console::Clear();

        for (size_t y = 0; y < fondoSecundario.size(); y++) {
            for (size_t x = 0; x < fondoSecundario[y].size(); x++) {
                Console::SetCursorPosition((int)x, (int)y);
                if (fondoSecundario[y][x] == 2) {
                    Console::BackgroundColor = ConsoleColor::Green;
                    Console::Write(" ");
                }
            }
        }
        Console::BackgroundColor = ConsoleColor::Black;
    }

    // Dibujar el logo en la posición especificada
    void DibujarLogoMenuPrincipal(int startX, int startY) {
        // Dibujar logo AIR PACIFIC
        for (size_t y = 0; y < logoAirPacific.size(); y++) {
            for (size_t x = 0; x < logoAirPacific[y].size(); x++) {
                Console::SetCursorPosition(startX + (int)x, startY + (int)y);
                if (logoAirPacific[y][x] == 1) {
                    Console::BackgroundColor = ConsoleColor::Black;
                    Console::Write(" ");
                }
            }
        }

        // Dibujar logo del globo terrestre a la derecha
        int globoX = startX + 30;
        for (size_t y = 0; y < logoGloboTerrestre.size(); y++) {
            for (size_t x = 0; x < logoGloboTerrestre[y].size(); x++) {
                Console::SetCursorPosition(globoX + (int)x, startY + (int)y);
                if (logoGloboTerrestre[y][x] == 1) {
                    Console::BackgroundColor = ConsoleColor::Blue;
                    Console::Write(" ");
                }
                else if (logoGloboTerrestre[y][x] == 2) {
                    Console::BackgroundColor = ConsoleColor::Green;
                    Console::Write(" ");
                }
            }
        }

        // Restaurar color de fondo
        Console::BackgroundColor = ConsoleColor::Black;

        // Escribe texto "SISTEMA DE TICKETS - AIR PACIFIC"
        Console::SetCursorPosition(startX, startY + logoAirPacific.size() + 1);
        Console::ForegroundColor = ConsoleColor::White;
        cout << "SISTEMA DE TICKETS - AIR PACIFIC";
        Console::ForegroundColor = ConsoleColor::Gray;
    }

    // Dibujar un borde rectangular para menús
    void DibujarBordeMenu(int x, int y, int ancho, int alto, ConsoleColor color) {
        ConsoleColor colorOriginal = Console::BackgroundColor;
        Console::BackgroundColor = color;

        // Línea superior e inferior
        for (int i = 0; i < ancho; i++) {
            Console::SetCursorPosition(x + i, y);
            Console::Write(" ");
            Console::SetCursorPosition(x + i, y + alto - 1);
            Console::Write(" ");
        }

        // Líneas laterales
        for (int i = 1; i < alto - 1; i++) {
            Console::SetCursorPosition(x, y + i);
            Console::Write(" ");
            Console::SetCursorPosition(x + ancho - 1, y + i);
            Console::Write(" ");
        }

        Console::BackgroundColor = colorOriginal;
    }
}