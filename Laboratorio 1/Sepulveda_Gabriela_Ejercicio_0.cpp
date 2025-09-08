// Programa: Ejercicio 0
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Crear 3 pacientes con nombre, edad, peso y altura usando un struct, mostrando los datos en la terminal.

#include <iostream>
#include <string>

// Definición de la estructura Paciente.
struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
};

int main() {
    // Creación de 3 pacientes con parámetros nombre, edad, peso y estatura.
    Paciente p1 = {"Isidora González", 21, 56.3, 1.68};
    Paciente p2 = {"Leonardo Sepúlveda", 46, 93.2, 1.77};
    Paciente p3 = {"Javiera Medel", 25, 53.6, 1.62};

    // Mostrar la información de los pacientes 1, 2 y 3.
    std::cout << "Paciente 1:" << std::endl;
    std::cout << "- Nombre: " << p1.nombre << std::endl;
    std::cout << "- Edad: " << p1.edad << " años" << std::endl;
    std::cout << "- Peso: " << p1.peso << " kilogramos" << std::endl;
    std::cout << "- Altura: " << p1.altura << " metros" << std::endl << std::endl;

    std::cout << "Paciente 2:" << std::endl;
    std::cout << "- Nombre: " << p2.nombre << std::endl;
    std::cout << "- Edad: " << p2.edad << " años" << std::endl;
    std::cout << "- Peso: " << p2.peso << " kilogramos" << std::endl;
    std::cout << "- Altura: " << p2.altura << " metros" << std::endl << std::endl;

    std::cout << "Paciente 3:" << std::endl;
    std::cout << "- Nombre: " << p3.nombre << std::endl;
    std::cout << "- Edad: " << p3.edad << " años" << std::endl;
    std::cout << "- Peso: " << p3.peso << " kilogramos" << std::endl;
    std::cout << "- Altura: " << p3.altura << " metros" << std::endl;

    return 0;
}
