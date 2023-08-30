#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include "clases/Jugador.h"
#include "clases/Pais.h"
#include "clases/Tablero.h"


// Function prototypes
// void DisplayHelp(const std::map<std::string, std::string>& commandHelp);
void InitializeGame(); 
void ayuda();
void Turno(const std::string& JugadorId);
void Save(const std::string& filename);
void Load(const std::string& filename);

// Global variables

// std::vector<Jugador> jugadores;
// std::vector<Pais> paises;
void crear_paises();

Tablero tablero;


int main() {
    crear_paises();
    cout << "Bienvenido a RISK" << std::endl;
    ayuda();
    
    //comandos para interactuar con el programa
    // std::map<std::string, std::string> commandHelp;
    // commandHelp["ayuda"] = "Mostrar lista de comandos disponibles.";
    // commandHelp["inicializar"] = "Inicializar el juego con datos de archivo.";
    // commandHelp["turno"] = "";
    // commandHelp["guardar"] = "Guardar la partida actual";
    // commandHelp["cargar"] = "cargar una partida antigua";
    

    std::string command;
    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "ayuda") {
            ayuda();
        } else if (cmd == "inicializar") {
            
            InitializeGame();
            

        } else if (cmd == "turno") {
            std::string JugadorId;
            iss >> JugadorId;
            Turno(JugadorId);
        } else if (cmd == "guardar") {
            std::string filename;
            iss >> filename;
            Save(filename);
        } else if (cmd == "cargar") {
            std::string filename;
            iss >> filename;
            Load(filename);
        } 
        else {
            std::cout << "Comando no válido. Escribe 'ayuda' para obtener la lista de comandos." << std::endl;
        }
    }

    return 0;
}




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


// void DisplayHelp(const std::map<std::string, std::string>& commandHelp) {
//     std::cout << "Comandos disponibles:" << std::endl;
//     for (const auto& entry : commandHelp) {
//         std::cout << entry.first << ": " << entry.second << std::endl;
//     } 
// }


void crear_paises(){
    Pais pais;
    //Se llenan los datos de los paises
    //Norte america
    pais.nombre = "Alaska";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Alberta";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = " America Central";
    pais.continente = "America del norte";
   pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Estados Unidos Orientales";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Groenlandia";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Territorio Noroccidental";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Ontario";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Quebec";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
    
    pais.nombre = "Estados Unidos Occidentales";
    pais.continente = "America del norte";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    //sur america
    pais.nombre = "Argentina";
    pais.continente = "America del Sur";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Brasil";
    pais.continente = "America del Sur";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Peru";
    pais.continente = "America del Sur";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
    
    pais.nombre = "Venezuela";
    pais.continente = "America del Sur";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
    
    //Australia
    pais.nombre = "Australia Oriental";
    pais.continente = "Australia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Indonesia";
    pais.continente = "Australia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Nueva Guinea";
    pais.continente = "Australia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Australia Occidental";
    pais.continente = "Australia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
    
    //Europa
    pais.nombre = "Gran Bretaña";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
   
    pais.nombre = "Islandia";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Europa del Norte";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Escandinavia";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Europa del Sur";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Ucrania";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
   
    pais.nombre = "Europa Occidental";
    pais.continente = "Europa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
   
    //Asia
    pais.nombre = "Afghanistan";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "China";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "India";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Irkutsk";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Japon";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Kamchatka";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Medio Oriente";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Mongolia";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Siam";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Siberia";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Ural";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Yakutsk";
    pais.continente = "Asia";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    //Africa
    pais.nombre = "Congo";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Africa Oriental";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Egipto";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Madagascar";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Africa del Norte";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);

    pais.nombre = "Africa del Sur";
    pais.continente = "Africa";
    pais.dueno="vacio";
    tablero.paises.push_back(pais);
};


void InitializeGame() {
    //el usuario ingresa el numero de jugadores
    int numjugadores;
    std::cout << "Ingrese el numero de jugadores: ";
    std::cin >> numjugadores;

    while (numjugadores<3 || numjugadores>6)
     {
       std::cout<<"numero de jugadores incorrectos, por favor ingrese un numero entre 3 y 6"<<std::endl;
       std::cin>>numjugadores;
    }

   
    
    //se crean los jugadores y se le añaden las tropas iniciales
    for (int i = 0; i < numjugadores; ++i) {
        Jugador Jugador;
        std::cout << "Enter Jugador " << (i + 1) << " name: ";
        std::cin >> Jugador.nombre;

        
        if (numjugadores == 3)
        {
            Jugador.tropas = 35; // Numero de tropas iniciales
            tablero.jugadores.push_back(Jugador);

        }
        else if (numjugadores == 4)
        {
            Jugador.tropas = 30; // Numero de tropas iniciales
            tablero.jugadores.push_back(Jugador);

        }
        
        else if (numjugadores == 5)
        {
            Jugador.tropas = 25; // Numero de tropas iniciales
            tablero.jugadores.push_back(Jugador);

        }

        else if (numjugadores == 6)
        {
            Jugador.tropas = 20; // Numero de tropas iniciales
            tablero.jugadores.push_back(Jugador);

        }

        }

        // se reparten los paises entre los jugadores
       for (int j = 0; j < tablero.paises.size(); j++){ 
        std::cout << tablero.jugadores[j%numjugadores].nombre<<" Seleccione el pais donde quiere poner tropas:"  << std::endl;
        
        std::string x;
        std::cin>>x;
            int i=0;
            do
            {
                i++;
            if (tablero.paises[i].dueno == "vacio")
            {
               tablero.paises[i].dueno= tablero.jugadores[j%numjugadores].nombre;
               tablero.paises[i].tropas = 1;
               tablero.jugadores[j%numjugadores].tropas = tablero.jugadores[j%numjugadores].tropas - 1;
               tablero.jugadores[j%numjugadores].paisesj.push_back(tablero.paises[i]);

            }
            else if (tablero.paises[i].dueno != x)
            {
                std::cout<<"No se encontro el pais, verifique si tiene errores de ortografia"<<std::endl;
                j--;
            }
            else{
                
                std::cout<<"Ya hay tropas en este pais, seleccione otro"<<std::endl;

                j--;
            }
            } while (tablero.paises[i].nombre== x );

             
            // tablero.jugadores = jugadores;
            // tablero.paises = paises;
        
       
       }
    
    
    
}


void Turno(int JugadorId) {
    // verificar que turno si corresponde
    if (tablero.turnoActual != JugadorId) {
        std::cout << "No es el turno de este jugador" << std::endl;
        return;
    }

    tablero.empezar_turno();
}

void Save(const std::string& filename) {
    
}

void Load(const std::string& filename) {
   
}

