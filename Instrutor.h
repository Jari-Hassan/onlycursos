#pragma once
#include <string>
using namespace std;

class Instructor {
public:
    string nombre;
    string especialidad;
    int    aniosExperiencia;
    double calificacion;

    Instructor(string n = "", string e = "", int a = 0, double c = 5.0)
        : nombre(n), especialidad(e), aniosExperiencia(a), calificacion(c) {
    }
};