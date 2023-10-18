#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <unordered_map>
#include <string>
#include <fstream>

struct NodoHuffman {
    char caracter;
    int frecuencia;
    NodoHuffman* izquierda;
    NodoHuffman* derecha;
};

class Huffman {
public:
    Huffman();
    ~Huffman();

    void comprimirArchivo(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida);
    void descomprimirArchivo(const std::string& nombreArchivoEntrada, const std::string& nombreArchivoSalida);

private:
    std::unordered_map<char, std::string> generarTablaDeCodigos(NodoHuffman* raiz, std::string codigo = "");
    NodoHuffman* construirArbolHuffman(std::unordered_map<char, int>& frecuencias);
    void guardarTablaDeCodigos(const std::unordered_map<char, std::string>& tablaDeCodigos, std::ofstream& archivoSalida);
    std::unordered_map<std::string, char> cargarTablaDeCodigos(std::ifstream& archivoEntrada);
};

#endif // HUFFMAN_H
