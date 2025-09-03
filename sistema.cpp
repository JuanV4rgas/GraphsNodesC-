#include "sistema.h"
#include <algorithm>
#include <cctype> //libreria necesaria para isdigit, encargado de revisar si un string es de solo numeros
#include <fstream>
#include <functional>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>

Sistema::Sistema() {}
void Sistema::mensajeayuda() {
  std::cout << "Comandos disponibles:\n"
            << "   ayuda  - Muestra los comandos disponibles\n"
            << "   salir  - Cierra la aplicación\n";
}

void Sistema::menu_ayuda() {
  std::cout << "Lista de comandos disponibles:\n";
  std::cout << "   cargar_imagen \n";
  std::cout << "   cargar_volumen \n";
  std::cout << "   info_imagen\n";
  std::cout << "   info_volumen\n";
  std::cout << "   proyeccion2D \n";
  std::cout << "   codificar_imagen \n";
  std::cout << "   decodificar_archivo \n";
  std::cout << "   segmentar \n";
  std::cout << "   salir\n";
  std::cout
      << "Si quieres saber como funciona algun comando escribe la palabra "
         "'ayuda' seguida del nombre del comando para conseguir más "
         "información. En la ayuda de cada comando se encuentra la información "
         "de los argumentos que deben ser llamados junto con el comando."
      << std::endl;
}

bool Sistema::contieneNumeros(std::string str) {
  for (char c : str) {
    if (std::isdigit(c))
      return true; // Si encontramos un número, retornamos true
  }
  return false;
}

