#pragma once
#include "Nodo.h"
#include <functional>
#include <iostream>
using namespace std;

// Lista Simple Enlazada Generica con Templates
template <typename T>
class ListaEnlazada {
private:
    Nodo<T>* cabeza;
    int longitud;

    // METODO RECURSIVO: Buscar elemento recursivamente
    Nodo<T>* buscarRecursivo(Nodo<T>* actual, function<bool(const T&)> criterio) {
        if (actual == nullptr) return nullptr;
        if (criterio(actual->dato)) return actual;
        return buscarRecursivo(actual->siguiente, criterio);
    }

    // METODO RECURSIVO: Contar elementos que cumplen condicion
    int contarRecursivo(Nodo<T>* actual, function<bool(const T&)> criterio) {
        if (actual == nullptr) return 0;
        int cuenta = criterio(actual->dato) ? 1 : 0;
        return cuenta + contarRecursivo(actual->siguiente, criterio);
    }

public:
    // Constructor
    ListaEnlazada() : cabeza(nullptr), longitud(0) {}

    // Destructor
    ~ListaEnlazada() {
        while (cabeza != nullptr) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }

    // METODO 1: Agregar al final
    void agregar(const T& elemento) {
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (cabeza == nullptr) {
            cabeza = nuevo;
        }
        else {
            Nodo<T>* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
        longitud++;
    }

    // METODO 2: Insertar en posicion especifica
    bool insertarEn(int posicion, const T& elemento) {
        if (posicion < 0 || posicion > longitud) return false;
        Nodo<T>* nuevo = new Nodo<T>(elemento);
        if (posicion == 0) {
            nuevo->siguiente = cabeza;
            cabeza = nuevo;
        }
        else {
            Nodo<T>* actual = cabeza;
            for (int i = 0; i < posicion - 1; i++) {
                actual = actual->siguiente;
            }
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
        longitud++;
        return true;
    }

    // METODO 3: Eliminar elemento por criterio (lambda)
    bool eliminar(function<bool(const T&)> criterio) {
        if (cabeza == nullptr) return false;

        if (criterio(cabeza->dato)) {
            Nodo<T>* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            longitud--;
            return true;
        }

        Nodo<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            if (criterio(actual->siguiente->dato)) {
                Nodo<T>* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                longitud--;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    // METODO 4: Buscar elemento (usa recursividad)
    T* buscar(function<bool(const T&)> criterio) {
        Nodo<T>* encontrado = buscarRecursivo(cabeza, criterio);
        return (encontrado != nullptr) ? &(encontrado->dato) : nullptr;
    }

    // METODO 5: Obtener por indice
    T* obtenerEn(int indice) {
        if (indice < 0 || indice >= longitud) return nullptr;
        Nodo<T>* actual = cabeza;
        for (int i = 0; i < indice; i++) {
            actual = actual->siguiente;
        }
        return &(actual->dato);
    }

    // METODO 6: Contar elementos que cumplen condicion (usa recursividad)
    int contar(function<bool(const T&)> criterio) {
        return contarRecursivo(cabeza, criterio);
    }

    // METODO 7: Filtrar
    ListaEnlazada<T> filtrar(function<bool(const T&)> criterio) {
        ListaEnlazada<T> resultado;
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            if (criterio(actual->dato)) {
                resultado.agregar(actual->dato);
            }
            actual = actual->siguiente;
        }
        return resultado;
    }

    // METODO 8: Mostrar con funcion lambda
    void mostrar(function<void(const T&)> funcion) {
        Nodo<T>* actual = cabeza;
        while (actual != nullptr) {
            funcion(actual->dato);
            actual = actual->siguiente;
        }
    }

    // METODO 9: Verificar si existe
    bool existe(function<bool(const T&)> criterio) {
        return buscarRecursivo(cabeza, criterio) != nullptr;
    }

    // Aux
    bool estaVacia() const { return cabeza == nullptr; }
    int tamanio() const { return longitud; }
    void obtenerTodos(function<void(const T&)> callback) { mostrar(callback); }
};