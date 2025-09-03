#include "ArbolHuffman.h"
#include <iostream>
#include <queue>


ArbolHuffman::ArbolHuffman(){
    raiz = nullptr;
}

ArbolHuffman::~ArbolHuffman() {
    this->destruir();
}

void ArbolHuffman::destruir() {
    destruirDesde(this->raiz);
    this->raiz = nullptr;
}

void ArbolHuffman::destruirDesde(NodoHuffman* nodo) {
    if (nodo == nullptr) {
        return;
    }

    destruirDesde(nodo->obtenerIzq());
    destruirDesde(nodo->obtenerDer());

    delete nodo;
}


NodoHuffman* ArbolHuffman::obtenerRaiz(){
    return raiz;
}

void ArbolHuffman::construirDesdeCola(std::priority_queue<NodoHuffman*, std::vector<NodoHuffman*>, NodoHuffman::Comparador>& cola) {
    if (cola.empty()) {
        std::cout << "Error: la cola está vacía. No se puede construir el árbol.\n";
        this->raiz = nullptr;
        return;
    }

    while (cola.size() > 1) {
        // extraer los dos nodos de menor frecuencia
        NodoHuffman* x = cola.top();
        cola.pop();

        NodoHuffman* y = cola.top();
        cola.pop();

        // crear nuevo nodo z
        NodoHuffman* z = new NodoHuffman(x, y); // constructor ya suma frecuencias

        // insertar z en la cola
        cola.push(z);
    }

    // el último nodo en la cola es la raíz del árbol
    this->raiz = cola.top();
    cola.pop();

    std::cout << "Árbol Huffman construido correctamente. Raíz con frecuencia: "
              << this->raiz->obtenerFrec() << std::endl;
}




void ArbolHuffman::generarCodigos(std::string codigos[]) {
    if (this->raiz == nullptr) return;

    if (raiz->obtenerIzq() == nullptr && raiz->obtenerDer() == nullptr) {
        // Caso de un solo nodo
        codigos[raiz->obtenerDato()] = "0";
    } else {
        generarDesde(raiz, "", codigos);
    }
}


void ArbolHuffman::generarDesde(NodoHuffman* nodo, std::string codigoActual, std::string codigos[]) {
    if (nodo == nullptr) {
        return;
    }

    if (nodo->obtenerIzq() == nullptr && nodo->obtenerDer() == nullptr) {
        // Nodo hoja: asignamos el código
        int intensidad = nodo->obtenerDato();
        codigos[intensidad] = codigoActual;
        return;
    }

    generarDesde(nodo->obtenerIzq(), codigoActual + "0", codigos);
    generarDesde(nodo->obtenerDer(), codigoActual + "1", codigos);
}


void ArbolHuffman::recorridoPorNiveles() {
    if (this->raiz == nullptr) {
        std::cout << "El árbol está vacío.\n";
        return;
    }

    std::queue<NodoHuffman*> cola;
    cola.push(this->raiz);

    int nivel = 0;
    std::cout << "Recorrido por niveles del árbol de Huffman:\n";

    while (!cola.empty()) {
        int nodosEnNivel = cola.size();
        std::cout << "Nivel " << nivel << ":\n";

        for (int i = 0; i < nodosEnNivel; i++) {
            NodoHuffman* actual = cola.front();
            cola.pop();

            bool esHoja = (actual->obtenerIzq() == nullptr && actual->obtenerDer() == nullptr);

            if (esHoja) {
                std::cout << "  Hoja -> Intensidad: " << actual->obtenerDato()
                          << ", Frecuencia: " << actual->obtenerFrec() << "\n";
            } else {
                std::cout << "  Nodo interno -> Frecuencia: " << actual->obtenerFrec() << "\n";
            }

            if (actual->obtenerIzq() != nullptr) {
                cola.push(actual->obtenerIzq());
            }

            if (actual->obtenerDer() != nullptr) {
                cola.push(actual->obtenerDer());
            }
        }

        nivel++;
    }
}