void Sistema::loopear() {
  std::vector<std::string> comandos;
  std::string palabra;
  while (true) {
    comandos.clear();
    std::cout << std::endl;
    std::cout << "$ ";

    // Leer la línea completa
    std::string linea;
    if (!std::getline(std::cin, linea)) {
      break;
    }

    for (char &c : linea) {
      c = std::tolower(c);
    }

    // Extraer el primer token (comando) de la línea
    std::istringstream iss(linea);

    // Guardar toda la linea en un vector de strings
    while (iss >> palabra) {
      comandos.push_back(palabra);
    }

    std::string comando;

    // Analizar los comandos
    // Comandos de un argumento
    if (comandos.size() == 1) {
      if (comandos[0] == "ayuda") {
        menu_ayuda();
      } else if (comandos[0] == "salir") {
        std::cout << "Saliendo de la aplicación.\n";
        break;
      } else if (comandos[0] == "info_imagen") {
        this->infoImagen();
      } else if (comandos[0] == "info_volumen") {
        this->infoVolumen();
      } else if (comandos[0] == "cargar_imagen") {
        std::cout << "Uso: cargar_imagen <nombre_archivo.pgm>\n";
      } else if (comandos[0] == "cargar_volumen") {
        std::cout << "Uso: cargar_volumen <nombre_base> <n_im>\n";
      } else if (comandos[0] == "proyeccion2d") {
        std::cout << "Uso: proyeccion2D <direccion> <criterio> "
                     "<nombre_archivo.pgm>\n";
      } else if (comandos[0] == "codificar_imagen") {
        std::cout << "Uso: codificar_imagen <nombre_archivo.huf>\n";
      } else if (comandos[0] == "decodificar_archivo") {
        std::cout << "Uso: decodificar_archivo <nombre_archivo.huf> "
                     "<nombre_imagen.pgm>\n";
      } else if (comandos[0] == "segmentar") {
        std::cout << "Uso: segmentar <salida_imagen.pgm> <sx1> <sy1> <sl1> "
                     "<sx2> <sy2> <sl2> ...\n";
      } else {
        std::cout << "Comando no encontrado" << std::endl;
      }
    }

    // Comandos de dos argumentos
    else if (comandos.size() == 2) {
      if (comandos[0] == "ayuda" && comandos[1] == "cargar_imagen") {
        std::cout
            << "Cargar imagen: carga en memoria la imagen identificada con "
               "nombre_imagen.pgm.\n"
            << "Solo es posible cargar una única imagen por sesión, por lo que "
               "si se llama nuevamente\n"
            << "el comando con otro archivo, se sobreescribe la anterior.\n"
            << "Comando: cargar_imagen nombre_imagen.pgm\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "cargar_volumen") {
        std::cout
            << "Cargar volumen: carga en memoria la serie ordenada de imágenes "
               "con nombre_base y\n"
            << "tamaño n_im (máx. 99). Cada imagen debe nombrarse como "
               "nombre_baseXX.pgm,\n"
            << "donde XX son dos dígitos en el rango 01..n_im.\n"
            << "Comando: cargar_volumen nombre_base n_im\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "info_imagen") {
        std::cout << "info_imagen: muestra la información básica de la imagen "
                     "cargada en memoria:\n"
                  << "nombre de archivo, ancho y alto en pixeles.\n"
                  << "Comando: info_imagen\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "info_volumen") {
        std::cout
            << "info_volumen: muestra la información básica del volumen (serie "
               "de imágenes)\n"
            << "cargado en memoria: nombre base, cantidad de imágenes, ancho y "
               "alto.\n"
            << "Comando: info_volumen\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "proyeccion2d") {
        std::cout
            << "proyeccion2D: genera la proyección 2D del volumen cargado, en "
               "la dirección indicada\n"
            << "(x, y o z), aplicando uno de los criterios (minimo, maximo, "
               "promedio, mediana).\n"
            << "Luego guarda la imagen resultante en nombre_archivo.pgm.\n"
            << "Comando: proyeccion2D direccion criterio "
               "nombre_archivo.pgm\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "codificar_imagen") {
        std::cout
            << "codificar_imagen: codifica la imagen cargada en memoria usando "
               "Huffman,\n"
            << "almacenando el resultado en archivo .huf.\n"
            << "Comando: codificar_imagen nombre_archivo.huf\n\n";
      } else if (comandos[0] == "ayuda" &&
                 comandos[1] == "decodificar_archivo") {
        std::cout
            << "decodificar_archivo: toma un archivo .huf, lo decodifica y "
               "genera la\n"
            << "imagen PGM correspondiente.\n"
            << "Comando: decodificar_archivo nombre_archivo.huf "
               "nombre_imagen.pgm\n\n";
      } else if (comandos[0] == "ayuda" && comandos[1] == "segmentar") {
        std::cout << "segmentar: realiza la segmentación de la imagen cargada "
                     "a partir de "
                     "semillas.\n"
                  << "Se pueden ingresar hasta 5 semillas con sus coordenadas "
                     "y etiqueta.\n"
                  << "Comando: segmentar salida_imagen.pgm sx1 sy1 sl1 sx2 sy2 "
                     "sl2 ...\n\n";
      } else if (comandos[0] == "cargar_imagen") {
        if (comandos[1].substr(comandos[1].size() - 4) != ".pgm") {
          std::cout << "Error: el archivo debe terminar en .pgm\n";
        } else {
          this->cargarImagen(comandos[1]);
        }
      } else if (comandos[0] == "codificar_imagen") {
        if (comandos[1].substr(comandos[1].size() - 4) != ".huf") {
          std::cout << "Error: el archivo debe terminar en .huf\n";
        } else {
          this->codificarImagen(comandos[1]);
        }
      } else {
        std::cout << "Comando no encontrado" << std::endl;
      }
    }
    // Comandos de tres argumentos
    else if (comandos.size() == 3) {

      if (comandos[0] == "cargar_volumen") {
        if (contieneNumeros(comandos[2]) == false ||
            std::stoi(comandos[2]) > 99) {
          std::cout << "El volumen " << comandos[1]
                    << " no ha podido ser cargado. El tercer argumento debe "
                       "ser un número entero entre 1 y 100"
                    << std::endl;
        } else {
          this->cargarVolumen(comandos[1], std::stoi(comandos[2]));
        }
      } else if (comandos[0] == "decodificar_archivo") {
        if ((comandos[1].substr(comandos[1].size() - 4) != ".huf") ||
            (comandos[2].substr(comandos[2].size() - 4) != ".pgm")) {
          std::cout << "Error: el primer archivo debe terminar en .huf y el "
                       "segundo archivo en .pgm\n";
        } else {
          this->decodificarArchivo(comandos[1], comandos[2]);
        }
      } else {
        std::cout << "Comando no encontrado." << std::endl;
      }
    }
    // Comandos de cuatro o más argumentos
    else if (comandos.size() >= 4) {
      if (comandos[0] == "segmentar") {
        if (comandos[1].substr(comandos[1].size() - 4) != ".pgm") {
          std::cout << "Error: el archivo debería terminar en .pgm\n";
        } else if (comandos.size() > 17) {
          std::cout << "Usted ha ingresado demasiados argumentos. Puede llamar "
                       "maximo 5 semillas."
                    << std::endl;
        } else if (comandos.size() != 5 && comandos.size() != 8 &&
                   comandos.size() != 11 && comandos.size() != 14 &&
                   comandos.size() != 17) {
          std::cout << "No ha ingresado la cantidad de datos correctos. El "
                       "formato es: nombre_archivo x1 y1 l1..."
                    << std::endl;
        } else {
          segmentarImagen(comandos);
        }
      } else if (comandos[0] == "proyeccion2d") {
        if (comandos[3].substr(comandos[3].size() - 4) != ".pgm") {
          std::cout << "Error: el archivo debe terminar en .pgm\n";
        } else {
          proyeccion2D(comandos[1], comandos[2], comandos[3]);
        }
      } else {
        std::cout << "Comando no encontrado." << std::endl;
      }
    }
  }
}

