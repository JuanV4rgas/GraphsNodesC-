
#ifndef ARBOL_HUFFMAN_H
#define ARBOL_HUFFMAN_H

#include <string>
#include <queue>
#include "NodoHuffman.h"

class ArbolHuffman {
protected:
    NodoHuffman* raiz;

public:
ArbolHuffman();
~ArbolHuffman();
NodoHuffman* obtenerRaiz();
void destruir();
void destruirDesde(NodoHuffman* nodo);
void construirDesdeCola(std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, NodoHuffman::Comparador>& cola);
void generarCodigos(std::string codigos[]);
void generarDesde(NodoHuffman* nodo, std::string codigoActual, std::string codigos[]);
void recorridoPorNiveles();



};
    
#endif