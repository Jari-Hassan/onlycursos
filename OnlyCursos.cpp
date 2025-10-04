#include "pch.h"
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
#include "Fondos.h" // Incluimos nuestro nuevo archivo de fondos

// Es importante incluir estos namespaces al principio
using namespace System;
using namespace std;

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
    // Dibujar el fondo gráfico usando nuestras matrices
    Fondos::DibujarFondoMenuPrincipal();
    Fondos::DibujarLogoMenuPrincipal(18, 3);

    // Dibuja un borde para el menú
    Fondos::DibujarBordeMenu(18, 14, 50, 15, ConsoleColor::Green);

    int x = 18, y = 15;
    Console::ForegroundColor = ConsoleColor::Cyan;
    Console::SetCursorPosition(x + 2, y);
    cout << "   ___                  ____                       ";
    Console::SetCursorPosition(x + 2, y + 1);
    cout << "  / _ \\ _ __   ___ _ __/ ___|   _ _ __ ___  ___  ___";
    Console::SetCursorPosition(x + 2, y + 2);
    cout << " | | | | '_ \\ / _ \\ '_ \\___ \\ | | | '__/ __|/ _ \\/ __|";
    Console::SetCursorPosition(x + 2, y + 3);
    cout << " | |_| | |_) |  __/ | | |__) || |_| | |  \\__ \\ (_) \\__ \\";
    Console::SetCursorPosition(x + 2, y + 4);
    cout << "  \\___/| .__/ \\___|_| |_____/ \\__,_|_|  |___/\\___/|___/";
    Console::SetCursorPosition(x + 2, y + 5);
    cout << "       |_| Plataforma de Cursos Online Gratis";

    Console::ForegroundColor = ConsoleColor::White;
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

// -------- Helpers de "pantalla" --------
void esperarEnter() {
    cout << "\n\nPresione ENTER para volver al menu...";
    cin.get();
}

void pantallaListarCursos() {
    // Usar fondo secundario
    Fondos::DibujarFondoSecundario();

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "========== CURSOS DISPONIBLES ==========";
    Console::ForegroundColor = ConsoleColor::White;

    int y = 4;
    int n = 1;
    cursos.mostrar([&](const Curso& c) {
        Console::SetCursorPosition(5, y++);
        cout << n++ << ". " << c.titulo;
        Console::SetCursorPosition(5, y++);
        cout << "   Categoria: " << c.categoria << " | Nivel: " << c.nivel;
        Console::SetCursorPosition(5, y++);
        cout << "   Instructor: " << c.nombreInstructor << " | Duracion: " << c.duracionHoras << "h";
        Console::SetCursorPosition(5, y++);
        cout << "   Inscritos: " << c.inscritos;
        Console::SetCursorPosition(5, y++);
        cout << "   Temario:";
        for (size_t i = 0; i < c.temario.size(); ++i) {
            Console::SetCursorPosition(7, y++);
            cout << "- " << c.temario[i];
        }
        y++; // Espacio entre cursos
        });

    Console::SetCursorPosition(5, y);
    esperarEnter();
}

void pantallaVerUsuarios() {
    Fondos::DibujarFondoSecundario();

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "========== USUARIOS REGISTRADOS ==========";
    Console::ForegroundColor = ConsoleColor::White;

    int y = 4;
    int n = 1;
    usuarios.mostrar([&](const Usuario& u) {
        Console::SetCursorPosition(5, y++);
        cout << n++ << ". " << u.nombre << " " << u.apellido;
        Console::SetCursorPosition(5, y++);
        cout << "   DNI: " << u.dni << " | Correo: " << u.correo;
        Console::SetCursorPosition(5, y++);
        cout << "   Fecha registro: " << u.fechaRegistro;
        y++; // Espacio entre usuarios
        });

    Console::SetCursorPosition(5, y);
    cout << "Total usuarios: " << usuarios.tamanio();
    esperarEnter();
}

void pantallaVerInscritosPorCurso() {
    Fondos::DibujarFondoSecundario();

    string tituloCurso;
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "VER INSCRITOS POR CURSO";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Titulo del curso: ";
    getline(cin, tituloCurso);

    Curso* curso = cursos.buscar([&](const Curso& c) { return c.titulo == tituloCurso; });
    if (!curso) {
        Console::SetCursorPosition(5, 6);
        cout << "Curso no encontrado.";
        esperarEnter();
        return;
    }

    Console::SetCursorPosition(5, 6);
    cout << "Inscritos en: " << tituloCurso;

    int y = 8;
    int n = 1;
    bool hay = false;
    inscripciones.mostrar([&](const Inscripcion& insc) {
        if (insc.tituloCurso == tituloCurso) {
            hay = true;
            Usuario* u = usuarios.buscar([&](const Usuario& x) { return x.correo == insc.correoUsuario; });

            Console::SetCursorPosition(5, y++);
            if (u) cout << n++ << ". " << u->nombre << " " << u->apellido;
            else   cout << n++ << ". " << insc.correoUsuario;

            Console::SetCursorPosition(5, y++);
            cout << "   Progreso: " << insc.progreso << "%";

            Console::SetCursorPosition(5, y++);
            cout << "   Fecha: " << insc.fechaInscripcion;
            y++; // Espacio entre inscripciones
        }
        });

    if (!hay) {
        Console::SetCursorPosition(5, y);
        cout << "No hay inscritos aun.";
    }

    esperarEnter();
}

