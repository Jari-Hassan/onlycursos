#pragma once
// Nodo genérico para estructuras de datos enlazadas
template <typename T>
class Nodo {
public:
    T dato;
    Nodo* siguiente;

    // Constructor
    Nodo(T valor) : dato(valor), siguiente(nullptr) {}
};