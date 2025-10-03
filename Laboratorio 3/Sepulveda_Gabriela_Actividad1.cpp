// Programa: Actividad 1 - Implementación de una cola dinámica
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementación de una cola dinámica para gestionar estudiantes universitarios.

#include <iostream>
#include <string>
using namespace std;

// Se define la estructura Nodo, en donde consideramos nombre del estudiante, carrera, promedio y un puntero hacia el siguiente nodo.

struct Nodo {
    string nombre;
    string carrera;
    float promedio;
    Nodo* siguiente;
};

// Se crea la función "universitario", que inserta un nuevo estudiante al final de la cola.
// También se consideran los parámetros inicio, fin, y los datos del estudiante a insertar.

void universitario(Nodo*& inicio, Nodo*& fin, string nombre, string carrera, float promedio) {

    //Creación de un nuevo Nodo, donde asignamos datos y lo consideramos como el último de la cola.
    Nodo* nuevo = new Nodo();         // se crea un nuevo nodo dinámicamente
    nuevo->nombre = nombre;           // se asignan los datos al nodo
    nuevo->carrera = carrera;
    nuevo->promedio = promedio;
    nuevo->siguiente = nullptr;       

    // En el caso de que la cola esté vacía, incio y fin apuntan al nuevo Nodo.
    // En el caso de que ya exista un elemento en la cola, el último apntará al nuevo, y el parámetro fin se actualizará.

    if (inicio == nullptr) {          
        inicio = fin = nuevo;         
    } 
    else {                          
        fin->siguiente = nuevo;      
        fin = nuevo;                  
    }
    cout << "Estudiante " << nombre << " ingresado a la cola con éxito.\n";
}

// Se crea la función desencolar, la cual elimina al estudiante que esté en el inicio de la cola.
// Se consideran los parámetros de inicio, fin y los datos que se le solicitan al estudiante.

bool desencolar(Nodo*& inicio, Nodo*& fin, string& nombre, string& carrera, float& promedio) {
    
    if (inicio == nullptr) return false;  
    Nodo* aux = inicio;                   
    nombre = aux->nombre;                 
    carrera = aux->carrera;
    promedio = aux->promedio;

    inicio = inicio->siguiente;           
    if (inicio == nullptr) fin = nullptr; 
    delete aux;                           
    return true;
}

// Se crea la función colaVacia, que ayuda a saber si la cola está vacía.

bool colaVacia(Nodo* inicio) {
    return inicio == nullptr;
}

// Se crea la función colaLlena, que ayuda a verificar si la cola está llena. 
// Hay que considerar que en una lista dinámica, la cola nunca se llena.

bool colaLlena() {
    return false;
}

// Se crea la función mostrarDatos, que nos muestra a todos los estudiantes de la cola, desde el inicio hasta el final.

void mostrarDatos(Nodo* inicio) {
    if (inicio == nullptr) {
        cout << "La cola está vacía.\n";
        return;
    }
    cout << "Datos actuales de la cola (inicio -> fin):\n";
    Nodo* actual = inicio;  
    int pos = 1;
    while (actual != nullptr) {
        cout << pos << ". " << actual->nombre
             << " | " << actual->carrera
             << " | Promedio: " << actual->promedio << endl;
        actual = actual->siguiente;  
        pos++;
    }
}

// Se crea la función liberarCola, que libera la memoria usada antes de la ejecución.

void liberarCola(Nodo*& inicio) {
    while (inicio!= nullptr) {
        Nodo* aux = inicio;
        inicio = inicio->siguiente;
        delete aux;
    }
}

// Función principal, que corresponde al menú interactivo con el usuario.
// 1. Insertar estudiante (encolar)
// 2. Eliminar estudiante (desencolar)
// 3. Mostrar toda la cola
// 4. Verificar si la cola está vacía
// 5. Verificar si la cola está llena
// 6. Salir del programa

int main() {
    Nodo* inicio = nullptr; 
    Nodo* fin = nullptr;
    int opcion;
    string nombre, carrera;
    float promedio;

    do {
        cout << "\n- MENÚ INTERACTIVO DE COLA DE ESTUDIANTES -\n";
        cout << "1. Encolar (Agregar estudiante al final)\n";
        cout << "2. Desencolar (Eliminar estudiante del inicio)\n";
        cout << "3. Mostrar cola\n";
        cout << "4. Consultar por Cola vacía\n";
        cout << "5. Consultar por Cola Llena\n";
        cout << "6. Salir de programa\n";
        cout << "\nSeleccione una opción: ";
        cin >> opcion;
        cin.ignore(); 

        switch (opcion) {
            case 1:
                cout << "Nombre: ";
                getline(cin, nombre);
                cout << "Carrera: ";
                getline(cin, carrera);
                cout << "Promedio: ";
                cin >> promedio;
                cin.ignore();
                universitario(inicio, fin, nombre, carrera, promedio);
                break;
            case 2:
                if (desencolar(inicio, fin, nombre, carrera, promedio)) {
                    cout << "Se desencoló a: "
                         << nombre << " | " << carrera
                         << " | Promedio: " << promedio << endl;
                } else {
                    cout << "La cola está vacía, no se puede desencolar.\n";
                }
                break;
            case 3:
                mostrarDatos(inicio);
                break;
            case 4:
                cout << (colaVacia(inicio) ? "La cola está vacía.\n" : "La cola no está vacía.\n");
                break;
            case 5:
                cout << (colaLlena() ? "La cola está llena.\n" : "La cola no está llena (lista dinámica).\n");
                break;
            case 6:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida, por favor intente de nuevo.\n";
        }
    } while (opcion != 6);

    liberarCola(inicio);
    fin = nullptr;

    return 0;
}