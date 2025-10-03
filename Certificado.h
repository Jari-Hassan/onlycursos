#pragma once
#include <string>
using namespace std;

class Certificado {
public:
    string correoUsuario;
    string tituloCurso;
    string fechaEmision;
    string codigoCertificado;

    Certificado(string u = "", string c = "", string f = "", string cod = "")
        : correoUsuario(u), tituloCurso(c), fechaEmision(f), codigoCertificado(cod) {
    }
};