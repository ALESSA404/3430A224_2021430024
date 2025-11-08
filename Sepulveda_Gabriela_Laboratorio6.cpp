// Programa: Laboratorio 6 - Algoritmo de Dijkstra con pasos intermedios
// Autora: Gabriela Antonia Sepúlveda Rojas
// Descripción: Este programa implementa el algoritmo de Dijkstra para encontrar las rutas más cortas desde un nodo origen hacia todos los demás
// en un grafo. Muestra los pasos intermedios (conjuntos S, VS y vector de distancias D[]) y genera una visualización del grafo usando Graphviz.

// Entradas: N (número de nodos, máximo 26), nodo origen (letra entre 'a' y 'a'+N-1), matriz de adyacencia NxN (-1 indica ausencia de arista)
// Salidas: Distancias mínimas desde el nodo origen, archivo grafo.txt y su versión grafo.png (visualización del grafo).

#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int MAX_LETTERS = 26;
const int INF = numeric_limits<int>::max() / 4;

// Declaración de funciones.
void leer_matriz(vector<vector<int>>& M, int N);
void imprimir_matriz(const vector<vector<int>>& M, int N);
void imprimir_distancias(const vector<int>& D, int N, char offset);
void imprimir_conjunto(const vector<char>& conjunto, const string& nombre);
void dijkstra_con_pasos(const vector<vector<int>>& M, int N, int src, vector<int>& D, char offset);
void generar_grafo(const vector<vector<int>>& M, int N, char offset);

// Función principal
int main() {
    int N;
    cout << "Ingrese N (numero de nodos, max " << MAX_LETTERS << "): ";
    if (!(cin >> N)) {
        cerr << "Entrada invalida para N.\n";
        return 1;
    }
    if (N <= 0 || N > MAX_LETTERS) {
        cerr << "N debe estar entre 1 y " << MAX_LETTERS << ".\n";
        return 1;
    }

    char offset = 'a';
    cout << "Ingrese el nodo origen (letra entre " << offset << " y " << char(offset + N - 1) << "): ";
    string origen_s;
    cin >> origen_s;

    // Validación del nodo de origen.
    if (origen_s.size() != 1 || origen_s[0] < offset || origen_s[0] >= offset + N) {
        cerr << "Nodo origen invalido.\n";
        return 1;
    }
    int src = origen_s[0] - offset;

    cout << "Ingrese la matriz " << N << "x" << N << " (use -1 para representar ausencia de arista):\n";
    vector<vector<int>> M(N, vector<int>(N, -1));
    leer_matriz(M, N);

    cout << "\nMatriz ingresada:\n";
    imprimir_matriz(M, N);

    // Vector de distancias mínimas.
    vector<int> D(N, INF);
    dijkstra_con_pasos(M, N, src, D, offset);

    cout << "\nResultado final (distancias desde " << origen_s << "):\n";
    imprimir_distancias(D, N, offset);

    // Generación del grafo en formato Graphviz.
    generar_grafo(M, N, offset);
    cout << "\nSe generó el grafo correctamente.\n";

    return 0;
}

// Lee los valores de la matriz de adyacencia desde la entrada
void leer_matriz(vector<vector<int>>& M, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int w;
            while (!(cin >> w)) {
                cin.clear();
                string basura;
                getline(cin, basura);
                cout << "Entrada invalida, intente nuevamente M[" << i << "][" << j << "]: ";
            }
            M[i][j] = w;
        }
    }
}

// Imprime la matriz con su respectivo formato.
void imprimir_matriz(const vector<vector<int>>& M, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << setw(4) << M[i][j] << " ";
        }
        cout << "\n";
    }
}

// Imprime las distancias actuales a cada nodo.
void imprimir_distancias(const vector<int>& D, int N, char offset) {
    for (int i = 0; i < N; ++i) {
        cout << offset + i << ": ";
        if (D[i] == INF) cout << "INF";
        else cout << D[i];
        if (i + 1 < N) cout << "   ";
    }
    cout << "\n";
}

// Muestra los conjuntos S y VS.
void imprimir_conjunto(const vector<char>& conjunto, const string& nombre) {
    cout << nombre << " = { ";
    for (char c : conjunto) {
        if (c == ' ') break;
        cout << c << " ";
    }
    cout << "}\n";
}

