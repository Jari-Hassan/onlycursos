#pragma once
#include <string>
#include <vector>
using namespace std;

class Curso {
public:
    string titulo;
    string categoria;
    int inscritos;
    vector<string> temario;
    string nombreInstructor;
    int duracionHoras;
    string nivel; // Principiante, Intermedio, Avanzado

    Curso(string t = "", string cat = "", string inst = "", int dur = 0, string niv = "Principiante")
        : titulo(t), categoria(cat), inscritos(0), nombreInstructor(inst),
        duracionHoras(dur), nivel(niv) {
        if (categoria == "Programacion") {
            temario = {
                "Introduccion al lenguaje",
                "Variables y tipos de datos",
                "Estructuras de control",
                "Funciones y procedimientos",
                "POO - Programacion Orientada a Objetos",
                "Proyecto final"
            };
        }
        else if (categoria == "Diseño") {
            temario = {
                "Principios de diseño",
                "Herramientas profesionales",
                "Diseño de interfaces",
                "Prototipado",
                "Caso practico real"
            };
        }
        else {
            temario = {
                "Modulo 1: Introduccion",
                "Modulo 2: Conceptos basicos",
                "Modulo 3: Practica",
                "Modulo 4: Proyecto final"
            };
        }
    }
};