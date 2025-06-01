#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

class NodoHuffman {
protected:
    int dato;
    int frecuencia;
    NodoHuffman* izq;
    NodoHuffman* der;

public:
    NodoHuffman(int valor, int freq);
    NodoHuffman(NodoHuffman* izq, NodoHuffman* der);
    ~NodoHuffman();

    int obtenerDato();
    int obtenerFrec();
    NodoHuffman* obtenerIzq();
    NodoHuffman* obtenerDer();

    class Comparador {
    public:
        bool operator()(NodoHuffman* a, NodoHuffman* b);
    };
};

#endif
