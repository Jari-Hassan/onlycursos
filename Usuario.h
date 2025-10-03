#pragma once
#include <string>
using namespace std;

class Usuario {
public:
    string nombre;
    string apellido;
    string correo;
    string dni;
    string fechaRegistro;

    Usuario(string n = "", string a = "", string d = "", string c = "", string f = "01/10/2025")
        : nombre(n), apellido(a), dni(d), correo(c), fechaRegistro(f) {
    }
};