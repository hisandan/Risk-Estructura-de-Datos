#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include <iostream> // Include this for cin and cout
#include <algorithm>
#include "Pais.h"

class Jugador {
public:
    std::string nombre;
    std::string color;
    int tropas;
    std::vector<std::string> cartas;
    std::vector<Pais> paisesj;

    void mover_tropas(Pais& pais1, Pais& pais2); // Declare the function

    // You can add other member functions or variables here if needed
};

#endif
