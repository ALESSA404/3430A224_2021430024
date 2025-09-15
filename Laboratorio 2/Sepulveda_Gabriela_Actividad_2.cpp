// Programa: Actividad 2 - Patio de contenedores
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Simular un patio de contenedores representado por varias pilas. El programa recibe como parámetros de línea de comandos la altura máxima (n) y el número de pilas (m). 
// Permite agregar contenedores manual o automáticamente, retirar un contenedor por su ID (moviendo temporalmente los que estén encima) y mostrar el estado actual del patio.

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

// Se define la estructura Pila (similar a la actividad 1)
struct Pila {
    int MAX;                // Capacidad máxima de la pila
    int TOPE;               // Índice del último elemento (0 en el caso de que esté vacía)
    bool BAND;              // Bandera del estado
    string datos[101];      // Contenedores almacenados

    // Se verifica si la pila está vacía.
    bool Pila_vacia(int TOPE, bool &BAND) {
        BAND = (TOPE == 0);
        return BAND;
    }

    // Se verifica si la pila está llena.
    bool Pila_llena(int TOPE, int MAX, bool &BAND) {
        BAND = (TOPE == MAX);
        return BAND;
    }

    // Se inserta un contenedor en la pila (push).
    void Push(bool &BAND, int &TOPE, int MAX, string datos[], const string &DATO) {
        Pila_llena(TOPE, MAX, BAND);
        if (BAND) {
            cout << "No existe espacio, pila llena. No se pudo agregar " << DATO << ".\n";
        } else {
            TOPE++;
            datos[TOPE] = DATO;
            cout << "Agregado: \"" << DATO << "\" en la pila.\n";
        }
    }

    // Se retira el contenedor en el tope de la pila (pop).
    string Pop(string datos[], int &TOPE, bool &BAND) {
        Pila_vacia(TOPE, BAND);
        if (BAND) {
            cout << "Subdesbordamiento, pila vacía. No se pudo retirar.\n";
            return "";
        } else {
            string DATO = datos[TOPE];
            TOPE--;
            return DATO;
        }
    }

    // Se muestra todo el contenido de la pila en la terminal.
    void Mostrar(string datos[], int TOPE, int idx) {
        cout << "Pila " << idx << " (tope → base): ";
        if (TOPE == 0) {
            cout << "(vacía)";
        } else {
            for (int i = TOPE; i >= 1; i--) {
                cout << datos[i];
                if (i > 1) cout << " | ";
            }
        }
        cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    // Se valida que se reciban los parámetros solicitados (altura y número de pilas)
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <n> <m>\n";
        cerr << "  n = altura máxima por pila (<=100)\n";
        cerr << "  m = número de pilas (<=20)\n";
        return 1;
    }

    int n = stoi(argv[1]);  // Altura máxima por pila
    int m = stoi(argv[2]);  // Número de pilas

    // Se validan ambos rangos.
    if (n < 1 || n > 100 || m < 1 || m > 20) {
        cerr << "Valores inválidos: n debe estar en [1..100], m en [1..20].\n";
        return 1;
    }

    // Creacion del patio depilas, considerando el parámetro m.
    Pila patio[20];
    for (int i = 0; i < m; i++) {
        patio[i].MAX = n;
        patio[i].TOPE = 0;
        patio[i].BAND = false;
    }

    // Menú para la selección de modo de ingreso de los contenedores.
    int modo;
    cout << "Seleccione modo de ingreso de contenedores:\n";
    cout << "1. Automático (colocar en la primera pila disponible)\n";
    cout << "2. Manual (usuario indica la pila)\n";
    cout << "Opción: ";
    cin >> modo;
    cin.ignore();

