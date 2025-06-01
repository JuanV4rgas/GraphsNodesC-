#ifndef ETIQUETA_H
#define ETIQUETA_H

#include <vector>
#include <string>

class Etiqueta {
private:
    int ancho, alto;
    std::vector<std::vector<int>> etiquetas;
public:
    Etiqueta(int w, int h);
    void asignar(int x, int y, int etiqueta);
    int obtener(int x, int y) const;
    int getAncho() const;
    int getAlto() const;
    void guardarComoPGM(const std::string& archivo, int intensidadMax = 255) const;
};

#endif // ETIQUETA_H
