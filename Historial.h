#pragma once
#include <string>
using namespace std;

class Historial {
public:
    string accion;
    string detalle;
    string fecha;

    Historial(string a = "", string d = "", string f = "")
        : accion(a), detalle(d), fecha(f) {
    }
};