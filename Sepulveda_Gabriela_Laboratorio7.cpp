// Programa: Laboratorio 7 - Algoritmo de Prim (Árbol de Expansión Mínimo)
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Implementa el algoritmo de Prim para obtener el árbol de costo mínimo (MST) a partir de una matriz de adyacencia NxN. 
// Muestra los pasos intermedios, el conjunto L y genera dos grafos con Graphviz: el grafo original y el MST resultante.

#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>
#include <cstdlib>

using namespace std;

const int INF = numeric_limits<int>::max() / 4;
const int MAX_NODOS = 26;

// Declaración de funciones a utilizar.
void leerMatriz(vector<vector<int>>& M, int N);
void imprimirMatriz(const vector<vector<int>>& M, int N);
void prim(const vector<vector<int>>& M, int N, char offset);
void generarGrafo(const vector<vector<int>>& M, int N, const string& nombreArchivo, char offset, bool mst);

// Función principal del programa.
int main() {
    int N;
    cout << "Ingrese N (numero de nodos, max " << MAX_NODOS << "): ";
    if (!(cin >> N) || N < 2 || N > MAX_NODOS) {
        cerr << "Error: N debe ser un entero entre 2 y " << MAX_NODOS << ".\n";
        return 1;
    }
    // Etiquetas de nodos, en este caso letras: a, b, c, ...
    char offset = 'a';

    cout << "Ingrese la matriz " << N << "x" << N << " (use -1 o 0 si no hay arista):\n";
    vector<vector<int>> M(N, vector<int>(N, -1));
    leerMatriz(M, N);

    cout << "\nMatriz ingresada:\n";
    imprimirMatriz(M, N);

    cout << "\n--- Ejecutando algoritmo de Prim ---\n";
    prim(M, N, offset);

    // Se genera el grafo original para su visualización.
    generarGrafo(M, N, "grafo_original.txt", offset, false);
    cout << "\nGrafo original generado (grafo_original.png)\n";

    return 0;
}

// Funciones auxiliares
// Se lee la matriz de adyacencia desde la terminal.
void leerMatriz(vector<vector<int>>& M, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int w;
            while (!(cin >> w)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida, reingrese M[" << i << "][" << j << "]: ";
            }
            M[i][j] = w;
        }
    }
}

// Se imprime la matriz de adyacencia formateada.
void imprimirMatriz(const vector<vector<int>>& M, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4);
            if (M[i][j] <= 0) cout << "-";
            else cout << M[i][j];
        }
        cout << "\n";
    }
}

// Se implementa el algoritmo de Prim para encontrar el MST.
void prim(const vector<vector<int>>& M, int N, char offset) {
    vector<int> key(N, INF);       // Costos mínimos
    vector<int> parent(N, -1);     // Predecesores
    vector<bool> inMST(N, false);  // Nodos ya incluidos
    vector<vector<int>> mst(N, vector<int>(N, -1)); // Matriz del MST

    key[0] = 0; // Se comienza desde el nodo 'a'.

    cout << "\nNodo inicial: a\n";

    for (int count = 0; count < N - 1; ++count) {
        // Se selecciona el nodo con la clave mínima que no está en el MST.
        int u = -1;
        int minKey = INF;
        for (int v = 0; v < N; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break; 

        inMST[u] = true;
        cout << "\n> Nodo agregado al MST: " << char(offset + u) << "\n";

        // Actualiza las claves de los nodos adyacentes.
        for (int v = 0; v < N; ++v) {
            int peso = M[u][v];
            if (peso > 0 && !inMST[v] && peso < key[v]) {
                parent[v] = u;
                key[v] = peso;
            }
        }

        // Se muestra el estado actual del conjunto L (nodos en el MST).
        cout << "L = { ";
        for (int i = 0; i < N; ++i)
            if (inMST[i]) cout << char(offset + i) << " ";
        cout << "}\n";
    }

    // Construcción de la matriz del MST resultante.
    for (int i = 1; i < N; ++i) {
        if (parent[i] != -1) {
            int u = parent[i];
            int v = i;
            mst[u][v] = mst[v][u] = M[u][v];
        }
    }

    cout << "\n- Arbol de costo mínimo (MST) -\n";
    imprimirMatriz(mst, N);

    // Generar archivo DOT para el MST.
    generarGrafo(mst, N, "grafo_mst.txt", offset, true);
    cout << "\nGrafo MST generado (grafo_mst.png)\n";
}

// Se genera el grafo en formato DOT (para Graphviz).
void generarGrafo(const vector<vector<int>>& M, int N, const string& nombreArchivo, char offset, bool mst) {
    ofstream fp(nombreArchivo);
    if (!fp.is_open()) {
        cerr << "Error al crear archivo DOT.\n";
        return;
    }

    fp << "graph G {\n";
    fp << "  node [style=filled fillcolor=\"#ffd6e7\" shape=circle];\n"; // color rosita 💗
    fp << "  edge [color=" << (mst ? "deeppink" : "gray") << " penwidth=" << (mst ? "2.0" : "1.0") << "];\n";

    // Nodos del grafo.
    for (int i = 0; i < N; ++i) {
        char name = offset + i;
        fp << "  " << name << " [label=\"" << name << "\"];\n";
    }

    // Aristas con pesos.
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            int w = M[i][j];
            if (w > 0) {
                fp << "  " << char(offset + i) << " -- " << char(offset + j)
                   << " [label=\"" << w << "\"];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    // Se genera la imagen PNG usando Graphviz.
    string png = nombreArchivo.substr(0, nombreArchivo.find('.')) + ".png";
    string cmd = "dot -Tpng -o" + png + " " + nombreArchivo;
    int rc = system(cmd.c_str());
    if (rc != 0) cerr << "Advertencia: Graphviz no se ejecuto correctamente.\n";
}
