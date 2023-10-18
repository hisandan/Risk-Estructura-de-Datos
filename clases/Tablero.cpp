#include "Tablero.h"
#include "Jugador.h"
#include <sstream>
#include <iostream>
using namespace std;


void Tablero::distribuir_tropas() {
    int nuevas_tropas = 0;
    nuevas_tropas = jugadores[turnoActual].paisesj.size() / 2;
    jugadores[turnoActual].tropas += nuevas_tropas;
    std::cout << "Se han agregado " << nuevas_tropas << " tropas a " << jugadores[turnoActual].nombre << std::endl;
    // ubicar las nuevas tropas
    for(int t = 0; t < nuevas_tropas; t++) {
        std::cout << jugadores[turnoActual].nombre<<" - Seleccione el pais donde quiere poner una unidad de tropa:" << t+1 << "/" << nuevas_tropas << std::endl << "$ ";

        std::string x;
        std::getline(std::cin, x);

        int i=0;
        bool encontrado = false;
        std::cout << x << std::endl;
        for (int z = 0; !encontrado && z < jugadores[turnoActual].paisesj.size(); z++) {
            // std::cout << tablero.paises[z].nombre << endl;
            if (jugadores[turnoActual].paisesj[z].nombre == x) {
                // cout << "...................." << endl;
                i = z;
                encontrado = true; // Se encontró el país
                jugadores[turnoActual].paisesj[z].tropas++;
                paises[z].tropas++;
                cout << "... Tropa ubicada en "<< jugadores[turnoActual].paisesj[z].nombre << endl;
            }
        }

        if (!encontrado) {
                std::cout << "... No se encontro el pais, verifique si tiene errores de ortografia o que el país le pertenezca" << std::endl;
                t--;
                continue; // Pasa a la siguiente iteración del bucle for
        }
    }
    
}

void Tablero::siguenteturno() {
    turnoActual++;
    if (turnoActual == jugadores.size()) {
        turnoActual = 0;
    }
}

void Tablero::consultaPais(string pais_name) {
    bool encontrado = false;
    for (int i = 0; !encontrado && i < paises.size(); i++) {
        if (paises[i].nombre == pais_name) {
            encontrado = true;
            cout << "-- Nombre: " << paises[i].nombre << endl;
            cout << "-- Continente: " << paises[i].continente << endl;
            cout << "-- Tropas: " << paises[i].tropas << endl;
            cout << "-- Jugador: " << paises[i].dueno << endl;
        }
    }
    if (!encontrado) {
        cout << "No se encontro el pais" << endl;
    }
}

void Tablero::atacar_pais (string pais_origen, string pais_destino) {

    bool pais_origen_encontrado = false;
    bool pais_origen_correcto = false;

    bool pais_destino_encontrado = false;
    bool pais_destino_correcto = true;

    // verificar que el pais de origen pertenece al jugador del turno actual
    for (int i = 0; !pais_origen_encontrado && i < paises.size(); i++) {
        if (paises[i].nombre == pais_origen) {
            pais_origen_encontrado = true;
            if (paises[i].dueno == jugadores[turnoActual].nombre) {
                pais_origen_correcto = true;
            }

        }
    }
    if (!pais_origen_encontrado) {
        cout << "No se encontro el pais de origen" << endl;
        return;
    }
    if (!pais_origen_correcto) {
        cout << "El pais de origen no le pertenece" << endl;
        return;
    }
    // verificar que el pais de destino no pertenece al jugador del turno actual
    for (int i = 0; !pais_destino_encontrado && i < paises.size(); i++) {
        if (paises[i].nombre == pais_destino) {
            pais_destino_encontrado = true;
            if (paises[i].dueno == jugadores[turnoActual].nombre) {
                pais_destino_correcto = false;
            }

        }
    }
    if (!pais_destino_encontrado) {
        cout << "No se encontro el pais de destino" << endl;
        return;

    }
    if (!pais_destino_correcto) {
        cout << "El pais de destino ya le  pertenece" << endl;
        return;
    }

    // verificar que el pais de origen y destino sean adyacentes
    bool adyacente = false;
    for (int i = 0; !adyacente && i < paises.size(); i++) {
        if (paises[i].nombre == pais_origen) {
            for (int j = 0; !adyacente && j < paises[i].adyacentes.size(); j++) {
                if (paises[i].adyacentes[j] == pais_destino) {
                    adyacente = true;
                }
            }
        }
    }
    
    if (!adyacente) {
        cout << "El pais de origen y destino no son adyacentes" << endl;
        return;
    }



}

void Tablero::empezar_turno() {
    distribuir_tropas();
    cout << "\n\nLista de comandos disponibles para el Turno:\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| Comando                  | Descripción                                      |\n"
        //  << "+--------------------------+--------------------------------------------------+\n"
        //  << "| costo_conquista <territorio> | Calcula el costo y la secuencia de           |\n"
        //  << "|                          | territorios a ser conquistados para lograr       |\n"
        //  << "|                          | controlar el territorio dado por el usuario.     |\n"
        //  << "|                          | Por ejemplo, para el territorio 'colombia':      |\n"
        //  << "|                          | costo_conquista colombia.                        |\n"
        //  << "+--------------------------+--------------------------------------------------+\n"
        //  << "| conquista_mas_barata     | Calcula el territorio que implique un menor      |\n"
        //  << "|                          | número de unidades de ejército perdidas.         |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| atacar_pais              | Ataca al pais destino                            |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| consulta_pais <nomb_pais>| Información de un país (Tropas, Jugadro, etc)    |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| terminar_turno           | Termina el turno Actual                          |\n"
         << "+--------------------------+--------------------------------------------------+\n";

    std::string command;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "atacar_pais") {
            string pais_origen;
            string pais_destino;
            std::cout << "Atacando -> Pais de Origen: "<< endl << "$ ";
            std::getline(std::cin, pais_origen);
            std::cout << "Atacando -> Pais de Destino: "<< endl << "$ ";
            std::getline(std::cin, pais_destino);
            atacar_pais(pais_origen, pais_destino);
            // atacar_pais();
            
        } else if (cmd == "consulta_pais") {
            // string pais_name;
            // iss >> pais_name;
            // cout << iss.str() << endl;
            consultaPais(iss.str().substr(14));
            // ayuda();
            continue;            
        } else if (cmd == "terminar_turno") {
            
            siguenteturno(); 
            break;
        } 
        else {
            std::cout << "Comando no válido." << std::endl;
        }
    }
    
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
