#ifndef DADOS_H
#define DADOS_H

#include <string>
#include <vector>

class Dados {
public:
    std::string tipo; // atacante o defensor  --> en la vida real son rojos o blancos
    std::vector<int> dados; // cada dado es un int


    Dados(std::string color, std::vector<int> dados) : color(color), dados(dados) {}

    void tirarDados() {
        for (int i = 0; i < dados.size(); i++) {
            dados[i] = rand() % 6 + 1;
        }
    }

    void ordenarDados() {
        std::sort(dados.begin(), dados.end());
    }

    void imprimirDados() {
        for (int i = 0; i < dados.size(); i++) {
            std::cout << dados[i] << " ";
        }
        std::cout << std::endl;
    }

    int obtenerMayor() {
        int mayor = dados[0];
        for (int i = 1; i < dados.size(); i++) {
            if (dados[i] > mayor) {
                mayor = dados[i];
            }
        }
        return mayor;
    }

    int obtenerSegundoMayor() {
        int mayor = obtenerMayor();
        int segundoMayor = dados[0];
        for (int i = 1; i < dados.size(); i++) {
            if (dados[i] > segundoMayor && dados[i] < mayor) {
                segundoMayor = dados[i];
            }
        }
        return segundoMayor;
    }
    

    
        
};




#endif