// Programa: Ejercicio 3
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Cálculo de promedios de edad, peso e IMC de cada paciente, usando listas.

#include <iostream>
#include <string>

// Definición de la estructura Paciente..
struct Paciente {
    std::string nombre;
    int edad;
    float peso;
    float altura;
    Paciente* siguiente; 
};

// Función que crea un nuevo paciente, considerando nombre, edad, peso y altura.
Paciente* crearPaciente(const std::string& nombre, int edad, float peso, float altura) {
    Paciente* nuevo = new Paciente;  
    nuevo->nombre = nombre;           
    nuevo->edad = edad;              
    nuevo->peso = peso;             
    nuevo->altura = altura;           
    nuevo->siguiente = NULL;          
    return nuevo;                     
}

// Función que agrega un paciente al final de la lista.
void agregarPaciente(Paciente*& cabeza, Paciente* nuevo) {
    if (cabeza == NULL) { 
        cabeza = nuevo;
    } 
    else { 
        Paciente* actual = cabeza;
        while (actual->siguiente != NULL) { 
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo; 
    }
}

void imprimirPacientesConIMC(Paciente* cabeza) {
    if (cabeza == NULL) {
        std::cout << "\nSin datos disponibles.\n";
        return;
    }

    std::cout << "\nPacientes:\n\n";
    Paciente* actual = cabeza;
    while (actual != NULL) {
        // Cálculo del IMC: peso / (altura * altura)
        float imc = actual->peso / (actual->altura * actual->altura);

        std::cout << "- Nombre: " << actual->nombre << std::endl;
        std::cout << "- Edad: " << actual->edad << " años" << std::endl;
        std::cout << "- Peso: " << actual->peso << " kilogramos" << std::endl;
        std::cout << "- Altura: " << actual->altura << " metros" << std::endl;
        std::cout << "- IMC: " << imc << "\n" << std::endl;

        actual = actual->siguiente;
    }
}

// Función para calcular promedio de edades y peso de los pacientes ingresados.
void calcularPromedios(Paciente* cabeza) {
    if (cabeza == NULL) {
        std::cout << "\nNo hay pacientes en la lista.\n";
        return;
    }

    int sumaEdades = 0;
    float sumaPesos = 0.0;
    int contador = 0;

    Paciente* actual = cabeza;
    while (actual != NULL) {
        sumaEdades += actual->edad;
        sumaPesos += actual->peso;
        contador++;                  
        actual = actual->siguiente;  
    }

    std::cout << "- Promedio de edades: " << (sumaEdades / (float)contador) << " años" << std::endl;
    std::cout << "- Promedio de pesos: " << (sumaPesos / contador) << " kg" << std::endl;
}

void liberarPacientes(Paciente* cabeza) {
    while (cabeza != NULL) {
        Paciente* siguiente = cabeza->siguiente;
        delete cabeza; 
        cabeza = siguiente; 
    }
}

int main() {
    Paciente* lista = NULL;

    // Creación y agregación de pacientes a la lista.
    agregarPaciente(lista, crearPaciente("Isidora González", 21, 56.3, 1.68));
    agregarPaciente(lista, crearPaciente("Leonardo Sepúlveda", 46, 93.2, 1.77));
    agregarPaciente(lista, crearPaciente("Javiera Medel", 25, 53.6, 1.62));

    // Mostrar los pacientes de la lista, más el IMC.
    imprimirPacientesConIMC(lista);

    // Calcular y mostrar los promedios de edad y peso entre los pacientes ingresados.
    calcularPromedios(lista);

    // Liberación de memoria.
    liberarPacientes(lista);

    return 0;
}