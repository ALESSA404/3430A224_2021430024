// Programa: Laboratorio 8 - Algoritmos de Ordenamiento Interno con Tiempos
// Nombre: Gabriela Antonia Sepúlveda Rojas
// Descripción: Programa que ordena un mismo conjunto de datos utilizando cinco algoritmos de ordenamiento interno (Burbuja, Inserción, Selección, Shellsort y Quicksort) y mide el tiempo que demora cada uno. 
// El usuario ingresa N y un parámetro VER; el programa genera un vector aleatorio, lo duplica para usar los mismos datos en todos los métodos, calcula los tiempos con chrono y, si VER = 's', muestra los vectores ordenados.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Función imprimir_vector: Encargada de imprimir el contenido de un vector, dado un título.
void imprimir_vector(const vector<int>& v, const string& titulo) {
    cout << titulo << " ";
    for (size_t i = 0; i < v.size(); i++) {
        cout << "a[" << i << "]=" << v[i] << " ";
    }
    cout << "\n";
}

// Función burbuja (bubble_sort): Encargada de implementar el algoritmo de ordenamiento por burbuja, comparando elementos adyacentes.
void bubble_sort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                swap(v[j], v[j + 1]);
            }
        }
    }
}

// Función inserción (insertion_sort): Encargada de implementar el algoritmo de ordenamiento por inserción, ubicando cada elemento en su posición correcta dentro de la parte ordenada del vector.
void insertion_sort(vector<int>& v) {
    int n = v.size();
    for (int i = 1; i < n; i++) {
        int key = v[i];
        int j = i - 1;

        // Busca dónde insertar la "key", desplazando elementos mayores hacia la derecha.
        while (j >= 0 && v[j] > key) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Función selección (selection_sort): Encargada de implementar el algoritmo de ordenamiento por selección, buscando el menor elemento en cada iteración y colocándolo en la posición correcta.
void selection_sort(vector<int>& v) {
    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        // Busca el menor desde i hacia adelante.
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min_index]) {
                min_index = j;
            }
        }

        swap(v[i], v[min_index]);
    }
}

// Función shellsort: Encargada de implementar el algoritmo de ordenamiento Shellsort, que mejora la inserción al permitir intercambios de elementos distantes.
void shellsort(vector<int>& v) {
    int n = v.size();
    // Se divide el vector por "gaps" que van disminuyendo.
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Inserción modificada según el gap.
        for (int i = gap; i < n; i++) {
            int temp = v[i];
            int j;

            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

// Función partición para Quicksort: Encargada de dividir el vector en dos partes según un pivote.
int partition_qs(vector<int>& v, int low, int high) {
    int pivot = v[high]; // pivote
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (v[j] < pivot) {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[high]);
    return i + 1;
}

// Función quicksort: Encargada de implementar el algoritmo de ordenamiento Quicksort, utilizando la función de partición.
void quicksort(vector<int>& v, int low, int high) {
    if (low < high) {
        int pi = partition_qs(v, low, high);
        quicksort(v, low, pi - 1);
        quicksort(v, pi + 1, high);
    }
}

// Se define una función genérica para medir el tiempo de ejecución de un algoritmo.
template<typename Func>
long long medir_tiempo(Func f, vector<int> v) {
    auto inicio = high_resolution_clock::now();
    f(v);
    auto fin = high_resolution_clock::now();

    return duration_cast<milliseconds>(fin - inicio).count();
}

// Programa principal, donde se ejecutan los pasos solicitados.
int main(int argc, char** argv) {

    // Validación mínima de argumentos.
    if (argc < 3) {
        cout << "Uso: ./Sepulveda_Gabriela_Laboratorio8 N s|n\n";
        return 1;
    }

    int N = atoi(argv[1]);
    char VER = argv[2][0];

    if (N <= 0) {
        cout << "El valor de N debe ser positivo.\n";
        return 1;
    }

    // Se genera el vector base con N elementos aleatorios entre 0 y 4999.
    srand(time(NULL));
    vector<int> base(N);
    for (int i = 0; i < N; i++) base[i] = rand() % 5000;

    // En el caso de VER = 's', imprimir el vector inicial.
    if (VER == 's') {
        imprimir_vector(base, "Vector inicial:");
    }

    // Se crean copias independientes del vector base para cada algoritmo.
    vector<int> v_burbuja = base;
    vector<int> v_insercion = base;
    vector<int> v_seleccion = base;
    vector<int> v_shell = base;
    vector<int> v_quick = base;

    // Se miden los tiempos de cada algoritmo, usando la función genérica medir_tiempo.
    long long t_burbuja   = medir_tiempo(bubble_sort, v_burbuja);
    long long t_insercion = medir_tiempo(insertion_sort, v_insercion);
    long long t_seleccion = medir_tiempo(selection_sort, v_seleccion);

    auto inicio_shell = high_resolution_clock::now();
    shellsort(v_shell);
    auto fin_shell = high_resolution_clock::now();
    long long t_shell = duration_cast<milliseconds>(fin_shell - inicio_shell).count();

    auto inicio_qs = high_resolution_clock::now();
    quicksort(v_quick, 0, N - 1);
    auto fin_qs = high_resolution_clock::now();
    long long t_quick = duration_cast<milliseconds>(fin_qs - inicio_qs).count();

    // Se imprime la tabla de tiempos, considerando método y tiempo en milisegundos.
    cout << "-----------------------------------------\n";
    cout << left << setw(12) << "Metodo" << "| Tiempo\n";
    cout << "-----------------------------------------\n";
    cout << left << setw(12) << "Burbuja"    << "| " << t_burbuja   << " milisegundos\n";
    cout << left << setw(12) << "Insercion"  << "| " << t_insercion << " milisegundos\n";
    cout << left << setw(12) << "Seleccion"  << "| " << t_seleccion << " milisegundos\n";
    cout << left << setw(12) << "Shellsort"  << "| " << t_shell     << " milisegundos\n";
    cout << left << setw(12) << "Quicksort"  << "| " << t_quick     << " milisegundos\n";
    cout << "-----------------------------------------\n";

    // En el caso de VER = 's', imprimir los vectores ordenados.
    if (VER == 's') {
        imprimir_vector(v_burbuja,   "Burbuja:");
        imprimir_vector(v_insercion, "Insercion:");
        imprimir_vector(v_seleccion, "Seleccion:");
        imprimir_vector(v_shell,     "Shellsort:");
        imprimir_vector(v_quick,     "Quicksort:");
    }

    return 0;
}
