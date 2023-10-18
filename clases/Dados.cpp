#include "Dados.h"
#include <iostream>
#include <algorithm>
#include <cstdlib> // Include this for rand()


Dados::Dados(std::string tipo, std::vector<int> dados) : tipo(tipo), dados(dados) {
    // You can perform any additional initialization here if needed
}

void Dados::tirarDados() {
    for (int i = 0; i < dados.size(); i++) {
        dados[i] = rand() % 6 + 1;
    }
}

void Dados::ordenarDados() {
    std::sort(dados.begin(), dados.end());
}

void Dados::imprimirDados() {
    for (int i = 0; i < dados.size(); i++) {
        std::cout << dados[i] << " ";
    }
    std::cout << std::endl;
}

int Dados::obtenerMayor() {
    int mayor = dados[0];
    for (int i = 1; i < dados.size(); i++) {
        if (dados[i] > mayor) {
            mayor = dados[i];
        }
    }
    return mayor;
}

int Dados::obtenerSegundoMayor() {
    int mayor = obtenerMayor();
    int segundoMayor = dados[0];
    for (int i = 1; i < dados.size(); i++) {
        if (dados[i] > segundoMayor && dados[i] < mayor) {
            segundoMayor = dados[i];
        }
    }
    return segundoMayor;
}
