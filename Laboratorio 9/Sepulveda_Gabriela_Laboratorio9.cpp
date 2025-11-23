// Programa: Laboratorio 9 - Tablas Hash con Manejo de Colisiones
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Este programa implementa una tabla hash de tamaño fijo (20), utilizando 4 métodos de manejo de colisiones:
// Lineal (L), Cuadrático (C), Doble hashing (D) y Encadenamiento separado (E).
// El usuario selecciona el método al inicio. Luego, a través de un menú, podrá insertar números,
// buscarlos, imprimir la tabla, cargar datos de ejemplo de la guía, vaciar la tabla o salir.

#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TAM = 20;

// Estructura Nodo, encargada de representar cada elemento en las listas enlazadas para el método de encadenamiento.
struct Nodo {
    int valor;
    Nodo* sig;
    Nodo(int v) : valor(v), sig(nullptr) {}
};

// Funciones hash, h1 y h2.
int h1(int k) {
    return k % TAM;
}

int h2(int k) {
    return 1 + (k % (TAM - 1));
}

// Función para imprimir la tabla en métodos lineales, cuadráticos y doble hashing.
void imprimir_tabla_lineal(const vector<int>& tabla) {
    cout << "\n- ESTADO DE LA TABLA (TAM = 20) -\n";
    for (int i = 0; i < TAM; i++) {
        cout << "Pos " << i << " | ";
        if (tabla[i] == -1)
            cout << "";
        else
            cout << tabla[i];
        cout << "\n";
    }
}

// Función para imprimir la tabla en el método de encadenamiento separado.
void imprimir_tabla_enc(const vector<Nodo*>& tabla) {
    cout << "\n- ESTADO DE LA TABLA (ENCADENAMIENTO Y TAM = 20) -\n";
    for (int i = 0; i < TAM; i++) {
        cout << "Pos " << i << " | ";
        Nodo* aux = tabla[i];
        while (aux != nullptr) {
            cout << aux->valor;
            if (aux->sig != nullptr) cout << " -> ";
            aux = aux->sig;
        }
        cout << "\n";
    }
}

// Método lineal.
// Función para insertar un elemento usando sondeo lineal, y función para buscar un elemento.
int insertar_L(int k, vector<int>& tabla) {
    int pos = h1(k);
    cout << "  h1 = " << pos << "\n";

    for (int i = 0; i < TAM; i++) {
        int p = (pos + i) % TAM;
        cout << "  intento " << i << ": pos " << p;

        if (tabla[p] == -1) {
            tabla[p] = k;
            cout << " -> insertado.\n";
            return p;
        } else {
            cout << " -> ocupado (" << tabla[p] << "). Colisión.\n";
        }
    }
    cout << "  Tabla llena, no se pudo insertar.\n";
    return -1;
}

bool buscar_L(int k, const vector<int>& tabla) {
    int pos = h1(k);

    for (int i = 0; i < TAM; i++) {
        int p = (pos + i) % TAM;

        if (tabla[p] == k) {
            cout << "  encontrado en pos " << p << "\n";
            return true;
        }
        if (tabla[p] == -1) {
            cout << "  casillero vacío -> no existe\n";
            return false;
        }
    }
    cout << "  no encontrado.\n";
    return false;
}

// Método cuadrático.
// Función para insertar un elemento usando sondeo cuadrático, y función para buscar un elemento.
int insertar_C(int k, vector<int>& tabla) {
    int base = h1(k);
    cout << "  h1 = " << base << "\n";

    for (int i = 0; i < TAM; i++) {
        int p = (base + i * i) % TAM;
        cout << "  intento " << i << ": pos " << p;

        if (tabla[p] == -1) {
            tabla[p] = k;
            cout << " -> insertado.\n";
            return p;
        } else {
            cout << " -> ocupado (" << tabla[p] << "). Colisión.\n";
        }
    }
    cout << "  Tabla llena.\n";
    return -1;
}

bool buscar_C(int k, const vector<int>& tabla) {
    int base = h1(k);

    for (int i = 0; i < TAM; i++) {
        int p = (base + i * i) % TAM;

        if (tabla[p] == k) {
            cout << "  encontrado en pos " << p << "\n";
            return true;
        }
        if (tabla[p] == -1) {
            cout << "  casillero vacío -> no existe\n";
            return false;
        }
    }
    cout << "  no encontrado.\n";
    return false;
}

