// Programa: Laboratorio 0
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Programa que lee un número para saber si es par, y un string para saber su longitud.

#include <iostream>
#include <string>

// Función que determina si un número es par.
bool esPar(int numero) {
    return numero % 2 == 0;
}

// Función que muestra la longitud de un string.
int longitudString(const std::string& texto) {
    return texto.length();
}

int main() {
    int numero;
    std::cout << "Ingrese un numero: ";
    std::cin >> numero;

    std::cout << "El numero ingresado es: " << numero << std::endl;

    if (esPar(numero)) {
        std::cout << "El numero " << numero << " es par." << std::endl;
    } else {
        std::cout << "El numero " << numero << " es impar." << std::endl;
    }

    // Mostrar si los números del 1 al 10 son pares o impares.
    std::cout << "Numeros del 1 al 10 y si son pares o impares:" << std::endl;
    for (int i = 1; i <= 10; i++) {
        std::cout << i << " -> ";
        if (esPar(i)) {
            std::cout << "Par";
        } else {
            std::cout << "Impar";
        }
        std::cout << std::endl; // Salto de línea.
    }

    // Leer un string ingresado por el usuario.
    std::string textoingresado;
    std::cout << "Ingrese un text cualquiera: ";
    std::cin.ignore();
    std::getline(std::cin, textoingresado);

    // Mostrar la longitud del string ingresado por el usuario.
    std::cout << "La longitud del texto ingresado es: " << longitudString(textoingresado) << std::endl;

    // Mostrar un texto prueba para saber si funciona bien el contador.
    std::string textoprueba = "Programacion";
    std::cout << "La longitud del texto prueba \"" << textoprueba << "\" es de: " 
              << longitudString(textoprueba) << std::endl;

    return 0;
}