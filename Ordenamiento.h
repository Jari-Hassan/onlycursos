#pragma once
#include "ListaEnlazada.h"
#include "Curso.h"
using namespace std;

// Ordenamiento Burbuja (descendente por inscritos)
void ordenarCursosBurbuja(ListaEnlazada<Curso>& cursos) {
    int n = cursos.tamanio();
    if (n <= 1) return;

    bool intercambio;
    do {
        intercambio = false;
        for (int i = 0; i < n - 1; ++i) {
            Curso* a = cursos.obtenerEn(i);
            Curso* b = cursos.obtenerEn(i + 1);
            if (a && b && a->inscritos < b->inscritos) {
                Curso tmp = *a; *a = *b; *b = tmp;
                intercambio = true;
            }
        }
    } while (intercambio);
}