// Programa: Ejercicio 1
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Crear un arreglo de pacientes con nombre, edad, peso y altura usando struct, y mostrar los datos en pantalla recorriendo el arreglo con un bucle.

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
    // Arreglo de pacientes, considerando nombre, peso y estatura.
    Paciente pacientes[3] = {
        {"Isidora González", 21, 56.3, 1.68},
        {"Leonardo Sepúlveda", 46, 93.2, 1.77},
        {"Javiera Medel", 25, 53.6, 1.62}
    };

    // Recorrer e imprimir cada paciente.
    for (int i = 0; i < 3; i++) {
        std::cout << "Paciente " << i + 1 << ":" << std::endl;
        std::cout << "- Nombre: " << pacientes[i].nombre << std::endl;
        std::cout << "- Edad: " << pacientes[i].edad << " años" << std::endl;
        std::cout << "- Peso: " << pacientes[i].peso << " kilogramos" << std::endl;
        std::cout << "- Altura: " << pacientes[i].altura << " metros" << std::endl << std::endl;
    }

    return 0;
}