void Sistema::cargarImagen(std::string archivo) {
  std::ifstream archivoPGM(archivo);
  if (!archivoPGM) {
    std::cout
        << "Error: La imagen " << archivo
        << " no pudo ser cargada. El archivo no existe o no pudo ser abierto"
        << std::endl;
    return;
  }

  std::string linea;
  int dato = 0;
  std::string auxiliar;
  int anchoAux, altoAux, intensidadMaxAux;
  std::vector<int> pixelesAux;

  // quita comentarios
  while (std::getline(archivoPGM, linea)) {
    std::size_t pos = linea.find("#");
    if (pos != std::string::npos) {
      linea = linea.substr(0, pos);
    }

    // quita lineas vacías
    if (linea.empty()) {
      continue;
    }

    std::istringstream iss(linea);

    if (dato == 0) {
      std::string formato;
      iss >> formato;
      if (formato != "P2") {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error: La imagen " << archivo
                  << " no es un archivo PGM válido (P2)." << std::endl;
        return;
      }
      dato++;
    } else if (dato == 1) {
      iss >> anchoAux >> altoAux;
      if (anchoAux <= 0 || altoAux <= 0) {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error. El ancho y alto deben ser al menos 1" << std::endl;
        return;
      }
      dato++;
    } else if (dato == 2) {
      iss >> intensidadMaxAux;
      if (intensidadMaxAux < 0 || intensidadMaxAux > 255) {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error: La intensidad máxima no está entre los valores "
                     "permitidos (0-255)."
                  << std::endl;
        return;
      }
      dato++;
    } else {
      int pixel;
      while (iss >> pixel) {
        if (pixel < 0) {
          std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                    << std::endl;
          std::cout << "Error: Existe un píxel con valor "
                       "menor a 0"
                    << std::endl;
          return;
        } else if (pixel > intensidadMaxAux) {
          std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                    << std::endl;
          std::cout << "No se pudo cargar la imagen. Existe un píxel con "
                       "intensidad mayor a la permitida ("
                    << intensidadMaxAux << ")." << std::endl;
          return;
        }
        pixelesAux.push_back(pixel);
      }
    }
  }

  // Validar la cantidad de píxeles
  if (pixelesAux.size() != static_cast<size_t>(anchoAux * altoAux)) {
    std::cout << "La imagen " << archivo << " no ha podido ser cargada."
              << std::endl;
    std::cout << "Error: La cantidad de datos no "
                 "coincide con las dimensiones."
              << std::endl;
    return;
  }
  // aquí se corrobora que todos los datos son correctos y pueden ser cargados
  // en la imagen
  if (imagen.imagenCargada) {
    imagen.nombre_imagen.clear();
    imagen.ancho = 0;
    imagen.alto = 0;
    imagen.intensidadMax = 0;
    imagen.imagenCargada = false;
    imagen.pixelesImg.clear();
  }
  imagen.nombre_imagen = archivo;
  imagen.ancho = anchoAux;
  imagen.alto = altoAux;
  imagen.intensidadMax = intensidadMaxAux;

  imagen.pixelesImg.resize(altoAux, std::vector<int>(anchoAux));

  int iterador = 0;
  for (int i = 0; i < altoAux; i++) {
    for (int j = 0; j < anchoAux; j++) {
      imagen.pixelesImg[i][j] = pixelesAux[iterador];
      iterador++;
    }
  }

  archivoPGM.close();
  imagen.imagenCargada = true;
  std::cout << "La imagen " << archivo << " ha sido cargada correctamente."
            << std::endl;
}

void Sistema::infoImagen() {
  if (imagen.imagenCargada) {
    std::cout << "Imagen Cargada en Memoria: " << imagen.nombre_imagen
              << std::endl;
    std::cout << "Ancho: " << imagen.ancho << std::endl;
    std::cout << "Alto: " << imagen.alto << std::endl;
  } else {
    std::cout << "No hay imagen cargada en memoria." << std::endl;
  }
}

void Sistema::cargarVolumen(std::string nombreBase, int nImagenes) {

  if (nImagenes < 1 || nImagenes > 99) {
    std::cout << "El volumen no pudo ser cargado." << std::endl;
    std::cout
        << "Se pueden cargar hasta 99 imágenes y usted ha intentado cargar "
        << nImagenes << "." << std::endl;
    return;
  }

  // Primera imagen, con esta se sacará la info general con la que todas se
  // compararán
  Imagen aux;
  std::vector<Imagen> imagenesAux;
  int anchoFijo, altoFijo;

  std::string nombreImagen = nombreBase + "01.pgm";
  bool cargar = cargarImagenVolumen(nombreImagen, aux);
  if (cargar == false) {
    std::cout << "El volumen no pudo ser cargado." << std::endl;
    std::cout << "La imagen " << nombreImagen << " presentó un error."
              << std::endl;
    return;
  } else {
    imagenesAux.push_back(aux);
    anchoFijo = aux.ancho;
    altoFijo = aux.alto;
  }

  for (int i = 1; i < nImagenes; i++) {
    aux.nombre_imagen.clear();
    aux.ancho = 0;
    aux.alto = 0;
    aux.intensidadMax = 0;
    aux.imagenCargada = false;
    aux.pixelesImg.clear();

    if (i + 1 < 10) {
      nombreImagen = nombreBase + "0" + std::to_string(i + 1) + ".pgm";
    } else {
      nombreImagen = nombreBase + std::to_string(i + 1) + ".pgm";
    }
    cargar = cargarImagenVolumen(nombreImagen, aux);
    if (cargar == false) {
      std::cout << "El volumen " << nombreBase << " no pudo ser cargado."
                << std::endl;

      return;
    } else {
      if (aux.ancho != anchoFijo || aux.alto != altoFijo) {
        std::cout << "El volumen no pudo ser cargado." << std::endl;
        std::cout << "El tamaño de la imagen " << nombreImagen
                  << " no coincide con el tamaño de la imagen "
                  << imagenesAux[0].nombre_imagen << "." << std::endl;
        return;
      }
      imagenesAux.push_back(aux);
    }
  }
  if (volumen.volumenCargado) {
    volumen.nombreBase.clear();
    volumen.cantImagenes = 0;
    volumen.anchoImagenes = 0;
    volumen.altoImagenes = 0;
    volumen.volumenCargado = false;
    volumen.imagenesVol.clear();
  }
  volumen.nombreBase = nombreBase;
  volumen.cantImagenes = nImagenes;
  volumen.anchoImagenes = anchoFijo;
  volumen.altoImagenes = altoFijo;

  for (int i = 0; i < imagenesAux.size(); i++) {
    volumen.imagenesVol.push_back(imagenesAux[i]);
  }
  volumen.volumenCargado = true;

  std::cout << "El volumen " << volumen.nombreBase
            << " ha sido cargado correctamente en memoria." << std::endl;
}

