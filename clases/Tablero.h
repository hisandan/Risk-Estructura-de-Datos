#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Tablero {


public:
    std::vector<Jugador> jugadores;
    std::vector<Pais> paises;
    int turnoActual;
    


    Tablero(std::vector<Jugador> jugadores, std::vector<Pais> paises) : jugadores(jugadores), paises(paises) {}

    void empezar_turno() {
        distribuir_tropas();
        siguenteturno();
    }
        
    


    void distribuir_tropas() {
        int tropas = 0;
        for (int i = 0; i < jugadores.size(); i++) {
            tropas = jugadores[i].paisesj.size() / 2;
            jugadores[i].tropas += tropas;
        }
    }


    void siguenteturno() {
        turnoActual++;
        if (turnoActual == jugadores.size()) {
            turnoActual = 0;
        }
    }

    Jugador obtenerJugadorTurno() {
        return jugadores[turnoActual];
    } 


    std::pair<int, int> comparar_dados(Dados atacante, Dados defensor) {
        // Devuelve el numero de tropas que se le quitan al atacante y el numero de ctropas que se le quitan al vendedor
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


    void Atacar(Pais atacante, Pais defensor){
        bool dueno_correcto = false;
        // Revisar si el atacante es del jugador actual
            for (int j = 0; j < jugadores[turnoActual].paisesj.size(); j++) {
                if (jugadores[turnoActual].paisesj[j].nombre == atacante.nombre) {
                        dueno_correcto = true;  
                       
                }
            }
        if(!dueno_correcto){
            cout << "No es tu pais" << endl;
             return;
        }
        dueno_correcto = true;
        // Revisar si el defensor es de otro jugador
        for (int j = 0; j < jugadores[turnoActual].paisesj.size(); j++) {
                if (jugadores[turnoActual].paisesj[j].nombre == atacante.nombre) {
                        dueno_correcto = false; 
                        cout << "No puedes atacar a tu propio pais" << endl; 
                        return;
                }
            }
       
        while(true){

       
       // DEFINIENDO CON CUANTOS DADOS ATACAR Y DEFENDER-------
        // Revisar si el atacante tiene mas de 1 tropa
        if(atacante.tropas < 2){
            cout << "No tienes suficientes tropas" << endl;
            return;
        } else if (atacante.tropas == 2) {
            cantidad_dados_atacante = 1;
        }else{
            cantidad_dados_atacante = 3;
        }
        int cantidad_dados_atacante = 2;

        // Revisar si el defensor tiene mas de 0 tropas
        if(defensor.tropas ==1){
            cantidad_dados_defensor = 1;
        }else{
            cantidad_dados_defensor = 2;
        }


        // CREANDO LOS DADOS-------------------------------------
        Dados dados_atacante("atacante", cantidad_dados_atacante);
        Dados dados_defensor("defensor", cantidad_dados_defensor);
        std::pair<int, int> resultado = comparar_dados(dados_atacante, dados_defensor);
        atacante.tropas -= resultado.first;
        defensor.tropas -= resultado.second;
        cout << "Tropas del atacante: " << atacante.tropas << endl;
        cout << "Tropas del defensor: " << defensor.tropas << endl;

        // si gano el atacante
        if(defensor.tropas==0){
            cout << "Ganaste el pais" << endl;
            // Cambiar el dueno del pais
            for (int i = 0; i < jugadores.size(); i++) {
                for (int j = 0; j < jugadores[i].paisesj.size(); j++) {
                    if (jugadores[i].paisesj[j].nombre == defensor.nombre) {
                        jugadores[i].paisesj.erase(jugadores[i].paisesj.begin() + j);
                        jugadores[turnoActual].paisesj.push_back(defensor);
                        defensor.dueno = jugadores[turnoActual].nombre;
                        break;
                    }
                }
            }
            // Preguntar cuantas tropas desea mover
            int tropas_mover;
            cout << "Cuantas tropas desea mover?" << endl;
            cin >> tropas_mover;
            // Revisar si el atacante tiene suficientes tropas
            if (tropas_mover > atacante.tropas) {
                cout << "No tienes suficientes tropas" << endl;
                return;
            }
            // Mover las tropas
            atacante.tropas -= tropas_mover;
            defensor.tropas += tropas_mover;
            return;
        }

        // Pregunta si desea parar de atacar
        string parar;
        cout << "Desea parar de atacar? (s/n)" << endl;
        cin >> parar;
        if(parar == "s"){
            return;
         }
        
    }



};


#endif