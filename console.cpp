#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

void ayuda() {
    cout << "\n\nLista de comandos disponibles:\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| Comando                  | Descripción                                      |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| inicializar              | Realiza las operaciones necesarias para          |\n"
         << "|                          | inicializar el juego.                            |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| turno <id_jugador>       | Realiza las operaciones descritas dentro del     |\n"
         << "|                          | turno de un jugador. Por ejemplo, si se desea    |\n"
         << "|                          | acceder al turno del jugador 5, se debe digitar  |\n"
         << "|                          | el comando de esta manera: turno 5.              |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| guardar <nombre_archivo> | Guarda el estado actual del juego en un archivo  |\n"
         << "|                          | de texto. Por ejemplo, si se desea guardar la    |\n"
         << "|                          | partida bajo el nombre de 'juego', se debe       |\n"
         << "|                          | digitar el comando de esta manera:               |\n"
         << "|                          | guardar juego.                                   |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| guardar_comprimido       | Guarda el estado actual del juego en un archivo  |\n"
         << "| <nombre_archivo>         | binario comprimido. Por ejemplo, si se desea     |\n"
         << "|                          | guardar la partida bajo el nombre de 'juego',    |\n"
         << "|                          | se debe digitar el comando de esta manera:       |\n"
         << "|                          | guardar_comprimido juego.                        |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| inicializar <nombre_archivo> | Inicializa el juego con los datos contenidos |\n"
         << "|                          | en el archivo identificado por <nombre_archivo>. |\n"
         << "|                          | Por ejemplo, si se desea leer el archivo         |\n"
         << "|                          | denominado 'juego' para continuar con la         |\n"
         << "|                          | partida guardada, se debe digitar:               |\n"
         << "|                          | inicializar juego.                               |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| costo_conquista <territorio> | Calcula el costo y la secuencia de           |\n"
         << "|                          | territorios a ser conquistados para lograr       |\n"
         << "|                          | controlar el territorio dado por el usuario.     |\n"
         << "|                          | Por ejemplo, para el territorio 'colombia':      |\n"
         << "|                          | costo_conquista colombia.                        |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| conquista_mas_barata     | Calcula el territorio que implique un menor      |\n"
         << "|                          | número de unidades de ejército perdidas.         |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| ayuda                    | Muestra la lista de comandos disponibles.        |\n"
         << "+--------------------------+--------------------------------------------------+\n"
         << "| salir                    | Sale del juego Risk.                             |\n"
         << "+--------------------------+--------------------------------------------------+\n";
}

void inicializar() {
    cout << "Función: inicializar" << endl;
}

void turno(const string &id_jugador) {
    cout << "Función: turno, Parámetros: " << id_jugador << endl;
}
 
void salir() {
    cout << "Función: salir" << endl;
    exit(0);
}

void guardar() {
    cout << "Función: guardar" << endl;
}

void guardar_comprimido() {
    cout << "Función: guardar_comprimido" << endl;
}

void inicializar_archivo(const string &nombre_archivo) {
    cout << "Función: inicializar_archivo, Parámetros: " << nombre_archivo << endl;
}

void costo_conquista(const string &territorio) {
    cout << "Función: costo_conquista, Parámetros: " << territorio << endl;
}

void conquista_mas_barata() {
    cout << "Función: conquista_mas_barata" << endl;
}


void verificar_comando() {
    cout << "Verificando comando" << endl;
}



int main() {
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "|                            BIENVENIDO A:                           |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "                                RISK                                  " << endl;
    // ... (Print the ASCII art here)
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "|               Digite el comando 'ayuda' para obtener información   |" << endl;
    cout << "|               de los comandos disponibles.                         |" << endl;
    cout << "+--------------------------------------------------------------------+" << endl;
    cout << "$ ";

    while (true) {
        string inp;
        getline(cin, inp);
        vector<string> ;
        size_t pos = 0;
        while ((pos = inp.find(" ")) != string::npos) {
            commands.push_back(inp.substr(0, pos));
            inp.erase(0, pos + 1);
        }commands
        commands.push_back(inp);

        string command = commands[0];
        if (command == "inicializar") {
            if (commands.size() != 1) {
                cout << "Cantidad de parametros incorrecto." << endl;
            } else {
                inicializar();
            }
        } else if (command == "turno") {
            if (commands.size() != 2) {
                cout << "Cantidad de parametros incorrecto." << endl;
            } else {
                turno(commands[1]);
            }
        }
        // ... (Implement the rest of the command cases similarly)
        else {
            cout << "Comando no reconocido" << endl;
        }
    }

    return 0;
}
