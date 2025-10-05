// Programa: Actividad 2 - Estructura de Datos Dinámicas
// Nombre: Gabriela Sepúlveda Rojas
// Descripción: Este programa maneja una lista dinámica que representa la estructura primaria de una proteína. 
// Permite insertar, modificar y eliminar residuos de aminoácidos, así como exportar la lista a un formato compatible con Graphviz para su visualización.

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <vector>

// Se crea la estructura Nodo para la lista dinámica, donde cada uno representa un residuo de aminoácido
// Consideramos que resn es el nombre del residuo (ej: MET) y resid es su identificador (ej: 1)
struct Nodo {
    std::string resn;     
    std::string resid;
    Nodo* siguiente;
};

// Función para eliminar espacios en blanco al inicio y al final de una cadena.
static inline std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) start++;
    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end-1]))) end--;
    return s.substr(start, end - start);
}

// Insertar un nuevo residuo al final de la lista dinámica.
void insertarFinal(Nodo*& cabeza, const std::string& resn, const std::string& resid) {
    Nodo* nuevo = new Nodo{resn, resid, nullptr};  
    if (!cabeza) { // Si la lista está vacía, el nuevo nodo es el inicio.
        cabeza = nuevo;
        return;
    }
    Nodo* temp = cabeza;
    while (temp->siguiente) temp = temp->siguiente; 
    temp->siguiente = nuevo;  
}

// Se crea modificarResn, para modificar el resn de un residuo existente (emulando una mutación).
void modificarResn(Nodo* cabeza, int posicion, const std::string& nuevoResn) {
    Nodo* temp = cabeza;
    int i = 1;
    while (temp && i < posicion) {  // Avanza hacia la posición deseada por el usuario.
        temp = temp->siguiente;
        i++;
    }
    if (temp) temp->resn = nuevoResn;  // Se modifica si la posición es válida.
    else std::cout << "Posición no válida\n";
}

// Se crea eliminarNodo, que elimina un residuo en una posición específica indicada por el usuario.
void eliminarNodo(Nodo*& cabeza, int posicion) {
    if (!cabeza) return;  // Lista vacía, nada que eliminar.
    Nodo* temp = cabeza;

    if (posicion == 1) { // Eliminar el primer nodo.
        cabeza = cabeza->siguiente;
        delete temp;
        return;
    }

    int i = 1;
    Nodo* prev = nullptr;
    while (temp && i < posicion) {
        prev = temp;
        temp = temp->siguiente;
        i++;
    }

    if (!temp) {  // Posición no válida, se le pedirá al usuario que lo intente nuevamente.
        std::cout << "Posición no válida, intente nuevamente.\n";
        return;
    }

    prev->siguiente = temp->siguiente;  // Se desvincula el nodo a eliminar.
    delete temp;                        
}

// Con mostrarLista, mostraremos la lista de residuos en la consola.
void mostrarLista(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp) {
        // Mostramos resn y resid juntos (ej: MET1)
        std::cout << temp->resn << temp->resid << " -> ";
        temp = temp->siguiente;
    }
    std::cout << "NULL\n";  // NULL nos indicará que estamos en el final de la lista.
}