bool Sistema::cargarImagenVolumen(std::string archivo, Imagen &imagen) {
  std::ifstream archivoPGM(archivo);
  if (!archivoPGM) {
    std::cout
        << "Error: La imagen " << archivo
        << " no pudo ser cargada. El archivo no existe o no pudo ser abierto"
        << std::endl;
    return false;
  }

  std::string linea;
  int dato = 0;
  std::string auxiliar;
  int anchoAux, altoAux, intensidadMaxAux;
  std::vector<int> pixelesAux;

  // quita comentarios
  while (std::getline(archivoPGM, linea)) {
    std::size_t pos = linea.find("#");
    if (pos != std::string::npos) {
      linea = linea.substr(0, pos);
    }

    // quita lineas vacías
    if (linea.empty()) {
      continue;
    }

    std::istringstream iss(linea);

    if (dato == 0) {
      std::string formato;
      iss >> formato;
      if (formato != "P2") {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error: La imagen " << archivo
                  << " no es un archivo PGM válido (P2)." << std::endl;
        return false;
      }
      dato++;
    } else if (dato == 1) {
      iss >> anchoAux >> altoAux;
      if (anchoAux <= 0 || altoAux <= 0) {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error. El ancho y alto deben ser al menos 1" << std::endl;
        return false;
      }
      dato++;
    } else if (dato == 2) {
      iss >> intensidadMaxAux;
      if (intensidadMaxAux < 0 || intensidadMaxAux > 255) {
        std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                  << std::endl;
        std::cout << "Error: La intensidad máxima no está entre los valores "
                     "permitidos (0-255)."
                  << std::endl;
        return false;
      }
      dato++;
    } else {
      int pixel;
      while (iss >> pixel) {
        if (pixel < 0) {
          std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                    << std::endl;
          std::cout << "Error: Existe un píxel con valor "
                       "menor a 0"
                    << std::endl;
          return false;
        } else if (pixel > intensidadMaxAux) {
          std::cout << "La imagen " << archivo << " no ha podido ser cargada."
                    << std::endl;
          std::cout << "No se pudo cargar la imagen. Existe un píxel con "
                       "intensidad mayor a la permitida ("
                    << intensidadMaxAux << ")." << std::endl;
          return false;
        }
        pixelesAux.push_back(pixel);
      }
    }
  }

  // Validar la cantidad de píxeles
  if (pixelesAux.size() != static_cast<size_t>(anchoAux * altoAux)) {
    std::cout << "La imagen " << archivo << " no ha podido ser cargada."
              << std::endl;
    std::cout << "Error: La cantidad de datos no "
                 "coincide con las dimensiones."
              << std::endl;
    return false;
  }
  // aquí se corrobora que todos los datos son correctos y pueden ser cargados
  // en la imagen
  if (imagen.imagenCargada) {
    imagen.pixelesImg.clear();
  }
  imagen.nombre_imagen = archivo;
  imagen.ancho = anchoAux;
  imagen.alto = altoAux;
  imagen.intensidadMax = intensidadMaxAux;

  imagen.pixelesImg.resize(altoAux, std::vector<int>(anchoAux));

  int iterador = 0;
  for (int i = 0; i < altoAux; i++) {
    for (int j = 0; j < anchoAux; j++) {
      imagen.pixelesImg[i][j] = pixelesAux[iterador];
      iterador++;
    }
  }

  archivoPGM.close();
  imagen.imagenCargada = true;

  return true;
}

void Sistema::infoVolumen() {
  if (volumen.imagenesVol.empty()) {
    std::cout << "No hay un volumen cargado en memoria." << std::endl;
  } else {
    std::cout << "Volumen cargado en memoria: " << volumen.nombreBase
              << std::endl;
    std::cout << "Tamaño: " << volumen.imagenesVol.size() << std::endl;
    std::cout << "Ancho: " << volumen.imagenesVol[0].ancho << std::endl;
    std::cout << "Alto: " << volumen.imagenesVol[0].alto << std::endl;
  }
}

