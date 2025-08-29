// Programa: Calcular Cuadrado
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Este programa calcula el cuadrado de un número y lo imprime en la consola.

#include <iostream>  // Librería para entrada y salida.

// Función que calcula el cuadrado de un número.
double calcularcuadrado(double numero) {
    return numero * numero;
}

// Función que imprime el cuadrado de un número en la consola.
void mostrarcuadrado(double numero) {
    std::cout << "- El cuadrado de " << numero << " es " << calcularcuadrado(numero) << "\n";
}

int main() {
    // Mostrar cuadrados de números ingresados, en este caso el 12 y el 3.
    mostrarcuadrado(12);
    mostrarcuadrado(3);
}
