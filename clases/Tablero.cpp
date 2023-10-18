#include "Tablero.h"
#include "Dados.h"
#include "Jugador.h"
#include <sstream>
#include <iostream>

#include "nlohmann/json.hpp" // Include the JSON library
#include <fstream>
using json = nlohmann::json; // Define a shortcut for the JSON library


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

    // Datos pais origen
    string jugador_atacante = jugadores[turnoActual].nombre;
    int tropas_pais_origen;
    for (int i = 0;  i < paises.size(); i++) {
        if (paises[i].nombre == pais_origen) {
            tropas_pais_origen = paises[i].tropas;
            cout << "tropas" << tropas_pais_origen << endl;
        }
    }
    if (tropas_pais_origen < 2) {
        cout << "El pais de origen no tiene suficientes tropas" << endl;
        return;
    }

    // Datos pais destino
    string jugador_defensor;
    for (int i = 0;  i < paises.size(); i++) {
        if (paises[i].nombre == pais_destino) {
            jugador_defensor = paises[i].dueno;
            break;
        }
    }

    int tropas_pais_destino;
    for (int i = 0; i < paises.size(); i++) {
        if (paises[i].nombre == pais_destino) {
            tropas_pais_destino = paises[i].tropas;
        }
    }


    // Imprime la información del ataque
    cout <<"--->"<< jugador_atacante << " ataca a "<<jugador_defensor << " desde " << pais_origen << " hacia " << pais_destino << endl;
    cout << "-- Tropas en " << pais_origen << ": " << tropas_pais_origen << endl;
    cout << "-- Tropas en " << pais_destino << ": " <<tropas_pais_destino << endl;
    
    // Lanza los dados
    bool gana_atacante = lanzar_dados();

    // realiza cambios en tropas
    if(gana_atacante){
        // atacante gana
        // se resta una tropa al pais de destino
        for (int i = 0; i < paises.size(); i++) {
            if (paises[i].nombre == pais_destino) {
                paises[i].tropas--;
                break;
            }
        }
        // se resta una tropa al jugador del pais de destino
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores[i].nombre == jugador_defensor) {
                jugadores[i].tropas--;
                break;
            }
        }
        // en caso de que el pais quede sin tropas se le asigna al atacante pasando todas las tropas excepto una  del pais atacante al pais de destino
        if (tropas_pais_destino == 1) {

            // imprime que el pais ha sido conquistado
            cout << "-- El pais ha sido conquistado!!" << endl;
            // se pasa todas las tropas excepto una del pais de origen al pais de destino
            for (int i = 0; i < paises.size(); i++) {
                if (paises[i].nombre == pais_origen) {
                    paises[i].tropas--;
                    break;
                }
            }
            for (int i = 0; i < paises.size(); i++) {
                if (paises[i].nombre == pais_destino) {
                    paises[i].tropas = tropas_pais_origen;
                    break;
                }
            }
            // se pasa el pais de destino al jugador atacante
            for (int i = 0; i < jugadores.size(); i++) {
                if (jugadores[i].nombre == jugador_defensor) {
                    for (int j = 0; j < jugadores[i].paisesj.size(); j++) {
                        if (jugadores[i].paisesj[j].nombre == pais_destino) {
                            jugadores[i].paisesj.erase(jugadores[i].paisesj.begin() + j);
                            break;
                        }
                    }
                    break;
                }
            }
            for (int i = 0; i < jugadores.size(); i++) {
                if (jugadores[i].nombre == jugador_atacante) {
                    jugadores[i].paisesj.push_back(paises[i]);
                    break;
                }
            }
        }
    }
    else{
        // gana defensor
        // se resta una tropa al pais de origen
        for (int i = 0; i < paises.size(); i++) {
            if (paises[i].nombre == pais_origen) {
                paises[i].tropas--;
                break;
            }
        }
        // se resta una tropa al jugador del pais de origen
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores[i].nombre == jugador_atacante) {
                jugadores[i].tropas--;
                break;
            }
        }

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
            cout << "-- Ataque finalizado" << endl<< endl;
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

bool Tablero::lanzar_dados() {
    // Devuelve true si gana el atacante o false si gana el defensor

    //     El resultado del ataque se define a través de los dados: el jugador
    // atacante lanza 3 dados de color rojo, mientras que el jugador que defiende lanza 2 dados blancos. Los dados
    // de uno y otro se emparejan y se comparan para determinar cuántas unidades de ejército pierde o gana cada
    // uno: si el del atacante es mayor que el del defensor, el defensor pierde una unidad de ejército del territorio
    // atacado; si el del defensor es mayor al del atacante, el atacante pierde una unidad de ejército del territorio
    // desde el que se ataca; si hay empate, el defensor es quien gana, por lo que el atacante pierde una unidad
    // de ejército de su territorio

    // jugador atacante tiene 3 datos
    Dados atacante("rojo", {0, 0, 0});

    // jugador defensor tiene 2 datos
    Dados defensor("blanco", {0, 0});


    // Lanzar dados
    // presione enter para tirar dados
    cout << "-- Atacante: Presione enter para tirar dados..." ;
    cin.ignore();
    atacante.tirarDados();
    atacante.imprimirDados();

    cout << "-- Defensor: Presione enter para tirar dados..." ;
    cin.ignore();
    defensor.tirarDados();
    defensor.imprimirDados();


    // Ordenar dados
    atacante.ordenarDados();
    defensor.ordenarDados();

    // // Imprimir dados
    // cout << "Dados del atacante: ";
    // atacante.imprimirDados();
    // cout << "Dados del defensor: ";
    // defensor.imprimirDados();


    // Obtener mayor
    int mayor_atacante = atacante.obtenerMayor();
    int mayor_defensor = defensor.obtenerMayor();

    // Obtener segundo mayor
    int segundo_mayor_atacante = atacante.obtenerSegundoMayor();
    int segundo_mayor_defensor = defensor.obtenerSegundoMayor();

    // Comparar dados
    if (mayor_atacante > mayor_defensor) {
        // El atacante gana
        cout << "El atacante gana" << endl;
        return true;
    } else if (mayor_atacante < mayor_defensor) {
        // El defensor gana
        cout << "El defensor gana" << endl;
        return false;
    } else {
        // Empate
        if (segundo_mayor_atacante > segundo_mayor_defensor) {
            // El atacante gana
            cout << "El atacante gana" << endl;
            return true;
        } else {
            // El defensor gana
            cout << "El defensor gana" << endl;
            return false;
        }
    }
}