void Sistema::proyeccion2D(std::string direccion, std::string criterio,
                           std::string nombre_archivo) {

  if (volumen.imagenesVol.empty()) {
    std::cout << "El volumen aun no ha sido cargado en memoria" << std::endl;
    return;
  }

  std::vector<int> auxProyeccion, auxMediana;
  Imagen imagenAux;
  std::vector<Imagen>::reverse_iterator itImagenes;
  std::vector<Imagen>::iterator itIm;
  int minimo, maximo, sumaPromedio = 0;
  imagenAux.nombre_imagen.clear();
  imagenAux.ancho = 0;
  imagenAux.alto = 0;
  imagenAux.intensidadMax = 0;
  imagenAux.imagenCargada = false;
  imagenAux.pixelesImg.clear();

  if (direccion == "x") {

    for (itImagenes = volumen.imagenesVol.rbegin();
         itImagenes != volumen.imagenesVol.rend(); itImagenes++) {
      for (int j = 0; j < volumen.anchoImagenes; j++) {
        for (int i = 0; i < volumen.altoImagenes; i++) {
          int pixel = itImagenes->pixelesImg[i][j];

          if (criterio == "minimo") {
            if (i == 0 || pixel < minimo)
              minimo = pixel;
          } else if (criterio == "maximo") {
            if (i == 0 || pixel > maximo)
              maximo = pixel;
          } else if (criterio == "promedio") {
            sumaPromedio += pixel;
          } else if (criterio == "mediana") {
            auxMediana.push_back(pixel);
          } else {
            std::cout << "Usted no ha ingresado un criterio valido. (minimo / "
                         "maximo / promedio / mediana)."
                      << std::endl;
            return;
          }
        }

        if (criterio == "minimo") {
          auxProyeccion.push_back(minimo);
        } else if (criterio == "maximo") {
          auxProyeccion.push_back(maximo);
        } else if (criterio == "promedio") {
          auxProyeccion.push_back(sumaPromedio / volumen.altoImagenes);
        } else if (criterio == "mediana") {
          std::sort(auxMediana.begin(), auxMediana.end());
          int size = auxMediana.size();
          auxProyeccion.push_back(
              size % 2 == 0
                  ? (auxMediana[size / 2 - 1] + auxMediana[size / 2]) / 2
                  : auxMediana[size / 2]);
        }
        auxMediana.clear();
        sumaPromedio = 0;
      }
    }

    imagenAux.nombre_imagen = nombre_archivo;
    imagenAux.ancho = volumen.anchoImagenes;
    imagenAux.alto = volumen.cantImagenes;
    imagenAux.intensidadMax =
        *std::max_element(auxProyeccion.begin(), auxProyeccion.end());
    imagenAux.imagenCargada = true;
    imagenAux.pixelesImg.resize(imagenAux.alto,
                                std::vector<int>(imagenAux.ancho));

    int iterador = 0;
    for (int i = 0; i < imagenAux.alto; i++) {
      for (int j = 0; j < imagenAux.ancho; j++) {
        imagenAux.pixelesImg[i][j] = auxProyeccion[iterador];
        iterador++;
      }
    }
  } else if (direccion == "y") {

    for (int i = 0; i < volumen.altoImagenes; i++) {
      for (itImagenes = volumen.imagenesVol.rbegin();
           itImagenes != volumen.imagenesVol.rend(); itImagenes++) {
        for (int j = 0; j < volumen.anchoImagenes; j++) {
          int pixel = itImagenes->pixelesImg[i][j];

          if (criterio == "minimo") {
            if (j == 0 || pixel < minimo) {
              minimo = pixel;
            }
          } else if (criterio == "maximo") {
            if (j == 0 || pixel > maximo)
              maximo = pixel;
          } else if (criterio == "promedio") {
            sumaPromedio += pixel;
          } else if (criterio == "mediana") {
            auxMediana.push_back(pixel);
          } else {
            std::cout << "Usted no ha ingresado un criterio valido. (minimo / "
                         "maximo / promedio / mediana)."
                      << std::endl;
            return;
          }
        }

        if (criterio == "minimo") {
          auxProyeccion.push_back(minimo);
        } else if (criterio == "maximo") {
          auxProyeccion.push_back(maximo);
        } else if (criterio == "promedio") {
          auxProyeccion.push_back(sumaPromedio / volumen.anchoImagenes);
        } else if (criterio == "mediana") {
          std::sort(auxMediana.begin(), auxMediana.end());
          int size = auxMediana.size();
          auxProyeccion.push_back(
              size % 2 == 0
                  ? (auxMediana[size / 2 - 1] + auxMediana[size / 2]) / 2
                  : auxMediana[size / 2]);
        }
        auxMediana.clear();
        sumaPromedio = 0;
      }
    }

    imagenAux.nombre_imagen = nombre_archivo;
    imagenAux.ancho = volumen.cantImagenes;
    imagenAux.alto = volumen.altoImagenes;
    imagenAux.intensidadMax =
        *std::max_element(auxProyeccion.begin(), auxProyeccion.end());
    imagenAux.imagenCargada = true;
    imagenAux.pixelesImg.resize(imagenAux.alto,
                                std::vector<int>(imagenAux.ancho));

    int iterador = 0;
    for (int i = 0; i < imagenAux.alto; i++) {
      for (int j = 0; j < imagenAux.ancho; j++) {
        imagenAux.pixelesImg[i][j] = auxProyeccion[iterador];
        iterador++;
      }
    }
  } else if (direccion == "z") {
    for (int i = 0; i < volumen.altoImagenes; i++) {
      for (int j = 0; j < volumen.anchoImagenes; j++) {
        for (itIm = volumen.imagenesVol.begin();
             itIm != volumen.imagenesVol.end(); itIm++) {
          int pixel = itIm->pixelesImg[i][j];

          if (criterio == "minimo") {
            if (itIm == volumen.imagenesVol.begin() || pixel < minimo) {
              minimo = pixel;
            }
          } else if (criterio == "maximo") {
            if (itIm == volumen.imagenesVol.begin() || pixel > maximo)
              maximo = pixel;
          } else if (criterio == "promedio") {
            sumaPromedio += pixel;
          } else if (criterio == "mediana") {
            auxMediana.push_back(pixel);
          } else {
            std::cout << "Usted no ha ingresado un criterio valido. (minimo / "
                         "maximo / promedio / mediana)."
                      << std::endl;
            return;
          }
        }

        if (criterio == "minimo") {
          auxProyeccion.push_back(minimo);
        } else if (criterio == "maximo") {
          auxProyeccion.push_back(maximo);
        } else if (criterio == "promedio") {
          auxProyeccion.push_back(sumaPromedio / volumen.cantImagenes);
        } else if (criterio == "mediana") {
          std::sort(auxMediana.begin(), auxMediana.end());
          int size = auxMediana.size();
          auxProyeccion.push_back(
              size % 2 == 0
                  ? (auxMediana[size / 2 - 1] + auxMediana[size / 2]) / 2
                  : auxMediana[size / 2]);
        }
        auxMediana.clear();
        sumaPromedio = 0;
      }
    }

    imagenAux.nombre_imagen = nombre_archivo;
    imagenAux.ancho = volumen.anchoImagenes;
    imagenAux.alto = volumen.altoImagenes;
    imagenAux.intensidadMax =
        *std::max_element(auxProyeccion.begin(), auxProyeccion.end());
    imagenAux.imagenCargada = true;
    imagenAux.pixelesImg.resize(imagenAux.alto,
                                std::vector<int>(imagenAux.ancho));

    int iterador = 0;
    for (int i = 0; i < imagenAux.alto; i++) {
      for (int j = 0; j < imagenAux.ancho; j++) {
        imagenAux.pixelesImg[i][j] = auxProyeccion[iterador];
        iterador++;
      }
    }
  } else {
    std::cout << "Usted no ha ingresado una direccion valida (x / y / z)."
              << std::endl;
    return;
  }

  std::ofstream archivoPGM(nombre_archivo);
  if (archivoPGM.is_open()) {
    archivoPGM << "P2" << std::endl;
    archivoPGM << imagenAux.ancho << " " << imagenAux.alto << std::endl;
    archivoPGM << imagenAux.intensidadMax << std::endl;

    for (int i = 0; i < imagenAux.alto; i++) {
      for (int j = 0; j < imagenAux.ancho; j++) {
        archivoPGM << imagenAux.pixelesImg[i][j] << " ";
      }
      archivoPGM << std::endl;
    }

    archivoPGM.close();
    std::cout << "La proyección 2D del volumen en memoria ha sido generada y "
                 "almacenada en el archivo "
              << nombre_archivo << "." << std::endl;
  } else {
    std::cout << "La proyección 2D del volumen en memoria no ha podido ser "
                 "generada."
              << std::endl;
  }
}

