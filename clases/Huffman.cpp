#include "Huffman.h"
#include <queue>
#include <bitset>
#include <iostream>
using namespace std;

struct ComparadorNodos {
    bool operator()(NodoHuffman* izquierda, NodoHuffman* derecha) {
        return izquierda->frecuencia > derecha->frecuencia;
    }
};

Huffman::Huffman() {}

Huffman::~Huffman() {}

void Huffman::guardarTablaDeCodigos(const std::unordered_map<char, std::string>& tablaDeCodigos, std::ofstream& archivoSalida) {
    
    // Imprimir tabla de códigos
    for (const auto& par : tablaDeCodigos) {
        archivoSalida << par.first << par.second << std::endl;
    }
    archivoSalida << "#"; // Marcar el final de la tabla de códigos
}

std::unordered_map<std::string, char> Huffman::cargarTablaDeCodigos(std::ifstream& archivoEntrada) {
    std::unordered_map<std::string, char> tablaDeCodigos;
    char caracter;
    std::string codigo;
    while (archivoEntrada.get(caracter)) {
        if (caracter == '#') {
            break; // Fin de la tabla de códigos
        }
        archivoEntrada.get(caracter); // Leer el siguiente caracter (después del espacio)
        archivoEntrada >> codigo;
        tablaDeCodigos[codigo] = caracter;
    }
    return tablaDeCodigos;
}

// std::unordered_map<char, std::string> Huffman::generarTablaDeCodigos(NodoHuffman* raiz, std::string codigo) {
//     // char c = '\0'; // Default value
//     // if (raiz) {
//     //     c = raiz->caracter;
//     //     cout << "Generando tabla de codigos: " << codigo << "-------------> " << c  << endl;
//     // }else{

//     //     cout << "Generando tabla de codigos: " << codigo   << endl;
//     // }

//     std::unordered_map<char, std::string> tablaDeCodigos;
//     if (raiz) {
//         if (!raiz->izquierda && !raiz->derecha) {
//             tablaDeCodigos[raiz->caracter] = codigo;
//         }
//         tablaDeCodigos = generarTablaDeCodigos(raiz->izquierda, codigo + "0");
//         tablaDeCodigos.insert(generarTablaDeCodigos(raiz->derecha, codigo + "1").begin(), tablaDeCodigos.end());
//     }
//     return tablaDeCodigos;
// }
std::unordered_map<char, std::string> Huffman::generarTablaDeCodigos(NodoHuffman* raiz, std::string codigo) {
    std::unordered_map<char, std::string> tablaDeCodigos;
    if (raiz) {
        if (!raiz->izquierda && !raiz->derecha) {
            tablaDeCodigos[raiz->caracter] = codigo;
        }
        
        // Generar tabla de codigos para el lado izquierdo del árbol
        std::unordered_map<char, std::string> tablaIzquierda = generarTablaDeCodigos(raiz->izquierda, codigo + "0");
        // Insertar elementos del lado izquierdo en la tabla final
        for (const auto& par : tablaIzquierda) {
            tablaDeCodigos[par.first] = par.second;
        }
        
        // Generar tabla de codigos para el lado derecho del árbol
        std::unordered_map<char, std::string> tablaDerecha = generarTablaDeCodigos(raiz->derecha, codigo + "1");
        // Insertar elementos del lado derecho en la tabla final
        for (const auto& par : tablaDerecha) {
            tablaDeCodigos[par.first] = par.second;
        }
    }
    return tablaDeCodigos;
}


