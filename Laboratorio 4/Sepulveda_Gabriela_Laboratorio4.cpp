// Programa: Árbol Binario de Búsqueda (sin duplicados) con visualización Graphviz
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementa un árbol binario de búsqueda con operaciones de inserción, eliminación, búsqueda y recorridos (preorden, inorden, posorden). 
// Además, genera un archivo DOT para visualizar el árbol usando Graphviz.

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <unordered_map>
#include <limits>

using namespace std;

// Estructura Nodo para el árbol binario
struct Nodo {
    int clave;
    Nodo* izquierdo;
    Nodo* derecho;
    Nodo(int k): clave(k), izquierdo(nullptr), derecho(nullptr) {}
};

// Se inserta un valor en el árbol; en este caso devuelve true si se insertó y false si ya existía.
bool insertarNodo(Nodo*& raiz, int val) {
    if (!raiz) {
        raiz = new Nodo(val);
        return true;
    }
    if (val < raiz->clave) return insertarNodo(raiz->derecho, val);
    if (val > raiz->clave) return insertarNodo(raiz->izquierdo, val);
    return false;
}

// Encuentra el mínimo de un subárbol (en eset caso se utiliza en la eliminación)
Nodo* minimo(Nodo* raiz) {
    while (raiz && raiz->izquierdo) raiz = raiz->izquierdo;
    return raiz;
}

// Se elimina un valor; en este caso devuelve true si se eliminó y false si no se encontró.
bool eliminarNodo(Nodo*& raiz, int val) {
    if (!raiz) return false;
    if (val < raiz->clave) return eliminarNodo(raiz->izquierdo, val);
    if (val > raiz->clave) return eliminarNodo(raiz->derecho, val);
    // Encontrado
    if (!raiz->izquierdo && !raiz->derecho) {
        delete raiz;
        raiz = nullptr;
        return true;
    }
    if (!raiz->izquierdo) {
        Nodo* tmp = raiz;
        raiz = raiz->derecho;
        delete tmp;
        return true;
    }
    if (!raiz->derecho) {
        Nodo* tmp = raiz;
        raiz = raiz->izquierdo;
        delete tmp;
        return true;
    }
    // Si tiene dos hijos, se reemplaza con el sucesor (mínimo del subárbol derecho).
    Nodo* succ = minimo(raiz->derecho);
    raiz->clave = succ->clave;
    return eliminarNodo(raiz->derecho, succ->clave);
}

// Se busca si un valor existe en el árbol, donde devuelve true si existe y false si no.
bool existe(Nodo* raiz, int val) {
    Nodo* cur = raiz;
    while (cur) {
        if (val < cur->clave) cur = cur->izquierdo;
        else if (val > cur->clave) cur = cur->derecho;
        else return true;
    }
    return false;
}

//Recorridos del árbol binario de búsqueda.

// Preorden: Raíz - Izquierdo - Derecho
void preorden(Nodo* raiz, vector<int>& salida) {
    if (!raiz) return;
    salida.push_back(raiz->clave);
    preorden(raiz->izquierdo, salida);
    preorden(raiz->derecho, salida);
}

// Inorden: Izquierdo - Raíz - Derecho
void inorden(Nodo* raiz, vector<int>& salida) {
    if (!raiz) return;
    inorden(raiz->izquierdo, salida);
    salida.push_back(raiz->clave);
    inorden(raiz->derecho, salida);
}

// Posorden: Izquierdo - Derecho - Raíz
void posorden(Nodo* raiz, vector<int>& salida) {
    if (!raiz) return;
    posorden(raiz->izquierdo, salida);
    posorden(raiz->derecho, salida);
    salida.push_back(raiz->clave);
}

// Funciones para generar el archivo DOT y visualizar el árbol con Graphviz.

// Se le asigna un id a cada nodo para referenciarlo en el archivo DOT.
void asignarIds(Nodo* nodo, unordered_map<Nodo*, string>& mapaIds, int &contador) {
    if (!nodo) return;
    mapaIds[nodo] = "n" + to_string(contador++);
    asignarIds(nodo->izquierdo, mapaIds, contador);
    asignarIds(nodo->derecho, mapaIds, contador);
}

