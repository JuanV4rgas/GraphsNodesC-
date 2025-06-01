#ifndef SISTEMA_H
#define SISTEMA_H
#include "imagen.h"
#include "volumen.h"
#include "NodoHuffman.h"
#include "ArbolHuffman.h"
#include <string>

class Sistema {
public:
  // Atributos de sistema
  Imagen imagen;
  Volumen volumen;

  // Operaciones de sistema
  Sistema();

  void mensajeayuda();
  void menu_ayuda();
  void loopear();
  bool contieneNumeros(std::string a);
  void cargarImagen(std::string archivo);
  bool cargarImagenVolumen(std::string archivo, Imagen &imagen);
  void cargarVolumen(std::string archivo, int nImagenes);
  void infoImagen();
  void infoVolumen();
  void proyeccion2D(std::string direccion, std::string criterio, std::string nombre_archivo);
  void codificarImagen(std::string nombre_archivo_huf);
  void decodificarArchivo(std::string nombre_archivo_huf, std::string nombre_imagen_pgm);
};

#endif