NodoHuffman* Huffman::construirArbolHuffman(std::unordered_map<char, int>& frecuencias) {
    std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, ComparadorNodos> colaDePrioridad;
    for (auto par : frecuencias) {
        NodoHuffman* nodo = new NodoHuffman();
        nodo->caracter = par.first;
        nodo->frecuencia = par.second;
        nodo->izquierda = nullptr;
        nodo->derecha = nullptr;
        colaDePrioridad.push(nodo);
    }
    while (colaDePrioridad.size() > 1) {
        // cout << "Recorriendo Cola de prioridad (size Actual): " << colaDePrioridad.size() << endl;
        NodoHuffman* izquierda = colaDePrioridad.top();
        colaDePrioridad.pop();
        NodoHuffman* derecha = colaDePrioridad.top();
        colaDePrioridad.pop();
        NodoHuffman* nodoPadre = new NodoHuffman();
        nodoPadre->frecuencia = izquierda->frecuencia + derecha->frecuencia;
        nodoPadre->caracter = '\0';
        nodoPadre->izquierda = izquierda;
        nodoPadre->derecha = derecha;
        colaDePrioridad.push(nodoPadre);
    }
    return colaDePrioridad.top();
}

void Huffman::comprimirArchivo(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida) {
    std::ifstream archivoEntrada(nombreArchivoEntrada, std::ios::in);
    std::ofstream archivoSalida(nombreArchivoSalida, std::ios::out | std::ios::binary);

    std::unordered_map<char, int> frecuencias;
    char caracter;
    while (archivoEntrada.get(caracter)) {
        frecuencias[caracter]++;
        // std::cout << caracter;
    }

    // Imprimir tabla de frecuencias
    // cout << "Imprimiendo tabla de frecuencias"<<endl;
    // for (const auto par : frecuencias) {
    //     cout << "Frecuencia: " << par.first << " ->" << par.second << endl;
    // }

    NodoHuffman* raiz = construirArbolHuffman(frecuencias);
    std::unordered_map<char, std::string> tablaDeCodigos = generarTablaDeCodigos(raiz);
    // cout << "Tabla de codigos generada" << endl;
    // cout << "Testeando tabla de codigos" << endl;
    // cout << unordered_map.find('a') << endl;
    std::cout << "Tabla de Códigos:" << std::endl;
    for (const auto par : tablaDeCodigos) {
        cout << "Codigo: " << par.first << " ->" << par.second << endl;
    }

    guardarTablaDeCodigos(tablaDeCodigos, archivoSalida);

    archivoEntrada.clear();
    archivoEntrada.seekg(0); // Volver al inicio del archivo para recorrerlo de nuevo

    std::string codigo;
    while (archivoEntrada.get(caracter)) {
        // archivoSalida.put(tablaDeCodigos[caracter]);
        archivoSalida.write(tablaDeCodigos[caracter].c_str(), tablaDeCodigos[caracter].size());
        archivoSalida.put(' ');

        // codigo += tablaDeCodigos[caracter];
        // while (codigo.length() >= 8) {
        //     std::bitset<8> byte(codigo.substr(0, 8));
        //     archivoSalida.put(byte.to_ulong());
        //     std::cout << byte.to_ulong() << endl;
        //     codigo = codigo.substr(8);
        // }
    }

    // Manejar los últimos bits que quedan en 'codigo'
    if (!codigo.empty()) {
        std::bitset<8> byte(codigo + std::string(8 - codigo.length(), '0'));
        archivoSalida.put(byte.to_ulong());
    }

    archivoEntrada.close();
    archivoSalida.close();
}

void Huffman::descomprimirArchivo(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida) {
    std::ifstream archivoEntrada(nombreArchivoEntrada, std::ios::in | std::ios::binary);
    std::ofstream archivoSalida(nombreArchivoSalida, std::ios::out);

    std::unordered_map<std::string, char> tablaDeCodigos = cargarTablaDeCodigos(archivoEntrada);

    std::string codigo;
    char byte;
    while (archivoEntrada.get(byte)) {
        std::bitset<8> bits(byte);
        codigo += bits.to_string();
        for (size_t i = 0; i < codigo.length(); ++i) {
            std::string subcadena = codigo.substr(0, i + 1);
            if (tablaDeCodigos.find(subcadena) != tablaDeCodigos.end()) {
                archivoSalida << tablaDeCodigos[subcadena];
                codigo = codigo.substr(i + 1);
                i = -1; // Reiniciar el índice
            }
        }
    }

    archivoEntrada.close();
    archivoSalida.close();
}