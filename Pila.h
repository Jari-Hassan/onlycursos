#pragma once
#include "Nodo.h"
#include <functional>
using namespace std;

// Pila Generica - LIFO
template <typename T>
class Pila {
private:
    Nodo<T>* tope;
    int longitud;

public:
    Pila() : tope(nullptr), longitud(0) {}
    ~Pila() {
        while (!estaVacia()) {
            T temp;
            pop(temp);
        }
    }

    void push(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        nuevo->siguiente = tope;
        tope = nuevo;
        longitud++;
    }

    bool pop(T& elemento) {
        if (estaVacia()) return false;
        Nodo<T>* temp = tope;
        elemento = tope->dato;
        tope = tope->siguiente;
        delete temp;
        longitud--;
        return true;
    }

    bool top(T& elemento) const {
        if (estaVacia()) return false;
        elemento = tope->dato;
        return true;
    }

    void limpiar() { T temp; while (pop(temp)); }

    void mostrar(const function<void(const T&)>& f) const {
        Nodo<T>* actual = tope;
        while (actual != nullptr) { f(actual->dato); actual = actual->siguiente; }
    }

    bool estaVacia() const { return tope == nullptr; }
    int tamanio() const { return longitud; }
};