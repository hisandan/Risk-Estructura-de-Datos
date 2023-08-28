#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Pais.h"

class Jugador {
public:
    std::string nombre;
    std::string color;
    int tropas;
    std::vector<std::string> cartas;
    std::vector<Pais> paisesj;

    mover_tropas(Pais pais1, Pais pais2) {

        // verificar que el jugador sea dueño de los paises
        if(pais1.dueno != nombre || pais2.dueno != nombre) {
            cout << "No es dueño de los paises" << endl;
            return;
        }

        // preguntar cuantas tropas desea mover
        int tropas;
        cout << "¿Cuantas tropas desea mover?" << endl;
        cin >> tropas;

        // debe dejar al menos 1 unidad en cada uno de sus países
        if(pais1.tropas - tropas < 1) {
            cout << "Debe dejar minimo 1 tropa en el pais "<< pais1.nombre << endl;
            return;
        }

        //verificar que los paises sean adyacentes
        if(!pais1.adyacentes.contains(pais2.nombre)) {
            cout << "Los paises no son adyacentes" << endl;
            return;
        }

        pais1.tropas -= tropas;
        pais2.tropas += tropas;

    }


};



#endif