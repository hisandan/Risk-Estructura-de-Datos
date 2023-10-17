#ifndef PAIS_H
#define PAIS_H

#include <string>
#include <vector>

class Pais {
public:
    std::string nombre;
    std::string continente;
    std::string dueno;
    std::string npaises;
    std::vector<std::string> adyacentes; // nombre de paises adyacentes
    int tropas;
    
};

#endif