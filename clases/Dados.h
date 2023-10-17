#ifndef DADOS_H
#define DADOS_H

#include <string>
#include <vector>

class Dados {
public:
    std::string tipo; // atacante o defensor  --> en la vida real son rojos o blancos
    std::vector<int> dados; // cada dado es un int

    Dados(std::string tipo, std::vector<int> dados);

    void tirarDados();

    void ordenarDados();

    void imprimirDados();

    int obtenerMayor();

    int obtenerSegundoMayor();
};

#endif