void pantallaMisCursos() {
    Fondos::DibujarFondoSecundario();

    string correo;
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "MIS CURSOS";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Tu correo: ";
    getline(cin, correo);

    Console::SetCursorPosition(5, 6);
    cout << "Tus cursos inscritos:";

    int y = 8;
    int n = 1;
    bool hay = false;
    inscripciones.mostrar([&](const Inscripcion& insc) {
        if (insc.correoUsuario == correo) {
            hay = true;
            Console::SetCursorPosition(5, y++);
            cout << n++ << ". " << insc.tituloCurso;

            Console::SetCursorPosition(5, y++);
            cout << "   Progreso: " << insc.progreso << "% | Fecha: " << insc.fechaInscripcion;
            y++; // Espacio entre cursos
        }
        });

    if (!hay) {
        Console::SetCursorPosition(5, y);
        cout << "No tienes cursos inscritos.";
    }

    esperarEnter();
}

void pantallaBuscarCategoria() {
    Fondos::DibujarFondoSecundario();

    string categoria;
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "BUSCAR CURSO POR CATEGORIA";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Categoria (Programacion/Diseno/etc): ";
    getline(cin, categoria);

    Console::SetCursorPosition(5, 6);
    cout << "Cursos de " << categoria << ":";

    int y = 8;
    int n = 1;
    int total = cursos.contar([&](const Curso& c) { return c.categoria == categoria; });

    cursos.mostrar([&](const Curso& c) {
        if (c.categoria == categoria) {
            Console::SetCursorPosition(5, y++);
            cout << n++ << ". " << c.titulo;

            Console::SetCursorPosition(5, y++);
            cout << "   Nivel: " << c.nivel << " | Inscritos: " << c.inscritos;
            y++; // Espacio entre cursos
        }
        });

    Console::SetCursorPosition(5, y);
    cout << "Total encontrados: " << total;

    esperarEnter();
}

void pantallaOrdenarCursos() {
    Fondos::DibujarFondoSecundario();

    ordenarCursosBurbuja(cursos);
    registrarHistorial("ORDENAMIENTO", "Cursos ordenados por inscritos");

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(30, 2);
    cout << "CURSOS ORDENADOS POR INSCRITOS (DESC)";
    Console::ForegroundColor = ConsoleColor::White;

    int y = 4;
    int pos = 1;
    cursos.mostrar([&](const Curso& c) {
        Console::SetCursorPosition(5, y++);
        cout << pos++ << ". " << c.titulo << " (" << c.inscritos << " inscritos)";
        });

    esperarEnter();
}

void pantallaHistorial() {
    Fondos::DibujarFondoSecundario();

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "HISTORIAL DE ACCIONES (PILA)";
    Console::ForegroundColor = ConsoleColor::White;

    int y = 4;
    int n = 1;
    if (historial.estaVacia()) {
        Console::SetCursorPosition(5, y);
        cout << "No hay historial registrado.";
    }
    else {
        historial.mostrar([&](const Historial& h) {
            Console::SetCursorPosition(5, y++);
            cout << n++ << ". [" << h.accion << "] " << h.detalle;

            Console::SetCursorPosition(5, y++);
            cout << "   Fecha: " << h.fecha;
            y++; // Espacio entre registros
            });
    }

    esperarEnter();
}

void pantallaRegistrarUsuario() {
    Fondos::DibujarFondoSecundario();

    string nombre, apellido, dni, correo;
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "REGISTRAR USUARIO";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Nombre: ";
    getline(cin, nombre);

    Console::SetCursorPosition(5, 5);
    cout << "Apellido: ";
    getline(cin, apellido);

    Console::SetCursorPosition(5, 6);
    cout << "DNI: ";
    getline(cin, dni);

    Console::SetCursorPosition(5, 7);
    cout << "Correo: ";
    getline(cin, correo);

    bool existe = usuarios.existe([&](const Usuario& u) { return u.correo == correo; });

    Console::SetCursorPosition(5, 9);
    if (existe) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "ERROR: El correo ya esta registrado!";
    }
    else {
        usuarios.agregar(Usuario(nombre, apellido, dni, correo, obtenerFechaActual()));
        registrarHistorial("REGISTRO", "Usuario: " + nombre + " " + apellido);
        Console::ForegroundColor = ConsoleColor::Green;
        cout << "Usuario registrado con exito!";
    }

    Console::ForegroundColor = ConsoleColor::White;
    esperarEnter();
}

