#include "sistema.h"
#include <iostream>
#include <string>

int main() {
    Sistema sistema;
    // Mensaje inicial o de bienvenida
    std::cout << "Bienvenido. Escribe un comando para continuar." << std::endl;

    // Mostramos mensaje de ayuda al inicio
    sistema.mensajeayuda(); 
    // Ciclo para pedir comando
    sistema.loopear();

    return 0;

}