void Sistema::codificarImagen(std::string nombre_archivo_huf) {
  if (imagen.imagenCargada == false) {
    std::cout << "Error: No hay imagen cargada en memoria." << std::endl;
    return;
  }

  std::priority_queue<NodoHuffman *, std::vector<NodoHuffman *>,
                      NodoHuffman::Comparador>
      cola;
  std::vector<int> frecuencia(imagen.intensidadMax + 1, 0);

  for (int i = 0; i < imagen.alto; i++) {
    for (int j = 0; j < imagen.ancho; j++) {
      int valor = imagen.pixelesImg[i][j];
      if (valor >= 0 && valor <= imagen.intensidadMax) {
        frecuencia[valor]++;
      }
    }
  }

  for (int i = 0; i <= imagen.intensidadMax; i++) {
    if (frecuencia[i] > 0) {
      NodoHuffman *nodo = new NodoHuffman(i, frecuencia[i]);
      cola.push(nodo);
    }
  }

  std::cout << "Cola de prioridad (intensidad, frecuencia):\n";
  std::priority_queue<NodoHuffman *, std::vector<NodoHuffman *>,
                      NodoHuffman::Comparador>
      copia = cola;
  while (!copia.empty()) {
    NodoHuffman *nodo = copia.top();
    std::cout << nodo->obtenerDato() << ": " << nodo->obtenerFrec()
              << std::endl;
    copia.pop();
  }

  ArbolHuffman arbol;
  arbol.construirDesdeCola(cola);

  std::cout << "Recorrido por niveles del árbol de Huffman:\n";
  arbol.recorridoPorNiveles();

  std::string codigos[256];
  arbol.generarCodigos(codigos);

  std::cout << "\nCódigos Huffman generados:\n";

  for (int i = 0; i <= imagen.intensidadMax; i++) {
    if (!codigos[i].empty()) {
      std::cout << "Intensidad: " << i << "----- Codigo: " << codigos[i]
                << "\n";
    }
  }

  // Codificar imagen
  std::string bitsCodificados = "";
  for (int i = 0; i < imagen.alto; i++) {
    for (int j = 0; j < imagen.ancho; j++) {
      int intensidad = imagen.pixelesImg[i][j];
      bitsCodificados += codigos[intensidad];
    }
  }

  // Empaquetar bits en bytes
  std::vector<unsigned char> bytesCodificados;
  unsigned char byteActual = 0;
  int bitCount = 0;

  for (char bit : bitsCodificados) {
    byteActual <<= 1;
    if (bit == '1')
      byteActual |= 1;
    bitCount++;

    if (bitCount == 8) {
      bytesCodificados.push_back(byteActual);
      byteActual = 0;
      bitCount = 0;
    }
  }

  // Rellenar con ceros si el último byte quedó incompleto
  if (bitCount > 0) {
    byteActual <<= (8 - bitCount);
    bytesCodificados.push_back(byteActual);
  }

  // Escribir archivo .huf
  std::ofstream archivo(nombre_archivo_huf.c_str(), std::ios::binary);

  // Escribir ancho (2 bytes)
  unsigned short w = imagen.ancho;
  archivo.write(reinterpret_cast<char *>(&w), sizeof(unsigned short));

  // Escribir alto (2 bytes)
  unsigned short h = imagen.alto;
  archivo.write(reinterpret_cast<char *>(&h), sizeof(unsigned short));

  // Escribir intensidad máxima (1 byte)
  unsigned char m = static_cast<unsigned char>(imagen.intensidadMax);
  archivo.write(reinterpret_cast<char *>(&m), sizeof(unsigned char));

  // Escribir frecuencias (M+1 valores, 8 bytes cada uno)
  for (int i = 0; i <= imagen.intensidadMax; i++) {
    unsigned long f = static_cast<unsigned long>(frecuencia[i]);
    archivo.write(reinterpret_cast<char *>(&f), sizeof(unsigned long));
  }

  // Escribir bits comprimidos como bytes
  for (unsigned char b : bytesCodificados) {
    archivo.write(reinterpret_cast<char *>(&b), sizeof(unsigned char));
  }

  archivo.close();

  std::cout << "\nArchivo " << nombre_archivo_huf
            << " generado correctamente.\n";
}

