# GraphsNodesC-

## Descripción
**GraphsNodesC-** es un proyecto en C/C++ que implementa estructuras de datos y algoritmos clave, tales como:

- Implementaciones de **Grafos** (carga, recorrido, álgebra).
- Árbol de **Huffman** (compresión/decompresión de datos).
- Procesamiento de imágenes en formato **PGM**.
- Utilidades adicionales para trabajar con estructuras y cálculos.

Fue desarrollado como parte de un proyecto académico junto a Valeria Herrera y Laura Sofía Aponte para trabajar con estructuras de datos y procesamiento gráfico.

---

## Estructura del repositorio

- **grafo.h / grafo.cpp** – Clases y funciones para definición y manipulación de grafos.
- **ArbolHuffman.h / ArbolHuffman.cpp** – Implementación de árbol de Huffman para codificación y decodificación.
- **imagen.h / imagen.cpp** – Módulos para leer, escribir y manipular imágenes PGM (`hola.pgm`, `test-5.pgm`).
- **sistema.h / sistema.cpp** – Funciones auxiliares o integradoras del sistema.
- **semilla.h / semilla.cpp** – Funcionalidad relacionada con generación o inicialización de valores.
- **volumen.h / volumen.cpp** – Lógica para cálculos de volumen.
- **main.cpp** – Punto de entrada del programa.
- **Makefile** – Facilita la compilación del proyecto.
- **comandos.txt** – Instrucciones útiles o registros de comandos ejecutados.
- **archivos PGM** (`hola.pgm`, `test-5.pgm`) – Imágenes de ejemplo usadas para pruebas o demostraciones.
- **.replit**, **replit.nix** – Archivos de configuración para entorno Replit (entorno en línea).
- **.ccls-cache** – Archivo de caché para herramientas de análisis en C/C++ (omitido en despliegues).

---

## Instalación y ejecución

**Procesamiento de imagenes:**
./main --imagen hola.pgm
./main --imagen test-5.pgm

##Arboles de Huffman:
./main --huffman texto.txt texto.huf
./main --huffman texto.huf texto_out.txt


**Grafos:**
./main --grafo grafo.txt


**Comandos (archivo comandos.txt)**

Dentro del repositorio se incluye un archivo comandos.txt que contiene ejemplos de ejecución y pruebas.
Puedes ejecutarlos directamente en la terminal, por ejemplo:
./main --imagen hola.pgm
./main --huffman entrada.txt salida.huf
./main --huffman salida.huf salida.txt
./main --grafo grafo.txt


