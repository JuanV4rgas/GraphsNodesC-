#ifndef VOLUMEN_H
#define VOLUMEN_H
#include "imagen.h"
#include <vector>
#include <string>

class Volumen {
public:
  std::string nombreBase;
  int cantImagenes;
  int anchoImagenes;
  int altoImagenes;
  bool volumenCargado = false;
  std::vector<Imagen> imagenesVol;


  Volumen();
};


#endif