// Escribe nodos y aristas en el archivo DOT, incluyendo nodos nulos.
void escribirGraphviz(Nodo* raiz, ofstream &ofs) {
    if (!raiz) return;
    unordered_map<Nodo*, string> mapaIds;
    int contadorIds = 1;
    asignarIds(raiz, mapaIds, contadorIds);

    int contadorNulos = 1;

    // Se declaran nodos con sus etiquetas.
    for (auto &p : mapaIds) {
        Nodo* nodo = p.first;
        const string &id = p.second;
        ofs << id << " [label=\"" << nodo->clave << "\", style=filled, fillcolor=pink];\n";
    }

    // Se escriben las aristas (incluyendo nodos nulos).
    for (auto &p : mapaIds) {
        Nodo* nodo = p.first;
        const string &id = p.second;
        // Se revisa el hijo izquierdo
        if (nodo->izquierdo) {
            ofs << id << " -> " << mapaIds[nodo->izquierdo] << ";\n";
        } else {
            string idNulo = "nulo" + to_string(contadorNulos++);
            ofs << idNulo << " [shape=point];\n";
            ofs << id << " -> " << idNulo << ";\n";
        }
        // Se revisa el hijo derecho
        if (nodo->derecho) {
            ofs << id << " -> " << mapaIds[nodo->derecho] << ";\n";
        } else {
            string idNulo = "nulo" + to_string(contadorNulos++);
            ofs << idNulo << " [shape=point];\n";
            ofs << id << " -> " << idNulo << ";\n";
        }
    }
}

// Se genera el archivo DOT completo (en este caso "grafo_final.txt").
bool generarDot(Nodo* raiz, const string& nombreArchivo = "grafo_final.txt") {
    ofstream ofs(nombreArchivo);
    if (!ofs.is_open()) {
        cerr << "Error: no se pudo crear el archivo " << nombreArchivo << "\n";
        return false;
    }
    ofs << "digraph G {\n";
    ofs << "  rankdir=TB;\n";
    ofs << "  node [style=filled fillcolor=pink];\n";
    escribirGraphviz(raiz, ofs);
    ofs << "}\n";
    ofs.close();
    return true;
}

// Se ejecuta un comando del sistema y se devuelve el código de retorno.
int ejecutarComando(const string &cmd) {
    int rc = system(cmd.c_str());
    return rc;
}

// Se genera el grafo y se intenta abrir la imagen resultante.
void generarYAbrirGrafo(Nodo* raiz) {
    if (!generarDot(raiz, "grafo.txt")) {
        cout << "No se pudo generar grafo.txt\n";
        return;
    }
    cout << "Ejecutando: dot -Tpng -ografo.png grafo.txt\n";
    int rc = ejecutarComando("dot -Tpng -ografo.png grafo.txt");
    if (rc != 0) {
        cerr << "Advertencia: comando 'dot' devolvió código " << rc << ". Verifique Graphviz.\n";
        return;
    }
    cout << "Imagen 'grafo.png' generada. Intentando abrir...\n";
    if (ejecutarComando("xdg-open grafo.png &") != 0) {
        ejecutarComando("eog grafo.png &");
    }
}

// Funcion de lectura de enteros con validación
int leerEntero(const string &mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            string resto;
            getline(cin, resto);
            return valor;
        }
        cout << "Entrada inválida. Ingrese un número entero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Funcion de lectura de respuesta sí/no con validación
bool leerSiNo(const string &mensaje) {
    string resp;
    while (true) {
        cout << mensaje;
        if (!(cin >> resp)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Responda 's' o 'n'.\n";
            continue;
        }
        char c = tolower(resp[0]);
        if (c == 's') return true;
        if (c == 'n') return false;
        cout << "Respuesta no reconocida. Ingrese 's' (sí) o 'n' (no).\n";
    }
}

