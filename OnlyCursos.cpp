#include"pch.h"
#include <iostream>
#include <string>
#include <ctime>
#include "Nodo.h"
#include "ListaEnlazada.h"
#include "Pila.h"
#include "Cola.h"
#include "Usuario.h"
#include "Curso.h"
#include "Inscripcion.h"
#include "Calificacion.h"
#include "Historial.h"
#include "Ordenamiento.h"

using namespace std;
using namespace System;

// ======= Estructuras globales (MEMORIA) =======
ListaEnlazada<Usuario> usuarios;
ListaEnlazada<Curso> cursos;
ListaEnlazada<Inscripcion> inscripciones;
ListaEnlazada<Calificacion> calificaciones;
Pila<Historial> historial;
Cola<string> solicitudesPendientes;

// Fecha actual (dd/mm/aaaa) — versión simple
string obtenerFechaActual() {
    time_t now = time(0);
    tm* t = localtime(&now); // Visual Studio puede dar warning (C4996), pero compila.
    return to_string(t->tm_mday) + "/" + to_string(1 + t->tm_mon) + "/" + to_string(1900 + t->tm_year);
}

// Registrar acción en historial (Pila)
void registrarHistorial(string accion, string detalle) {
    historial.push(Historial(accion, detalle, obtenerFechaActual()));
}

// -------- Menú principal (pantalla) --------
void mostrarMenu() {
    int x = 18, y = 3;
    Console::ForegroundColor = ConsoleColor::Cyan;
    Console::SetCursorPosition(x, y);
    cout << "   ___                  ____                       \n";
    Console::SetCursorPosition(x, y + 1);
    cout << "  / _ \\ _ __   ___ _ __/ ___|   _ _ __ ___  ___  ___\n";
    Console::SetCursorPosition(x, y + 2);
    cout << " | | | | '_ \\ / _ \\ '_ \\___ \\ | | | '__/ __|/ _ \\/ __|\n";
    Console::SetCursorPosition(x, y + 3);
    cout << " | |_| | |_) |  __/ | | |__) || |_| | |  \\__ \\ (_) \\__ \\\n";
    Console::SetCursorPosition(x, y + 4);
    cout << "  \\___/| .__/ \\___|_| |_____/ \\__,_|_|  |___/\\___/|___/\n";
    Console::SetCursorPosition(x, y + 5);
    cout << "       |_| Plataforma de Cursos Online Gratis\n";

    Console::ForegroundColor = ConsoleColor::White;
    Console::SetCursorPosition(x, y + 6);
    cout << "________________________________________________________________";
    Console::SetCursorPosition(x + 2, y + 7);  cout << " [1]  REGISTRAR USUARIO";
    Console::SetCursorPosition(x + 2, y + 8);  cout << " [2]  LISTAR CURSOS (con temario)";
    Console::SetCursorPosition(x + 2, y + 9);  cout << " [3]  INSCRIBIRSE EN CURSO";
    Console::SetCursorPosition(x + 2, y + 10); cout << " [4]  VER USUARIOS REGISTRADOS";
    Console::SetCursorPosition(x + 2, y + 11); cout << " [5]  VER INSCRITOS POR CURSO";
    Console::SetCursorPosition(x + 2, y + 12); cout << " [6]  VER MIS CURSOS (por correo)";
    Console::SetCursorPosition(x + 2, y + 13); cout << " [7]  CALIFICAR CURSO";
    Console::SetCursorPosition(x + 2, y + 14); cout << " [8]  BUSCAR CURSO POR CATEGORIA";
    Console::SetCursorPosition(x + 2, y + 15); cout << " [9]  ORDENAR CURSOS POR INSCRITOS";
    Console::SetCursorPosition(x + 2, y + 16); cout << " [10] VER HISTORIAL DE ACCIONES";
    Console::SetCursorPosition(x + 2, y + 17); cout << " [0]  SALIR";
    Console::SetCursorPosition(x, y + 18);
    cout << "________________________________________________________________";
    Console::SetCursorPosition(x + 2, y + 19);
    cout << " OPCION: ";
}

