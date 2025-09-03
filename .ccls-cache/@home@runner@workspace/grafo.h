#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include "imagen.h"
#include "semilla.h"

class Grafo {
private:
    const Imagen& imagenOriginal;
    std::vector<std::vector<int>> etiquetas;

public:
    Grafo(const Imagen& img);

    std::vector<std::vector<int>> segmentar(const std::vector<Semilla>& semillas);
    std::vector<std::pair<int, int>> obtenerVecinos(int x, int y) const;
};

#endif // GRAFO_H