void Sistema::decodificarArchivo(std::string nombre_archivo_huf,
                                 std::string nombre_imagen_pgm) {
  std::ifstream archivo(nombre_archivo_huf.c_str(), std::ios::binary);
  if (!archivo.is_open()) {
    std::cout << "Error: no se pudo abrir el archivo " << nombre_archivo_huf
              << std::endl;
    return;
  }

  // 1. Leer encabezado
  unsigned short ancho, alto;
  unsigned char maxIntensidad;

  archivo.read(reinterpret_cast<char *>(&ancho), sizeof(unsigned short));
  archivo.read(reinterpret_cast<char *>(&alto), sizeof(unsigned short));
  archivo.read(reinterpret_cast<char *>(&maxIntensidad), sizeof(unsigned char));

  if (archivo.fail()) {
    std::cout
        << "Error: formato inválido del archivo (encabezado incompleto).\n";
    return;
  }

  // 2. Leer frecuencias
  std::vector<unsigned long> frecuencias(maxIntensidad + 1);
  for (int i = 0; i <= maxIntensidad; i++) {
    archivo.read(reinterpret_cast<char *>(&frecuencias[i]),
                 sizeof(unsigned long));
    if (archivo.fail()) {
      std::cout << "Error: no se pudieron leer las frecuencias del archivo.\n";
      return;
    }
  }

  // 3. Construir árbol Huffman
  std::priority_queue<NodoHuffman *, std::vector<NodoHuffman *>,
                      NodoHuffman::Comparador>
      cola;
  for (int i = 0; i <= maxIntensidad; i++) {
    if (frecuencias[i] > 0) {
      NodoHuffman *nodo = new NodoHuffman(i, frecuencias[i]);
      cola.push(nodo);
    }
  }

  ArbolHuffman arbol;
  arbol.construirDesdeCola(cola);
  NodoHuffman *raiz = arbol.obtenerRaiz();

  // Caso solo una intensidad
  if (raiz->obtenerIzq() == nullptr && raiz->obtenerDer() == nullptr) {
    int valor = raiz->obtenerDato();

    // Llenar la matriz con el único valor
    std::vector<std::vector<int>> pixeles(alto, std::vector<int>(ancho, valor));

    // Escribir PGM
    std::ofstream salida(nombre_imagen_pgm.c_str());
    if (!salida.is_open()) {
      std::cout << "Error: no se pudo crear el archivo de salida "
                << nombre_imagen_pgm << "\n";
      return;
    }

    salida << "P2\n";
    salida << "# Imagen decodificada desde Huffman (caso único valor)\n";
    salida << ancho << " " << alto << "\n";
    salida << (int)maxIntensidad << "\n";

    for (int i = 0; i < alto; i++) {
      for (int j = 0; j < ancho; j++) {
        salida << pixeles[i][j] << " ";
      }
      salida << "\n";
    }

    salida.close();
    std::cout << "Imagen decodificada correctamente (caso único símbolo) en: "
              << nombre_imagen_pgm << "\n";
    return;
  }

  // 4. Leer bits comprimidos
  std::vector<unsigned char> datosCodificados(
      std::istreambuf_iterator<char>(archivo), {});

  if (datosCodificados.empty()) {
    std::cout << "Error: no se encontraron datos codificados en el archivo.\n";
    return;
  }

  // 5. Decodificar bits
  std::vector<std::vector<int>> pixeles(alto, std::vector<int>(ancho));
  int fila = 0, col = 0;
  NodoHuffman *actual = raiz;
  int simbolosDecodificados = 0;
  int totalSimbolos = ancho * alto;

  for (unsigned char byte : datosCodificados) {
    for (int i = 7; i >= 0 && simbolosDecodificados < totalSimbolos; i--) {
      bool bit = (byte >> i) & 1;
      actual = (bit) ? actual->obtenerDer() : actual->obtenerIzq();

      if (actual->obtenerIzq() == nullptr && actual->obtenerDer() == nullptr) {
        pixeles[fila][col] = actual->obtenerDato();
        simbolosDecodificados++;
        col++;
        if (col == ancho) {
          col = 0;
          fila++;
        }
        actual = raiz;
      }
    }
  }

  if (simbolosDecodificados < totalSimbolos) {
    std::cout << "Error: el archivo parece estar incompleto o dañado.\n";
    return;
  }

  // 6. Escribir imagen .pgm
  std::ofstream salida(nombre_imagen_pgm.c_str());
  if (!salida.is_open()) {
    std::cout << "Error: no se pudo crear el archivo de salida "
              << nombre_imagen_pgm << "\n";
    return;
  }

  salida << "P2\n";
  salida << "# Imagen decodificada desde Huffman\n";
  salida << ancho << " " << alto << "\n";
  salida << (int)maxIntensidad << "\n";

  for (int i = 0; i < alto; i++) {
    for (int j = 0; j < ancho; j++) {
      salida << pixeles[i][j] << " ";
    }
    salida << "\n";
  }

  salida.close();
  std::cout << "Imagen decodificada correctamente y guardada en: "
            << nombre_imagen_pgm << "\n";
}