// Funcion para imprimir una secuencia de enteros separados por guiones.
void imprimirSecuencia(const vector<int>& seq) {
    for (size_t i = 0; i < seq.size(); ++i) {
        cout << seq[i];
        if (i + 1 < seq.size()) cout << " - ";
    }
    cout << "\n";
}

// Se libera la memoria del árbol final.
void liberarArbol(Nodo* raiz) {
    if (!raiz) return;
    liberarArbol(raiz->izquierdo);
    liberarArbol(raiz->derecho);
    delete raiz;
}

// Se inserta un conjunto de ejemplo en el árbol.
void insertarEjemplo(Nodo*& raiz) {
    int ejemplo[] = {120, 87, 140, 43, 99, 130, 22, 65, 93, 135, 56};
    for (int v : ejemplo) insertarNodo(raiz, v);
    cout << "Conjunto ejemplo insertado.\n";
}

// Menú interactivo para el usuario.
int main() {
    Nodo* raiz = nullptr;
    bool ejecutando = true;

    while (ejecutando) {
        cout << "\n- MENÚ INTERACTIVO DE ÁRBOL BINARIO DE BÚSQUEDA -\n";
        cout << "1) Insertar número al árbol\n";
        cout << "2) Eliminar número del árbol\n";
        cout << "3) Modificar elemento existente\n";
        cout << "4) Mostrar recorridos del árbol (Preorden, Inorden, Posorden)\n";
        cout << "5) Generar grafo final y visualizar\n";
        cout << "6) Insertar conjunto ejemplo en el árbol\n";
        cout << "7) Eliminar árbol actual\n";
        cout << "8) Salir\n";

        int opcion = leerEntero("Elija una opción: ");

        switch (opcion) {
            case 1: {
                int v = leerEntero("Ingrese entero a insertar: ");
                if (insertarNodo(raiz, v)) cout << "Valor insertado: " << v << "\n";
                else cout << "No se insertó, el valor ya existe: " << v << "\n";
                break;
            }
            case 2: {
                int v = leerEntero("Ingrese entero a eliminar: ");
                if (eliminarNodo(raiz, v)) cout << "Valor eliminado: " << v << "\n";
                else cout << "No se encontró el valor: " << v << "\n";
                break;
            }
            case 3: {
                int viejo = leerEntero("Ingrese valor a modificar (valor viejo): ");
                int nuevo = leerEntero("Ingrese nuevo valor: ");
                if (viejo == nuevo) {
                    cout << "Los valores son iguales, intente con otro valor.\n";
                    break;
                }
                if (existe(raiz, nuevo)) {
                    cout << "No se puede modificar: el nuevo valor ya existe (" << nuevo << ").\n";
                    break;
                }
                if (!eliminarNodo(raiz, viejo)) {
                    cout << "No se encontró el valor viejo: " << viejo << "\n";
                    break;
                }
                insertarNodo(raiz, nuevo);
                cout << "Modificación: " << viejo << " -> " << nuevo << "\n";
                break;
            }
            case 4: {
                vector<int> pre, in, post;
                preorden(raiz, pre);
                inorden(raiz, in);
                posorden(raiz, post);
                cout << "\n-- Preorden --\n";
                imprimirSecuencia(pre);
                cout << "-- Inorden --\n";
                imprimirSecuencia(in);
                cout << "-- Posorden --\n";
                imprimirSecuencia(post);
                break;
            }
            case 5: {
                if (!raiz) {
                    cout << "Árbol vacío. Inserte elementos antes de generar el grafo.\n";
                } else {
                    generarYAbrirGrafo(raiz);
                }
                break;
            }
            case 6:
                insertarEjemplo(raiz);
                break;
            case 7:
                if (raiz) {
                    liberarArbol(raiz);
                    raiz = nullptr;
                    cout << "Árbol eliminado.\n";
                } else cout << "No hay árbol para eliminar.\n";
                break;
            case 8:
                ejecutando = false;
                break;
            default:
                cout << "Opción no válida.\n";
        }
    }

    liberarArbol(raiz);
    cout << "Programa terminado.\n";
    return 0;
}