void Tablero::guardar_json(std::string filename) {
    json tablero_json;

    // Convert the Tablero data to JSON
    // Convert the 'paises' vector to a JSON array
    json paises_array;
    for (const Pais& pais : paises) {
        json pais_json;
        pais_json["nombre"] = pais.nombre;
        pais_json["continente"] = pais.continente;
        pais_json["dueno"] = pais.dueno;
        pais_json["npaises"] = pais.npaises;
        pais_json["adyacentes"] = pais.adyacentes;
        pais_json["tropas"] = pais.tropas;
        // Convert other relevant data from the Pais class

        // Add the pais_json to the paises_array
        paises_array.push_back(pais_json);
    }

    tablero_json["paises"] = paises_array;

    tablero_json["turnoActual"] = turnoActual;

    // Convert the 'jugadores' vector to a JSON array
    json jugadores_array;
    for (const Jugador& jugador : jugadores) {
        json jugador_json;
        jugador_json["nombre"] = jugador.nombre;
        jugador_json["color"] = jugador.color;
        jugador_json["tropas"] = jugador.tropas;
        // Convert other relevant data from the Jugador class

        // If Jugador class contains additional data, add it here.
        jugador_json["cartas"] = jugador.cartas;

        // Convert and add data from the 'paisesj' vector
        json paisesj_array;
        for (const Pais& pais : jugador.paisesj) {
            json pais_json;
            pais_json["nombre"] = pais.nombre;
            // Include any other relevant data from the Pais class
            paisesj_array.push_back(pais_json);
        }
        jugador_json["paisesj"] = paisesj_array;

        // Add the jugador_json to the jugadores_array
        jugadores_array.push_back(jugador_json);
    }

    tablero_json["jugadores"] = jugadores_array;

    // Open a file for writing
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << tablero_json.dump(4); // Pretty print with an indentation of 4
        outputFile.close();
        std::cout << "Tablero data saved to JSON file." << std::endl;
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}


void Tablero::cargar_json(std::string filename) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        json tablero_json;
        inputFile >> tablero_json;

        // Load the 'paises' data from the JSON
        if (tablero_json.find("paises") != tablero_json.end()) {
            paises.clear(); // Clear existing data
            for (const auto& pais_json : tablero_json["paises"]) {
                Pais pais;
                pais.nombre = pais_json["nombre"];
                pais.continente = pais_json["continente"];
                pais.dueno = pais_json["dueno"];
                pais.npaises = pais_json["npaises"];
                pais.adyacentes = pais_json["adyacentes"].get<std::vector<std::string>>();
                pais.tropas = pais_json["tropas"];
                // Load other relevant data from the Pais class

                // Add the loaded pais to the 'paises' vector
                paises.push_back(pais);
            }
        }

        // Load the 'turnoActual' data from the JSON
        if (tablero_json.find("turnoActual") != tablero_json.end()) {
            turnoActual = tablero_json["turnoActual"];
        }

        // Load the 'jugadores' data from the JSON
        if (tablero_json.find("jugadores") != tablero_json.end()) {
            jugadores.clear(); // Clear existing data
            for (const auto& jugador_json : tablero_json["jugadores"]) {
                Jugador jugador;
                jugador.nombre = jugador_json["nombre"];
                jugador.color = jugador_json["color"];
                jugador.tropas = jugador_json["tropas"];
                // Load other relevant data from the Jugador class

                // Load the 'cartas' data
                if (jugador_json.find("cartas") != jugador_json.end()) {
                    jugador.cartas = jugador_json["cartas"].get<std::vector<std::string>>();
                }

                // Load the 'paisesj' data
                if (jugador_json.find("paisesj") != jugador_json.end()) {
                    for (const auto& pais_json : jugador_json["paisesj"]) {
                        Pais pais;
                        pais.nombre = pais_json["nombre"];
                        // Load other relevant data from the Pais class

                        // Add the loaded pais to the player's 'paisesj' vector
                        jugador.paisesj.push_back(pais);
                    }
                }

                // Add the loaded jugador to the 'jugadores' vector
                jugadores.push_back(jugador);
            }
        }

        std::cout << "Tablero data loaded from JSON file." << std::endl;
        inputFile.close();
    } else {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }
}