// -------- Cursos por defecto --------
void inicializarCursos() {
    Curso cpp("C++ desde cero", "Programacion", "Juan Perez", 40, "Principiante");
    cpp.temario = {
        "1. Introduccion a C++",
        "2. Variables y tipos de datos",
        "3. Operadores y expresiones",
        "4. Estructuras de control (if, while, for)",
        "5. Funciones y procedimientos",
        "6. Arrays y punteros",
        "7. POO: Clases y objetos",
        "8. Herencia y polimorfismo",
        "9. Templates y STL",
        "10. Proyecto final: Sistema de gestion"
    };
    cursos.agregar(cpp);

    Curso diseno("Diseño UX/UI Profesional", "Diseño", "Maria Rodriguez", 30, "Intermedio");
    diseno.temario = {
        "1. Principios de diseño UX",
        "2. Investigacion de usuarios",
        "3. Wireframes y prototipos",
        "4. Figma para diseñadores",
        "5. Diseño de interfaces modernas",
        "6. Design Systems",
        "7. Accesibilidad y usabilidad",
        "8. Proyecto: App movil"
    };
    cursos.agregar(diseno);

    Curso python("Python para Inteligencia Artificial", "Programacion", "Carlos Diaz", 50, "Avanzado");
    python.temario = {
        "1. Fundamentos de Python",
        "2. NumPy y Pandas",
        "3. Visualizacion con Matplotlib",
        "4. Introduccion a Machine Learning",
        "5. Algoritmos de clasificacion",
        "6. Redes neuronales basicas",
        "7. TensorFlow y Keras",
        "8. Proyecto: Modelo predictivo"
    };
    cursos.agregar(python);

    Curso js("JavaScript Moderno ES6+", "Programacion", "Ana Torres", 35, "Intermedio");
    js.temario = {
        "1. Sintaxis moderna ES6+",
        "2. Arrow functions y destructuring",
        "3. Promesas y async/await",
        "4. Fetch API y AJAX",
        "5. Manipulacion del DOM",
        "6. Frameworks: React basics",
        "7. Proyecto: Aplicacion web interactiva"
    };
    cursos.agregar(js);
}

// -------- Helpers de “pantalla” --------
void esperarEnter() {
    cout << "\n\nPresione ENTER para volver al menu...";
    cin.get();
}

void pantallaListarCursos() {
    Console::Clear();
    cout << "========== CURSOS DISPONIBLES ==========\n\n";
    int n = 1;
    cursos.mostrar([&](const Curso& c) {
        cout << n++ << ". " << c.titulo << "\n";
        cout << "   Categoria: " << c.categoria << " | Nivel: " << c.nivel << "\n";
        cout << "   Instructor: " << c.nombreInstructor << " | Duracion: " << c.duracionHoras << "h\n";
        cout << "   Inscritos: " << c.inscritos << "\n";
        cout << "   Temario:\n";
        for (size_t i = 0; i < c.temario.size(); ++i) {
            cout << "     - " << c.temario[i] << "\n";
        }
        cout << "\n";
        });
    esperarEnter();
}

void pantallaVerUsuarios() {
    Console::Clear();
    cout << "========== USUARIOS REGISTRADOS ==========\n\n";
    int n = 1;
    usuarios.mostrar([&](const Usuario& u) {
        cout << n++ << ". " << u.nombre << " " << u.apellido << "\n";
        cout << "   DNI: " << u.dni << " | Correo: " << u.correo << "\n";
        cout << "   Fecha registro: " << u.fechaRegistro << "\n\n";
        });
    cout << "Total usuarios: " << usuarios.tamanio() << "\n";
    esperarEnter();
}

