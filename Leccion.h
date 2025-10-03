#pragma once
#include <string>
using namespace std;

class Leccion {
public:
    string titulo;
    int    duracionMinutos;
    bool   completada;

    Leccion(string t = "", int d = 0, bool c = false)
        : titulo(t), duracionMinutos(d), completada(c) {
    }
};