void pantallaInscribirseEnCurso() {
    Fondos::DibujarFondoSecundario();

    string correo, tituloCurso;
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "INSCRIBIRSE EN CURSO";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Tu correo: ";
    getline(cin, correo);

    Console::SetCursorPosition(5, 5);
    cout << "Titulo del curso: ";
    getline(cin, tituloCurso);

    bool usuarioExiste = usuarios.existe([&](const Usuario& u) { return u.correo == correo; });
    Curso* cursoEncontrado = cursos.buscar([&](const Curso& c) { return c.titulo == tituloCurso; });
    bool yaInscrito = inscripciones.existe([&](const Inscripcion& i) {
        return i.correoUsuario == correo && i.tituloCurso == tituloCurso;
        });

    Console::SetCursorPosition(5, 7);
    if (!usuarioExiste) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "ERROR: Usuario no encontrado!";
    }
    else if (cursoEncontrado == nullptr) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "ERROR: Curso no encontrado!";
    }
    else if (yaInscrito) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "ERROR: Ya estas inscrito en este curso!";
    }
    else {
        inscripciones.agregar(Inscripcion(correo, tituloCurso, obtenerFechaActual()));
        cursoEncontrado->inscritos++;
        solicitudesPendientes.encolar("Inscripcion: " + correo + " -> " + tituloCurso);
        registrarHistorial("INSCRIPCION", correo + " en " + tituloCurso);
        Console::ForegroundColor = ConsoleColor::Green;
        cout << "Inscripcion realizada con exito!";
    }

    Console::ForegroundColor = ConsoleColor::White;
    esperarEnter();
}

void pantallaCalificarCurso() {
    Fondos::DibujarFondoSecundario();

    string correo, tituloCurso, comentario;
    int estrellas;

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::SetCursorPosition(35, 2);
    cout << "CALIFICAR CURSO";
    Console::ForegroundColor = ConsoleColor::White;

    Console::SetCursorPosition(5, 4);
    cout << "Tu correo: ";
    getline(cin, correo);

    Console::SetCursorPosition(5, 5);
    cout << "Curso a calificar: ";
    getline(cin, tituloCurso);

    Console::SetCursorPosition(5, 6);
    cout << "Estrellas (1-5): ";
    cin >> estrellas;
    cin.ignore(10000, '\n');

    Console::SetCursorPosition(5, 7);
    cout << "Comentario: ";
    getline(cin, comentario);

    bool estaInscrito = inscripciones.existe([&](const Inscripcion& i) {
        return i.correoUsuario == correo && i.tituloCurso == tituloCurso;
        });

    Console::SetCursorPosition(5, 9);
    if (!estaInscrito) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "Debes estar inscrito para calificar!";
    }
    else if (estrellas < 1 || estrellas > 5) {
        Console::ForegroundColor = ConsoleColor::Red;
        cout << "Calificacion invalida (1-5)!";
    }
    else {
        calificaciones.agregar(Calificacion(correo, tituloCurso, estrellas, comentario));
        registrarHistorial("CALIFICACION", correo + " califico " + tituloCurso);
        Console::ForegroundColor = ConsoleColor::Green;
        cout << "Gracias por tu calificacion!";
    }

    Console::ForegroundColor = ConsoleColor::White;
    esperarEnter();
}

int main() {
    Console::SetWindowSize(110, 35); // ventana; el buffer por defecto ya permite scroll

    // Inicializar fondos
    Fondos::InicializarFondos();

    // Inicializar cursos por defecto (en memoria)
    inicializarCursos();

    int opcion;
    do {
        mostrarMenu();
        if (!(cin >> opcion)) { cin.clear(); cin.ignore(10000, '\n'); opcion = -1; }
        cin.ignore(10000, '\n');  // limpiar salto

        switch (opcion) {
        case 1: // REGISTRAR USUARIO
            pantallaRegistrarUsuario();
            break;

        case 2: // LISTAR CURSOS (con temario)
            pantallaListarCursos();
            break;

        case 3: // INSCRIBIRSE EN CURSO
            pantallaInscribirseEnCurso();
            break;

        case 4: // VER USUARIOS REGISTRADOS
            pantallaVerUsuarios();
            break;

        case 5: // VER INSCRITOS POR CURSO
            pantallaVerInscritosPorCurso();
            break;

        case 6: // VER MIS CURSOS
            pantallaMisCursos();
            break;

        case 7: // CALIFICAR CURSO
            pantallaCalificarCurso();
            break;

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
            Fondos::DibujarFondoSecundario();
            Console::ForegroundColor = ConsoleColor::Green;
            Console::SetCursorPosition(35, 15);
            cout << "Gracias por usar OpenCursos!";
            Console::SetCursorPosition(0, 30);
            break;

        default:
            Fondos::DibujarFondoSecundario();
            Console::ForegroundColor = ConsoleColor::Red;
            Console::SetCursorPosition(35, 15);
            cout << "Opcion invalida!";
            Console::ForegroundColor = ConsoleColor::White;
            esperarEnter();
            break;
        }

    } while (opcion != 0);

    return 0;
}