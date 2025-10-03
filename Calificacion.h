#pragma once
#include <string>
using namespace std;

class Calificacion {
public:
    string correoUsuario;
    string tituloCurso;
    int    estrellas;   // 1-5
    string comentario;

    Calificacion(string u = "", string c = "", int e = 5, string com = "")
        : correoUsuario(u), tituloCurso(c), estrellas(e), comentario(com) {
    }
};