// Método de doble hashing.
// Función para insertar un elemento usando doble hashing, y función para buscar un elemento.
int insertar_D(int k, vector<int>& tabla) {
    int p1 = h1(k);
    int p2 = h2(k);

    cout << "  h1 = " << p1 << "   h2 = " << p2 << "\n";

    for (int i = 0; i < TAM; i++) {
        int p = (p1 + i * p2) % TAM;
        cout << "  intento " << i << ": posición " << p;

        if (tabla[p] == -1) {
            tabla[p] = k;
            cout << " -> insertado.\n";
            return p;
        }
        cout << " -> ocupado (" << tabla[p] << "). Colisión.\n";
    }

    cout << "  Tabla llena.\n";
    return -1;
}

bool buscar_D(int k, const vector<int>& tabla) {
    int p1 = h1(k);
    int p2 = h2(k);

    for (int i = 0; i < TAM; i++) {
        int p = (p1 + i * p2) % TAM;

        if (tabla[p] == k) {
            cout << "  encontrado en pos " << p << "\n";
            return true;
        }
        if (tabla[p] == -1) {
            cout << "  casillero vacío -> no existe\n";
            return false;
        }
    }
    cout << "  no encontrado.\n";
    return false;
}

// Método de encadenamiento separado.
// Función para insertar un elemento usando encadenamiento separado, y función para buscar un elemento.
int insertar_E(int k, vector<Nodo*>& tabla) {
    int pos = h1(k);
    cout << "  h1 = " << pos << "\n";

    Nodo* nuevo = new Nodo(k);
    nuevo->sig = tabla[pos];
    tabla[pos] = nuevo;

    cout << "  Insertado en lista de pos " << pos << "\n";
    return pos;
}

bool buscar_E(int k, const vector<Nodo*>& tabla) {
    int pos = h1(k);

    Nodo* aux = tabla[pos];
    while (aux != nullptr) {
        if (aux->valor == k) {
            cout << "  encontrado en pos " << pos << "\n";
            return true;
        }
        aux = aux->sig;
    }

    cout << "  no encontrado en la lista.\n";
    return false;
}

// Datos del ejemplo de la guía del laboratorio N°9.
vector<int> datos_guia = {
    23, 42, 5, 66, 14, 43, 59, 81,
    37, 49, 28, 55, 94, 80, 64
};

// Función principal.
int main(int argc, char** argv) {
    cout << "Laboratorio 9 - Tablas Hash\n";
    cout << "Tamaño fijo: 20\n\n";

    if (argc < 2) {
        cout << "Uso del programa:\n   ./Sepulveda_Gabriela_Laboratorio9 L|C|D|E\n";
        return 0;
    }

    char metodo = toupper(argv[1][0]);
    if (metodo != 'L' && metodo != 'C' && metodo != 'D' && metodo != 'E') {
        cout << "Método inválido.\n";
        return 0;
    }

    // Estructuras según método, inicializadas vacías.
    vector<int> tabla(TAM, -1);
    vector<Nodo*> tablaE(TAM, nullptr);

    int op, x;

    while (true) {
        cout << "\n- MENU INTERACTIVO -\n";
        cout << "1) Insertar número\n";
        cout << "2) Buscar número\n";
        cout << "3) Imprimir tabla\n";
        cout << "4) Insertar datos de ejemplo de la guía\n";
        cout << "5) Vaciar tabla\n";
        cout << "6) Salir del programa\n";
        cout << "Seleccione una opción: ";
        cin >> op;

        if (op == 6) break;

        switch (op) {
            case 1:
                cout << "Ingrese número a insertar: ";
                cin >> x;
                cout << "Insertando " << x << "\n";

                if (metodo == 'L') insertar_L(x, tabla);
                if (metodo == 'C') insertar_C(x, tabla);
                if (metodo == 'D') insertar_D(x, tabla);
                if (metodo == 'E') insertar_E(x, tablaE);
                break;

            case 2:
                cout << "Ingrese número a buscar: ";
                cin >> x;

                if (metodo == 'L') buscar_L(x, tabla);
                if (metodo == 'C') buscar_C(x, tabla);
                if (metodo == 'D') buscar_D(x, tabla);
                if (metodo == 'E') buscar_E(x, tablaE);
                break;

            case 3:
                if (metodo == 'E') imprimir_tabla_enc(tablaE);
                else imprimir_tabla_lineal(tabla);
                break;

            case 4:
                cout << "Cargando datos de la guía...\n";
                for (int v : datos_guia) {
                    cout << "\nInsertando " << v << "...\n";
                    if (metodo == 'L') insertar_L(v, tabla);
                    if (metodo == 'C') insertar_C(v, tabla);
                    if (metodo == 'D') insertar_D(v, tabla);
                    if (metodo == 'E') insertar_E(v, tablaE);
                }
                break;

            case 5:
                tabla.assign(TAM, -1);
                for (auto& ptr : tablaE) ptr = nullptr;
                cout << "Tabla reiniciada.\n";
                break;

            default:
                cout << "Opción inválida, intente nuevamente.\n";
        }
    }

    return 0;
}
