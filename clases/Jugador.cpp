#include "Jugador.h"
#include <iostream> // Include this for cin and cout

void Jugador::mover_tropas(Pais& pais1, Pais& pais2) {
    // Check that the player is the owner of the countries
    if (pais1.dueno != nombre || pais2.dueno != nombre) {
        std::cout << "No es dueño de los paises" << std::endl;
        return;
    }

    // Ask how many troops the player wants to move
    int tropas;
    std::cout << "¿Cuantas tropas desea mover?" << std::endl;
    std::cin >> tropas;

    // The player must leave at least 1 unit in each of their countries
    if (pais1.tropas - tropas < 1) {
        std::cout << "Debe dejar mínimo 1 tropa en el país " << pais1.nombre << std::endl;
        return;
    }

    // Check if the countries are adjacent
    if (std::find(pais1.adyacentes.begin(), pais1.adyacentes.end(), pais2.nombre) == pais1.adyacentes.end()) {
        std::cout << "Los países no son adyacentes" << std::endl;
        return;
    }

    pais1.tropas -= tropas;
    pais2.tropas += tropas;
}