    // Ingreso de contenedores ("fin" terminará el ciclo).
    cout << "Ingrese contenedores separados por espacio ('fin' para terminar):\n";
    string id;
    while (cin >> id && id != "fin") {
        if (modo == 1) {
            // Tipo automático: busca la primera pila con espacio.
            bool colocado = false;
            for (int i = 0; i < m; i++) {
                if (patio[i].TOPE < patio[i].MAX) {
                    patio[i].Push(patio[i].BAND, patio[i].TOPE, patio[i].MAX, patio[i].datos, id);
                    cout << " → Colocado en pila " << i << "\n";
                    colocado = true;
                    break;
                }
            }
            if (!colocado) cout << "No hay espacio para " << id << "\n";
        } else {
            // Tipo manual: el usuario elige en qué pila colocar el contenedor.
            int pilaIdx;
            cout << "Ingrese número de pila para " << id << " (0.." << m-1 << "): ";
            cin >> pilaIdx;
            if (pilaIdx < 0 || pilaIdx >= m) {
                cout << "Pila inválida, intente nuevamente.\n";
            } else {
                patio[pilaIdx].Push(patio[pilaIdx].BAND, patio[pilaIdx].TOPE,
                                    patio[pilaIdx].MAX, patio[pilaIdx].datos, id);
                cout << " → Colocado en pila " << pilaIdx << "\n";
            }
        }
    }
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Menú interactivo principal.
    int opcion;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar estado del patio de pilas\n";
        cout << "2. Agregar contenedor\n";
        cout << "3. Retirar contenedor por ID\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: { // Mostrar estado de todas las pilas disponibles.
                for (int i = 0; i < m; i++) {
                    patio[i].Mostrar(patio[i].datos, patio[i].TOPE, i);
                }
                break;
            }
            case 2: { // Agregar un contenedor al patio de pilas.
                cout << "Ingrese ID del contenedor: ";
                cin >> id;
                if (modo == 1) {
                    // Automático
                    bool colocado = false;
                    for (int i = 0; i < m; i++) {
                        if (patio[i].TOPE < patio[i].MAX) {
                            patio[i].Push(patio[i].BAND, patio[i].TOPE, patio[i].MAX, patio[i].datos, id);
                            cout << " → Colocado en pila " << i << "\n";
                            colocado = true;
                            break;
                        }
                    }
                    if (!colocado) cout << "No hay espacio disponible.\n";
                } else {
                    // Manual
                    int pilaIdx;
                    cout << "Ingrese número de pila (0.." << m-1 << "): ";
                    cin >> pilaIdx;
                    if (pilaIdx >= 0 && pilaIdx < m) {
                        patio[pilaIdx].Push(patio[pilaIdx].BAND, patio[pilaIdx].TOPE,
                                            patio[pilaIdx].MAX, patio[pilaIdx].datos, id);
                        cout << " → Colocado en pila " << pilaIdx << "\n";
                    } else {
                        cout << "Pila inválida, por favor reintentar.\n";
                    }
                }
                break;
            }
            case 3: { // Retirar un contenedor buscándolo por su ID.
                cout << "Ingrese ID del contenedor a retirar: ";
                cin >> id;

                bool encontrado = false;
                // Se busca el contenedor en cada pila.
                for (int i = 0; i < m; i++) {
                    for (int j = patio[i].TOPE; j >= 1; j--) {
                        if (patio[i].datos[j] == id) {
                            encontrado = true;
                            cout << "Contenedor " << id << " encontrado en pila " << i << ".\n";

                            // Se mueven temporalmente los contenedores que están encima.
                            while (patio[i].TOPE > j) {
                                string movido = patio[i].Pop(patio[i].datos, patio[i].TOPE, patio[i].BAND);
                                bool movidoOK = false;
                                for (int k = 0; k < m; k++) {
                                    if (k == i) continue; // Evitar mover a la misma pila.
                                    if (patio[k].TOPE < patio[k].MAX) {
                                        patio[k].Push(patio[k].BAND, patio[k].TOPE,
                                                      patio[k].MAX, patio[k].datos, movido);
                                        cout << " → Mover " << movido << " de pila " << i << " → pila " << k << "\n";
                                        movidoOK = true;
                                        break;
                                    }
                                }
                                if (!movidoOK) {
                                    cout << "No hay espacio para mover " << movido << ".\n";
                                    break;
                                }
                            }

                            // Cuando está despejado, se retira el contenedor indicado.
                            if (patio[i].TOPE == j) {
                                string retirado = patio[i].Pop(patio[i].datos, patio[i].TOPE, patio[i].BAND);
                                cout << "Retirado " << retirado << " de pila " << i << " con éxito.\n";
                            }
                            break;
                        }
                    }
                    if (encontrado) break;
                }
                if (!encontrado) cout << "Contenedor no encontrado, intente nuevamente.\n";
                break;
            }
            case 4: // Salir del programa
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción no válida, por favor reintentar.\n";
        }
    } while (opcion != 4); // El menú se repite hasta que el usuario decida salir

    return 0;
}