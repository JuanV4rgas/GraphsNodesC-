#include "etiqueta.h"
#include <fstream>

Etiqueta::Etiqueta(int w, int h)
    : ancho(w), alto(h), etiquetas(h, std::vector<int>(w, 0)) {}

void Etiqueta::asignar(int x, int y, int etiqueta) {
    etiquetas[y][x] = etiqueta;
}

int Etiqueta::obtener(int x, int y) const {
    return etiquetas[y][x];
}

int Etiqueta::getAncho() const {
    return ancho;
}

int Etiqueta::getAlto() const {
    return alto;
}

void Etiqueta::guardarComoPGM(const std::string& archivo, int intensidadMax) const {
    std::ofstream out(archivo);
    out << "P2\n";
    out << ancho << " " << alto << "\n";
    out << intensidadMax << "\n";
    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x)
            out << etiquetas[y][x] << " ";
        out << "\n";
    }
    out.close();
}
