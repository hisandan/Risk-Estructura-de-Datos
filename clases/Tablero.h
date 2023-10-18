#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <string>
#include <vector>
#include "Dados.h"
#include "Pais.h"

class Jugador; // Forward declaration

// class Pais {
// public:
//     std::string nombre;
//     int tropas;
//     std::string dueno;
// };

class Tablero {
public:
    std::vector<Jugador> jugadores;
    std::vector<Pais> paises;
    int turnoActual = 0;

    Tablero() {}
    Tablero(std::vector<Jugador> jugadores, std::vector<Pais> paises) : jugadores(jugadores), paises(paises) {}
    void empezar_turno();
    void consultaPais(std::string pais_name);
    void atacar_pais(std::string pais_origen, std::string pais_destino);
    void distribuir_tropas();
    void siguenteturno();
    Jugador obtenerJugadorTurno();
    bool lanzar_dados();

    void guardar_json(std::string filename);
    void cargar_json(std::string filename);

};

#endif