// Implementación de Dijkstra con pasos intermedios, mostrando S, VS y D[].
void dijkstra_con_pasos(const vector<vector<int>>& M, int N, int src, vector<int>& D, char offset) {
    vector<bool> visited(N, false);
    vector<char> S(N, ' ');   
    vector<char> VS(N, ' ');  

    // Se inicializan las distancias desde el nodo origen
    for (int i = 0; i < N; ++i) D[i] = INF;
    D[src] = 0;
    for (int j = 0; j < N; ++j) {
        if (M[src][j] >= 0) D[j] = M[src][j];
    }

    // Estado inicial del algoritmo
    cout << "\n- Estado inicial -\n";
    imprimir_matriz(M, N);
    cout << "\n";
    imprimir_conjunto(S, "S");

    // Se llena VS con todos los nodos, excepto el origen
    for (int i = 0, k = 0; i < N; ++i) {
        if (i != src) VS[k++] = offset + i;
    }
    imprimir_conjunto(VS, "VS");
    cout << "D[] inicial:\n";
    imprimir_distancias(D, N, offset);
    cout << "- Fin del estado inicial -\n";

    // Se le agrega el nodo origen a S
    S[0] = offset + src;
    {
        vector<char> tmp;
        for (int i = 0; i < N; ++i) {
            char c = offset + i;
            if (c == offset + src) continue;
            tmp.push_back(c);
        }
        fill(VS.begin(), VS.end(), ' ');
        for (size_t k = 0; k < tmp.size(); ++k) VS[k] = tmp[k];
    }

    cout << "\n> Agregado " << char(offset + src) << " a S\n";
    imprimir_conjunto(S, "S");
    imprimir_conjunto(VS, "VS");
    cout << "D[]:\n"; imprimir_distancias(D, N, offset);

    // Bucle principal del algoritmo, iterando N-1 veces
    for (int iter = 1; iter < N; ++iter) {
        // Se elige el vértice con la distancia mínima en VS
        int bestIdx = -1;
        int bestVal = INF;
        for (int i = 0; i < N; ++i) {
            char c = offset + i;
            bool inVS = false;
            for (char x : VS) { if (x == ' ') break; if (x == c) { inVS = true; break; } }
            if (!inVS) continue;
            if (D[i] != INF && D[i] != 0) {
                if (D[i] < bestVal) { bestVal = D[i]; bestIdx = i; }
            }
        }

        if (bestIdx == -1) {
            cout << "\nSin vértices alcanzables. Fin del algoritmo.\n";
            break;
        }

        char chosen = offset + bestIdx;
        cout << "\n> Iter " << iter << ": elige vértice " << chosen << " con D = " << D[bestIdx] << "\n";

        // Se agrega el vértice elegido a S
        for (int k = 0; k < N; ++k) {
            if (S[k] == ' ') { S[k] = chosen; break; }
        }

        // Se elimina el vértice elegido de VS
        {
            vector<char> tmp;
            for (char c : VS) { if (c == ' ') break; if (c != chosen) tmp.push_back(c); }
            fill(VS.begin(), VS.end(), ' ');
            for (size_t k = 0; k < tmp.size(); ++k) VS[k] = tmp[k];
        }

        imprimir_conjunto(S, "S");
        imprimir_conjunto(VS, "VS");

        // Se actualizan las distancias D[], considerando el vértice elegido
        int idx_v = bestIdx;
        cout << "> Actualizando distancias usando v = " << chosen << "\n";
        for (int w = 0; w < N; ++w) {
            if (M[idx_v][w] >= 0) {
                int old = D[w];
                int candidate = (D[idx_v] == INF) ? INF : D[idx_v] + M[idx_v][w];
                int newd = (old == INF) ? candidate : min(old, candidate);

                if (newd != old) {
                    cout << "D[" << char(offset + w) << "] cambia: ";
                    if (old == INF) cout << "INF"; else cout << old;
                    cout << " -> " << newd << " (por " << chosen << " + " << M[idx_v][w] << ")\n";
                }
                D[w] = newd;
            }
        }

        cout << "D[] ahora: "; imprimir_distancias(D, N, offset);
    }
}

// Se genera el archivo grafo.txt y su versión grafo.png, usando Graphviz.
void generar_grafo(const vector<vector<int>>& M, int N, char offset) {
    ofstream fp("grafo.txt");
    if (!fp.is_open()) {
        cerr << "Error, no se pudo crear grafo.txt\n";
        return;
    }

    fp << "digraph G {\n";
    fp << "  graph [rankdir=LR];\n";
    fp << "  node [style=filled fillcolor=\"#ffd6e7\" shape=circle];\n";

    // Se definen los nodos, etiquetados con letras
    for (int i = 0; i < N; ++i) {
        char name = offset + i;
        fp << "  " << name << " [label=\"" << name << "\"];\n";
    }

    // Se definen las aristas con sus respectivos pesos
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            int w = M[i][j];
            if (w >= 0) {
                fp << "  " << char(offset + i) << " -> " << char(offset + j)
                   << " [label=\"" << w << "\"];\n";
            }
        }
    }

    fp << "}\n";
    fp.close();

    int rc = system("dot -Tpng -ografo.png grafo.txt");
    if (rc != 0) {
        cout << "AVISO: Graphviz devolvió código " << rc << ". Verifique instalación.\n";
    } else {
        cout << "grafo.png generado correctamente.\n";
        system("eog grafo.png &");
    }
}