#include "NodoHuffman.h"

NodoHuffman::NodoHuffman(int valor, int freq) {
    dato = valor;
    frecuencia = freq;
    izq = nullptr;
    der = nullptr;
}

NodoHuffman::NodoHuffman(NodoHuffman* izquierdo, NodoHuffman* derecho) {
    dato= -1;
    frecuencia = izquierdo->obtenerFrec() + derecho->obtenerFrec();
    izq = izquierdo;
    der = derecho;
}

NodoHuffman::~NodoHuffman() {
    izq = nullptr;
    der = nullptr;
}



int NodoHuffman::obtenerDato() {
    return dato;
}

int NodoHuffman::obtenerFrec() {
    return frecuencia;
}

NodoHuffman* NodoHuffman::obtenerIzq() {
    return izq;
}

NodoHuffman* NodoHuffman::obtenerDer() {
    return der;
}

// Comparador
bool NodoHuffman::Comparador::operator()(NodoHuffman* a, NodoHuffman* b) {
    return a->obtenerFrec() > b->obtenerFrec();
}
