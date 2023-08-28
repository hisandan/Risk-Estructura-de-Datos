#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Tablero {
public:
    Tablero(std::vector<Jugador> jugadores, std::vector<Pais> paises) : jugadores(jugadores), paises(paises) {}
    std::vector<Jugador> jugadores;
    std::vector<Pais> paises;
};


#endif