// Se crea la función exportarGraphviz para exportar la lista a Graphviz de forma automática.
void exportarGraphviz(Nodo* cabeza, const std::string& nombreArchivoDot, const std::string& nombreArchivoPng) {
    if (!cabeza) {
        std::cout << "- Lista vacía: nada que exportar.\n";
        return;
    }

    std::ofstream outfile(nombreArchivoDot);
    if (!outfile.is_open()) {
        std::cerr << "No se pudo crear el archivo: " << nombreArchivoDot << "\n";
        return;
    }

    // Encabezado de Graphviz, configuración de estilo y dirección del grafo.
    outfile << "digraph G {\n";
    outfile << "  rankdir=LR;\n";  // Grafo de izquierda a derecha
    outfile << "  graph [nodesep=0.6, ranksep=0.7];\n";
    outfile << "  node [shape=oval, style=filled, fillcolor=pink, color=black, fontcolor=black];\n\n";

    // Agregar nodos con etiquetas (resn + resid), asegurando que no haya espacios en blanco.
    Nodo* temp = cabeza;
    int index = 0;
    std::vector<std::string> ids;
    while (temp) {
        std::string id = "n" + std::to_string(index);
        std::string label = trim(temp->resn) + trim(temp->resid); // ej: "MET1"
        // Evitamos comillas dobles en label (se reemplazarán por comillas simples si existieran)
        for (char &c : label) if (c == '"') c = '\'';
        outfile << "  " << id << " [label=\"" << label << "\"];\n";
        ids.push_back(id);
        temp = temp->siguiente;
        index++;
    }

    // Se agregan aristas en orden lineal, conectando cada nodo con el siguiente.
    outfile << "\n  // Aristas (orden lineal)\n";
    for (size_t i = 0; i + 1 < ids.size(); ++i) {
        outfile << "  " << ids[i] << " -> " << ids[i+1] << ";\n";
    }

    outfile << "}\n"; // Cierre del grafo.
    outfile.close();

    // Se ejecuta el comando del sistema para generar imagen .png
    std::string comando = "dot -Tpng " + nombreArchivoDot + " -o " + nombreArchivoPng;
    if (system(comando.c_str()) == 0)
        std::cout << "- Imagen Graphviz generada: " << nombreArchivoPng << "\n";
    else
        std::cout << "- Error al generar imagen, intente nuevamente.\n";
}

// Se crea la función para cargar la lista desde un archivo PDB, preprocesado para contener solo resn y resid.
void cargarDesdeArchivo(Nodo*& cabeza, const std::string& nombreArchivo) {
    std::ifstream infile(nombreArchivo);
    if (!infile.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return;
    }

    std::string line;
    while (std::getline(infile, line)) {
        if (line.length() < 3) continue;          // Saltar líneas vacías o cortas
        std::string resn = trim(line.substr(0,3));      // Primeros 3 caracteres: resn
        std::string resid = trim(line.substr(3));       // Resto de la línea: resid
        if (resn.empty() && resid.empty()) continue;
        insertarFinal(cabeza, resn, resid);      // Insertar en la lista
    }

    infile.close();
}

// Creación del menú interactivo para el usuario.
void menu(Nodo*& cabeza) {
    int opcion;
    do {
        std::cout << "\n--- MENÚ INTERACTIVO DE PROTEÍNAS ---\n";
        std::cout << "1) Insertar un residuo\n";
        std::cout << "2) Modificar resn (simulación de mutación)\n";
        std::cout << "3) Eliminar residuo\n";
        std::cout << "4) Mostrar datos\n";
        std::cout << "5) Exportar Graphviz (.dot + .png)\n";
        std::cout << "6) Salir\n";
        std::cout << "Opción: "; std::cin >> opcion;

        if(opcion == 1){
            std::string resn, resid;
            std::cout << "Ingrese resn: "; std::cin >> resn;
            std::cout << "Ingrese resid: "; std::cin >> resid;
            insertarFinal(cabeza, trim(resn), trim(resid));
        } 
        else if(opcion == 2){
            int pos; std::string nuevoResn;
            std::cout << "Posición a modificar: "; std::cin >> pos;
            std::cout << "Nuevo resn: "; std::cin >> nuevoResn;
            modificarResn(cabeza, pos, trim(nuevoResn));
        } 
        else if(opcion == 3){
            int pos;
            std::cout << "Posición a eliminar: "; std::cin >> pos;
            eliminarNodo(cabeza, pos);
        } 
        else if(opcion == 4){
            mostrarLista(cabeza);
        } 
        else if(opcion == 5){
            exportarGraphviz(cabeza, "estructura.dot", "estructura.png");
        }

    } while(opcion != 6);
}

// Función principal.
int main() {
    Nodo* cabeza = nullptr;

    // Se carga automáticamente la proteína desde el archivo preprocesado, en este caso 3NIR.
    cargarDesdeArchivo(cabeza, "PDB/3nir_Resids_ChainA_Format_Uniq.pdb");
    std::cout << "- Lista de residuos cargada correctamente desde el archivo.\n";

    // Se ejecuta el menú interactivo
    menu(cabeza);

    // Se libera memoria de la lista antes de salir.
    Nodo* temp;
    while(cabeza) {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }

    return 0;
}