void Sistema::segmentarImagen(std::vector<std::string> comandos) {
  if (!imagen.imagenCargada) {
    std::cout << "No se pudo segmentar. No hay imagen cargada en memoria"
              << std::endl;
    return;
  }
  Grafo grafo(imagen);

  std::vector<Semilla> semillas;

  for (size_t i = 2; i < comandos.size(); i += 3) {
    int x = std::stoi(comandos[i]);
    int y = std::stoi(comandos[i + 1]);
    int etiqueta = std::stoi(comandos[i + 2]);

    if (x < 0 || x >= imagen.ancho || y < 0 || y >= imagen.alto ||
        etiqueta < 1 || etiqueta > 255) {

      std::cout << "Error: La semilla (" << x << ", " << y << ", " << etiqueta
                << ") está fuera de los límites o tiene una etiqueta inválida."
                << std::endl;
      return;
    }

    semillas.push_back(Semilla(x, y, etiqueta));
  }
  std::vector<std::vector<int>> etiquetas = grafo.segmentar(semillas);
  std::string nombreArchivo = comandos[1];
  int alto = imagen.alto;
  int ancho = imagen.ancho;

  std::ofstream out(nombreArchivo);
  if (!out.is_open()) {
    std::cout << "No se pudo guardar la imagen segmentada." << std::endl;
    return;
  }

  // Escribir encabezado PGM
  out << "P2\n";
  out << "# Imagen segmentada\n";
  out << ancho << " " << alto << "\n";
  out << "255\n";

  // Escribir la matriz de etiquetas como intensidades
  for (int y = 0; y < alto; ++y) {
    for (int x = 0; x < ancho; ++x) {
      out << etiquetas[y][x] << " ";
    }
    out << "\n";
  }

  out.close();

  std::cout << "La imagen en memoria fue segmentada correctamente y almacenada "
               "en el archivo "
            << nombreArchivo << "." << std::endl;
}
