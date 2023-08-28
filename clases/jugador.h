#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>

struct Jugador {
    
    std::string nombre;
    std::string color;
    int tropas;
    std::vector<std::string> cartas;
};



#endif