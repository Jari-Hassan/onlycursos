#pragma once
#include <string>
using namespace std;

class Inscripcion {
public:
    string correoUsuario;
    string tituloCurso;
    int    progreso;          
    string fechaInscripcion;
    bool   completado;

    Inscripcion(string u = "", string c = "", string f = "01/10/2025")
        : correoUsuario(u), tituloCurso(c), progreso(0), fechaInscripcion(f), completado(false) {
    }
};