void pantallaVerInscritosPorCurso() {
    Console::Clear();
    string tituloCurso;
    cout << "VER INSCRITOS POR CURSO\n";
    cout << "Titulo del curso: ";
    getline(cin, tituloCurso);

    Curso* curso = cursos.buscar([&](const Curso& c) { return c.titulo == tituloCurso; });
    if (!curso) {
        cout << "\nCurso no encontrado.\n";
        return esperarEnter();
    }

    cout << "\nInscritos en: " << tituloCurso << "\n\n";
    int n = 1; bool hay = false;
    inscripciones.mostrar([&](const Inscripcion& insc) {
        if (insc.tituloCurso == tituloCurso) {
            hay = true;
            Usuario* u = usuarios.buscar([&](const Usuario& x) { return x.correo == insc.correoUsuario; });
            if (u) cout << n++ << ". " << u->nombre << " " << u->apellido << "\n";
            else   cout << n++ << ". " << insc.correoUsuario << "\n";
            cout << "   Progreso: " << insc.progreso << "%\n";
            cout << "   Fecha: " << insc.fechaInscripcion << "\n\n";
        }
        });
    if (!hay) cout << "No hay inscritos aun.\n";
    esperarEnter();
}

void pantallaMisCursos() {
    Console::Clear();
    string correo;
    cout << "MIS CURSOS\n";
    cout << "Tu correo: ";
    getline(cin, correo);

    cout << "\nTus cursos inscritos:\n\n";
    int n = 1; bool hay = false;
    inscripciones.mostrar([&](const Inscripcion& insc) {
        if (insc.correoUsuario == correo) {
            hay = true;
            cout << n++ << ". " << insc.tituloCurso << "\n";
            cout << "   Progreso: " << insc.progreso << "% | Fecha: " << insc.fechaInscripcion << "\n\n";
        }
        });
    if (!hay) cout << "No tienes cursos inscritos.\n";
    esperarEnter();
}

void pantallaBuscarCategoria() {
    Console::Clear();
    string categoria;
    cout << "BUSCAR CURSO POR CATEGORIA\n";
    cout << "Categoria (Programacion/Diseno/etc): ";
    getline(cin, categoria);

    cout << "\nCursos de " << categoria << ":\n\n";
    int n = 1;
    int total = cursos.contar([&](const Curso& c) { return c.categoria == categoria; });
    cursos.mostrar([&](const Curso& c) {
        if (c.categoria == categoria) {
            cout << n++ << ". " << c.titulo << "\n";
            cout << "   Nivel: " << c.nivel << " | Inscritos: " << c.inscritos << "\n\n";
        }
        });
    cout << "Total encontrados: " << total << "\n";
    esperarEnter();
}

void pantallaOrdenarCursos() {
    Console::Clear();
    ordenarCursosBurbuja(cursos);
    registrarHistorial("ORDENAMIENTO", "Cursos ordenados por inscritos");

    cout << "CURSOS ORDENADOS POR INSCRITOS (DESC)\n\n";
    int pos = 1;
    cursos.mostrar([&](const Curso& c) {
        cout << pos++ << ". " << c.titulo << " (" << c.inscritos << " inscritos)\n";
        });
    esperarEnter();
}

void pantallaHistorial() {
    Console::Clear();
    cout << "HISTORIAL DE ACCIONES (PILA)\n\n";
    int n = 1;
    if (historial.estaVacia()) {
        cout << "No hay historial registrado.\n";
    }
    else {
        historial.mostrar([&](const Historial& h) {
            cout << n++ << ". [" << h.accion << "] " << h.detalle << "\n";
            cout << "   Fecha: " << h.fecha << "\n\n";
            });
    }
    esperarEnter();
}

