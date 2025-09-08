// Programa: Ejercicio 4
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Sistema para la gestión de pacientes usando listas (menú, promedio, IMC y carga de archivos CSV).

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Creación de estructura Paciente, junto a sus parámetros.
struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* siguiente;
};

// Creación de un nuevo paciente.
Paciente* crearPaciente(const std::string& nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente;
    nuevo->nombre = nombre;
    nuevo->edad = edad;
    nuevo->peso = peso;
    nuevo->altura = altura;
    nuevo->siguiente = NULL;
    return nuevo;
}

void agregarPaciente(Paciente*& cabeza, Paciente* nuevo) {
    if (cabeza == NULL) {
        cabeza = nuevo;
    } else {
        Paciente* actual = cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

// Imprimir todos los pacientes, junto a su IMC.
void imprimirPacientes(Paciente* cabeza) {
    if (cabeza == NULL) {
        std::cout << "\nSin datos disponibles.\n";
        return;
    }

    std::cout << "\nPacientes:\n";
    Paciente* actual = cabeza;
    while (actual != NULL) {
        float imc = actual->peso / (actual->altura * actual->altura);
        std::cout << "- Nombre: " << actual->nombre << std::endl;
        std::cout << "- Edad: " << actual->edad << " años" << std::endl;
        std::cout << "- Peso: " << actual->peso << " kg" << std::endl;
        std::cout << "- Altura: " << actual->altura << " m" << std::endl;
        std::cout << "- IMC: " << imc << "\n" << std::endl;
        
        actual = actual->siguiente;
    }
}

// Calcular promedios de edad y peso de los pacientes ingresados.
void calcularPromedios(Paciente* cabeza) {
    if (cabeza == NULL) {
        std::cout << "\nSin datos disponibles.\n";
        return;
    }

    int sumaEdades = 0, contador = 0;
    float sumaPesos = 0.0;

    Paciente* actual = cabeza;
    while (actual != NULL) {
        sumaEdades += actual->edad;
        sumaPesos += actual->peso;
        contador++;
        actual = actual->siguiente;
    }

    std::cout << "\nPromedio de edades: " << (sumaEdades / (float)contador) << " años" << std::endl;
    std::cout << "Promedio de pesos: " << (sumaPesos / contador) << " kg" << std::endl;
}

// Eliminar paciente por nombre.
void eliminarPaciente(Paciente*& cabeza, const std::string& nombre) {
    if (cabeza == NULL) return;

    if (cabeza->nombre == nombre) {
        Paciente* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        std::cout << "Paciente eliminado.\n";
        return;
    }

    Paciente* actual = cabeza;
    while (actual->siguiente != NULL && actual->siguiente->nombre != nombre) {
        actual = actual->siguiente;
    }

    if (actual->siguiente != NULL) {
        Paciente* temp = actual->siguiente;
        actual->siguiente = temp->siguiente;
        delete temp;
        std::cout << "Paciente eliminado correctamente.\n";
    } else {
        std::cout << "Paciente no encontrado.\n";
    }
}

// Cargar pacientes desde archivo CSV
void cargarDesdeArchivo(Paciente*& cabeza, const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo CSV.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string nombre;
        int edad;
        float peso, altura;

        std::getline(ss, nombre, ',');
        ss >> edad;
        ss.ignore();
        ss >> peso;
        ss.ignore();
        ss >> altura;

        agregarPaciente(cabeza, crearPaciente(nombre, edad, peso, altura));
    }

    archivo.close();
    std::cout << "Pacientes cargados correctamente desde archivo CSV.\n";
}

void liberarPacientes(Paciente* cabeza) {
    while (cabeza != NULL) {
        Paciente* siguiente = cabeza->siguiente;
        delete cabeza;
        cabeza = siguiente;
    }
}

// Menú interactivo de inicio.
void menu() {
    std::cout << "\n--- MENÚ DE GESTIÓN DE PACIENTES ---\n";
    std::cout << "1. Agregar nuevo paciente\n";
    std::cout << "2. Imprimir pacientes disponibles\n";
    std::cout << "3. Calcular promedios de peso y edad\n";
    std::cout << "4. Eliminar pacientes del sistema\n";
    std::cout << "5. Cargar pacientes desde archivo CSV\n";
    std::cout << "6. Salir del programa\n";
    std::cout << "Seleccione una opcion: ";
}

int main() {
    Paciente* lista = NULL;
    int opcion;

    do {
        menu();
        std::cin >> opcion;
        std::cin.ignore();

        if (opcion == 1) {
            std::string nombre;
            int edad;
            float peso, altura;
            std::cout << "Ingrese nombre: ";
            std::getline(std::cin, nombre);
            std::cout << "Ingrese edad: ";
            std::cin >> edad;
            std::cout << "Ingrese peso (en kilogramos): ";
            std::cin >> peso;
            std::cout << "Ingrese altura (en metros): ";
            std::cin >> altura;

            agregarPaciente(lista, crearPaciente(nombre, edad, peso, altura));
        }
        else if (opcion == 2) {
            imprimirPacientes(lista);
        }
        else if (opcion == 3) {
            calcularPromedios(lista);
        }
        else if (opcion == 4) {
            std::string nombre;
            std::cout << "Ingrese el nombre del paciente a eliminar del sistema: ";
            std::getline(std::cin, nombre);
            eliminarPaciente(lista, nombre);
        }
        else if (opcion == 5) {
            std::string archivo;
            std::cout << "Ingrese el nombre del archivo CSV: ";
            std::getline(std::cin, archivo);
            cargarDesdeArchivo(lista, archivo);
        }
    } while (opcion != 6);

    liberarPacientes(lista);
    return 0;
}
