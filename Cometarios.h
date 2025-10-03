#pragma once
#include <string>
using namespace std;

class Comentario {
public:
    string correoUsuario;
    string tituloCurso;
    string texto;
    string fecha;

    Comentario(string u = "", string c = "", string t = "", string f = "")
        : correoUsuario(u), tituloCurso(c), texto(t), fecha(f) {
    }
};