int main() {
    Console::SetWindowSize(110, 35); // ventana; el buffer por defecto ya permite scroll

    // Inicializar cursos por defecto (en memoria)
    inicializarCursos();

    int opcion;
    do {
        Console::Clear();
        mostrarMenu();
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000, '\n'); opcion = -1; }
        cin.ignore(10000, '\n');  // limpiar salto

        switch (opcion) {
        case 1: { // REGISTRAR USUARIO (pantalla)
            Console::Clear();
            string nombre, apellido, dni, correo;
            cout << "REGISTRAR USUARIO\n\n";
            cout << "Nombre: ";   getline(cin, nombre);
            cout << "Apellido: "; getline(cin, apellido);
            cout << "DNI: ";      getline(cin, dni);
            cout << "Correo: ";   getline(cin, correo);

            bool existe = usuarios.existe([&](const Usuario& u) { return u.correo == correo; });
            cout << "\n";
            if (existe) {
                cout << "ERROR: El correo ya esta registrado!\n";
            }
            else {
                usuarios.agregar(Usuario(nombre, apellido, dni, correo, obtenerFechaActual()));
                registrarHistorial("REGISTRO", "Usuario: " + nombre + " " + apellido);
                cout << "Usuario registrado con exito!\n";
            }
            esperarEnter();
            break;
        }

        case 2: // LISTAR CURSOS (con temario) — otra pantalla
            pantallaListarCursos();
            break;

        case 3: { // INSCRIBIRSE EN CURSO
            Console::Clear();
            string correo, tituloCurso;
            cout << "INSCRIBIRSE EN CURSO\n\n";
            cout << "Tu correo: ";        getline(cin, correo);
            cout << "Titulo del curso: "; getline(cin, tituloCurso);

            bool usuarioExiste = usuarios.existe([&](const Usuario& u) { return u.correo == correo; });
            Curso* cursoEncontrado = cursos.buscar([&](const Curso& c) { return c.titulo == tituloCurso; });
            bool yaInscrito = inscripciones.existe([&](const Inscripcion& i) { return i.correoUsuario == correo && i.tituloCurso == tituloCurso; });

            cout << "\n";
            if (!usuarioExiste) {
                cout << "ERROR: Usuario no encontrado!\n";
            }
            else if (cursoEncontrado == nullptr) {
                cout << "ERROR: Curso no encontrado!\n";
            }
            else if (yaInscrito) {
                cout << "ERROR: Ya estas inscrito en este curso!\n";
            }
            else {
                inscripciones.agregar(Inscripcion(correo, tituloCurso, obtenerFechaActual()));
                cursoEncontrado->inscritos++;
                solicitudesPendientes.encolar("Inscripcion: " + correo + " -> " + tituloCurso);
                registrarHistorial("INSCRIPCION", correo + " en " + tituloCurso);
                cout << "Inscripcion realizada con exito!\n";
            }
            esperarEnter();
            break;
        }

        case 4: // VER USUARIOS REGISTRADOS
            pantallaVerUsuarios();
            break;

        case 5: // VER INSCRITOS POR CURSO
            pantallaVerInscritosPorCurso();
            break;

        case 6: // VER MIS CURSOS
            pantallaMisCursos();
            break;

        case 7: { // CALIFICAR CURSO
            Console::Clear();
            string correo, tituloCurso, comentario; int estrellas;
            cout << "CALIFICAR CURSO\n\n";
            cout << "Tu correo: ";           getline(cin, correo);
            cout << "Curso a calificar: ";   getline(cin, tituloCurso);
            cout << "Estrellas (1-5): ";     cin >> estrellas; cin.ignore(10000, '\n');
            cout << "Comentario: ";          getline(cin, comentario);

            bool estaInscrito = inscripciones.existe([&](const Inscripcion& i) { return i.correoUsuario == correo && i.tituloCurso == tituloCurso; });

            cout << "\n";
            if (!estaInscrito) {
                cout << "Debes estar inscrito para calificar!\n";
            }
            else if (estrellas < 1 || estrellas > 5) {
                cout << "Calificacion invalida (1-5)!\n";
            }
            else {
                calificaciones.agregar(Calificacion(correo, tituloCurso, estrellas, comentario));
                registrarHistorial("CALIFICACION", correo + " califico " + tituloCurso);
                cout << "Gracias por tu calificacion!\n";
            }
            esperarEnter();
            break;
        }

        case 8: // BUSCAR CURSO POR CATEGORIA
            pantallaBuscarCategoria();
            break;

        case 9: // ORDENAR CURSOS POR INSCRITOS
            pantallaOrdenarCursos();
            break;

        case 10: // VER HISTORIAL
            pantallaHistorial();
            break;

        case 0:
            Console::Clear();
            cout << "Gracias por usar OpenCursos!\n";
            break;

        default:
            Console::Clear();
            cout << "Opcion invalida!\n";
            esperarEnter();
            break;
        }

    } while (opcion != 0);

    return 0;
}