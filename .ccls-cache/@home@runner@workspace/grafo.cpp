#include "grafo.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>

struct Nodo {
  int costo;
  int x;
  int y;
  int etiqueta;

  Nodo(int c, int x_, int y_, int e) : costo(c), x(x_), y(y_), etiqueta(e) {}

  // Para que funcione con std::greater en la cola de prioridad
  bool operator>(const Nodo &otro) const { return costo > otro.costo; }
};

Grafo::Grafo(const Imagen &img) : imagenOriginal(img) {}

std::vector<std::vector<int>>
Grafo::segmentar(const std::vector<Semilla> &semillas) {
  const int INF = 1000000000;
  int ancho = imagenOriginal.ancho;
  int alto = imagenOriginal.alto;

  // 1. Crear una grilla de distancias por semilla
  std::vector<std::vector<std::vector<int>>> distanciasPorSemilla;

  // 2. Ejecutar Dijkstra por cada semilla
  for (size_t s = 0; s < semillas.size(); ++s) {
    std::vector<std::vector<int>> distancias(alto,
                                             std::vector<int>(ancho, INF));
    std::priority_queue<Nodo, std::vector<Nodo>, std::greater<Nodo>> cola;

    int x0 = semillas[s].x;
    int y0 = semillas[s].y;

    distancias[y0][x0] = 0;
    cola.push(Nodo(0, x0, y0, semillas[s].etiqueta));

    while (!cola.empty()) {
      Nodo actual = cola.top();
      cola.pop();
      int x = actual.x;
      int y = actual.y;
      int costo = actual.costo;

      // Ignorar si ya tenemos un costo mejor guardado
      if (costo > distancias[y][x])
        continue;

      int intensidadActual = imagenOriginal.pixelesImg[y][x];
      std::vector<std::pair<int, int>> vecinos = obtenerVecinos(x, y);

      for (size_t i = 0; i < vecinos.size(); ++i) {
        int nx = vecinos[i].first;
        int ny = vecinos[i].second;

        int intensidadVecino = imagenOriginal.pixelesImg[ny][nx];
        int nuevoCosto = costo + std::abs(intensidadActual - intensidadVecino);

        if (nuevoCosto < distancias[ny][nx]) {
          distancias[ny][nx] = nuevoCosto;
          cola.push(Nodo(nuevoCosto, nx, ny, semillas[s].etiqueta));
        }
      }
    }

    distanciasPorSemilla.push_back(distancias);
  }

  // 3. Determinar la etiqueta ganadora para cada pixel
  std::vector<std::vector<int>> etiquetas(alto, std::vector<int>(ancho, 0));

  for (int y = 0; y < alto; ++y) {
    for (int x = 0; x < ancho; ++x) {
      int mejorDistancia = INF;
      int etiquetaGanadora = 0;

      for (size_t s = 0; s < semillas.size(); ++s) {
        int dist = distanciasPorSemilla[s][y][x];
        if (dist < mejorDistancia) {
          mejorDistancia = dist;
          etiquetaGanadora = semillas[s].etiqueta;
        }
        // Si hay empate, se queda con la primera semilla
      }

      etiquetas[y][x] = etiquetaGanadora;
    }
  }

  return etiquetas;
}

std::vector<std::pair<int, int>> Grafo::obtenerVecinos(int x, int y) const {
  std::vector<std::pair<int, int>> vecinos;

  if (x > 0)
    vecinos.emplace_back(x - 1, y);
  if (x < imagenOriginal.ancho - 1)
    vecinos.emplace_back(x + 1, y);
  if (y > 0)
    vecinos.emplace_back(x, y - 1);
  if (y < imagenOriginal.alto - 1)
    vecinos.emplace_back(x, y + 1);

  return vecinos;
}
