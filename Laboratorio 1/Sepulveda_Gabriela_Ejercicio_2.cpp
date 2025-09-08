// Programa: Ejercicio 2
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementación de una lista enlazada simple de pacientes usando punteros.

#include <iostream>
#include <string>

// Definición de la estructura Paciente.
struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* siguiente;
};

// Función para crear un nuevo paciente,
Paciente* crearPaciente(const std::string& nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente; 
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Función para agregar paciente.
void agregarPaciente(Paciente*& cabeza, Paciente* nuevo) {
    if (cabeza == nullptr) {
        cabeza = nuevo; 
    } else {
        Paciente* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Función para imprimir la lista de pacientes.
void imprimirPacientes(Paciente* cabeza) {
    std::cout << "\nPacientes:\n\n";
    Paciente* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "- Nombre: " << actual->nombre << std::endl;
        std::cout << "- Edad: " << actual->edad << " años" << std::endl;
        std::cout << "- Peso: " << actual->peso << " kilogramos" << std::endl;
        std::cout << "- Altura: " << actual->altura << " metros \n" << std::endl;
        actual = actual->siguiente; 
    }
}

// Función para la liberación de memoria.
void liberarPacientes(Paciente* cabeza) {
    Paciente* actual = cabeza;
    while (actual != nullptr) {
        Paciente* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
}

int main() {
    Paciente* lista = nullptr;

    // Agregación y creación de los 3 pacientes principales.
    agregarPaciente(lista, crearPaciente("Isidora González", 21, 56.3, 1.68));
    agregarPaciente(lista, crearPaciente("Leonardo Sepúlveda", 46, 93.2, 1.77));
    agregarPaciente(lista, crearPaciente("Javiera Medel", 25, 53.6, 1.62));

    // Llamada a la lista de pacientes.
    imprimirPacientes(lista);

    // Liberación de memoria.
    liberarPacientes(lista);

    return 0;
}
