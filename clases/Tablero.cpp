#include "Tablero.h"
#include "Jugador.h"


void Tablero::distribuir_tropas() {
    int tropas = 0;
    for (int i = 0; i < jugadores.size(); i++) {
        tropas = jugadores[i].paisesj.size() / 2;
        jugadores[i].tropas += tropas;
    }
}

void Tablero::siguenteturno() {
    turnoActual++;
    if (turnoActual == jugadores.size()) {
        turnoActual = 0;
    }
}
void Tablero::empezar_turno() {
    distribuir_tropas();
    siguenteturno();
}

Jugador Tablero::obtenerJugadorTurno() {
    return jugadores[turnoActual];
}

std::pair<int, int> Tablero::comparar_dados(Dados atacante, Dados defensor) {
    std::pair<int, int> resultado;
    int tropas_atacante = 0;
    int tropas_defensor = 0;
    for (int i = 0; i < atacante.dados.size(); i++) {
        if (atacante.dados[i] > defensor.dados[i]) {
            tropas_defensor++;
        } else {
            tropas_atacante++;
        }
    }
    resultado.first = tropas_atacante;
    resultado.second = tropas_defensor;
    return resultado;
}

void Tablero::Atacar(Pais atacante, Pais defensor) {
    // Implement the attack logic here
    // You will need to add the necessary code to handle attacks between countries
    // and ownership changes as mentioned in your original code.
    // Make sure to include the required headers and logic for your game.
    // This code is a placeholder, and you should customize it according to your game's rules.
}
