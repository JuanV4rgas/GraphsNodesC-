#ifndef IMAGEN_H
#define IMAGEN_H
#include <vector>
#include <string>

class Imagen {
public:
  std::string nombre_imagen;
  int ancho;
  int alto;
  int intensidadMax;
  bool imagenCargada = false;
  std::vector<std::vector<int>> pixelesImg;

  Imagen();

};

#endif