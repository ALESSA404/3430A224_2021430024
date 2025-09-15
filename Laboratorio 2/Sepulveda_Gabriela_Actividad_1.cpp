// Programa: Actividad 1 - Pila de datos
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementar una pila utilizando un arreglo estático. El usuario puede definir el tamaño máximo de la pila, agregar elementos, retirar elementos y mostrar el estado actual de la pila. 

#include <iostream>
#include <string>
using namespace std;

// Definimos la estructura Pila (con atributos como capacidad máxima, indice, bandera y arreglo estático que almacena los elementos).
struct Pila {
    int MAX;          
    int TOPE;         
    bool BAND;        
    string datos[100]; 

    // Se verifica si la pila está vacía, y devuelve un true en caso de que no existan elementos.
    bool Pila_vacia(int TOPE, bool &BAND) {
        BAND = (TOPE == 0); 
        return BAND;
    }

    // Se verifica si la pila está llena, y devuelve un true si ya alcanzó su máximo.
    bool Pila_llena(int TOPE, int MAX, bool &BAND) {
        BAND = (TOPE == MAX); 
        return BAND;
    }

    // Se inserta un elemento en la pila (push), donde revisamos si existe espacio y dependiedo de aquello, entregamos un mensaje.
    void Push(bool &BAND, int &TOPE, int MAX, string datos[], string DATO) {
        Pila_llena(TOPE, MAX, BAND); 
        if (BAND) {
            cout << "No existe espacio, pila llena\n";
        } else {
            TOPE++;              
            datos[TOPE] = DATO;  
            cout << "Agregado: \"" << DATO << "\"\n";
        }
    }

    // Se retira un elemento de la pila (pop), donde revisamos si hay elementos, guardamos y reducimos el tope.
    string Pop(string datos[], int &TOPE, bool &BAND) {
        Pila_vacia(TOPE, BAND); 
        if (BAND) {
            cout << "Subdesbordamiento, pila vacía\n";
            return "";
        } else {
            string DATO = datos[TOPE]; 
            TOPE--;                    
            cout << "Retirado: \"" << DATO << "\"\n";
            return DATO;
        }
    }

    // Se muestra todos los elementos de la pila en la terminal.
    void Mostrar(string datos[], int TOPE) {
        if (TOPE == 0) {
            cout << "La pila está vacía.\n";
        } else {
            cout << "Contenido de la pila (tope → base):\n";
            for (int i = TOPE; i >= 1; i--) {
                cout << "- " << datos[i] << "\n";
            }
        }
    }
};

int main() {
    Pila pila;
    pila.TOPE = 0;     
    pila.BAND = false; 

    // Se le pide al usuario que ingrese la caapcidad máxima de la pila.
    cout << "Ingrese el tamaño máximo de la pila (<=100): ";
    cin >> pila.MAX;

    int opcion;
    string dato;
    do {
        // Se realiza un menú interactivo para el usuario.
        cout << "\nMenu:\n";
        cout << "1. Push (Agregar elemento)\n";
        cout << "2. Pop (Retirar elemento)\n";
        cout << "3. Mostrar pila\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: // Se agrega un elemento.
                cout << "Ingrese el dato a agregar: ";
                cin.ignore();          // Limpiamos buffer.
                getline(cin, dato);    // Capturamos la cadena.
                pila.Push(pila.BAND, pila.TOPE, pila.MAX, pila.datos, dato);
                break;
            case 2: // Se retira un elemento.
                pila.Pop(pila.datos, pila.TOPE, pila.BAND);
                break;
            case 3: // Se muestra al usuario la pila.
                pila.Mostrar(pila.datos, pila.TOPE);
                break;
            case 4: // Salir del programa.
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida, por favor reintentar.\n";
        }
    } while (opcion != 4); // Se repite el menú hasta que el usuario desee salir del programa.

    return 0;
}