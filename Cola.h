#pragma once
#include "Nodo.h"
#include <functional>
using namespace std;

// Cola Generica - FIFO
template <typename T>
class Cola {
private:
    Nodo<T>* frente;
    Nodo<T>* fin;
    int longitud;

public:
    Cola() : frente(nullptr), fin(nullptr), longitud(0) {}
    ~Cola() {
        while (!estaVacia()) {
            T temp;
            desencolar(temp);
        }
    }

    void encolar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (estaVacia()) frente = fin = nuevo;
        else { fin->siguiente = nuevo; fin = nuevo; }
        longitud++;
    }

    bool desencolar(T& elemento) {
        if (estaVacia()) return false;
        Nodo<T>* temp = frente;
        elemento = frente->dato;
        frente = frente->siguiente;
        if (frente == nullptr) fin = nullptr;
        delete temp;
        longitud--;
        return true;
    }

    bool verFrente(T& elemento) const {
        if (estaVacia()) return false;
        elemento = frente->dato;
        return true;
    }

    void limpiar() { T t; while (desencolar(t)); }

    void mostrar(const function<void(const T&)>& f) const {
        Nodo<T>* actual = frente;
        while (actual != nullptr) { f(actual->dato); actual = actual->siguiente; }
    }

    bool estaVacia() const { return frente == nullptr; }
    int tamanio() const { return longitud; }
};
